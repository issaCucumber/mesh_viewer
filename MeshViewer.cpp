//
//  MeshViewer.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "MeshViewer.hpp"

namespace MeshViewer {
    
    //display function
    //drawing the object
    void display(void){
        
        if(Controller::showFlatshading()){
            glShadeModel (GL_FLAT);
        }else if (Controller::showSmoothshading()){
            glShadeModel (GL_SMOOTH);
        }
        
        /****************************************/
        /*          Enable z-buferring          */
        /****************************************/
        glEnable(GL_DEPTH);
        glEnable(GL_NORMALIZE);
        
        /****************************************/
        /*      Clear buffer before drawing     */
        /****************************************/
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /****************************************/
        /*      Set up viewport, projection     */
        /****************************************/
        Screen::setViewPortProjection(Controller::showPerspective());
        
        /****************************************/
        /*             Set up camera            */
        /****************************************/
        Camera::setCameraLocation();
        
        /****************************************/
        /*             Draw Graphics            */
        /****************************************/
        //draw axes
        DrawingPen::drawZaxis();
        DrawingPen::drawXaxis();
        DrawingPen::drawYaxis();
        //draw grid lines
        DrawingPen::drawFloorGrid();
        //draw selected model
        DrawingPen::drawModel();
        //drawing bounding box
        DrawingPen::drawBoundingBox();
        
        /****************************************/
        /*       Implicitly flush buffers       */
        /****************************************/
        glutSwapBuffers();
        
    }
    
    int setupStage(int argc, char **argv){
        
        /****************************************/
        /*            Initialize GLUT           */
        /****************************************/
        glutInit(&argc, argv);
        // use double buffer to get better results on animation
        // use depth buffer for hidden surface removal
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
        
        /****************************************/
        /*              Create window           */
        /****************************************/
        Screen::setupWindow();
        
        /****************************************/
        /*         Set up OpenGL lights         */
        /****************************************/
        Lighting::lettherebelight();
        
        /****************************************/
        /*           Display function           */
        /****************************************/
        glutDisplayFunc(display);
        
        /****************************************/
        /*        Mouse click functions         */
        /****************************************/
        glutMouseFunc(Controller::mouseHandler);
        
        /****************************************/
        /*       Mouse motion functions         */
        /****************************************/
        glutMotionFunc(Controller::motionHandler);
        
        /****************************************/
        /*         Key press functions          */
        /****************************************/
        glutKeyboardFunc(Controller::keyPressHandler);
        
        /****************************************/
        /*         Window reshape callback      */
        /****************************************/
        glutReshapeFunc(Screen::onWindowResize);
        
        /****************************************/
        /*            Create GLUI menu          */
        /****************************************/
        Controller::createGLUIMenu(Screen::getWindowObj());
        
        // enter the main loop
        glutMainLoop();
        
        return EXIT_SUCCESS;
    }
    
    int startApplication(int argc, char **argv){
        if(Controller::selectModel() == EXIT_SUCCESS){ //load default model
           return setupStage(argc, argv);
        }
        
        return EXIT_FAILURE;
        
    }
    
}
