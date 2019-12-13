#include "ofApp.h"
#include "ctype.h"
#include "ofxQR.h"

void ofApp::setup()
{
//    shader.load("shadersGL3/shader");
    ofSetVerticalSync(true);

    ofEnableNormalizedTexCoords();
    
    ofSetSmoothLighting(true);
    
//    ofEnableLighting();
//    ofEnableDepthTest();
//           light.setup();
//           light.enable();
//           light.setPosition(-100,100,200);
    
    material.setShininess(120);
//    material.setSpecularColor(ofColor(0,0,0));
//    material.setDiffuseColor(ofColor(0,0,0));
//    material.setAmbientColor(ofColor(0,0,0));
    
    material.setAmbientColor(ofColor::mintCream);
    ofFloatColor ambient;
    
    
//    -----------------
    text = "https://google.com";

        generate();
    //    labels = {
    //        "   LOW  ",
    //        " MEDIUM ",
    //        "QUARTILE",
    //        "  HIGH  "
    //    };
    
    // Create a QR Code.
//    code = ofx::QRCode("https://www.google.com");

    // ofBox uses texture coordinates from 0-1, so you can load whatever
    // sized images you want and still use them to texture your box
    // but we have to explicitly normalize our tex coords here
    ofEnableNormalizedTexCoords();
//    img.load ("frogwithsnails.jpg");
    sfSans.load("SF-Pro-Text-Regular.otf",21);
    sfSans50.load("SF-Pro-Text-Regular.otf",50);

    ofBackgroundGradient(250, 200);
    
    img.load("border.png");
}


void ofApp::update()
{
    float t = ofGetElapsedTimef();

    rotation += glm::vec3(ofSignedNoise(t, 0, 0),
                          ofSignedNoise(0, t, 0),
                          ofSignedNoise(0, 0, t));
    
}

void ofApp::draw()
{
    ofBackground(250,0);
    
    //---USER INPUT INTERFACE-----------
//    ofBackground(0,20,30,40);
    
//    shader.begin();
//    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//    shader.end();
//    
//    img.draw(0,0,ofGetWidth(), ofGetHeight());
        
    //    img.draw(ofGetWidth(), ofGetHeight());
    //    workSans.drawString("Hello", 100, 100);

        ofSetColor(ofColor::blueSteel);
        sfSans.drawString("Enter free text or URL: " + text, 50, 40);
        
    //    ofNoFill();
    img.draw(20,10,ofGetWidth()/1.05,50);
//        ofSetLineWidth (2);
//        ofSetColor(255,255,255,100);
//        ofDrawRectangle(20,10,ofGetWidth()/1.05,50);
    //    ofNoFill();
    //    ofSetColor(ofColor::blueViolet);
    //    ofRectangle myRect;
    //    myRect.x = 10;
    //    myRect.y = 10;
    //    myRect.width = 700;
    //    myRect.height = 100;
    //    ofDrawRectRounded(myRect, 64);


        //       std::stringstream ss;
        //
        //    ss << "KEYBOARD INPUT" << std::endl << std::endl;
        //       ss << "-/= to set the number of pixels per module: " << numPixelsPerModule << std::endl;
        //       ss << "[/] to set the number of border modules: " << numBorderModules << std::endl;
        //       ss << "Right arrow to change the ECC: " << ofx::QRCode::to_string(ecc) << std::endl;
        //
        //       ss << std::endl;
        //    ss << " Enter free text or URL: " << std::endl << std::endl << text << std::endl;;
        //
        //       ofDrawBitmapStringHighlight(ss.str(), glm::vec3(10, 16, 0));




//--CUBES-----------------------
    float movementSpeed = .025;
    float cloudSize = ofGetWidth() / 3;
    float maxCubeSize = 100;
    float spacing = 25;
    int cubeCount = 50;
    
//    ofEnableLighting();
//    cam.begin();
//
//    enable material;
//    material.begin();


    for(int i = 0; i < cubeCount; i++)
    {
        ofPushMatrix();
        ofSetColor(255);
        
        
        float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
        ofVec3f pos(
            ofSignedNoise(t, 0, 0),
            ofSignedNoise(0, t, 0),
            ofSignedNoise(0, 0, t));

        float cubeSize = maxCubeSize * ofNoise(pos.x, pos.y, pos.z);

        pos *= cloudSize;
        ofTranslate(pos);
        ofRotateXDeg(pos.x);
        ofRotateYDeg(pos.y);
        ofRotateZDeg(pos.z);

        code.getTexture().bind();
        ofDrawBox(code.getWidth());
        code.getTexture().unbind();

        ofPopMatrix();

    }
    
//    disable matrial;
//    material.end();

//    cam.end();

//    ofDisableLighting();
  
//    ofBackgroundGradient(ofColor::blueSteel, ofColor::blueViolet);
}


void ofApp::keyPressed(int key)
{
    bool regenerate = true;

    if (key == '-')
    {
        numPixelsPerModule = std::max(numPixelsPerModule - 1, std::size_t(1));
    }
    else if (key == '=')
    {
        numPixelsPerModule = std::min(numPixelsPerModule + 1, std::numeric_limits<std::size_t>::max());
    }
    else if (key == '[')
    {
        numBorderModules = std::max(numBorderModules - 1, std::size_t(1));
    }
    else if (key == ']')
    {
        numBorderModules = std::min(numBorderModules + 1, std::numeric_limits<std::size_t>::max());
    }
    else if (key == OF_KEY_RIGHT)
    {
        switch (ecc)
        {
            case ofx::QRCode::ECC::LOW:
                ecc = ofx::QRCode::ECC::MEDIUM;
                break;
            case ofx::QRCode::ECC::MEDIUM:
                ecc = ofx::QRCode::ECC::QUARTILE;
                break;
            case ofx::QRCode::ECC::QUARTILE:
                ecc = ofx::QRCode::ECC::HIGH;
                break;
            case ofx::QRCode::ECC::HIGH:
                ecc = ofx::QRCode::ECC::LOW;
                break;
        }
    }
    else if (key == OF_KEY_RETURN)
    {
        text += '\n';
    }
    else if (key == OF_KEY_BACKSPACE || key == OF_KEY_BACKSPACE)
    {
        if (!text.empty())
            text.erase(text.end() - 1);
    }
    else if (key > 0 && key < 255)
    {
        text += char(key);
    }
    else regenerate = false;

    if (regenerate)
    {
        generate();
    }
}

//--------------------------------------------------------------

//void ofApp::keyPressed(int key){
//    if(key == OF_KEY_RETURN && inputText.length() > 0) {
//            if(key == OF_KEY_RETURN && inputText.length() > 0) {
//                ofx::QRCode code = ofx::QRCode(inputText);
//                std::string str2 = inputText;
//                tuple<ofx::QRCode, string> tup(code, str2);
//                codes[insertNewQRIndex].swap(tup);
//                insertNewQRIndex = insertNewQRIndex < (totalQRCodeNumber - 1) ? insertNewQRIndex + 1 : 0;
//                inputText = "";
//            } else if(key == OF_KEY_BACKSPACE) {
//                if (inputText.size () > 0)  inputText.resize (inputText.size () - 1);
//            } else if(isalnum(key) || ispunct(key) || key == ' ') {
//                inputText += key;
//            }
//        }
//
//}

void ofApp::generate()
{
    code.setText(text, ecc);
    code.setNumBorderModules(numBorderModules);
    code.setNumPixelsPerModule(numPixelsPerModule);
}
