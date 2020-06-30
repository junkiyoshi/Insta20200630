#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->draw_MAGATAMA(glm::vec2(185, 200), 125, 0, false, false, false);
	this->draw_MAGATAMA(glm::vec2(495, 200), 125, 0, true, false, false);
	this->draw_MAGATAMA(glm::vec2(185, 520), 125, 0, true, true, false);
	this->draw_MAGATAMA(glm::vec2(495, 520), 125, 0, false, true, true);
}

//--------------------------------------------------------------
void ofApp::draw_MAGATAMA(glm::vec2 location, float radius, float rotate_deg, bool draw_handle, bool noise_deg, bool fill) {

	fill ? ofFill() : ofNoFill();

	float len = radius * 0.5522;
	float deg = 0;

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(rotate_deg);

	vector<glm::vec2> vertices;	
	vector<pair<glm::vec2, glm::vec2>> handle_list;

	vertices.push_back(glm::vec2(0, 0));
	deg = 180;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));
	
	vertices.push_back(glm::vec2(radius * 0.5, radius * -0.5));
	deg = 90;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius * -1));
	deg = 0;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len  * sin(deg * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius, 0));
	deg = 270;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * cos((deg + 180) * DEG_TO_RAD), len * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(0, radius));
	deg = 0;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * cos(deg * DEG_TO_RAD), len * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	vertices.push_back(glm::vec2(radius * -0.5, radius * 0.5));
	deg = 90;
	if (noise_deg) { deg += ofMap(ofNoise(glm::vec3(vertices.back(), ofGetFrameNum() * 0.008)), 0, 1, -90, 90); }
	handle_list.push_back(make_pair<glm::vec2, glm::vec2>(
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos(deg * DEG_TO_RAD), len * 0.5 * sin(deg * DEG_TO_RAD))),
		glm::vec2(vertices.back() + glm::vec2(len * 0.5 * cos((deg + 180) * DEG_TO_RAD), len * 0.5 * sin((deg + 180) * DEG_TO_RAD)))));

	ofSetColor(39);
	ofBeginShape();
	for (int i = 0; i < vertices.size(); i++) {

		int n = (i + 1) % vertices.size();

		ofVertex(vertices[i]);
		ofBezierVertex(handle_list[i].second, handle_list[n].first, vertices[n]);
	}

	ofNextContour(true);
	for (deg = 0; deg <= 360; deg += 5) {

		ofVertex(glm::vec2(0, radius * 0.5) + glm::vec2(radius * 0.1 * cos(deg * DEG_TO_RAD), radius * 0.1 * sin(deg * DEG_TO_RAD)));
	}
	ofEndShape(true);


	if (draw_handle) {

		ofSetColor(139);
		ofSetLineWidth(1);
		for (int i = 0; i < vertices.size(); i++) {

			ofDrawCircle(vertices[i], 4);

			ofDrawCircle(handle_list[i].first, 2);
			ofDrawCircle(handle_list[i].second, 2);

			ofDrawLine(vertices[i], handle_list[i].first);
			ofDrawLine(vertices[i], handle_list[i].second);
		}
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}