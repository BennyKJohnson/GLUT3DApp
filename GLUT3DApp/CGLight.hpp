//
//  CGLight.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGLight_hpp
#define CGLight_hpp

#include <stdio.h>
#include "CG.hpp"

typedef enum CGLightType {
    CGLightTypeAmbient,
    CGLightTypeOmni,
    CGLightTypeDirectional,
    CGLightTypeSpot
} CGLightType;

class CGLight {
    
    
public:
    
    CGColor color;
    
    CGLightType type;
    
    void render();
    
    CGLight() {
    
        color = CGColorSimpleYellow();
        
        type = CGLightTypeAmbient;
    }
    
};

#endif /* CGLight_hpp */
