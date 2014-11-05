/**
 * Serial Duplex 
 * by Tom Igoe. 
 * 
 * Sends a byte out the serial port when you type a key
 * listens for bytes received, and displays their value. 
 * This is just a quick application for testing serial data
 * in both directions. 
 */

import controlP5.*;
import processing.serial.*;

ControlP5 cp5;

Serial myPort;
byte k[];
byte iv[];
byte input_file[];
byte outBuffer[];
byte inBuffer[];


Textlabel tl_title;
Textlabel tl_key;
Textlabel tl_iv;
Textlabel tl_text;

OutputStream output_file;

void setup() {
  size(240, 150);
  noStroke();

  cp5 = new ControlP5(this);
    tl_title = cp5.addTextlabel("title")
                    .setText("KRIPTOPY")
                    .setPosition(90,10)
                    .setColorValue(0xffffff00)
                    ;
      cp5.addButton("ENCRYPT",1,20,30,90,40);
      cp5.addButton("DECRYPT",1,130,30,90,40);
      cp5.addButton("FINISH",1,75,90,90,40);

  text("prova", 120, 120);
  k = loadBytes("/Users/mumu/Desktop/my.key");
  iv = loadBytes("/Users/mumu/Desktop/my.iv");
  input_file = loadBytes("/Users/mumu/Desktop/input.txt");
  output_file = createOutput("/Users/mumu/Desktop/output.txt");
  outBuffer = new byte[16];
  inBuffer = new byte[16];

  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 115200);
  myPort.clear();
  myPort.buffer(16);

}

void draw() {
  background(0);
}


void serialEvent(Serial p){
  if(p==myPort){
      myPort.readBytes(inBuffer);
      for(int i=0; i<16;i++){
        try {
        output_file.write(inBuffer[i]);        
        } catch (IOException e) {}
      }
      println("received");
  }  
  } 

public void controlEvent(ControlEvent theEvent) {
 if(theEvent.isController()) { 
    
    print("control event from : "+theEvent.controller().name());
    println(", value : "+theEvent.controller().value());
    
    if(theEvent.controller().name()=="ENCRYPT"){
      en();
    }
    if(theEvent.controller().name()=="DECRYPT"){
      de();
    }
    if(theEvent.controller().name()=="FINISH"){  
        try {
          output_file.flush();
        } catch (IOException e) {}
        try {
          output_file.close();
        } catch (IOException e) {} 
        exit();

        }
    }  
}

public void en() { 
  myPort.write("EEEEEEEEEEEEEEEE");
  println("Encrypt");
  sendAll();
}

public void de() {
  myPort.write("DDDDDDDDDDDDDDDD");
  println("Decrypt");
  sendAll();
}

public void sendAll() {
  for (int i = 0 ; i < 16; i++) {
    myPort.write(k[i]);
  }
    println("KEY");
    for (int i = 0 ; i < 16; i++) {
    myPort.write(iv[i]);
  }
    println("IV");
  for (int i = 0 ; i < (input_file.length); i++) {
    myPort.write(input_file[i]);
  }
  int tot = 16-(input_file.length%16);
  for (int i = 0 ; tot!=16 && i < 16-(input_file.length%16); i++) {
    myPort.write(32);
  }
  myPort.write("$$$$$$$$$$$$$$$$"); 
   println("FINISH");
 
}


