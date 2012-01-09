//
//  mouseControl.h
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#pragma once

#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include "ofMain.h"

class mouseControl {
    
public:
    
    mouseControl();
    void update();
    
    void move(ofPoint myMouse);
    void leftClickUp(ofPoint myMouse);
    void leftClickDown(ofPoint myMouse);
    void rightClick(ofPoint myMouse);
    void leftMouseDragged(ofPoint myMouse);
    
    bool mouseMoved;
    bool moved(ofPoint myMouse);
    
    bool mLeftButton;
    bool getLeftButton();
    
    ofPoint prevMouse;
    
    //CGEventRef move;            //move
    CGEventRef click1_down;     //left click down
    CGEventRef click1_up;       //left click up
    CGEventRef leftDragged;
};

