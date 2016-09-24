//
//  mFileParser.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "mFileParser.hpp"

namespace mFileParser {
    
    int parseFileandGenerateHEMaps(std::string input_file_path){
        
        FILE * fp;
        int     vertexIndex, faceIndex, facevertex1, facevertex2, facevertex3;
        float   vertexX, vertexY, vertexZ;
        
        fp = fopen(input_file_path.c_str(), "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);
        
        char * line = NULL;
        char dataType[10];
        size_t len = 0;
        ssize_t read;
        
        MeshDataStruct::reset(); //refresh mesh data storage
        
        if(MeshDataStruct::loadDataFromCache(input_file_path)){ //if the file has loaded before, load the data from cache
            std::cout << "Load from cache...\n";
            return EXIT_SUCCESS;
        }
        
        std::cout << "Start Parsing M File ... " << input_file_path.c_str() << "\n";
        
        while ((read = getline(&line, &len, fp)) != -1) {
            
            if ( sscanf( line, "%s", dataType ) != EOF ){
                if(strcmp(dataType, "Vertex") == 0){
                    
                    //This line is a vertex. store it to the vertices map
                    if(sscanf( line, "Vertex %d  %f %f %f", &vertexIndex, &vertexX, &vertexY, &vertexZ) != EOF){
                        
                        //add vertex to vertex map
                        MeshDataStruct::addVertex(vertexIndex, vertexX, vertexY, vertexZ);
                    }
                    
                    
                } else if (strcmp(dataType, "Face") == 0){
                    
                    if(sscanf( line, "Face %d  %d %d %d", &faceIndex, &facevertex1, &facevertex2, &facevertex3) != EOF){
                        
                        //add the 3 edges to half edges map
                        MeshDataStruct::addHalfEdges(faceIndex, facevertex1, facevertex2, facevertex3);
                        
                        //add face to face map
                        MeshDataStruct::addFace(faceIndex, facevertex1, facevertex2, facevertex3);
                        
                        //update the vertex edge
                        MeshDataStruct::updateVertex(facevertex1, facevertex1, facevertex2);
                        MeshDataStruct::updateVertex(facevertex2, facevertex2, facevertex3);
                        MeshDataStruct::updateVertex(facevertex3, facevertex3, facevertex1);
                        
                    }
                    
                }
            }
        }
        
        MeshDataStruct::saveDataToCache(input_file_path); //save the parsed data to cache
        
        
        //for debugging
        //        int test_vertexIdex = 20009;
        //        float * testvertexNormal = MeshDataStruct::calculateVertexNormal(test_vertexIdex);
        //        std::cout << "Calculating vertex normal :: " << test_vertexIdex << " = (" << *testvertexNormal << "," << *(testvertexNormal+1) << "," << *(testvertexNormal+2) << ")\n";
        
        
        /*printf("Total half edges : %d\n", MeshDataStruct::getEdgesCount());
         printf("Total faces : %d\n", MeshDataStruct::getFacesCount());
         printf("Total vertices : %d\n", MeshDataStruct::getVerticesCount());
         
         //debug
         HEDataStruct::HE_vert* test_vertex = MeshDataStruct::getVertex(test_vertexIdex);
         printf("double check vertex %d : (%f, %f, %f) \n", test_vertexIdex, test_vertex->x, test_vertex->y, test_vertex->z );
         
         int test_faceIdex = 37886;
         HEDataStruct::HE_face* test_face = MeshDataStruct::getFace(test_faceIdex);
         HEDataStruct::HE_edge* test_face_edge = test_face->edge;
         printf("double check vertex for face %d : (%f, %f, %f) \n", test_faceIdex, test_face_edge->vert->x, test_face_edge->vert->y, test_face_edge->vert->z );*/
        
        
        //printAllVertices();
        return EXIT_SUCCESS;
        
    }
}

