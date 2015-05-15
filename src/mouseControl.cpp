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
#include "testApp.h"

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
    
    //myMouse = (0,0);
    mouseCursorPosition.x = 0;
    mouseCursorPosition.y = 0;
    
    //move(myMouse);
    
    //simulateDemo "moveThenClick()" vars
    pressWaitTime = true;
    releaseWaitTime = true;
    moving = false;
}


void mouseControl::update(){
    
    if (moving) moveThenClick(); //only needed for experimental methods
}

//----- move mouse ----------------

void mouseControl::move(int x, int y){
    ofPoint newMouse;
    newMouse.x = x;
    newMouse.y = y;
    move(newMouse);
}

void mouseControl::move(ofPoint _myMouse){
    
    myMouse = _myMouse;
    
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

//-------- left mouse press -------------------

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


//------- move then click -------------------------
//an experiment: 
//will move mouse to specified ofPoint, then left click and release.

bool mouseControl::moveThenClick(ofPoint _toWhere){
    
    toWhere = _toWhere;
    cout << "moveThenClick: " << toWhere.x << " " << toWhere.y << endl;
    moving = true;
    
    currMouse.x = ((testApp*)ofGetAppPtr())->myMouse.x;
    currMouse.y = ((testApp*)ofGetAppPtr())->myMouse.y;
    
    moveThenClick();
}

bool mouseControl::moveThenClick(){
    
    //moveThenClick(toWhere);
        
    xRemaining = toWhere.x - currMouse.x;
    yRemaining = toWhere.y - currMouse.y;
    
    if (abs(yRemaining) > 2 || abs(xRemaining) > 2){
        currMouse.y += yRemaining*0.019;
        currMouse.x += xRemaining*0.019;
        move(currMouse);
        //moving = true;
        //cout << "move "<< currMouse.x << " " << currMouse.y << endl;
        //cout << "Remaining "<< xRemaining << " " << yRemaining << endl;
        
    } //else moving = false;
    
    if (abs(yRemaining) <= 2 && abs(xRemaining) <= 2){
        
        if (pressWaitTime){
            cout << "button down on target"<< endl;
            //click
            leftButtonDown(currMouse);
            timeStmp = ofGetElapsedTimef();
            pressWaitTime = false;
        }
        
        if (ofGetElapsedTimef() - timeStmp > 0.3f){ //press and hold wait time
            
            if (releaseWaitTime){
                leftButtonUp(currMouse);
                cout << "button should be up" << endl;
                timeStmp = ofGetElapsedTimef();
                releaseWaitTime = false;
            }
            if (ofGetElapsedTimef() - timeStmp > 1.0f){ //wait time after release
                pressWaitTime = true;       //reset both to true
                releaseWaitTime = true;
                ((testApp*)ofGetAppPtr())->myMouse = currMouse; //tell app where we left the mouse
                moving = false;
                cout << "moving now false" << endl;
            } //else moving = true;                
        }//else moving = true;   
    }
}

bool mouseControl::getMoving(){

    return moving;
    //if (moving) moveThenClick();
}