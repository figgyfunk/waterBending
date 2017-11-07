#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"

class ofMolecule {
public:
	
	ofMolecule();
	ofMolecule(ofVec2f p, ofShader shader);
	void update(ofVec2f blobCenter);
	void draw(ofVec2f blobCenter);

	ofVec2f vel; 
	ofVec2f pos; 
	ofVec2f frc; 
	ofVec2f pos2;
	ofVec2f pos3;
	float drag;
	ofShader shad;
	float mouseX; 
	float mouseY;
	ofVec2f vel2; 
	ofVec2f vel3;


};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofShader shader;
		int count;

		int camWidth, camHeight;

		ofVideoGrabber vidGrabber;

		
};
