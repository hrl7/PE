/**
 * ControlP5 Knob
 *
 *
 * find a list of public methods available for the Knob Controller
 * at the bottom of this sketch.
 *
 * by Andreas Schlegel, 2012
 * www.sojamo.de/libraries/controlp5
 *
 */

import controlP5.*;
import processing.serial.*;
Serial port;

ControlP5 cp5;

int myColorBackground = color(0, 0, 0);
int knobValue = 100;

Knob[] indicator = new Knob[4];
Slider[] speedController = new Slider[4];
void setup() {
  String name = Serial.list()[5];
  println(name);
  port = new Serial(this, name, 9600);
  size(700, 400);
  smooth();
  noStroke();

  cp5 = new ControlP5(this);

  for (int i=0;i<4;i++) {
    indicator[i] = genMotorIndicator(i*140, 20, "angle_motor"+i);
    speedController[i] = genSpeedController(i*140, 250, "speed_motor"+i);
  }
}

Slider genSpeedController(int x, int y, String name) {
  Slider sl = cp5.addSlider(name)
    .setPosition(x, y)
      .setRange(0, 65536/4)
        ;  
  cp5.getController(name).getValueLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);
  cp5.getController(name).getCaptionLabel().align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
  return sl;
}

Knob genMotorIndicator(int x, int y, String name) {
  return  cp5.addKnob(name)
    .setRange(0, 360)
      .setValue(0)
        .setStartAngle(-PI*0.5)
          .setAngleRange(PI*2)
            .setPosition(x, y)
              .setRadius(50)
                .setDragDirection(Knob.VERTICAL)
                  ;
}

void draw() {
  background(myColorBackground);
  fill(knobValue);
  rect(0, height/2, width, height/2);
  readMotorPosition();
}

void sendSpeed(int motor_id, int speed){
  speed = speed/32;
  int buf = motor_id << 3;
  buf = buf | speed >> 7;
  port.write(0xff);
  port.write(0xff);
  port.write(buf);
  port.write(0xff & (speed << 1)); 
  delay(10);
    port.write(0xff);
  port.write(0xff);
  port.write(buf);
  port.write(0xff & (speed << 1)); 
}

void speed_motor0(int val){
  sendSpeed(0,val);

}
void speed_motor1(int val){
  sendSpeed(1,val);
}
void speed_motor2(int val){
  sendSpeed(2,val);
}
void speed_motor3(int val){
  sendSpeed(3,val);
}
void keyPressed() {
}
void slider(float theColor) {

  println("a slider event. setting background to "+theColor);
}


void readMotorPosition() {
  int buf = 0;
  int motorId = 0;
  int initCount = 0;
  int position = 0;
  boolean isFirst = true;
  //println(port.available());
  while (port.available () > 0) {

    buf = port.read();
    if (buf == 0xff) {
      initCount++;
    } 
    else if (initCount != 2) {
      return ;
    } 
    else {
      if (isFirst) {
        position = (0x03 & buf) << 7;
        motorId = buf >> 3;
        //cout << "Position :" << static_cast<std::bitset<9> >(position) << endl;

        isFirst = false;
      } 
      else {
        position = position | (buf >> 1);
        if (motorId<4)indicator[motorId].setValue(position%360);
         print(motorId);
         print(" : ");
        println(position);
      }
    }
  }
}
/*
a list of all methods available for the Knob Controller
 use ControlP5.printPublicMethodsFor(Knob.class);
 to print the following list into the console.
 
 You can find further details about class Knob in the javadoc.
 
 Format:
 ClassName : returnType methodName(parameter type)
 
 controlP5.Knob : Knob setConstrained(boolean) 
 controlP5.Knob : Knob setDragDirection(int) 
 controlP5.Knob : Knob setMax(float) 
 controlP5.Knob : Knob setMin(float) 
 controlP5.Knob : Knob setNumberOfTickMarks(int) 
 controlP5.Knob : Knob setRadius(float) 
 controlP5.Knob : Knob setRange(float) 
 controlP5.Knob : Knob setResolution(float) 
 controlP5.Knob : Knob setScrollSensitivity(float) 
 controlP5.Knob : Knob setSensitivity(float) 
 controlP5.Knob : Knob setShowRange(boolean) 
 controlP5.Knob : Knob setStartAngle(float) 
 controlP5.Knob : Knob setTickMarkLength(int) 
 controlP5.Knob : Knob setTickMarkWeight(float) 
 controlP5.Knob : Knob setValue(float) 
 controlP5.Knob : Knob setViewStyle(int) 
 controlP5.Knob : Knob showTickMarks(boolean) 
 controlP5.Knob : Knob shuffle() 
 controlP5.Knob : Knob snapToTickMarks(boolean) 
 controlP5.Knob : Knob update() 
 controlP5.Knob : boolean isConstrained() 
 controlP5.Knob : boolean isShowRange() 
 controlP5.Knob : boolean isShowTickMarks() 
 controlP5.Knob : float getAngle() 
 controlP5.Knob : float getRadius() 
 controlP5.Knob : float getRange() 
 controlP5.Knob : float getResolution() 
 controlP5.Knob : float getStartAngle() 
 controlP5.Knob : float getTickMarkWeight() 
 controlP5.Knob : float getValue() 
 controlP5.Knob : int getDragDirection() 
 controlP5.Knob : int getNumberOfTickMarks() 
 controlP5.Knob : int getTickMarkLength() 
 controlP5.Knob : int getViewStyle() 
 controlP5.Controller : CColor getColor() 
 controlP5.Controller : ControlBehavior getBehavior() 
 controlP5.Controller : ControlWindow getControlWindow() 
 controlP5.Controller : ControlWindow getWindow() 
 controlP5.Controller : ControllerProperty getProperty(String) 
 controlP5.Controller : ControllerProperty getProperty(String, String) 
 controlP5.Controller : Knob addCallback(CallbackListener) 
 controlP5.Controller : Knob addListener(ControlListener) 
 controlP5.Controller : Knob bringToFront() 
 controlP5.Controller : Knob bringToFront(ControllerInterface) 
 controlP5.Controller : Knob hide() 
 controlP5.Controller : Knob linebreak() 
 controlP5.Controller : Knob listen(boolean) 
 controlP5.Controller : Knob lock() 
 controlP5.Controller : Knob plugTo(Object) 
 controlP5.Controller : Knob plugTo(Object, String) 
 controlP5.Controller : Knob plugTo(Object[]) 
 controlP5.Controller : Knob plugTo(Object[], String) 
 controlP5.Controller : Knob registerProperty(String) 
 controlP5.Controller : Knob registerProperty(String, String) 
 controlP5.Controller : Knob registerTooltip(String) 
 controlP5.Controller : Knob removeBehavior() 
 controlP5.Controller : Knob removeCallback() 
 controlP5.Controller : Knob removeCallback(CallbackListener) 
 controlP5.Controller : Knob removeListener(ControlListener) 
 controlP5.Controller : Knob removeProperty(String) 
 controlP5.Controller : Knob removeProperty(String, String) 
 controlP5.Controller : Knob setArrayValue(float[]) 
 controlP5.Controller : Knob setArrayValue(int, float) 
 controlP5.Controller : Knob setBehavior(ControlBehavior) 
 controlP5.Controller : Knob setBroadcast(boolean) 
 controlP5.Controller : Knob setCaptionLabel(String) 
 controlP5.Controller : Knob setColor(CColor) 
 controlP5.Controller : Knob setColorActive(int) 
 controlP5.Controller : Knob setColorBackground(int) 
 controlP5.Controller : Knob setColorCaptionLabel(int) 
 controlP5.Controller : Knob setColorForeground(int) 
 controlP5.Controller : Knob setColorValueLabel(int) 
 controlP5.Controller : Knob setDecimalPrecision(int) 
 controlP5.Controller : Knob setDefaultValue(float) 
 controlP5.Controller : Knob setHeight(int) 
 controlP5.Controller : Knob setId(int) 
 controlP5.Controller : Knob setImages(PImage, PImage, PImage) 
 controlP5.Controller : Knob setImages(PImage, PImage, PImage, PImage) 
 controlP5.Controller : Knob setLabelVisible(boolean) 
 controlP5.Controller : Knob setLock(boolean) 
 controlP5.Controller : Knob setMax(float) 
 controlP5.Controller : Knob setMin(float) 
 controlP5.Controller : Knob setMouseOver(boolean) 
 controlP5.Controller : Knob setMoveable(boolean) 
 controlP5.Controller : Knob setPosition(PVector) 
 controlP5.Controller : Knob setPosition(float, float) 
 controlP5.Controller : Knob setSize(PImage) 
 controlP5.Controller : Knob setSize(int, int) 
 controlP5.Controller : Knob setStringValue(String) 
 controlP5.Controller : Knob setUpdate(boolean) 
 controlP5.Controller : Knob setValueLabel(String) 
 controlP5.Controller : Knob setView(ControllerView) 
 controlP5.Controller : Knob setVisible(boolean) 
 controlP5.Controller : Knob setWidth(int) 
 controlP5.Controller : Knob show() 
 controlP5.Controller : Knob unlock() 
 controlP5.Controller : Knob unplugFrom(Object) 
 controlP5.Controller : Knob unplugFrom(Object[]) 
 controlP5.Controller : Knob unregisterTooltip() 
 controlP5.Controller : Knob update() 
 controlP5.Controller : Knob updateSize() 
 controlP5.Controller : Label getCaptionLabel() 
 controlP5.Controller : Label getValueLabel() 
 controlP5.Controller : List getControllerPlugList() 
 controlP5.Controller : PImage setImage(PImage) 
 controlP5.Controller : PImage setImage(PImage, int) 
 controlP5.Controller : PVector getAbsolutePosition() 
 controlP5.Controller : PVector getPosition() 
 controlP5.Controller : String getAddress() 
 controlP5.Controller : String getInfo() 
 controlP5.Controller : String getName() 
 controlP5.Controller : String getStringValue() 
 controlP5.Controller : String toString() 
 controlP5.Controller : Tab getTab() 
 controlP5.Controller : boolean isActive() 
 controlP5.Controller : boolean isBroadcast() 
 controlP5.Controller : boolean isInside() 
 controlP5.Controller : boolean isLabelVisible() 
 controlP5.Controller : boolean isListening() 
 controlP5.Controller : boolean isLock() 
 controlP5.Controller : boolean isMouseOver() 
 controlP5.Controller : boolean isMousePressed() 
 controlP5.Controller : boolean isMoveable() 
 controlP5.Controller : boolean isUpdate() 
 controlP5.Controller : boolean isVisible() 
 controlP5.Controller : float getArrayValue(int) 
 controlP5.Controller : float getDefaultValue() 
 controlP5.Controller : float getMax() 
 controlP5.Controller : float getMin() 
 controlP5.Controller : float getValue() 
 controlP5.Controller : float[] getArrayValue() 
 controlP5.Controller : int getDecimalPrecision() 
 controlP5.Controller : int getHeight() 
 controlP5.Controller : int getId() 
 controlP5.Controller : int getWidth() 
 controlP5.Controller : int listenerSize() 
 controlP5.Controller : void remove() 
 controlP5.Controller : void setView(ControllerView, int) 
 java.lang.Object : String toString() 
 java.lang.Object : boolean equals(Object) 
 
 
 */


