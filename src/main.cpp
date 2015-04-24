#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// 设置窗口大小和类型
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp()); // 6.2 动态内存分配：new 

}
