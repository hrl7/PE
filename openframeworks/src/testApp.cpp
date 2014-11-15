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
  serial.setup("COM4",9600);

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
        int numSent = serial.writeByte(1);
      } else {  
        pos_z=0;
        cout<<"2m以下"<<endl;
        int numSent = serial.writeByte(0);
      }
    }
  }

  //メッセージの送信

  m.setAddress( "/motor_v1" );
  m.addFloatArg( pos_z );
  sender.sendMessage( m );

  m.setAddress( "/motor_v2" );
  m.addFloatArg( pos_z );
  sender.sendMessage( m );
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
