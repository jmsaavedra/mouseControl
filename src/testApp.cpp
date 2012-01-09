#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //initialize x, y
    myMouse.x = ofGetWidth()/2;
    myMouse.y = ofGetHeight()/2;
    
    //execute move
    mouser.move(myMouse);
    
    //clickable rectangles
    rect_size = 100;
    rect1_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect1_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    rect2_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect2_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    
    rect1 = false;
    rect2 = false;
    
    //colors
    on.r=0;
    on.g=0;
    on.b=255;
    
    off.r=255;
    off.g=0;
    off.b=0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    //cout << mouser.moved(myMouse) << endl;
    //if(mouser.moved(myMouse) && 
    //cout << mouser.getLeftButton() << endl;
    if(mouser.moved(myMouse) && mouser.getLeftButton()){
        //cout << "dragged" << endl;
        mouser.leftMouseDragged(myMouse);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(255);
    
    ofSetColor(0);
    ofDrawBitmapString("use UP, DOWN, LEFT, RIGHT arrows to move mouse", 50,50);
    ofDrawBitmapString("hit RETURN to click", 50,70);
    
   
    ofSetColor(off.r,off.g,off.b);
    if(rect1) ofSetColor(on.r,on.g,on.b);
    ofRect(rect1_x, rect1_y, rect_size, rect_size);

    
    ofSetColor(off.r,off.g,off.b);
    
    if(rect2) ofSetColor(on.r,on.g,on.b);
    ofRect(rect2_x, rect2_y, rect_size, rect_size);
    
    ofSetColor(off.r, on.g, off.b);
    ofDrawBitmapString("rect 1", rect1_x-rect_size/2, rect1_y-rect_size/2);
    ofDrawBitmapString("rect 2", rect2_x-rect_size/2, rect2_y-rect_size/2);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key){
			
		case	OF_KEY_LEFT:
            myMouse.x -= 10;
            mouser.move(myMouse);
			break;
            
        case	OF_KEY_RIGHT:
            myMouse.x += 10;
            mouser.move(myMouse);
			break;
        
        case	OF_KEY_UP:
            myMouse.y -= 10;
            mouser.move(myMouse);
			break;
            
        case	OF_KEY_DOWN:
            myMouse.y += 10;
            mouser.move(myMouse);
			break;

        case    OF_KEY_RETURN:
            mouser.leftClickDown(myMouse);
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == OF_KEY_RETURN){
        cout << "left click up" << endl;
        mouser.leftClickUp(myMouse);
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    cout << "mouseMoved! " << x << y << endl;
    
    //myMouse.x = x;
    //myMouse.y = y;
    //mouser.move(myMouse);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
   
    cout << "mouseDragged! " << x << y << button << endl;
    
    // for dragging:
    if(rect1){
        rect1_x = x - rect_size/2;
        rect1_y = y - rect_size/2;
    }
    else if(rect2){
        rect2_x = x - rect_size/2;
        rect2_y = y - rect_size/2;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    cout << "left mouse pressed! " << x << y << button << endl;
    
    if(x > rect1_x && x < rect1_x+rect_size && y > rect1_y && y < rect1_y+rect_size){
        rect1 = true;
    } else rect1 = false;
    
    if(x > rect2_x && x < rect2_x+rect_size && y > rect2_y && y < rect2_y+rect_size){
        rect2 = true;
    } else rect2 = false;
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    cout << "left mouse released! " << x << y << button << endl;
    rect1 = false;
    rect2 = false;
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