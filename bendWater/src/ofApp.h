#pragma once

#include "ofMain.h"
class ofMolecule {

public:
	ofMolecule();
	ofMolecule(ofVec2f p);
	void update();
	void draw();
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f frc;
	float drag;

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
		
		vector <ofMolecule> m;

};


