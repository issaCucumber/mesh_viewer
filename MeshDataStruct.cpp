//
//  MeshDataStruct.cpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#include "MeshDataStruct.hpp"

#define oops(s) { perror((s)); exit(EXIT_FAILURE); }
#define MALLOC(s,t) if(((s) = malloc(t)) == NULL) { oops("error: malloc() "); }
#define CALLOC(arr, unit, n, err) if((arr = calloc(unit, n)) == NULL){ oops( err );}

#define HE_COORDS_DELIMITER "|"
#define HE_COORDS_SEPARATOR ","
#define __NUM_OF_EDGE_PER_FACE__ 3
#define __DIMENSION__   3
#define __X_VALUE__     0
#define __Y_VALUE__     1
#define __Z_VALUE__     2
#define __X_SIDE__      "X"
#define __Y_SIDE__      "Y"
#define __Z_SIDE__      "Z"
#define __DEFAULT_NORMAL_VAL__ -9999

namespace MeshDataStruct {
    
    bool fullDiscVertex; //flag indicate if the current vertex is fully surrounded by meshes
    
    int verticesCount;
    int facesCount;
    int edgesCount;
    
    //the vertex of the bounding box volume of the model
    //{lowX, highX, lowY, highY, lowZ, highZ}
    float length_x, length_y, length_z, max_length;
    float origintranslate_x = 0.0, origintranslate_y = 0.0, origintranslate_z = 0.0;
    std::string maxSide = __X_SIDE__;
    
    //keep the parsed mesh data in these map, linked with the mesh file name
    std::map<std::string, std::map<int, HEDataStruct::HE_vert *>> vertices_map_cache;
    std::map<std::string, std::map<int, HEDataStruct::HE_face *>> faces_map_cache;
    std::map<std::string, std::map<std::pair <int,int>, HEDataStruct::HE_edge *>> edges_map_cache;
    std::map<std::string, BoundingBox*> bounding_box_cache;
    
    //storage for vertices, faces and half edges
    std::map<int, HEDataStruct::HE_vert *> vertices_map; //vertices map
    std::map<int, HEDataStruct::HE_face *> faces_map; //faces map
    std::map<std::pair <int,int>, HEDataStruct::HE_edge *> halfedges_map; //use map to store the half edges, pair is defined as the begin_vertex, end_vertex
    
    bool isEdgeDefined(HEDataStruct::HE_edge * i){
        
        if(i == nullptr){
            fullDiscVertex = false; //mark that this vertex half disc vertex
        }
        
        return i != nullptr;
    }
    
    bool isSameEdge(HEDataStruct::HE_edge * a, HEDataStruct::HE_edge * b){
        
        return (a->vert->x == b->vert->x && a->vert->y == b->vert->y && a->vert->z == b->vert->z);
        
    }
    
    //calculate normal
    void normalize(float v[3]) {
        float d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
        if (d == 0.0) {
            std::cout << "zero length vector" ;
            return;
        }
        v[0] /= d; v[1] /= d; v[2] /= d;
    }
    
    void normcrossprod(float v1[3], float v2[3], float norm[3])
    {
        norm[0] = v1[1]*v2[2] - v1[2]*v2[1];
        norm[1] = v1[2]*v2[0] - v1[0]*v2[2];
        norm[2] = v1[0]*v2[1] - v1[1]*v2[0];
        normalize(norm);
    }
    
    float* calculateFaceNormal(HE_vert * p1, HE_vert * p2, HE_vert * p3){
        
        //define 2 vectors, v1{p1->p2} and v2{p1->p3}
        float v1i = p2->x - p1->x;
        float v1j = p2->y - p1->y;
        float v1k = p2->z - p1->z;
        
        float v2i = p3->x - p1->x;
        float v2j = p3->y - p1->y;
        float v2k = p3->z - p1->z;
        
        //calculate normal for all 3 vertices
        static float normal[3];
        float v1[3] = {v1i, v1j, v1k}; //vertex2 - vertex1
        float v2[3] = {v2i, v2j, v2k}; //vertex2 - vertex1
        
        normcrossprod(v1, v2, normal); //calculate normal
        
        return normal;
        
    }
    
    //computing the vertex normal
    //@params int vIndex : the index of the vertex
    bool calculateVertexNormal(int vIndex){
        
        fullDiscVertex = true; //set default
        std::list<int> adjacentFaces; //list to keep track of the adjacent faces
        
        HE_vert * curr_vertex = vertices_map[vIndex];
        HE_edge * outgoing_he = curr_vertex->edge;
        
        int num_of_adjacent_faces = 1;
        vertices_map[vIndex]->nx = outgoing_he->face->nx;
        vertices_map[vIndex]->ny = outgoing_he->face->ny;
        vertices_map[vIndex]->nz = outgoing_he->face->nz;
        
        HE_edge * curr_edge = outgoing_he;
        
        //one- ring traversal to find all adjacent faces around a vertex
        while (isEdgeDefined(curr_edge->pair) && !isSameEdge(curr_edge->pair->next, outgoing_he)) {
            
            curr_edge = curr_edge->pair->next;
            vertices_map[vIndex]->nx = vertices_map[vIndex]->nx + curr_edge->face->nx;
            vertices_map[vIndex]->ny = vertices_map[vIndex]->ny + curr_edge->face->ny;
            vertices_map[vIndex]->nz = vertices_map[vIndex]->nz + curr_edge->face->nz;
            
            adjacentFaces.push_back(curr_edge->face->face_index);
            num_of_adjacent_faces++;
        }
        
        if (!fullDiscVertex) { //half disc found, reverse and loop thru another side of the vertex
            
            std::list<int>::iterator it;
            curr_edge = outgoing_he;
            
            while (isEdgeDefined(curr_edge->prev->pair) && !isSameEdge(curr_edge->prev->pair, outgoing_he)) {
                
                curr_edge = curr_edge->prev->pair;
                
                bool foundFace = false;
                std::list<int>::iterator it;
                for (it=adjacentFaces.begin(); it!=adjacentFaces.end(); ++it){
                    
                    if(*it == curr_edge->face->face_index){
                        foundFace = true;
                    }
                }
                
                if(!foundFace){
                    vertices_map[vIndex]->nx = vertices_map[vIndex]->nx + curr_edge->face->nx;
                    vertices_map[vIndex]->ny = vertices_map[vIndex]->ny + curr_edge->face->ny;
                    vertices_map[vIndex]->nz = vertices_map[vIndex]->nz + curr_edge->face->nz;
                    
                    adjacentFaces.push_back(curr_edge->face->face_index);
                    num_of_adjacent_faces++;
                }
                
            }
            
        }
        
        //average
        vertices_map[vIndex]->nx = vertices_map[vIndex]->nx / num_of_adjacent_faces;
        vertices_map[vIndex]->ny = vertices_map[vIndex]->ny / num_of_adjacent_faces;
        vertices_map[vIndex]->nz = vertices_map[vIndex]->nz / num_of_adjacent_faces;
        
        return true;
    }
    
    //calculate normal
    
    //Get functions
    int getVerticesCount(){
        return verticesCount;
    }
    
    int getFacesCount(){
        return facesCount;
    }
    
    int getEdgesCount(){
        return edgesCount;
    }
    
    float* getBoundingBoxCoords(){
        static float boundingbox[6];
        boundingbox[0] = origintranslate_x - (length_x/2); //low x
        boundingbox[1] = origintranslate_x + (length_x/2); //high x
        boundingbox[2] = origintranslate_y - (length_y/2); //low y
        boundingbox[3] = origintranslate_y + (length_y/2); //high y
        boundingbox[4] = origintranslate_z - (length_z/2); //low y
        boundingbox[5] = origintranslate_z + (length_z/2); //high y
        
        return boundingbox;
    }
    
    float getEstVolumeRatioX(){
        
        //std::cout << *highX << ", " << *highY << ", " << *highZ << ", " << *lowX << ", " << *lowY << ", " << *lowZ << "\n";
        
        if(max_length == 0){
            return 1;
        }
        
        if(maxSide == __X_SIDE__){
            return 1 / max_length;
        }
        
        return (length_x / max_length) * (1 / max_length);
    }
    
    float getEstVolumeRatioY(){
        
        if(max_length == 0){
            return 1;
        }
        
        if(maxSide == __Y_SIDE__){
            return 1 / max_length;
        }
        
        return (length_y / max_length) * (1 / max_length);
    }
    
    float getEstVolumeRatioZ(){
        
        if(max_length == 0){
            return 1;
        }
        
        if(maxSide == __Z_SIDE__){
            return 1 / max_length;
        }
        
        return (length_z / max_length) * (1 / max_length);
    }
    
    float* getVertexNormal(int vIndex){
        
        if(vertices_map[vIndex]->nx == __DEFAULT_NORMAL_VAL__ ||
           vertices_map[vIndex]->ny == __DEFAULT_NORMAL_VAL__ ||
           vertices_map[vIndex]->nz == __DEFAULT_NORMAL_VAL__ ){ //normal at this vertex has not been calculated yet
            calculateVertexNormal(vIndex);
        }
        
        static float nv[__DIMENSION__];
        nv[__X_VALUE__] = vertices_map[vIndex]->nx;
        nv[__Y_VALUE__] = vertices_map[vIndex]->ny;
        nv[__Z_VALUE__] = vertices_map[vIndex]->nz;
        
        return nv;
    }
    
    HEDataStruct::HE_vert * getVertex(int vertexIndex){
        return vertices_map.at(vertexIndex);
    }
    
    HEDataStruct::HE_face * getFace(int faceIndex){
        return faces_map.at(faceIndex);
    }
    
    HEDataStruct::HE_edge * getHalfEdge(int begin_vertex, int end_vertex){
        return halfedges_map.at(std::pair<int, int>(begin_vertex, end_vertex));
    }
    
    std::map<int, HEDataStruct::HE_vert *> getVertexMap(){
        return vertices_map;
    }
    
    std::map<int, HEDataStruct::HE_face *> getFaceMap(){
        return faces_map;
    }
    
    float centralizeX(){
        return origintranslate_x;
    }
    
    float centralizeY(){
        return origintranslate_y;
    }
    
    float centralizeZ(){
        return origintranslate_z;
    }
    
    //Init functions
    void initVertexMap(){
        if (!vertices_map.empty()) {
            vertices_map.clear();
        }
    }
    
    void initFaceMap(){
        if (!faces_map.empty()) {
            faces_map.clear();
        }
    }
    
    void initHEMap(){
        if(!halfedges_map.empty()){
            //erase all
            halfedges_map.clear();
        }
    }
    
    //called when new model selected
    void reset(){
        initVertexMap();
        initFaceMap();
        initHEMap();
    }
    
    //Insert vertex to vertices array
    //@params int vIndex : running number of vertex
    //@param float x, y, z : coordinates of the vertex
    void addVertex(int vIndex, float x, float y, float z){
        
        HEDataStruct::HE_vert* newVertex = new HEDataStruct::HE_vert();
        newVertex->x = x;
        newVertex->y = y;
        newVertex->z = z;
        newVertex->vertex_index = vIndex;
        newVertex->nx = __DEFAULT_NORMAL_VAL__;
        newVertex->ny = __DEFAULT_NORMAL_VAL__;
        newVertex->nz = __DEFAULT_NORMAL_VAL__;
        
        static float* lowX = NULL;
        static float* lowY = NULL;
        static float* lowZ = NULL;
        static float* highX = NULL;
        static float* highY = NULL;
        static float* highZ = NULL;
        
        if (lowX == NULL || *lowX > newVertex->x) {
            lowX = &newVertex->x;
        }
        
        if (lowY == NULL || *lowY > newVertex->y) {
            lowY = &newVertex->y;
        }
        
        if (lowZ == NULL || *lowZ > newVertex->z) {
            lowZ = &newVertex->z;
        }
        
        if (highX == NULL || *highX < newVertex->x) {
            highX = &newVertex->x;
        }
        
        if (highY == NULL || *highY < newVertex->y) {
            highY = &newVertex->y;
        }
        
        if (highZ == NULL || *highZ < newVertex->z) {
            highZ = &newVertex->z;
        }
        
        length_x = *highX - *lowX;
        length_y = *highY - *lowY;
        length_z = *highZ - *lowZ;
        
        //scale up to unit cube
        max_length = length_x;
        
        if(length_y > length_x){
            max_length = length_y;
            maxSide = __Y_SIDE__;
            if(length_z > length_y){
                max_length = length_z;
                maxSide = __Z_SIDE__;
            }
        }else if(length_z > length_x){
            maxSide = __Z_SIDE__;
            max_length = length_z;
            if(length_y > length_z){
                max_length = length_y;
                maxSide = __Y_SIDE__;
            }
        }
        
        origintranslate_x = -1 * ((*lowX) + ( length_x/ 2 ));
        origintranslate_y = -1 * ((*lowY) + ( length_y/ 2 ));
        origintranslate_z = -1 * ((*lowZ) + ( length_z/ 2 ));
        
        vertices_map.emplace(vIndex, newVertex);
        verticesCount++; //keep track of the number of vertices
        
    }
    
    //Update the edge of the vertex when loop thru the faces
    //@params int vIndex : the index of the vertex in vertices array
    //@params int startVertex/ endvertex : the start vertex and end vertex of the edge
    void updateVertex(int vIndex, int startVertex, int endVertex){
        vertices_map[vIndex]->edge = halfedges_map.at(std::pair <int,int>(startVertex,endVertex));
    }
    
    void addFace(int fIndex, int vertex1, int vertex2, int vertex3){
        
        HEDataStruct::HE_face* new_face = new HEDataStruct::HE_face();
        new_face->edge = halfedges_map.at(std::pair<int, int>(vertex2, vertex3));
        new_face->face_index = fIndex;
        
        //calculate face normal for vertex normal calculation later
        float* normal = calculateFaceNormal(vertices_map[vertex1], vertices_map[vertex2], vertices_map[vertex3]);
        new_face->nx = *normal;
        new_face->ny = *(normal+1);
        new_face->nz = *(normal+2);
        
        faces_map.insert(std::pair<int, HEDataStruct::HE_face *>(fIndex, new_face)); //append the face to the list
        facesCount++;
        
        //assign the adjacent half edges to this face
        halfedges_map.at(std::pair<int, int>(vertex1, vertex2))->face = new_face;
        halfedges_map.at(std::pair<int, int>(vertex2, vertex3))->face = new_face;
        halfedges_map.at(std::pair<int, int>(vertex3, vertex1))->face = new_face;
        
    }
    
    //add new edges of the triangle mesh to the half edge map
    //@param fIndex the face index this triangle mesh belongs to
    //@param vertex1 1st vertex defined in the mfile
    //@param vertex2 2nd vertex defined in the mfile
    //@param vertex3 3rd vertex defined in the mfile
    void addHalfEdges(int fIndex, int vertex1, int vertex2, int vertex3){
        
        std::pair <int,int> edge1 = std::make_pair (vertex1, vertex2);
        std::pair <int,int> edge2 = std::make_pair (vertex2, vertex3);
        std::pair <int,int> edge3 = std::make_pair (vertex3, vertex1);
        
        HE_vert * p1 = vertices_map[vertex1];
        HE_vert * p2 = vertices_map[vertex2];
        HE_vert * p3 = vertices_map[vertex3];
        
        //define edge 1, set pair edge as NULL
        HEDataStruct::HE_edge* new_edge1 = new HEDataStruct::HE_edge();
        new_edge1->vert = p2;
        new_edge1->pair = nullptr;
        
        //define edge 2, set pair edge as NULL
        HEDataStruct::HE_edge* new_edge2 = new HEDataStruct::HE_edge();
        new_edge2->vert = p3;
        new_edge2->pair = nullptr;
        
        //define edge 3, set pair edge as NULL
        HEDataStruct::HE_edge* new_edge3 = new HEDataStruct::HE_edge();
        new_edge3->vert = p1;
        new_edge3->pair = nullptr;
        
        //define the prev and next half edge
        new_edge1->prev = new_edge3;
        new_edge2->prev = new_edge1;
        new_edge3->prev = new_edge2;
        
        new_edge1->next = new_edge2;
        new_edge2->next = new_edge3;
        new_edge3->next = new_edge1;
        
        //        std::string pair_str_21 = HE_COORDS_DELIMITER + std::to_string(vertex2) + HE_COORDS_SEPARATOR + std::to_string(vertex1) + HE_COORDS_DELIMITER;
        //        std::string pair_str_32 = HE_COORDS_DELIMITER + std::to_string(vertex3) + HE_COORDS_SEPARATOR + std::to_string(vertex2) + HE_COORDS_DELIMITER;
        //        std::string pair_str_13 = HE_COORDS_DELIMITER + std::to_string(vertex1) + HE_COORDS_SEPARATOR + std::to_string(vertex3) + HE_COORDS_DELIMITER;
        
        //define pair edges
        std::pair<int, int> pair_21 = std::make_pair(vertex2, vertex1);
        std::pair<int, int> pair_32 = std::make_pair(vertex3, vertex2);
        std::pair<int, int> pair_13 = std::make_pair(vertex1, vertex3);
        
        //for ( vertex1, vertex2 )
        std::map<std::pair<int, int>,HEDataStruct::HE_edge*>::iterator it1;
        std::map<std::pair<int, int>,HEDataStruct::HE_edge*>::iterator it2;
        std::map<std::pair<int, int>,HEDataStruct::HE_edge*>::iterator it3;
        
        it1 = halfedges_map.find(pair_21);
        if (it1 != halfedges_map.end()){ //found pair
            new_edge1->pair = halfedges_map.at(std::pair<int, int>(vertex2, vertex1));
            halfedges_map.at(std::pair<int, int>(vertex2, vertex1))->pair = new_edge1; //pair up
        }
        
        it2 = halfedges_map.find(pair_32);
        if (it2 != halfedges_map.end()){ //found pair
            new_edge2->pair = halfedges_map.at(std::pair<int, int>(vertex3, vertex2));
            halfedges_map.at(std::pair<int, int>(vertex3, vertex2))->pair = new_edge2; //pair up
        }
        
        it3 = halfedges_map.find(pair_13);
        if (it3 != halfedges_map.end()){ //found pair
            new_edge3->pair = halfedges_map.at(std::pair<int, int>(vertex1, vertex3));
            halfedges_map.at(std::pair<int, int>(vertex1, vertex3))->pair = new_edge3; //pair up
        }
        
        halfedges_map.insert(std::pair<std::pair <int,int>, HEDataStruct::HE_edge *>(edge1, new_edge1));
        halfedges_map.insert(std::pair<std::pair <int,int>, HEDataStruct::HE_edge *>(edge2, new_edge2));
        halfedges_map.insert(std::pair<std::pair <int,int>, HEDataStruct::HE_edge *>(edge3, new_edge3));
        
        //std::cout << "Added Face " << fIndex << "\n";
        
        //increase edge count by 3
        edgesCount += __NUM_OF_EDGE_PER_FACE__;
        
    }
    
    void saveDataToCache(std::string meshfilename){
        vertices_map_cache[meshfilename]    = vertices_map;
        faces_map_cache[meshfilename]       = faces_map;
        edges_map_cache[meshfilename]       = halfedges_map;
        
        BoundingBox* b_box = new BoundingBox();
        b_box->lengthX = length_x;
        b_box->lengthY = length_y;
        b_box->lengthZ = length_z;
        b_box->maxLength = max_length;
        b_box->maxSide_str = maxSide;
        b_box->originalX = origintranslate_x;
        b_box->originalY = origintranslate_y;
        b_box->originalZ = origintranslate_z;
        
        bounding_box_cache[meshfilename] = b_box;
    }
    
    bool loadDataFromCache(std::string meshfilename){
        std::map<std::string, std::map<int, HEDataStruct::HE_vert *>>::iterator search_it;
        
        search_it = vertices_map_cache.find(meshfilename);
        if (search_it != vertices_map_cache.end()){ //found pair
            vertices_map    = vertices_map_cache[meshfilename];
            faces_map       = faces_map_cache[meshfilename];
            halfedges_map   = edges_map_cache[meshfilename];
            
            length_x = bounding_box_cache[meshfilename]->lengthX;
            length_y = bounding_box_cache[meshfilename]->lengthY;
            length_z = bounding_box_cache[meshfilename]->lengthZ;
            max_length = bounding_box_cache[meshfilename]->maxLength;
            maxSide = bounding_box_cache[meshfilename]->maxSide_str;
            origintranslate_x = bounding_box_cache[meshfilename]->originalX;
            origintranslate_y = bounding_box_cache[meshfilename]->originalY;
            origintranslate_z = bounding_box_cache[meshfilename]->originalZ;
            
            return true;
        }
        
        return false;
    }
    
}
