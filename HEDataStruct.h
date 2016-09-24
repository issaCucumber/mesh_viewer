//
//  HEDataStruct.h
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef HEDataStruct_h
#define HEDataStruct_h

#include <utility>
#include <string>

namespace HEDataStruct {
    //definition for half edge construct
    typedef struct HE_edge {
        struct HE_vert* vert;   // vertex at the end of the half-edge
        struct HE_edge* pair;   // oppositely oriented half-edge
        struct HE_face* face;   // the incident face
        struct HE_edge* prev;   // previous half-edge around the face
        struct HE_edge* next;   // next half-edge around the face
        
        HE_edge(){};
    } HE_edge;
    
    typedef struct HE_vert {
        float x, y, z;              // the vertex coordinates
        struct HE_edge* edge;       // one of the half-edges emanating from the vertex
        float nx, ny, nz;           // normal vector (per-vertex normal by averaging the normals of faces that are adjacent to that vertex)
        int vertex_index;           // for debugging
        
        HE_vert(){};
    } HE_vert;
    
    typedef struct HE_face {
        struct HE_edge* edge;       // one of the half-edges bordering the face
        float nx, ny, nz;           // normal vector (per-face normal by using the cross product)
        int face_index;
        
        HE_face(){};
    } HE_face;
}

#endif /* HEDataStruct_h */
