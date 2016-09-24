//
//  DrawingPen.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "DrawingPen.hpp"

namespace DrawingPen {
    //axis length
    const GLfloat __AXIS_LENGTH__  = 0.5f;
    
    //wireframe line width
    const GLfloat __LINE_WIDTH__ = 2.0f;
    
    //color
    const GLfloat __X_AXIS_COLOR_VECTOR__[3]    = {1.0f, 0.0f, 0.0f}; //red
    const GLfloat __Y_AXIS_COLOR_VECTOR__[3]    = {0.0f, 1.0f, 0.0f}; //green
    const GLfloat __Z_AXIS_COLOR_VECTOR__[3]    = {0.0f, 0.0f, 1.0f}; //blue
    const GLfloat __MODEL_DEFAULT_COLOR__[3]    = {0.0f, 0.0f, 1.0f}; //blue
    const GLfloat __BBOX_DEFAULT_COLOR__[3]     = {1.0f, 0.0f, 1.0f}; //purple
    const GLfloat __GRIDLINE_COLOR__[3]         = {0.0f, 0.0f, 0.0f};
    
    //axis rotation
    const GLfloat __X_AXIS_ROTATION_PARAMS__[4] = {90.0f, 0.0f, 1.0f, 0.0f}; //angle, x, y, z
    const GLfloat __Y_AXIS_ROTATION_PARAMS__[4] = {-90.0f, 1.0f, 0.0f, 0.0f}; //angle, x, y, z
    
    //axis arrow translation
    const GLfloat __AXIS_TRANSLATION_PARAMS__[3] = {0.0, 0.0, __AXIS_LENGTH__}; //x, y, z
    
    //axis body/arrow settings
    const GLfloat __AXIS_CYLINDER_PARAMS__[5] = {0.01f, 0.01f, __AXIS_LENGTH__, 40, 40};
    const GLfloat __AXIS_CONE_PARAMS__[4] = {0.03f, 0.1f, 40, 40};
    
    const GLfloat __FLOORGRID_X_RANGE__[2] = {-10.0f, 10.f};
    const GLfloat __FLOORGRID_Z_RANGE__[2] = {-10.0f, 10.0f};
    const GLfloat __GRIDLINE_DIST__ = 0.5f;
    const GLfloat __GRIDLINE_Y_COORD__ = 0.0f;
    
    //material matrices
    const GLfloat no_mat[]              = { 0.0, 0.0, 0.0, 1.0 };
    const GLfloat mat_ambient[]         = { 0.7, 0.7, 0.7, 1.0 };
    const GLfloat mat_ambient_color[]   = { 0.8, 0.8, 0.2, 1.0 };
    const GLfloat mat_diffuse[]         = { 0.1, 0.5, 0.8, 1.0 };
    const GLfloat mat_specular[]        = { 1.0, 1.0, 1.0, 1.0 };
    const GLfloat no_shininess[]        = { 0.0 };
    const GLfloat low_shininess[]       = { 5.0 };
    const GLfloat high_shininess[]      = { 100.0 };
    const GLfloat mat_emission[]        = {0.3, 0.2, 0.2, 0.0};
    
    const GLfloat red_material[]        = { 1.0, 0.0, 0.0, 1.0 };
    const GLfloat green_material[]      = { 0.0, 1.0, 0.0, 1.0 };
    const GLfloat blue_material[]       = { 0.0, 0.0, 1.0, 1.0 };
    const GLfloat purple_material[]     = { 1.0, 0.0, 1.0, 1.0 };
    
    const GLfloat point_size = 5.0f;
    
    
    void drawAxisCylinder(){
        glBegin(GL_POLYGON);
        GLUquadricObj *obj = gluNewQuadric();
        gluCylinder(obj, __AXIS_CYLINDER_PARAMS__[0], __AXIS_CYLINDER_PARAMS__[1], __AXIS_CYLINDER_PARAMS__[2], __AXIS_CYLINDER_PARAMS__[3], __AXIS_CYLINDER_PARAMS__[4]);
        glEnd();
        
    }
    
    void drawAxisCone(){
        glBegin(GL_POLYGON);
        glutSolidCone(__AXIS_CONE_PARAMS__[0], __AXIS_CONE_PARAMS__[1], __AXIS_CONE_PARAMS__[2], __AXIS_CONE_PARAMS__[3]);
        glEnd();
        
    }
    
    void drawFloorGrid(){
        
        glPushMatrix();
        
        glColor3fv(__GRIDLINE_COLOR__);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        
        //draw grid lines parallel to x axis
        for (float i = __FLOORGRID_Z_RANGE__[0]; i <= __FLOORGRID_Z_RANGE__[1] ; i += __GRIDLINE_DIST__) {
            glBegin(GL_LINES);
            glVertex3f( __FLOORGRID_X_RANGE__[0], __GRIDLINE_Y_COORD__, i );
            glVertex3f( __FLOORGRID_X_RANGE__[1], __GRIDLINE_Y_COORD__, i );
            glEnd();
        }
        
        //draw grid lines parallel to z axis
        for (float i = __FLOORGRID_X_RANGE__[0]; i <= __FLOORGRID_X_RANGE__[1] ; i += __GRIDLINE_DIST__) {
            glBegin(GL_LINES);
            glVertex3f( i, __GRIDLINE_Y_COORD__, __FLOORGRID_Z_RANGE__[0] );
            glVertex3f( i, __GRIDLINE_Y_COORD__, __FLOORGRID_Z_RANGE__[1] );
            glEnd();
        }
        
        glPopMatrix();
        
    }
    
    void drawXaxis(){
        
        glColor3fv(__X_AXIS_COLOR_VECTOR__);
        glMaterialfv(GL_FRONT, GL_AMBIENT, red_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, red_material);
        glMaterialfv(GL_FRONT, GL_SPECULAR, red_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, red_material);
        
        glPushMatrix();
        glRotatef(__X_AXIS_ROTATION_PARAMS__[0], __X_AXIS_ROTATION_PARAMS__[1], __X_AXIS_ROTATION_PARAMS__[2], __X_AXIS_ROTATION_PARAMS__[3]);
        drawAxisCylinder();
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(__X_AXIS_ROTATION_PARAMS__[0], __X_AXIS_ROTATION_PARAMS__[1], __X_AXIS_ROTATION_PARAMS__[2], __X_AXIS_ROTATION_PARAMS__[3]);
        glTranslatef(__AXIS_TRANSLATION_PARAMS__[0], __AXIS_TRANSLATION_PARAMS__[1], __AXIS_TRANSLATION_PARAMS__[2]);
        drawAxisCone();
        glPopMatrix();
    }
    
    void drawYaxis(){
        glColor3fv(__Y_AXIS_COLOR_VECTOR__);
        glMaterialfv(GL_FRONT, GL_AMBIENT, green_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, green_material);
        glMaterialfv(GL_FRONT, GL_SPECULAR, green_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, green_material);
        
        glPushMatrix();
        glRotatef(__Y_AXIS_ROTATION_PARAMS__[0], __Y_AXIS_ROTATION_PARAMS__[1], __Y_AXIS_ROTATION_PARAMS__[2], __Y_AXIS_ROTATION_PARAMS__[3]);
        drawAxisCylinder();
        glPopMatrix();
        
        glPushMatrix();
        glRotatef(__Y_AXIS_ROTATION_PARAMS__[0], __Y_AXIS_ROTATION_PARAMS__[1], __Y_AXIS_ROTATION_PARAMS__[2], __Y_AXIS_ROTATION_PARAMS__[3]);
        glTranslatef(__AXIS_TRANSLATION_PARAMS__[0], __AXIS_TRANSLATION_PARAMS__[1], __AXIS_TRANSLATION_PARAMS__[2]);
        drawAxisCone();
        glPopMatrix();
    }
    
    void drawZaxis(){
        
        glPushMatrix();
        glColor3fv(__Z_AXIS_COLOR_VECTOR__);
        glMaterialfv(GL_FRONT, GL_AMBIENT, blue_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_material);
        glMaterialfv(GL_FRONT, GL_SPECULAR, blue_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, blue_material);
        
        drawAxisCylinder();
        
        glTranslatef(__AXIS_TRANSLATION_PARAMS__[0], __AXIS_TRANSLATION_PARAMS__[1], __AXIS_TRANSLATION_PARAMS__[2]);
        drawAxisCone();
        glPopMatrix();
    }
    
    void drawModel(){
        
        //draw object from the mfile
        std::map<int, HEDataStruct::HE_face *> faces = MeshDataStruct::getFaceMap();
        std::map<int, HEDataStruct::HE_face *>::iterator it;
        
        float ratioX = MeshDataStruct::getEstVolumeRatioX();
        float ratioY = MeshDataStruct::getEstVolumeRatioY();
        float ratioZ = MeshDataStruct::getEstVolumeRatioZ();
        
        glPushMatrix();
        
        glTranslatef(Controller::getMoveObjectXFactor(), Controller::getMoveObjectYFactor(), Controller::getMoveObjectZFactor());
        glRotatef(Controller::getMoveXAngle(), 0, 1, 0);
        glRotatef(Controller::getMoveYAngle(), 1, 0, 0);
        glScalef(ratioX * Controller::getScaleFactor(), ratioY * Controller::getScaleFactor(), ratioZ * Controller::getScaleFactor());
        
        //make the center of the model coincides with origin
        glTranslatef(MeshDataStruct::centralizeX(), MeshDataStruct::centralizeY(), MeshDataStruct::centralizeZ());
        
        glColor3f(__MODEL_DEFAULT_COLOR__[0], __MODEL_DEFAULT_COLOR__[1], __MODEL_DEFAULT_COLOR__[2]);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);
        
        for (it=faces.begin(); it!=faces.end(); ++it){
            HEDataStruct::HE_face * _f = it->second;
            
            HEDataStruct::HE_edge * _fe1 = _f->edge;
            HEDataStruct::HE_edge * _fe2 = _fe1->next;
            HEDataStruct::HE_edge * _fe3 = _fe2->next;
            
            if (Controller::showWireframe()) {
                
                glBegin(GL_LINE_LOOP);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe1->vert->vertex_index));
                glVertex3f(_fe1->vert->x, _fe1->vert->y, _fe1->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe2->vert->vertex_index));
                glVertex3f(_fe2->vert->x, _fe2->vert->y, _fe2->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe3->vert->vertex_index));
                glVertex3f(_fe3->vert->x, _fe3->vert->y, _fe3->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe1->vert->vertex_index));
                glVertex3f(_fe1->vert->x, _fe1->vert->y, _fe1->vert->z);
                glEnd();
                
            }else if(Controller::showPoints()){
                
                glPointSize(point_size);
                
                glBegin(GL_POINTS);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe1->vert->vertex_index));
                glVertex3f(_fe1->vert->x, _fe1->vert->y, _fe1->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe2->vert->vertex_index));
                glVertex3f(_fe2->vert->x, _fe2->vert->y, _fe2->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe3->vert->vertex_index));
                glVertex3f(_fe3->vert->x, _fe3->vert->y, _fe3->vert->z);
                glEnd();
            }else if (Controller::showFlatshading() || Controller::showSmoothshading()){
                
                glBegin(GL_TRIANGLES);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe1->vert->vertex_index));
                glVertex3f(_fe1->vert->x, _fe1->vert->y, _fe1->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe2->vert->vertex_index));
                glVertex3f(_fe2->vert->x, _fe2->vert->y, _fe2->vert->z);
                glNormal3fv(MeshDataStruct::getVertexNormal(_fe3->vert->vertex_index));
                glVertex3f(_fe3->vert->x, _fe3->vert->y, _fe3->vert->z);
                glEnd();
                
            }
            
        }
        
        glPopMatrix();
        
    }
    
    void drawBoundingBox(){
        
        if (Controller::showBoundingBox()) {
            float* bounding_box = MeshDataStruct::getBoundingBoxCoords();
            
            float ratioX = MeshDataStruct::getEstVolumeRatioX();
            float ratioY = MeshDataStruct::getEstVolumeRatioY();
            float ratioZ = MeshDataStruct::getEstVolumeRatioZ();
            
            glPushMatrix();
            
            glTranslatef(Controller::getMoveObjectXFactor(), Controller::getMoveObjectYFactor(), Controller::getMoveObjectZFactor());
            glRotatef(Controller::getMoveXAngle(), 0, 1, 0);
            glRotatef(Controller::getMoveYAngle(), 1, 0, 0);
            glScalef(ratioX * Controller::getScaleFactor(), ratioY * Controller::getScaleFactor(), ratioZ * Controller::getScaleFactor());
            
            //make the center of the model coincides with origin
            glTranslatef(-1 * MeshDataStruct::centralizeX(), -1 * MeshDataStruct::centralizeY(), -1 * MeshDataStruct::centralizeZ());
            
            glColor3fv(__BBOX_DEFAULT_COLOR__);
            glMaterialfv(GL_FRONT, GL_AMBIENT, purple_material);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, purple_material);
            glMaterialfv(GL_FRONT, GL_SPECULAR, purple_material);
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, purple_material);
            
            glBegin(GL_LINE_LOOP); //top face along Y axis
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[4]);
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[4]);
            glEnd();
            
            glBegin(GL_LINE_LOOP); //bottom face along Y axis
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[4]);
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[4]);
            glEnd();
            
            glBegin(GL_LINE_LOOP); //top face along X axis
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[4]);
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[4]);
            glEnd();
            
            glBegin(GL_LINE_LOOP); //bottom face along X axis
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[4]);
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[5]);
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[4]);
            glEnd();
            
            glBegin(GL_LINE_LOOP); //top face along Z axis
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[5]);
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[5]);
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[5]);
            glEnd();
            
            glBegin(GL_LINE_LOOP); //bottom face along Z axis
            glVertex3f(bounding_box[0], bounding_box[2], bounding_box[4]);
            glVertex3f(bounding_box[0], bounding_box[3], bounding_box[4]);
            glVertex3f(bounding_box[1], bounding_box[3], bounding_box[4]);
            glVertex3f(bounding_box[1], bounding_box[2], bounding_box[4]);
            glEnd();
            
            glPopMatrix();

        }
        
        
    }
}
