#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 0;
	for (int x = 90; x < ofGetWindowWidth(); x += 180) {

		for (int y = 90; y < ofGetWindowHeight(); y += 180) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

			ofColor color;
			for (int radius = 30; radius < 75; radius += 3) {

				ofMesh face, line;
				line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

				int start_deg = ofMap(ofNoise(noise_seed.x, radius * 0.02 + ofGetFrameNum() * 0.01), 0, 1, -360, 360);
				int deg_len = 30;

				color.setHsb((int)(ofMap(radius, 30, 75, 0, 255) + span) % 255, 255, 255);

				face.addVertex(glm::vec3());
				face.addColor(ofColor(color, 128));
				for (int deg = start_deg; deg < start_deg + deg_len; deg += 1) {

					face.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					face.addColor(ofColor(color, 64));

					line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					line.addColor(color);

					if (deg != start_deg) {

						face.addIndex(0);
						face.addIndex(face.getNumVertices() - 1);
						face.addIndex(face.getNumVertices() - 2);

						line.addIndex(line.getNumVertices() - 1);
						line.addIndex(line.getNumVertices() - 2);
					}
				}

				face.draw();
				line.draw();
			}

			ofPopMatrix();
			span += 20;
		}
	}
	
	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}