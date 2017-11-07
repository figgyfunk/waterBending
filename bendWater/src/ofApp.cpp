#include "ofApp.h"
ofMolecule m;
ofMolecule m2;
ofShader shader;
bool showStuff;
ofVec2f currentPixel;
ofVec2f previousPixel;



ofMolecule::ofMolecule() {
	pos = ofVec2f(0, 0);
	pos2 = ofVec2f(0, 0);
	pos3 = ofVec2f(0, 0);
	vel = ofVec2f(0, 0);
	drag = ofRandom(.6, .7);
	vel2 = ofVec2f(0, 0);
	vel3 = ofVec2f(0, 0);
	
	
}
ofMolecule::ofMolecule(ofVec2f p, ofShader shader) {
	pos = p;
	pos2 = p;
	pos3 = p;
	vel = ofVec2f(0, 0);
	vel2 = ofVec2f(0, 0);
	vel3 = ofVec2f(0, 0);
	
	shad = shader;
	
}
void ofMolecule::update(ofVec2f blobCenter) {
	drag = ofRandom(.90, .99);
	
	frc = blobCenter - pos;
	float dist = frc.length();
	frc.normalize();
	vel *= drag;
	vel += frc * 0.4;
	pos += vel;
	

	//keep in screen
	if (pos.x > ofGetWidth()) {
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}
	else if (pos.x < 0) {
		pos.x = 0;
		vel.x *= -1.0;
	}
	if (pos.y > ofGetHeight()) {
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1.0;
	}
}
void ofMolecule::draw(ofVec2f blobCenter) {
	ofSetColor(ofColor().black);

	shad.begin();
	shad.setUniform1f("timeValX", ofGetElapsedTimef() * 0.15);
	shad.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.23);
	shad.setUniform1f("drag", ofRandom(.96, .98));
	shad.setUniform3f("center", ofVec3f(pos.x, pos.y, 1));
	shad.setUniform2f("mouse", blobCenter);
	ofDrawSphere(pos.x, pos.y, 50);
	shad.end();
	

}
//--------------------------------------------------------------
void ofApp::setup(){
	showStuff = true;
	ofSetBackgroundAuto(false);
	ofBackground(ofColor().white);
	ofEnableAlphaBlending();
	ofSetFrameRate(150);
	shader.load("shaders/shader");

	m = ofMolecule(ofVec2f(0,0),shader);
	//m2 = ofMolecule(ofVec2f(ofGetWidth(), ofGetHeight()), shader);

	camWidth = 640;
	camHeight = 480;

	vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(camWidth, camHeight);

	currentPixel = ofVec2f(0, 0);
	previousPixel = currentPixel;
	 
}

//--------------------------------------------------------------
void ofApp::update(){
	
	count += 1;

	vidGrabber.update();

	if (vidGrabber.isFrameNew())
	{
		float max = 0; 
		ofPixels pixels = vidGrabber.getPixels();
		for (int i = 0; i < camWidth; i++)
		{
			for (int j = 0; j < camHeight; j++)
			{
				float bright = pixels.getColor(i, j).getBrightness();
				if (bright > max)
				{
					currentPixel = ofVec2f(i, j);
					max = bright;
				}
			}
		}


		
	}
	m.update(currentPixel);
	

	

}

//--------------------------------------------------------------
void ofApp::draw(){

	if (count % 2 == 0) {
		ofSetColor(255, 255, 255, 3);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	m.draw(currentPixel);
	ofSetColor(ofColor().white);
	ofCircle(previousPixel.x, previousPixel.y, 5);
	ofSetColor(ofColor().red);
	ofCircle(currentPixel.x, currentPixel.y, 5);
	previousPixel = currentPixel;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
		showStuff = !showStuff;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
