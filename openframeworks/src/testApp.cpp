#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
		
	ofEnableAlphaBlending(); //�����x(�A���t�@�`�����l��)��L���ɂ���
	ofSetCircleResolution(64); //�~�̉𑜓x��ݒ�
	ofSetFrameRate(120); //�t���[�����[�g�̐ݒ�


    //�w�肵���|�[�g�Őڑ�
    receiver.setup( PORT_receive );
	
	//ofBackground(0, 0, 0);

	//�w�肵��IP�A�h���X�ƃ|�[�g�ԍ��ŃT�[�o�[�ɐڑ�
    sender.setup( HOST, PORT_send1 );
	//sender2.setup( HOST, PORT_send2 );

	 // �V���A���ʐM�J�n
    serial.setup("COM4",9600);

	//ofBackground(200,200, 200); //�w�i�F�̐ݒ�
     
	//�ϐ�������
	p1_x=0;
	p1_z=0;
	pos_z= 0;
	pos_x= 0;
	serial1=0;
}

//--------------------------------------------------------------
void testApp::update(){

	
	

	
	

	 //���b�Z�[�W�̎󂯎��
	ofxOscMessage m;

    //���ݏ��ԑ҂���OSC���b�Z�[�W�����邩�m�F
    while( receiver.hasWaitingMessages() )
    {
        //���̃��b�Z�[�W���擾
        
        receiver.getNextMessage( &m );

		if ( m.getAddress() == "/p1_x" ){
			 p1_x = m.getArgAsFloat( 0 );

			 if(p1_x>0){
			// cout<<"0�ȏ�"<<endl;
			 
			 }
            // cout<<p1_x<<"�l"<<endl;
        }

		else if ( m.getAddress() == "/p1_z" ){
			
	
			p1_z = m.getArgAsFloat( 0 );
			
			if(p1_z>2){
				cout<<"2m�ȏ�"<<endl;
				pos_z=2;
				int numSent = serial.writeByte(1);
			 }

			else{
				pos_z=0;
				cout<<"2m�ȉ�"<<endl;
				int numSent = serial.writeByte(0);
			}

         
        }

	}

	
        //OSC���b�Z�[�W�����̂܂܃R���\�[���ɏo��
      //dumpOSC(m);

///////////////////////////////////////////////////////////////////////////

	  //���b�Z�[�W�̑��M

	
    //OSC���b�Z�[�W�̏���
   // ofxOscMessage m;
    //OSC�A�h���X�̎w��
    m.setAddress( "/motor_v1" );
    m.addFloatArg( pos_z );
 
    //���b�Z�[�W�𑗐M
    sender.sendMessage( m );

	 //OSC�A�h���X�̎w��
    m.setAddress( "/motor_v2" );
    m.addFloatArg( pos_z );
 
    //���b�Z�[�W�𑗐M
    sender.sendMessage( m );


  //noteoff
	/*
	//OSC�A�h���X�̎w��
    m.setAddress( "/midi/noteoff" );
    //OSC�����Ƃ��āA���݂̃}�E�X�̍��W(x, y)�𑗐M
    m.addIntArg( 1 );
    m.addIntArg( x/10 );
	m.addIntArg( y/10 );
    //���b�Z�[�W�𑗐M
    sender.sendMessage( m );
	*/
////////////////////////////////////////////////////////////////////////////////



}
//OSC���b�Z�[�W���R���\�[���ɏo�͂���֐�
void testApp::dumpOSC(ofxOscMessage m) {
    string msg_string;
    msg_string = m.getAddress();
    for (int i=0; i<m.getNumArgs(); i++ ) {
        msg_string += " ";
        if(m.getArgType(i) == OFXOSC_TYPE_INT32)
            msg_string += ofToString( m.getArgAsInt32(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            msg_string += ofToString( m.getArgAsFloat(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING)
            msg_string += m.getArgAsString(i);
    }
    cout << msg_string << endl;    
}
//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}