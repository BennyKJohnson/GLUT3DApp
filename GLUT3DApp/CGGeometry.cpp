//
//  CGGeometry.cpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGGeometry.hpp"

void CGGeometry::presentationGeometry() {
    
}

CGMaterial* CGGeometry::firstMaterial() {
    
    return materials[0];
    
}

void CGGeometry::setMaterial(CGMaterial* material) {
    
    materials.pop_back();
    materials.push_back(material);
    
}



CGMaterial* CGGeometry::materialWithName(std::string* name) {
    
    for (int i = 0; i < materials.size(); i++) {
        CGMaterial *material = materials[i];
        
        if (material->name != NULL && *material->name == *name) {
            return material;
        }
    }
    
    return NULL;
}
