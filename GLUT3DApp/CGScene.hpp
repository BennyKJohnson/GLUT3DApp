//
//  CGScene.hpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#ifndef CGScene_hpp
#define CGScene_hpp

#include <stdio.h>
#include "CGNode.hpp"

class CGScene {
    
    
public:
    CGNode *rootNode;
    void render();
    void renderNode(CGNode *node);
    CGScene();
};


#endif /* CGScene_hpp */
