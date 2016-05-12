//
//  CGGeometry.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGGeometry_hpp
#define CGGeometry_hpp

#include <stdio.h>
#include <vector>
#include "CGMaterial.hpp"
#include "CGGeometrySource.hpp"
#include <string>

class CGGeometry {
    
    
public:
    
    std::vector<CGMaterial*> materials;
    
    std::vector<CGGeometrySource*> geometrySources;
    
    
    virtual void presentationGeometry();
    
    CGMaterial* firstMaterial();
    
    CGMaterial* materialWithName(std::string* name);
    
    void setMaterial(CGMaterial* material);
    
    CGGeometry() {
        materials.push_back(new CGMaterial());
      //  this->materials.push_back(CGMaterial());
        
    }
    
};

#endif /* CGGeometry_hpp */
