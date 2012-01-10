//
//  mouseControl.cpp
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.

/* 
 
 derived from examples found 
 here: http://stackoverflow.com/questions/2734117/simulating-mouse-input-programmatically-in-os-x
 and here: http://stackoverflow.com/questions/4051587/apple-events-to-control-mouse-remotely
 
 Quartz Event Reference:
http://developer.apple.com/library/mac/#documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html
 
*/

#include <iostream>

#include "mouseControl.h"

mouseControl::mouseControl(){

}

void mouseControl::setup(){
    mLeftButton = false;
    mRightButton = false;
    draggingLeftButton = false;
    draggingRightButton = false;
    
    //moved
    eventTypeMouseMoved = kCGEventMouseMoved;
    //left button
    eventTypeLeftDragged = kCGEventLeftMouseDragged;
    eventTypeLeftMouseDown = kCGEventLeftMouseDown;
    eventTypeLeftMouseUp = kCGEventLeftMouseUp;
    //right button
    eventTypeRightDragged = kCGEventRightMouseDragged;
    eventTypeRightMouseDown = kCGEventRightMouseDown;
    eventTypeRightMouseUp = kCGEventRightMouseUp;  
}

void mouseControl::update(){
    
    
}

//----- move mouse ----------------
void mouseControl::move(ofPoint myMouse){
    
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    mouseEventMove = CGEventCreateMouseEvent ( CGEventSourceCreate(NULL),
                                                         eventTypeMouseMoved,
                                                         mouseCursorPosition,
                                                         kCGMouseButtonLeft);//ignored
    CGEventSetType(mouseEventMove, kCGEventMouseMoved); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventMove );
    
    CFRelease(mouseEventMove);
}

//-------- left mouse button -------------------

void mouseControl::leftButtonDown(ofPoint myMouse){
    
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonLeft;
    
    mouseEventLeftDown = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                 eventTypeLeftMouseDown,
                                                 mouseCursorPosition,
                                                 kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftDown, kCGEventLeftMouseDown); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftDown );
    
    CFRelease(mouseEventLeftDown);
    mLeftButton = true;
}

void mouseControl::leftButtonUp(ofPoint myMouse){
    
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonLeft;
    
    mouseEventLeftUp = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                  eventTypeLeftMouseDown,
                                                  mouseCursorPosition,
                                                  kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftUp, kCGEventLeftMouseUp); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftUp );
    
    CFRelease(mouseEventLeftUp);
    
    mLeftButton = false;
    if(draggingLeftButton){
        CFRelease(mouseEventLeftDragged);
        draggingLeftButton = false;
    }
}

bool mouseControl::getLeftButton(){
    return mLeftButton;
}


//-------- right mouse press -------------------

void mouseControl::rightButtonDown(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonRight;
    
    mouseEventRightDown = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                 eventTypeRightMouseDown,
                                                 mouseCursorPosition,
                                                 kCGMouseButtonRight );
    CGEventSetType(mouseEventRightDown, kCGEventRightMouseDown); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightDown );
    CFRelease(mouseEventRightDown);
    mRightButton = true;    
}

void mouseControl::rightButtonUp(ofPoint myMouse){
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonRight;
    
    mouseEventRightUp = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                      eventTypeRightMouseUp,
                                                      mouseCursorPosition,
                                                      kCGMouseButtonRight );
    CGEventSetType(mouseEventRightUp, kCGEventRightMouseUp); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightUp );
    CFRelease(mouseEventRightUp);
    mRightButton = false;
    if(draggingRightButton){
        CFRelease(mouseEventRightDragged);
        draggingRightButton = false;
    }
}

bool mouseControl::getRightButton(){
    return mRightButton;
}



//------- mouse dragged ------------------------

void mouseControl::leftMouseDragged(ofPoint myMouse){
    
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonLeft;
    
    mouseEventLeftDragged = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                     eventTypeLeftDragged,
                                                     mouseCursorPosition,
                                                     kCGMouseButtonLeft );
    CGEventSetType(mouseEventLeftDragged, kCGEventLeftMouseDragged); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventLeftDragged );
    draggingLeftButton = true;
}

void mouseControl::rightMouseDragged(ofPoint myMouse){
    
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonRight;
    
    mouseEventRightDragged = CGEventCreateMouseEvent (  CGEventSourceCreate(NULL),
                                                      eventTypeRightDragged,
                                                      mouseCursorPosition,
                                                      kCGMouseButtonRight );
    CGEventSetType(mouseEventRightDragged, kCGEventRightMouseDragged); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEventRightDragged );
    draggingRightButton = true;
}
