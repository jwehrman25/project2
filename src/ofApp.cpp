#include "ofApp.h"

glm::mat4 buildMatrix(glm::vec3 trans, float rot, glm::vec3 scale)
{
	using glm::mat4;
	mat4 translation = glm::translate(trans);
	mat4 rotation = glm::rotate(rot, glm::vec3(0.0, 0.0, 1.0));
	mat4 scaler = glm::scale(scale);
	return translation * rotation * scaler;
}

glm::mat4 buildViewMatrix(CameraData cam) 
{
	using namespace glm;
	return inverse(buildMatrix(cam.pos, cam.fov, vec3(1, 1, 1)));
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();

	mesh.load("JWPoly.ply");
	mesh2.load("MRPoly.ply");
	shader.load("mesh.vert", "texture.frag");
	cam.pos = glm::vec3(0, 0, 0);
	cam.fov = glm::radians(90.0f);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (forward) 
	{
		cam.pos = cam.pos - glm::vec3(0, 0, 0.05);
	}
	if (backward)
	{
		cam.pos = cam.pos + glm::vec3(0, 0, 0.05);
	}
	if (up) 
	{
		cam.pos = cam.pos + glm::vec3(0, 0.05, 0);
	}
	if (down)
	{
		cam.pos = cam.pos - glm::vec3(0, 0.05, 0);
	}
	if (left) 
	{
		cam.pos = cam.pos - glm::vec3(0.05, 0, 0);
	}
	if (right)
	{
		cam.pos = cam.pos + glm::vec3(0.05, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;
	float aspect = 1024.0f / 768.0f;

	mat4 model = rotate(1.0f, vec3(1, 1, 1)) * scale(vec3(1, 1, 1));
	mat4 view = inverse(translate(cam.pos));

	mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);

	mat4 mvp = proj * view * model;

	shader.begin();
	shader.setUniformMatrix4f("mvp", mvp);
	mesh.draw();
	mesh2.draw();
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		up = true;
	}
	if (key == OF_KEY_DOWN) {
		down = true;
	}
	if (key == 'a') {
		left = true;
	}
	if (key == 'd') {
		right = true;
	}
	if (key == 'w') {
		forward = true;
	}
	if (key == 's') {
		backward = true;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_UP) {
		up = false;
	}
	if (key == OF_KEY_DOWN) {
		down = false;
	}
	if (key == 'a') {
		left = false;
	}
	if (key == 'd') {
		right = false;
	}
	if (key == 'w') {
		forward = false;
	}
	if (key == 's') {
		backward = false;
	}

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
