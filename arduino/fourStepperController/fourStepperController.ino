/**
 *  http://spinelify.blog.fc2.com/blog-entry-66.html
 */


#include <SPI.h>

#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_BUSY 9


#define MOTORS 4
#define DBG

int run_state = 0;

void setup()
{
  delay(1000);
  Serial.begin(9600);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  digitalWrite(PIN_SPI_SS, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  L6480_select_motor(0);
  /*
  while(!L6480_getstatus()){
   Serial.println("Communication Error");
   delay(1000);
   }
   */
  for(int i = 0; i< MOTORS; i++){
    L6480_select_motor(i);
    L6480_resetdevice(); //L6480リセット
    L6480_setup();  //L6480を設定
    L6480_getstatus();//フラグリセット
  }

  delay(1000);
}

void reset(){
    for(int i = 0; i< MOTORS; i++){
    L6480_select_motor(i);
    L6480_resetdevice(); //L6480リセット
    L6480_setup();  //L6480を設定
    L6480_getstatus();//フラグリセット
  }
}

void loop(){
  for(int i = 0; i< MOTORS; i++){
    L6480_getstatus();
/*
    Serial.print("#");
     Serial.print(i);
     Serial.print(" : ");
     Serial.print(L6480_getparam_status(),BIN);
     Serial.print(" config :");
     Serial.println(L6480_getparam_config(),HEX);
     //     Serial.print("  ");
    // Serial.println(L6480_getparam_config(),HEX);
  */   
    L6480_select_motor(i);
   send_pos(i,map(L6480_getparam_abspos() % 1600,0,1600,0,360));  
    
}
  delay(100);
}

long stepspeed(long k){//速度換算
  long val=k/0.01490116119;
  return val;
}

void L6480_setup(){
  L6480_setparam_acc(0x20); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6480_setparam_dec(0x20); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6480_setparam_maxspeed(0x45); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  L6480_setparam_minspeed(0x01); //[R, WS]最小速度default 0x0000 (1+12bit) (0.238*val+[step/s])
  L6480_setparam_fsspd(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  L6480_setparam_kvalhold(0x6f); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvalrun(0x6f); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvalacc(0x6f); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvaldec(0x6f); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

  L6480_setparam_intspd(0x408); //245[R, WH]逆起電力補償切替点速度default 0x0408 (14bit) (0.238*val[step/s])
  L6480_setparam_stslp(0x019); //[R, WH]逆起電力補償低速時勾配default 0x19 (8bit) (0.000015*val[% s/step])
  L6480_setparam_fnslpacc(0x65); //[R, WH]逆起電力補償高速時加速勾配default 0x29 (8bit) (0.000015*val[% s/step])
  L6480_setparam_fnslpdec(0x65); //[R, WH]逆起電力補償高速時減速勾配default 0x29 (8bit) (0.000015*val[% s/step])
  L6480_setparam_ktherm(0x1); //[R, WR]不明default 0x0 (4bit) (0.03125*val+1)
  L6480_setparam_ocdth(0x1f); //[R, WR]過電流しきい値default 0x8 (5bit) (31.25*val+31.25[mV])
  L6480_setparam_stallth(0x1f); //[R, WR]失速電流しきい値？default 0x10 (5bit) (31.25*val+31.25[mV])
  L6480_setparam_stepmood(0x07); //[R, WH]ステップモードdefault 0x07 (8bit)L6480_setparam_alareen(val); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
  L6480_setparam_alareen(0xde); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
  L6480_setparam_gatecfg1(0x000);//[R, WH]geta driver configuration //default 0x000(1+3+3+5bit)
  L6480_setparam_gatecfg2(0x00);//[R, WH]geta driver configuration //default 0x00(3+5bit)
  L6480_setparam_config(0x2a08); //[R, WH]各種設定default 0x2e88 (3+3+1+1+1+1+1+1+1+3bit)  
}

void serialEvent(){
  int buf = 0;
  int motorId = 0;
  int initCount = 0;
  int spd = 0;
  int resetCount = 0;
  boolean isFirst = true;
  while (Serial.available () > 0) {

    buf = Serial.read();
    if (buf == 0x00){
        resetCount++;
        if(resetCount > 3){
           reset();
          return; 
        }
    }else if (buf == 0xff) {
      initCount++;
    } 
    else if (initCount != 2) {
      return ;
    } 
    else {
      if (isFirst) {
        spd = (0x03 & buf) << 7;
        motorId = buf >> 3;
        //cout << "Position :" << static_cast<std::bitset<9> >(position) << endl;

        isFirst = false;
      } 
      else {
        spd = spd | (buf >> 1);
        if (motorId<4){
            L6480_select_motor(motorId);
           L6480_run(1,spd*32); 
        }
      }
    }
  }

}




/**
 * Send motor_id and position(0~1023) with Serial
 * | 0xff | 0xff | (Motor_id 0~f)0xX 0b00  (degree 9bit)0xXX 0b0 |
 */
void send_pos(int motor_id,int pos){
  int buf = motor_id << 3;
  buf = buf | pos >> 7;
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(buf);
  Serial.write(0xff & (pos << 1)); 
  delay(5);
    Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(buf);
  Serial.write(0xff & (pos << 1)); 
}
