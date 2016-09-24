//
//  mFileParser.hpp
//  DM6101Assignment
//
//  Created by Christina Lui on 10/11/15.
//  Copyright © 2015 Christina Lui. All rights reserved.
//

#ifndef mFileParser_hpp
#define mFileParser_hpp

//C/ C++ library
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

//App Files
#include "MeshDataStruct.hpp"
using namespace MeshDataStruct;

//Assignment Objective 1: M-File Parser
//load and explain the M file data
//parse the M file data and translate it to Mesh Data Structure (refer to MeshDataStruct.hpp)

// M file format
//===============
// ( Vertex )
// Vertex [Vertex index] [x coord] [y coord] [z coord]
// ( Face )
// Face [Face index] [Vertex 1 index] [Vertex 2 index] [Vertex 3 index]
namespace mFileParser {
    int parseFileandGenerateHEMaps(std::string input_file_path);
}


#endif /* mFileParser_hpp */
