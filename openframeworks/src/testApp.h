#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofEvents.h"
 
#define HOST "localhost" //���M��z�X�g��IP��ݒ�
//�|�[�g�ԍ���ݒ�
#define PORT_receive 7000
#define PORT_send1 5001 //���M��̃|�[�g�ԍ���ݒ�
#define PORT_send22 8000 //���M��̃|�[�g�ԍ���ݒ� 



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
		void dumpOSC(ofxOscMessage m); //OSC���b�Z�[�W���o��

//////////////////////////////////�ϐ��錾//////////////

		float p1_x;
		float p1_z;

		float pos_z;
		float pos_x;

		
	unsigned char serial1;



private:

	 //OSC���b�Z�[�W����M����C���X�^���X
    ofxOscReceiver    receiver;
	 //OSC���b�Z�[�W�̑��M��
    ofxOscSender sender;
	//ofxOscSender sender2;

	//�V���A���ʐM�C���X�^���X
	ofSerial serial;
};

