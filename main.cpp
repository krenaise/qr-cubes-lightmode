#include "ofApp.h"


int main()
{
    ofRunApp(new ofApp());
    
    ofSetupOpenGL(1024,768, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
