//
//  mouseControl.h
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.

#pragma once

#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include "ofMain.h"

class mouseControl {
    
public:
    
    mouseControl();
    void setup();
    void update();
    
    void move(ofPoint myMouse);
    void leftButtonUp(ofPoint myMouse);
    void leftButtonDown(ofPoint myMouse);
    void rightButtonUp(ofPoint myMouse);
    void rightButtonDown(ofPoint myMouse);
    void leftMouseDragged(ofPoint myMouse);
    void rightMouseDragged(ofPoint myMouse);
    
    bool mLeftButton;
    bool getLeftButton();
    bool mRightButton;
    bool getRightButton();
    
    bool draggingLeftButton;
    bool draggingRightButton;
    
    CGEventSourceRef source;
    
    CGPoint mouseCursorPosition;
    
    //event refs
    CGEventRef mouseEventMove;
    CGEventRef mouseEventLeftDown;     //left click down
    CGEventRef mouseEventLeftUp;       //left click up
    CGEventRef mouseEventLeftDragged; //left dragged
    CGEventRef mouseEventRightDown;     //left click down
    CGEventRef mouseEventRightUp;       //left click up
    CGEventRef mouseEventRightDragged; //left dragged
    
    //event types
    CGEventType eventTypeMouseMoved;
    CGEventType eventTypeLeftMouseDown;
    CGEventType eventTypeLeftMouseUp;
    CGEventType eventTypeLeftDragged;
    CGEventType eventTypeRightMouseDown;
    CGEventType eventTypeRightMouseUp;
    CGEventType eventTypeRightDragged;
};

