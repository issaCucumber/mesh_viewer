//
//  Controller.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "Controller.hpp"

#define TRANSFORM_NONE          0
#define TRANSFORM_TRANSLATE     1
#define TRANSFORM_ROTATE        2
#define TRANSFORM_SCALE         3

#define OBJ_WIREFRAME	0
#define OBJ_SOLID		1
#define OBJ_SMOOTH		2
#define OBJ_POINTS      3

#define MODEL_BUNNY     0
#define MODEL_CAP       1
#define MODEL_EIGHT     2
#define MODEL_GARGOYLE  3
#define MODEL_KNOT      4

#define BOUNDING_BOX_ON     1
#define BOUNDING_BOX_OFF    0

#define RANDERING_USER_ID   1
#define MODEL_USER_ID       2
#define BBOX_USER_ID        3
#define RESET_USER_ID       4
#define PROJ_USER_ID        5

#define PROJ_PERSPECTIVE    0
#define PROJ_ORTHO          1

namespace Controller {
    
    const char* title = "DM6101 Assignment: Mesh Viewer Controller";
    
    const char TRANSFORM_TRANSLATE_KEY  = 't';
    const char TRANSFORM_ROTATE_KEY     = 'r';
    const char TRANSFORM_SCALE_KEY      = 's';
    const char TRANSFORM_RESET_KEY      = 'w';
    
    const std::string MFILE_FOLDER         = "mfiles/"; //w.r.t excutable file
    const std::string BUNNY_FILENAME       = "bunny.m";
    const std::string CAP_FILENAME         = "cap.m";
    const std::string EIGHT_FILENAME       = "eight.m";
    const std::string GARGOYLE_FILENAME    = "gargoyle.m";
    const std::string KNOT_FILENAME        = "knot.m";
    
    static int press_x_rotation, press_y_rotation, press_y_scale;
    static float x_angle = 0.0;
    static float y_angle = 0.0;
    static float scale_size = 1.0;
    static float x_move = 0.0;
    static float y_move = 0.0;
    
    //variables for converting mouse/ screen coordinates to model coordinates (using gluUnProject)
    static GLdouble objectCoordX, objectCoordY, objectCoordZ; //orginal model coordinates when mouse pressed
    static GLdouble cachedObjectCoordX = 0.0 , cachedObjectCoordY = 0.0, cachedObjectCoordZ = 0.0; //for translation, to store the final position of the object when key up
    static GLfloat object_x_move = 0.0;
    static GLfloat object_y_move = 0.0;
    static GLfloat object_z_move = 0.0;
    
    //control mode
    static int obj_mode         = OBJ_WIREFRAME;
    static int xform_mode       = TRANSFORM_NONE;
    static int display_model    = MODEL_BUNNY;
    static int bbox_mode        = BOUNDING_BOX_ON;
    static int proj_mode        = PROJ_PERSPECTIVE;
    
    //GLUI objects
    GLUI_Checkbox   *bbox_checkbox;
    GLUI_Checkbox   *proj_checkbox;
    GLUI_RadioGroup *radio_randering_types;
    GLUI_RadioGroup *radio_models;
    
    void resetController(){
        object_x_move = 0.0;
        object_y_move = 0.0;
        object_z_move = 0.0;
        
        cachedObjectCoordX = 0.0;
        cachedObjectCoordY = 0.0;
        cachedObjectCoordZ = 0.0;
        
        obj_mode = OBJ_WIREFRAME;
        xform_mode = TRANSFORM_NONE;
        
        x_angle = 0.0;
        y_angle = 0.0;
        scale_size = 1.0;
        x_move = 0.0;
        y_move = 0.0;
    }
    
    int selectModel(){
        resetController();
        
        std::string mesh_filename = "";
        switch (display_model) {
            case MODEL_BUNNY:
                mesh_filename = BUNNY_FILENAME;
                break;
            case MODEL_CAP:
                mesh_filename = CAP_FILENAME;
                break;
            case MODEL_EIGHT:
                mesh_filename = EIGHT_FILENAME;
                break;
            case MODEL_GARGOYLE:
                mesh_filename = GARGOYLE_FILENAME;
                break;
            case MODEL_KNOT:
                mesh_filename = KNOT_FILENAME;
                break;
            default:
                break;
        }
        
        return mFileParser::parseFileandGenerateHEMaps(MFILE_FOLDER + mesh_filename);
    }
    
    void control_cb( int control )
    {
        if (control == MODEL_USER_ID) { //change model
            selectModel();
        }else if(control == RESET_USER_ID){
            resetController();
            glutPostRedisplay();
        }
        
    }
    
    void createGLUIMenu(int main_window){
        
        GLUI *glui = GLUI_Master.create_glui( title, 0, 400, 50 ); /* name, flags,
                                                                     x, and y */
        new GLUI_StaticText( glui, "Controller Menu" );
        new GLUI_Separator( glui );
       // checkbox = new GLUI_Checkbox( glui, "Wireframe", &wireframe, 1, control_cb );
        
        //Radio buttons group for randering button group
        GLUI_Panel *randering_types_panel = new GLUI_Panel( glui, "Rendering Mode" );
        radio_randering_types = new GLUI_RadioGroup( randering_types_panel, &obj_mode, RANDERING_USER_ID, control_cb );
        new GLUI_RadioButton( radio_randering_types, "Wireframe" );
        new GLUI_RadioButton( radio_randering_types, "Solid" );
        new GLUI_RadioButton( radio_randering_types, "Solid Smooth" );
        new GLUI_RadioButton( radio_randering_types, "Point" );
        
        //Radio button group for models
        GLUI_Panel *models_panel = new GLUI_Panel( glui, "Select Model" );
        radio_models = new GLUI_RadioGroup( models_panel, &display_model, MODEL_USER_ID, control_cb );
        new GLUI_RadioButton( radio_models, "Bunny" );
        new GLUI_RadioButton( radio_models, "Cap" );
        new GLUI_RadioButton( radio_models, "Eight" );
        new GLUI_RadioButton( radio_models, "Gargoyle" );
        new GLUI_RadioButton( radio_models, "Knot" );
        
        //checkbox for bounding box
        bbox_checkbox = new GLUI_Checkbox( glui, "Bounding Box", &bbox_mode, BBOX_USER_ID, control_cb );
        
        //checkbox for showing ortho or perspective
        proj_checkbox = new GLUI_Checkbox( glui, "Show Orthographic", &proj_mode, PROJ_USER_ID, control_cb );
        
        new GLUI_Button( glui, "Reset", RESET_USER_ID, control_cb );
        new GLUI_Button( glui, "Quit", 0, (GLUI_Update_CB)exit );
        
        glui->set_main_gfx_window( main_window );
        
        /* We register the idle callback with GLUI, *not* with GLUT */
        //GLUI_Master.set_glutIdleFunc( myGlutIdle );
        GLUI_Master.set_glutIdleFunc( NULL );
        
    }
    
    float getScaleFactor(){
        return scale_size;
    }
    
    float getMoveXFactor(){
        return x_move;
    }
    
    float getMoveYFactor(){
        return y_move;
    }
    
    float getMoveObjectXFactor(){
        return object_x_move;
    }
    
    float getMoveObjectYFactor(){
        return object_y_move;
    }
    
    float getMoveObjectZFactor(){
        return object_z_move;
    }
    
    float getTransformMode(){
        return xform_mode;
    }
    
    bool showPoints(){
        return obj_mode == OBJ_POINTS;
    }
    
    bool showWireframe(){
        return obj_mode == OBJ_WIREFRAME;
    }
    
    bool showFlatshading(){
        return obj_mode == OBJ_SOLID;
    }
    
    bool showSmoothshading(){
        return obj_mode == OBJ_SMOOTH;
    }
    
    bool showBoundingBox(){
        return bbox_mode == BOUNDING_BOX_ON;
    }
    
    bool showPerspective(){
        return proj_mode == PROJ_PERSPECTIVE;
    }
    
    float getMoveXAngle(){
        return x_angle;
    }
    
    float getMoveYAngle(){
        return y_angle;
    }
    
    void motionHandler(int x, int y){
        if (xform_mode == TRANSFORM_ROTATE)
        {
            x_angle += (x - press_x_rotation)/5.0;
            
            if (x_angle > 180)
                x_angle -= 360;
            else if (x_angle <-180)
                x_angle += 360;
            
            press_x_rotation = x;
            
            y_angle += (y - press_y_rotation)/5.0;
            
            if (y_angle > 180)
                y_angle -= 360;
            else if (y_angle <-180)
                y_angle += 360;
            
            press_y_rotation = y;
            
        }
        else if (xform_mode == TRANSFORM_SCALE)
        {
            float old_size = scale_size;
            
            scale_size *= (1 + (press_y_scale - y)/80.0);
            
            if (scale_size <0)
                scale_size = old_size;
            
            press_y_scale = y;
            
        }else if (xform_mode == TRANSFORM_TRANSLATE)
        {
//            GLdouble * model = Camera::getModelMatrix();
//            GLdouble * proj = Screen::getProjectionMatrix();
//            GLint * view = Screen::getViewportMatrix();
            
            GLint view[4];
            GLdouble model[16];
            GLdouble proj[16];
            
            glGetDoublev( GL_MODELVIEW_MATRIX, model );
            glGetDoublev( GL_PROJECTION_MATRIX, proj );
            glGetIntegerv( GL_VIEWPORT, view );
            
            GLdouble newObjectCoordX, newObjectCoordY, newObjectCoordZ; //moved object coordinates
            GLfloat winX, winY, winZ; //window coordinates
            
            winX = (float)x;
            winY = (float)*(view+3) - (float)y;
            glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
            
            if(gluUnProject( winX, winY, winZ, model, proj, view, &newObjectCoordX, &newObjectCoordY, &newObjectCoordZ)){
                object_x_move = newObjectCoordX - objectCoordX + cachedObjectCoordX;
                object_y_move = newObjectCoordY - objectCoordY + cachedObjectCoordY;
                object_z_move = newObjectCoordZ - objectCoordZ + cachedObjectCoordZ;
                
            }else{
                std::cout << "(" << object_x_move << "," << object_y_move << "," << object_z_move << ")\n";
            }
            
        }
        
        glutPostRedisplay();
        
    }
    
    void mouseHandler(int button, int state, int x, int y)
    {
        if (state == GLUT_DOWN){
            
            if (xform_mode == TRANSFORM_TRANSLATE) {
                GLint view[4];
                GLdouble model[16];
                GLdouble proj[16];
                
                glGetDoublev( GL_MODELVIEW_MATRIX, model );
                glGetDoublev( GL_PROJECTION_MATRIX, proj );
                glGetIntegerv( GL_VIEWPORT, view );
                
                GLfloat winX, winY, winZ; //window coordinates
                
                //grab window screen coordinates, get the current mouse position
                winX = (float)x;
                winY = (float)*(view + 3) - (float)y; //the origin of windows coordinates is at top left, OpenGL starts at low left
                
                glReadPixels( winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
                if(!gluUnProject( winX, winY, winZ, model, proj, view, &objectCoordX, &objectCoordY, &objectCoordZ)){
                    std::cout << "Error converting the mouse coordinates to object coordinates : (" << x << "," << y << ")\n";
                }
                
            }else if (xform_mode == TRANSFORM_ROTATE){
                
                press_x_rotation = x;
                press_y_rotation = y;
                
            }else if (xform_mode == TRANSFORM_SCALE){
                
                press_y_scale = y;
            }
            
            
        }else if (state == GLUT_UP){
            
            if(xform_mode == TRANSFORM_TRANSLATE){
                cachedObjectCoordX = object_x_move;
                cachedObjectCoordY = object_y_move;
                cachedObjectCoordZ = object_z_move;
            }
            
        }
        
    }
    
    void keyPressHandler(unsigned char key, int x, int y){
        switch(key)
        {
            case TRANSFORM_SCALE_KEY:
                xform_mode = TRANSFORM_SCALE;
                break;
            case TRANSFORM_TRANSLATE_KEY:
                xform_mode = TRANSFORM_TRANSLATE;
                break;
            case TRANSFORM_ROTATE_KEY:
                xform_mode = TRANSFORM_ROTATE;
                break;
        }

    }
    
}
