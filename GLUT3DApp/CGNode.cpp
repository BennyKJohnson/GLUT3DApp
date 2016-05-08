//
//  CGNode.cpp
//  GLUT3DApp
//
//  Created by Ben Johnson on 8/05/2016.
//  Copyright © 2016 Benjamin Johnson. All rights reserved.
//

#include "CGNode.hpp"

void CGNode::addChildNode(CGNode *node) {
    // Set parent node
    node->parentNode = this;
    // Add to array of child nodes
    childNodes.push_back(node);
}

CGNode::CGNode() {
   
    
}