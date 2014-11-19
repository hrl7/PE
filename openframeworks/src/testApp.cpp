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

  float angle1 =  360 * readMotorAngle() / 1600.;
  float angle2 =  360 * readMotorAngle() / 1600.;
  float angle3 =  360 * readMotorAngle() / 1600.;
  float angle4 =  360 * readMotorAngle() / 1600.;

  sendMotorDegrees(angle1,angle2,angle3,angle4);
}

/**
  this method may return error value : -1.
  */
int testApp::readMotorAngle(){
     int nBytesRead = 0;
    char bytesReadString[4];
    
    nBytesRead = 0;
    int nRead = 0;
    char bytesRead[3];
    unsigned char bytesReturned[3];
    
    memset(bytesReturned, 0, 3);
    memset(bytesReadString, 0, 4);
    
    
    while ((nRead = serial.readBytes(bytesReturned, 3)) > 0) {
        
        nBytesRead = nRead;
    };
    
    if (nBytesRead > 0) {
        
        memcpy(bytesReadString, bytesReturned, 3);
        string x = bytesReadString;
        cout << "Bytes :" << nBytesRead << endl << bytesReturned << endl;

    }
  }
  if(result != -1)cout << static_cast<std::bitset<8> >(result) << endl;
  return result;

}

void testApp::sendMotorDegrees(float angle1, float angle2, float angle3, float angle4){
  ofxOscMessage m;
  if(angle1 > 0){
    m.setAddress( "/motor_v1" );
    m.addFloatArg( angle1 );
    sender.sendMessage( m );
  }

  if(angle2 > 0){
    m.setAddress( "/motor_v2" );
    m.addFloatArg( angle2 );
    sender.sendMessage( m );
  }
  if(angle3 > 0){
    m.setAddress( "/motor_v3" );
    m.addFloatArg( angle3 );
    sender.sendMessage( m );
  }
  if(angle4 > 0){
    m.setAddress( "/motor_v4" );
    m.addFloatArg( angle4 );
    sender.sendMessage( m );
  }
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
