//
//  CGGeometrySource.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 9/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGGeometrySource_hpp
#define CGGeometrySource_hpp

#include <stdio.h>
#include "CG.hpp"

typedef enum CGGeometrySourceSemantic {
    CGGeometrySourceSemanticVertex,
    CGGeometrySourceSemanticNormal,
    CGGeometrySourceSemanticColor,
} CGGeometrySourceSemantic;


class CGGeometrySource {
    
public:
    
    int vectorCount;
    CGVector3* data;
    
    CGGeometrySource(CGVector3 *data, int count) {
        
        this->data = data;
        this->vectorCount = count;
        
    }

};

#endif /* CGGeometrySource_hpp */
