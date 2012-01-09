//
//  mouseControl.cpp
//  mouseControlExample
//
//  Created by joseph saavedra on 1/9/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include <iostream>

#include "mouseControl.h"

mouseControl::mouseControl(){
    prevMouse.x = 0;
    prevMouse.y = 0;
    mouseMoved = false;
    mLeftButton = false;
}

//----- move mouse -------------
void mouseControl::move(ofPoint myMouse){
    
    CGEventRef move = CGEventCreateMouseEvent(
                                              NULL, kCGEventMouseMoved,
                                              CGPointMake(myMouse.x, myMouse.y),
                                              kCGMouseButtonLeft // ignored
                                              );
    CGEventPost(kCGHIDEventTap, move);
    CFRelease(move);
    
}

void mouseControl::update(){
    
    
}

//-------- move ---------------

bool mouseControl::moved(ofPoint myMouse){
    
    if (prevMouse.x != myMouse.x  || prevMouse.y != myMouse.y){ 
        prevMouse.x = myMouse.x;
        prevMouse.y = myMouse.y;
        return true;
    }
    else return false;
}

//-------- left mouse button -------------------
void mouseControl::leftClickDown(ofPoint myMouse){
    
    click1_down = CGEventCreateMouseEvent(
                                          NULL, kCGEventLeftMouseDown,
                                          CGPointMake(myMouse.x, myMouse.y),
                                          kCGMouseButtonLeft
                                          );
    CGEventPost(kCGHIDEventTap, click1_down);
    CFRelease(click1_down);
    mLeftButton = true;
}

void mouseControl::leftClickUp(ofPoint myMouse){
    
    click1_up = CGEventCreateMouseEvent(
                                        NULL, kCGEventLeftMouseUp,
                                        CGPointMake(myMouse.x, myMouse.y),
                                        kCGMouseButtonLeft
                                        );
    cout << click1_up <<endl;
    CGEventPost(kCGHIDEventTap, click1_up);
    
    CFRelease(click1_up);
    
    //leftMouseDragged(x, y);
    //CFRelease(leftDragged);
    mLeftButton = false;
}

bool mouseControl::getLeftButton(){
    return mLeftButton;
}


//-------------- mouse dragged ----------------
void mouseControl::leftMouseDragged(ofPoint myMouse){
    
    CGEventSourceRef source = CGEventSourceCreate(NULL);
    CGEventType eventType = kCGEventLeftMouseDragged;
    CGPoint mouseCursorPosition;
    mouseCursorPosition.x = myMouse.x;
    mouseCursorPosition.y = myMouse.y;
    CGMouseButton mouseButton = kCGMouseButtonLeft;
    
    CGEventRef mouseEvent = CGEventCreateMouseEvent ( source,
                                                     eventType,
                                                     mouseCursorPosition,
                                                     mouseButton );
    CGEventSetType(mouseEvent, kCGEventLeftMouseDragged); // Fix Apple Bug
    CGEventPost( kCGSessionEventTap, mouseEvent );
    CFRelease(mouseEvent);


    
    /*leftDragged = CGEventCreateMouseEvent(
                                          NULL, kCGEventLeftMouseDragged, 
                                          CGPointMake(x, y), 
                                          kCGMouseButtonLeft);
    
    CGEventPost(kCGHIDEventTap, leftDragged);*/
    
    //CFRelease(leftDragged);
}


//------------- right mouse press
void mouseControl::rightClick(ofPoint myMouse){
    
    
    
}


/*
 
 //source example came from: http://stackoverflow.com/questions/2734117/simulating-mouse-input-programmatically-in-os-x
 
 
 int main() {
 // Move to 200x200
 CGEventRef move1 = CGEventCreateMouseEvent(
 NULL, kCGEventMouseMoved,
 CGPointMake(200, 200),
 kCGMouseButtonLeft // ignored
 );
 // Move to 250x250
 CGEventRef move2 = CGEventCreateMouseEvent(
 NULL, kCGEventMouseMoved,
 CGPointMake(250, 250),
 kCGMouseButtonLeft // ignored
 );
 // Left button down at 250x250
 CGEventRef click1_down = CGEventCreateMouseEvent(
 NULL, kCGEventLeftMouseDown,
 CGPointMake(250, 250),
 kCGMouseButtonLeft
 );
 // Left button up at 250x250
 CGEventRef click1_up = CGEventCreateMouseEvent(
 NULL, kCGEventLeftMouseUp,
 CGPointMake(250, 250),
 kCGMouseButtonLeft
 );
 
 // Now, execute these events with an interval to make them noticeable
 CGEventPost(kCGHIDEventTap, move1);
 sleep(1);
 CGEventPost(kCGHIDEventTap, move2);
 sleep(1);
 CGEventPost(kCGHIDEventTap, click1_down);
 CGEventPost(kCGHIDEventTap, click1_up);
 
 // Release the events
 CFRelease(click1_up);
 CFRelease(click1_down);
 CFRelease(move2);
 CFRelease(move1);
 
 return 0;
 }*/