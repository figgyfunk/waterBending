#include "ofApp.h"
ofMolecule m;
ofShader shader;
ofShader shader2;

ofMolecule::ofMolecule() {
	pos = ofVec2f(0, 0);
	vel = ofVec2f(0, 0);
	drag = ofRandom(.6, .7);
	
	
}
ofMolecule::ofMolecule(ofVec2f p, ofShader shader) {
	pos = p;
	vel = ofVec2f(0, 0);
	drag = ofRandom(.6, .7);
	shad = shader;
	
}
void ofMolecule::update() {
	
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	
	frc = mouse - pos;

	float dist = frc.length();
	frc.normalize();
	vel *= drag;
	vel += frc * 0.6;
	
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
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofDrawSphere(0, 0, 100);
	ofPopMatrix();
	shad.end();
	

}
//--------------------------------------------------------------
void ofApp::setup(){
	
	shader.load("shaders/shader");
	 //m = ofMolecule(ofVec2f(0,0),shader);
	 
	 
}

//--------------------------------------------------------------
void ofApp::update(){

	//m.update();
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//m.draw();

	
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
