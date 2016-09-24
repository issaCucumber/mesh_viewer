//
//  MeshDataStruct.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef MeshDataStruct_hpp
#define MeshDataStruct_hpp

//C++ library
#include <iostream>
#include <stdio.h>
#include <map>
#include <list>
#include <utility>
#include <string>
#include <math.h>

//C library
#include <cstdio>
#include <cstdlib>
#include <cerrno>

//App Files
#include "HEDataStruct.h"

using namespace HEDataStruct;

//Assignment Objective 2: Computing Vertex Normals using Half-edge Data Structure
//1. Implementation the half-edge data structure to store the triangle meshes, using C++ map to store the half edges
//2. Calculate the vertex normals
//3. Calculate the bounding box volume of the model (to fit the model in a unit cube on the stage later)
namespace MeshDataStruct {
    
    typedef struct BoundingBox {
        float originalX, originalY, originalZ;
        float lengthX, lengthY, lengthZ;
        float maxLength;
        std::string maxSide_str;
        
        BoundingBox(){};
    } BoundingBox;
    
    //GETTER
    int getVerticesCount();
    int getFacesCount();
    int getEdgesCount();
    float getEstVolumeRatioX(); //get estimated volume ratio to form the unit cube that contains the model
    float getEstVolumeRatioY();
    float getEstVolumeRatioZ();
    float* getBoundingBoxCoords();
    float* getVertexNormal(int vIndex);
    
    HEDataStruct::HE_vert * getVertex(int vertexIndex);
    HEDataStruct::HE_face * getFace(int faceIndex);
    HEDataStruct::HE_edge * getHalfEdge(int begin_vertex, int end_vertex);
    std::map<int, HEDataStruct::HE_vert *> getVertexMap();
    std::map<int, HEDataStruct::HE_face *> getFaceMap();
    
    float centralizeX();
    float centralizeY();
    float centralizeZ();
    
    //RESET
    void reset();
    
    //INSERT/ UPDATE
    void addFace(int fIndex, int vertex1, int vertex2, int vertex3);
    void addVertex(int vIndex, float x, float y, float z);
    void addHalfEdges(int fIndex, int vertex1, int vertex2, int vertex3);
    void updateVertex(int vIndex, int startVertex, int endVertex);
    
    //CACHE CONTROL
    void saveDataToCache(std::string meshfilename);
    bool loadDataFromCache(std::string meshfilename);

}


#endif /* MeshDataStruct_hpp */
