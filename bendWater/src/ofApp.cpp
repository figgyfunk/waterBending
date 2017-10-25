#include "ofApp.h"
ofMolecule m;
ofMolecule m2;
ofShader shader;
ofShader shader2;


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
	drag = ofRandom(.6, .7);
	shad = shader;
	
}
void ofMolecule::update() {
	
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	
	frc = mouse - pos;
	ofVec2f frc2 = mouse - pos2;
	ofVec2f frc3 = mouse - pos3;

	float dist = frc.length();
	float dist2 = frc2.length();
	float dist3 = frc3.length();
	frc.normalize();
	frc2.normalize();
	frc3.normalize();

	vel *= drag;
	vel += frc * 0.6;
	vel2 *= (drag*.95);
	vel2 += frc2 * 0.7;
	vel3 *= (drag*.95);
	vel3 += frc3 * 0.75;
	shad.setUniform2f("mouse", mouse);
	
	pos += vel;
	pos2 += vel2;
	pos3 += vel3;

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
	shad.setUniform1f("drag", ofRandom(.2, .98));
	ofDrawSphere(pos.x, pos.y, 50);
	ofDrawSphere(pos2.x, pos2.y, 40);
	ofDrawSphere(pos3.x, pos3.y, 35);
	shad.end();
	

}
//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);
	ofEnableAlphaBlending();
	ofSetFrameRate(150);
	shader.load("shaders/shader");
	m = ofMolecule(ofVec2f(0,0),shader);
	m2 = ofMolecule(ofVec2f(ofGetWidth(), ofGetHeight()), shader);
	count = 0;
	 
	 
}

//--------------------------------------------------------------
void ofApp::update(){
	count += 1;
	m.update();
	m2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	if (count % 1 == 0) {
		ofSetColor(255, 255, 255, 3);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	m.draw();
	m2.draw();
	

	
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
