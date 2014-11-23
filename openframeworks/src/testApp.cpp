#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

  ofEnableAlphaBlending(); //ÈÄèÊòéÂ∫¶(„Ç¢„É´„Éï„Ç°„ÉÅ„É£„É≥„Éç„É´)„ÇíÊúâÂäπ„Å´„Åô„Çã
  ofSetCircleResolution(64); //ÂÜÜ„ÅÆËß£ÂÉèÂ∫¶„ÇíË®≠ÂÆö
  ofSetFrameRate(120); //„Éï„É¨„Éº„É†„É¨„Éº„Éà„ÅÆË®≠ÂÆö

  //ÊåáÂÆö„Åó„Åü„Éù„Éº„Éà„ÅßÊé•Á∂ö
  receiver.setup( PORT_receive );

  //ÊåáÂÆö„Åó„ÅüIP„Ç¢„Éâ„É¨„Çπ„Å®„Éù„Éº„ÉàÁï™Âè∑„Åß„Çµ„Éº„Éê„Éº„Å´Êé•Á∂ö
  sender.setup( HOST, PORT_send1 );

  // „Ç∑„É™„Ç¢„É´ÈÄö‰ø°ÈñãÂßã
  vector<ofSerialDeviceInfo> devices = serial.getDeviceList();
  for (int i = 0; i < devices.size(); i++) {
    cout << i << " : " << devices[i].getDeviceName() << endl;
  }

  serial.setup(0,9600);
  //serial.setup("COM4",9600);

  //Â§âÊï∞ÂàùÊúüÂåñ
  p1_x=0;
  p1_z=0;
  pos_z= 0;
  pos_x= 0;
  serial1=0;
}

//--------------------------------------------------------------
void testApp::update(){

  //„É°„ÉÉ„Çª„Éº„Ç∏„ÅÆÂèó„ÅëÂèñ„Çä
  ofxOscMessage m;
  //ÁèæÂú®È†ÜÁï™ÂæÖ„Å°„ÅÆOSC„É°„ÉÉ„Çª„Éº„Ç∏„Åå„ÅÇ„Çã„ÅãÁ¢∫Ë™ç
  while( receiver.hasWaitingMessages()){
    receiver.getNextMessage( &m );

    if ( m.getAddress() == "/p1_x" ){
      p1_x = m.getArgAsFloat( 0 );

      if(p1_x>0){
        // cout<<"0‰ª•‰∏ä"<<endl;
      }
      // cout<<p1_x<<"ÂÄ§"<<endl;
    }
    else if ( m.getAddress() == "/p1_z" ){
      p1_z = m.getArgAsFloat( 0 );
      if(p1_z>2){
        cout<<"2m‰ª•‰∏ä"<<endl;
        pos_z=2;
        serial.writeByte(1);
      } else {  
        pos_z=0;
        cout<<"2m‰ª•‰∏ã"<<endl;
        serial.writeByte(0);
      }
    }
  }

    receiveMotorAngleAndSendToGrassHopper();
}

void testApp::receiveMotorAngleAndSendToGrassHopper(){
    int initCount = 0;
    int buf = 0;
    int motorId = 0;
    int position = 0;
    bool isFirst = true;
    while (serial.available() > 0) {
        buf = serial.readByte();
        
        if(buf == 0xff){
            initCount++;
        } else if(initCount != 2) {
            return ;
        } else {
            if(isFirst){
                position = (0x03 & buf) << 7;
                motorId = buf >> 3;
                //cout << "Position :" << static_cast<std::bitset<9> >(position) << endl;

                isFirst = false;
            } else {
                position = position | (buf >> 1);
                
                
                if(motorId > 0 && motorId < 5){
                    sendMotorAngle(motorId,position);
                    cout << "Motor : #" << motorId << "  Position : " << position << endl;

                }
            }
        }
    }
}

void testApp::sendMotorAngle(int motorId, int angle){
  ofxOscMessage m;
    m.setAddress( "/motor" + ofToString(motorId) );
    m.addFloatArg( angle );
    sender.sendMessage( m );
}

//OSC„É°„ÉÉ„Çª„Éº„Ç∏„Çí„Ç≥„É≥„ÇΩ„Éº„É´„Å´Âá∫Âäõ„Åô„ÇãÈñ¢Êï∞
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
