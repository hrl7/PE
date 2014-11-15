#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofEvents.h"

#define HOST "localhost" //送信先ホストのIPを設定
//ポート番号を設定
#define PORT_receive 7000
#define PORT_send1 5001 //送信先のポート番号を設定
#define PORT_send22 8000 //送信先のポート番号を設定 

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
    void dumpOSC(ofxOscMessage m); //OSCメッセージを出力

    //////////////////////////////////変数宣言//////////////

    float p1_x;
    float p1_z;

    float pos_z;
    float pos_x;

    unsigned char serial1;

  private:
    //OSCメッセージを受信するインスタンス
    ofxOscReceiver    receiver;
    //OSCメッセージの送信者
    ofxOscSender sender;

    //シリアル通信インスタンス
    ofSerial serial;
};

