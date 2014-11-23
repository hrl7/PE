#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofEvents.h"

#define HOST "localhost" //ÈÄÅ‰ø°ÂÖà„Éõ„Çπ„Éà„ÅÆIP„ÇíË®≠ÂÆö
//„Éù„Éº„ÉàÁï™Âè∑„ÇíË®≠ÂÆö
#define PORT_receive 7000
#define PORT_send1 55000 //ÈÄÅ‰ø°ÂÖà„ÅÆ„Éù„Éº„ÉàÁï™Âè∑„ÇíË®≠ÂÆö
#define PORT_send22 8000 //ÈÄÅ‰ø°ÂÖà„ÅÆ„Éù„Éº„ÉàÁï™Âè∑„ÇíË®≠ÂÆö 

class testApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void dumpOSC(ofxOscMessage m); //OSC„É°„ÉÉ„Çª„Éº„Ç∏„ÇíÂá∫Âäõ
    void sendMotorAngle(int motorId, int degree);
    void sendVelocityToMotor(int speed);
    void receiveMotorAngleAndSendToGrassHopper();
    //////////////////////////////////Â§âÊï∞ÂÆ£Ë®Ä//////////////

    float p1_x;
    float p1_z;

    float pos_z;
    float pos_x;

    unsigned char serial1;

    //OSC„É°„ÉÉ„Çª„Éº„Ç∏„ÇíÂèó‰ø°„Åô„Çã„Ç§„É≥„Çπ„Çø„É≥„Çπ
    ofxOscReceiver    receiver;
    //OSC„É°„ÉÉ„Çª„Éº„Ç∏„ÅÆÈÄÅ‰ø°ËÄÖ
    ofxOscSender sender;

    //„Ç∑„É™„Ç¢„É´ÈÄö‰ø°„Ç§„É≥„Çπ„Çø„É≥„Çπ
    ofSerial serial;
};

