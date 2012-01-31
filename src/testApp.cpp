#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //initialize mouseControl
    mouser.setup();
            
    //clickable rectangles
    rect_size = 100;
    rect1_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect1_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    rect2_x = ofRandom(rect_size, ofGetWidth()-rect_size);
    rect2_y = ofRandom(rect_size, ofGetHeight()-rect_size);
    rect1L = false;  rect2L = false; rect1R = false; rect2R = false;
    //colors
    on.r=0;       on.g=0;     on.b=255;    
    off.r=255;    off.g=0;    off.b=0;
    
    // my targets for "simulationDemo" mode
    target[0].set(0,    0);        //will be rect1
    target[1].set(0,    0);        //will be rect1
    target[2].set(1154, 37);    //out of app 
    target[3].set(26,   12);    //osx apple menu 
    target[4].set(35,   35);    //abt this mac
    target[5].set(595,  155);    //close about this mac window
    
    // targets for iHateMe
    /*target[0].set(430,  ofGetHeight()/2+45);        //I
    target[1].set(760,    ofGetHeight()/2+45);        //HateMe
    target[2].set(1154, 37);    //out of app    
    target[3].set(26,  12);      //osx apple menu
    target[4].set(163,  256);   //shut down menu item
    target[5].set(875,  357);    //SHUT DOWN NOW
     */
    
    // other targets
    //target[x].set(145, 187);    //force quit menu item
    //target[x].set(70,  8);      //xCode menu
    //target[x].set(81,  215);    //xCode quit
    //target[x].set(875, 331);    //xCode stop all tasks
    
    chaosDemo = false;
    simulateDemo = false; //should be true for iHateMe
    currTarget = 0;
  
    //mouse start position
    myMouse.x = ofGetWidth()/2;
    myMouse.y = ofGetHeight()-100;
    cout << "myMouse.x start: " << myMouse.x << endl;
    cout << "myMouse.y start: " << myMouse.y << endl;  
    
    //execute move to start position
    mouser.move(myMouse);
    
    ofTrueTypeFont::setGlobalDpi(72);
    font.loadFont ("courier.ttf", 60, true, true);
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    if (simulateDemo){ //if we're in "simulateDemo" mode
        event3 = "entered simulation demo";
        target[0].x = rect1_x + rect_size/2 + 50; //add 50 to compensate for screen x
        target[0].y = rect1_y + rect_size/2 + 44; //add 44 to compensate for screen y
        target[1].x = rect2_x + rect_size/2 + 50; //add 50 to compensate for screen x
        target[1].y = rect2_y + rect_size/2 + 44; //add 44 to compensate for screen y
        mouser.update();
        if(  !mouser.getMoving() ) { //we're NOT currently moving
            mouser.moveThenClick(target[currTarget]);
            currTarget++;
            cout << "current target: " << currTarget << endl;
            if (currTarget > 6){
                currTarget = 0;
                simulateDemo = false;
                cout << "end simulation" << endl;
                event = "end simulation";
            }
        }
    }
    
    if (chaosDemo){
        mouser.update();
        if(  !mouser.getMoving() ) { //we're NOT currently moving
            ofPoint randomSpot;
            randomSpot.x = round((ofRandom(800)));
            randomSpot.y = round((ofRandom(1000)));
            mouser.moveThenClick(randomSpot);
            chaosCounter++;
        }
        if(chaosCounter > 5){
            chaosDemo = false;
            cout << "end chaosDemo" << endl;
            event = "end chaosDemo";
        }
        
        /* zach's chaos
        myMouse.y = 200 + 200 * sin(ofGetElapsedTimef());
        myMouse.x = 200 + 200 * sin(ofGetElapsedTimef()/2);
        
        mouser.move(myMouse);
        
        if (ofRandom(0,1) > 0.99) {
            
            mouser.leftButtonDown(myMouse);
            mouser.leftButtonUp(myMouse);
        }*/
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(250);
    
    ofSetColor(10);
    //font.drawString("I hate me.", ofGetWidth()/2-160, ofGetHeight()/2-25);
    ofDrawBitmapString("use UP, DOWN, LEFT, RIGHT arrows to move mouse", 50,50);
    ofDrawBitmapString("hit '1' to left click // hold '1' and move to drag", 50,70);
    ofDrawBitmapString("hit '2' to right click", 50,90);
    ofDrawBitmapString("press 's' to enter simulation demo", 50,110);
    ofDrawBitmapString("press 'c' to chaos simulation demo", 50,130);
    ofDrawBitmapString("click me!", rect1_x, rect1_y-10);
    ofDrawBitmapString("click me!", rect2_x, rect2_y-10);
    ofDrawBitmapString(event, ofGetWidth()/2+30, 50);
    ofDrawBitmapString(event2, ofGetWidth()/2+30, 70);
    ofDrawBitmapString(event3, ofGetWidth()/2+30, 90);
    event3 = "";
    
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
        
        case    's':
            currTarget = 0;
            event = "entered simulate Demo mode";
            cout << "simulateDemo" << endl;
            simulateDemo = true;
            break;
        
        case    'c':
            chaosCounter = 0;
            event = "entered chaos Demo mode";
            cout << "chaosDemo" << endl;
            chaosDemo = true;
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

   
    event = "mouse moved oF App x: " + ofToString(x) + " y: " + ofToString(y); 
    event2 = "true to screen      x:" + ofToString(x + 50) + " y: " + ofToString(y + 44);
    //50 and 44 are default position of app on a 15" MBP
    
    cout << "oF app x: " << x << " y; " << y << endl;    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    if(button == 0){ 
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
    else if(button == 2){
        event = "right mouse button dragged x: " + ofToString(x) + " y: " + ofToString(y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    //left button pressed
    if(button == 0){ 
        event = "left mouse button pressed x: " + ofToString(x) + " y: " + ofToString(y);
        cout << event << endl;
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
        cout << event << endl;
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
        event = "left mouse button released x: " + ofToString(x) + " y: " + ofToString(y);
        //cout << "left mouse released x: " << x << " y: "<< y << endl;
        cout << event << endl;
        rect1L = false;
        rect2L = false;
        
    } else if(button == 2){
        event = "right mouse button released x: " + ofToString(x) + " y: " + ofToString(y);
        //cout << "right mouse released x: " << x << " y: "<< y << button << endl;
        cout << event << endl;
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