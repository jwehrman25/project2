#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	glEnable(GL_CULL_FACE);

	mesh.load("JWPoly.ply");
	mesh2.load("MRPoly.ply");

	reloadShaders();

	vbo.setMesh(mesh, GL_STATIC_DRAW);
	vbo2.setMesh(mesh2, GL_STATIC_DRAW);

	cam.pos = glm::vec3(0, 0, 0);
	cam.fov = glm::radians(90.0f);
}

void ofApp::reloadShaders()
{
	shader.load("mesh.vert", "texture.frag");
	needsReload = false;
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	using namespace glm;
	cameraHead += dx;
    cameraPitch += dy;
	if (cameraPitch > radians(90.0f)) {
		cameraPitch = radians(89.9f);
	}
	if (cameraPitch < radians(-90.0f)) {
		cameraPitch = radians(-89.9f);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (needsReload) {
		reloadShaders();
	}
	using namespace glm;

	vec3 velocityWorldSpace{  mat3( rotate(-cameraPitch, vec3(1,0,0)) * rotate(-cameraHead, vec3(0,1,0))) * velocity };
	if (cameraPitch < 0 && velocityWorldSpace.y < 0) {
		velocityWorldSpace.y = (-1 * velocityWorldSpace.y);
	}
	if (cameraPitch > 0 && velocityWorldSpace.y > 0) {
		velocityWorldSpace.y = (-1 * velocityWorldSpace.y);
	}

	float dt{ static_cast<float>(ofGetLastFrameTime()) };
	
	position += velocityWorldSpace * dt;

}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;
	float width{ static_cast<float>(ofGetViewportWidth()) };
	float height{ static_cast<float>(ofGetViewportHeight()) };
	float aspect{ width / height };

	mat4 model = rotate(0.0f, vec3(1, 1, 1)) * scale(vec3(1, 1, 1));

	mat4 view = (rotate(cameraPitch, vec3(1, 0, 0)) * rotate(cameraHead, vec3(0, 1, 0))) * translate(-position);

	mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);

	mat4 mvp = proj * view * model;
	float count = 1.0f;
	mat4 mv = view * model;

	shader.begin();
	shader.setUniformMatrix4f("mvp", mvp);
	shader.setUniformMatrix4f("mv", mv);
	shader.setUniform1f("count", count);
	for (int i = 0; i < 100; i++) {

		/*
		 * Drawing 10,000 of the meshes would cause the camera movement to lag,
		 * making the switch to drawing VBOs does not noticable cause the camera to lag whatsoever.
		 */
		//mesh.draw();
		//mesh2.draw();
		vbo.drawElements(GL_TRIANGLES, vbo.getNumIndices());
		vbo2.drawElements(GL_TRIANGLES, vbo2.getNumIndices());
		count++;
		shader.setUniform1f("count", count);
	}
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		velocity.y = 1;
	}
	if (key == OF_KEY_DOWN) {
		velocity.y = -1;
	}
	if (key == 'w')
	{
		velocity.z = -1;
	}
	else if (key == 's')
	{
		velocity.z = 1;
	}
	else if (key == 'a')
	{
		velocity.x = -1;
	}
	else if (key == 'd')
	{
		velocity.x = 1;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'w' || key == 's')
	{
		velocity.z = 0;
	}
	else if (key == 'a' || key == 'd')
	{
		velocity.x = 0;
	}
	else if (key == OF_KEY_UP || key == OF_KEY_DOWN) {
		velocity.y = 0;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (prevX != 0 && prevY != 0)
	{
		// Update camera rotation based on mouse movement
		updateCameraRotation(mouseSensitivity * (x - prevX), mouseSensitivity * (y - prevY));
	}

	// Remember where the mouse was this frame.
	prevX = x;
	prevY = y;
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
