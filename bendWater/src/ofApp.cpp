#include "ofApp.h"
ofMolecule m;
ofMolecule m2;
ofShader shader;



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
void ofMolecule::update() {
	drag = ofRandom(.90, .99);
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	
	frc = mouse - pos;
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
void ofMolecule::draw() {
	ofSetColor(ofColor().black);

	shad.begin();
	shad.setUniform1f("timeValX", ofGetElapsedTimef() * 0.15);
	shad.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.23);
	shad.setUniform1f("drag", ofRandom(.96, .98));
	shad.setUniform3f("center", ofVec3f(pos.x, pos.y, 1));
	shad.setUniform2f("mouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	ofDrawSphere(pos.x, pos.y, 50);
	shad.end();
	

}
//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(false);
	//ofBackground(ofColor().white);
	ofEnableAlphaBlending();
	ofSetFrameRate(150);
	shader.load("shaders/shader");

	m = ofMolecule(ofVec2f(0,0),shader);
	//m2 = ofMolecule(ofVec2f(ofGetWidth(), ofGetHeight()), shader);

	 
	 
}

//--------------------------------------------------------------
void ofApp::update(){
	
	count += 1;
	m.update();
	//m2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	if (count % 2 == 0) {
		ofSetColor(255, 255, 255, 3);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	m.draw();
	//m2.draw();
	/*ofSetColor(ofColor().black);
	shader.begin();
	shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.15);
	shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.23);
	shader.setUniform1f("drag", ofRandom(.2, .98));
	shader.setUniform2f("mouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	shader.setUniform3f("center", ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 1));
	ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2, 1, 50);
	shader.end();*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
