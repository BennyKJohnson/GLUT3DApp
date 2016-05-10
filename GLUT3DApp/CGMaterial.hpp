//
//  CGMaterial.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 9/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGMaterial_hpp
#define CGMaterial_hpp

#include <stdio.h>
#include "CG.hpp"
#include <string.h>

class CGMaterial {
    

public:
    
    std::string *name;
    
    bool locksAmbientWithDiffuse;
    
    CGColor diffuse;
    
    CGColor ambient;
    
    CGColor specular;
    
    CGColor emission;
    
    float shininess;
    
    bool doubleSided;
    
    CGMaterial() {
        
        locksAmbientWithDiffuse = true;
        
        ambient = CGColor(0.2, 0.2, 0.2, 1);
        
        diffuse = CGColorBlue(); //CGColor(1, 1, 1, 1.0);
        
        specular = CGColor(0, 0, 0, 1);
        
        emission = CGColor(0, 0 , 0, 1);
        
        shininess = 0;
        
        doubleSided = false;
        
    }
    
    void loadMaterial();
};

#endif /* CGMaterial_hpp */
