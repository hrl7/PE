#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

  ofEnableAlphaBlending(); //透明度(アルファチャンネル)を有効にする
  ofSetCircleResolution(64); //円の解像度を設定
  ofSetFrameRate(120); //フレームレートの設定

  //指定したポートで接続
  receiver.setup( PORT_receive );

  //指定したIPアドレスとポート番号でサーバーに接続
  sender.setup( HOST, PORT_send1 );

  // シリアル通信開始
  vector<ofSerialDeviceInfo> devices = serial.getDeviceList();
  for (int i = 0; i < devices.size(); i++) {
    cout << i << " : " << devices[i].getDeviceName() << endl;
  }

  serial.setup(0,9600);
  //serial.setup("COM4",9600);

  //変数初期化
  p1_x=0;
  p1_z=0;
  pos_z= 0;
  pos_x= 0;
  serial1=0;
}

//--------------------------------------------------------------
void testApp::update(){
  //メッセージの受け取り
  ofxOscMessage m;
  //現在順番待ちのOSCメッセージがあるか確認
  while( receiver.hasWaitingMessages()){
    receiver.getNextMessage( &m );

    if ( m.getAddress() == "/p1_x" ){
      p1_x = m.getArgAsFloat( 0 );

      if(p1_x>0){
        // cout<<"0以上"<<endl;
      }
      // cout<<p1_x<<"値"<<endl;
    }
    else if ( m.getAddress() == "/p1_z" ){
      p1_z = m.getArgAsFloat( 0 );
      if(p1_z>2){
        cout<<"2m以上"<<endl;
        pos_z=2;
        serial.writeByte(1);
      } else {  
        pos_z=0;
        cout<<"2m以下"<<endl;
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
  int result = -1;

  while ( serial.available() > 3 ) {
    int i=4;
    while(i > 0){
      int buf = serial.readByte();
      if(buf != 0xff){
        result = result << 8 | buf;
        i--;
      } else {
        break;
      }
    }
  }
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

//OSCメッセージをコンソールに出力する関数
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
