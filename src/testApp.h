#pragma once

#include "ofMain.h"
#include "mouseControl.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    mouseControl mouser;
    ofPoint myMouse;
    
    int myMouseX;
    int myMouseY;
        
    bool    rect1;
    bool    rect2;
    
    float   rect_size;
    float   rect1_x, rect1_y;
    float   rect2_x, rect2_y;
    
    ofColor on;
    ofColor off;
		
};
