#pragma once

#include "ofMain.h"
#include "ofxQR.h"
#include "ofTrueTypeFont.h"

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void generate();

    std::string text;
    
    ofTrueTypeFont myFont;
    ofTrueTypeFont sfSans;
    ofTrueTypeFont sfSans50;

    ofBoxPrimitive cube;
    ofVboMesh cubeSides[ofBoxPrimitive::SIDES_TOTAL];
    
    ;    string currentQRText;
    std::vector<tuple<ofx::QRCode, string>> codes;
           
    int insertNewQRIndex;
    int totalQRCodeNumber;
    bool isPaused;
    
    ofx::QRCode code;
    
    glm::vec3 rotation;
    
    ofEasyCam cam;
    
    ofImage img;
    
    std::size_t numPixelsPerModule = ofx::QRCode::DEFAULT_NUM_PIXELS_PER_MODULE;
    std::size_t numBorderModules = ofx::QRCode::DEFAULT_NUM_BORDER_MODULES;

    ofx::QRCode::ECC ecc = ofx::QRCode::ECC::LOW;
    
};
