#include "ofApp.h"
ofMolecule m;
ofMolecule m2;
ofShader shader;
bool showStuff;



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
	//ofSetFrameRate(150);
	shader.load("shaders/shader");

	m = ofMolecule(ofVec2f(0,0),shader);
	//m2 = ofMolecule(ofVec2f(ofGetWidth(), ofGetHeight()), shader);

	camWidth = 640;
	camHeight = 480;

	vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(camWidth, camHeight);

	finder.setup("haarcascade_frontalface_default.xml");

	rgb.allocate(camWidth, camHeight);
	hsb.allocate(camWidth, camHeight);
	hue.allocate(camWidth, camHeight);
	sat.allocate(camWidth, camHeight);
	bri.allocate(camWidth, camHeight);
	filter1.allocate(camWidth, camHeight);
	filter2.allocate(camWidth, camHeight);
	finalImage.allocate(camWidth, camHeight);
	 
	 
}

//--------------------------------------------------------------
void ofApp::update(){
	
	count += 1;

	vidGrabber.update();

	if (vidGrabber.isFrameNew())
	{
		rgb.setFromPixels(vidGrabber.getPixels());
		hsb = rgb;
		hsb.convertRgbToHsv();
		hsb.convertToGrayscalePlanarImages(hue, sat, bri);

		int hueRange = 10;
		int satRange = 20;
		for (int i = 0; i < camWidth * camHeight; ++i) {
			filter1.getPixels()[i] = ofInRange(hue.getPixels()[i],
				findHue - hueRange,
				findHue + hueRange) ? 255 : 0;

			filter2.getPixels()[i] = ofInRange(sat.getPixels()[i],
				findSat - satRange,
				findSat + satRange) ? 255 : 0;
		}
		filter1.flagImageChanged();
		filter2.flagImageChanged();

		cvAnd(filter1.getCvImage(),
			filter2.getCvImage(),
			finalImage.getCvImage());
		finalImage.flagImageChanged();

		contours.findContours(finalImage,
			50,
			(camWidth*camHeight) / 3,
			3,
			false);

		finder.findHaarObjects(vidGrabber.getPixels());
	}
	if (finder.blobs.size() > 0) {
		m.update(finder.blobs[0].centroid);
	}

	

}

//--------------------------------------------------------------
void ofApp::draw(){

	/*if (count % 2 == 0) {
		ofSetColor(255, 255, 255, 3);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	//m.draw();
	//m2.draw();
	ofSetColor(ofColor().black);
	shader.begin();
	shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.15);
	shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.23);
	shader.setUniform1f("drag", ofRandom(.2, .98));
	shader.setUniform2f("mouse", ofVec2f(ofGetScreenWidth()/2, ofGetMouseY()));
	shader.setUniform3f("center", ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 1));
	ofDrawRectangle(ofGetScreenWidth()/2, 250, 1, ofGetScreenWidth(), ofGetScreenHeight() / 5);
	shader.end();*/

	if (showStuff) {
		ofSetColor(ofColor::white);
		vidGrabber.draw(0, 0, camWidth, camHeight);

		//hsb.draw(0, camHeight, 320, 240);

		//hue.draw(camWidth, 0, 320, 240);
		//sat.draw(camWidth, 240, 320, 240);
		//bri.draw(camWidth, 480, 320, 240);

		//filter1.draw(camWidth + 320, 0, 320, 240);
		//filter2.draw(camWidth + 320, 240, 320, 240);
		//finalImage.draw(0, camHeight, 320, 240);
	}
	contours.draw(0, 0);

	ofNoFill();
	//printf("size of blobs: %d", finder.blobs.size());
	if (finder.blobs.size() > 0) {
		m.draw(finder.blobs[0].centroid);
	}
	for (int i = 0; i < finder.blobs.size(); ++i) {
		ofDrawRectangle(finder.blobs[i].boundingRect);

	}
	ofFill();
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
	int mx = x % camWidth;
	int my = y % camHeight;

	findHue = hue.getPixels()[my*camWidth + mx];
	findSat = sat.getPixels()[my*camWidth + mx];
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
