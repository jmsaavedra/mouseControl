#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
            
    //clickable rectangles
    rect_size = 100;
    rect1_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect1_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    rect2_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect2_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    
    rect1L = false;
    rect2L = false;
    rect1R = false;
    rect2R = false;
    
    //colors
    on.r=0;
    on.g=0;
    on.b=255;
    
    off.r=255;
    off.g=0;
    off.b=0;
    
    //mouse start position
    myMouse.x = ofGetScreenHeight()/2;
    myMouse.y = ofGetScreenWidth()/2;
    
    //initialize mouseControl
    mouser.setup();
    
    //execute move to start position
    mouser.move(myMouse);
}

//--------------------------------------------------------------
void testApp::update(){
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(255);
    
    ofSetColor(0);
    ofDrawBitmapString("use UP, DOWN, LEFT, RIGHT arrows to move mouse", 50,50);
    ofDrawBitmapString("hit '1' to left click // hold '1' and move to drag", 50,70);
    ofDrawBitmapString("hit '2' to right click", 50,90);
    ofDrawBitmapString("click me!", rect1_x, rect1_y-10);
    ofDrawBitmapString("click me!", rect2_x, rect2_y-10);
    ofDrawBitmapString(event, ofGetWidth()/2+30, 50);
    
   
    ofSetColor(off);
    if(rect1L) ofSetColor(on);
    else if(rect1R) ofSetColor(100,255,100);
    ofRect(rect1_x, rect1_y, rect_size, rect_size);

    ofSetColor(off);
    if(rect2L) ofSetColor(on);
    else if(rect2R) ofSetColor(100,255,100);
    ofRect(rect2_x, rect2_y, rect_size, rect_size);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key){
			
		case	OF_KEY_LEFT:
            myMouse.x -= 10;
            if(mouser.getLeftButton()){ //if getLeftButton == true, we're dragging
                mouser.leftMouseDragged(myMouse);
            } else mouser.move(myMouse);
			break;
            
        case	OF_KEY_RIGHT:
            myMouse.x += 10;
            if(mouser.getLeftButton()){ //if getLeftButton == true, we're dragging
                mouser.leftMouseDragged(myMouse);
            }else mouser.move(myMouse);
			break;
        
        case	OF_KEY_UP:
            myMouse.y -= 10;
            if(mouser.getLeftButton()){ //if getLeftButton == true, we're dragging
                mouser.leftMouseDragged(myMouse);
            }else mouser.move(myMouse);
			break;
            
        case	OF_KEY_DOWN:
            myMouse.y += 10;
            if(mouser.getLeftButton()){ //if getLeftButton == true, we're dragging
                mouser.leftMouseDragged(myMouse);
            }else mouser.move(myMouse);
			break;

        case    '1':
            mouser.leftButtonDown(myMouse);
            break;
        
        case    '2':
            mouser.rightButtonDown(myMouse);
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch (key){
        case    '1':
            mouser.leftButtonUp(myMouse);
            break;
        case    '2':
            mouser.rightButtonUp(myMouse);
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
    event = "mouse moved x: " + ofToString(x) + " y: " + ofToString(y);    
    cout << event << endl;
    
    cout << myMouse.x << " " << x << endl;
    cout << myMouse.y << " " << y << endl;

    //if(myMouse.x != x) myMouse.x = x;
    //if(myMouse.y != y) myMouse.y = y;
    //mouser.move(myMouse);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    event = "left mouse button dragged x: " + ofToString(x) + " y: " + ofToString(y);
    cout << event << endl;
    
    if(rect1L){
        rect1_x = x - rect_size/2;
        rect1_y = y - rect_size/2;
    }
    else if(rect2L){
        rect2_x = x - rect_size/2;
        rect2_y = y - rect_size/2;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    //left button pressed
    if(button == 0){ 
        event = "left mouse button pressed x: " + ofToString(x) + " y: " + ofToString(y);
        cout << event << x << y << button << endl;
        if(x > rect1_x && x < rect1_x+rect_size && y > rect1_y && y < rect1_y+rect_size){
            rect1L = true;
        } else rect1L = false;
        
        if(x > rect2_x && x < rect2_x+rect_size && y > rect2_y && y < rect2_y+rect_size){
            rect2L = true;
        } else rect2L = false;
    }
    
    //right button pressed
    else if(button == 2){
        event = "right mouse button pressed x: " + ofToString(x) + " y: " + ofToString(y);
        cout << event << x << y << button << endl;
        if(x > rect1_x && x < rect1_x+rect_size && y > rect1_y && y < rect1_y+rect_size){
            rect1R = true;
        } else rect1R = false;
        
        if(x > rect2_x && x < rect2_x+rect_size && y > rect2_y && y < rect2_y+rect_size){
            rect2R = true;
        } else rect2R = false;
    }
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    //left button released
    if(button == 0){
        cout << "left mouse released! " << x << y << button << endl;
        rect1L = false;
        rect2L = false;
        
    } else if(button == 2){
        cout << "right mouse released! " << x << y << button << endl;
        rect1R = false;
        rect2R = false;
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}