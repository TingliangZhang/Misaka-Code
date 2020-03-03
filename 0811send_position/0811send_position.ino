#include <MsTimer2.h>

#include <SoftwareSerial.h>

#include <Printers.h>
#include <XBee.h>
#include "OpticalData.h"

#include "PID_v1.h"

#define SCK_PIN 21
#define SDIO_PIN 20

XBee xbee = XBee();
ZBRxResponse rxData = ZBRxResponse();
OpticalData opticalData(SCK_PIN, SDIO_PIN);  //create position data

XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x409C0220);
int ID = 1;
int counti = 0;

struct FrameData
{
  uint8_t ID;
  uint8_t frameType;
  uint8_t role;
  uint8_t Dmode;
  double x;
  double y;
  int angle;
  int Dspeed;
  int Dtime;
  int touch;
  int R;
  int G;
  int B;
  int i;
  int Unknown1;
  int Unknown2;
  int Unknown3;
};

//frameType = 1 -> Command(PC->Robot)
//frameType = 2 -> Status(Robot->PC)
//frameType = 3 -> ACK(OK)
struct FrameData setData(uint8_t ID,uint8_t frameType,uint8_t role,uint8_t Dmode,double x,double y,int angle,int Dspeed,int Dtime,int touch,int R,int G,int B,int i,int Unknown1,int Unknown2,int Unknown3)
{
  FrameData frameData;
  
  frameData.ID = ID;
  frameData.frameType = frameType;
  frameData.role = role;
  frameData.Dmode = Dmode;
  frameData.x = x;
  frameData.y = y;
  frameData.angle = angle;
  frameData.Dspeed = Dspeed;
  frameData.Dtime = Dtime;
  frameData.touch = touch;
  frameData.R = R;
  frameData.G = G;
  frameData.B = B;
  frameData.i = i;
  frameData.Unknown1 = Unknown1;
  frameData.Unknown2 = Unknown2;
  frameData.Unknown3 = Unknown3; 

  return frameData;
}


void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);
  Serial3.begin(115200);
  xbee.setSerial(Serial3);

  opticalData.begin();
  MsTimer2::set(10,sendStatus);
  //MsTimer2::set(11,readXbee);
  MsTimer2::start();
}

/*
  
//define Robotstatus -> example
uint8_t ID = 1;
uint8_t frameType = 2;
uint8_t role = 1;
uint8_t Dmode = 1;
double x = 246.78;
double y = 284.35;
int angle = 30;
int Dspeed = 20;
int Dtime = 20;
int touch = 3;
int R = 255;
int G = 255;
int B = 255;
int i = 3;
int Unknown1 = 0;
int Unknown2 = 0;
int Unknown3 = 0;


//send frame data

   //Destination Address(MAC)
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x4091BE9B); 

  //set payload(frame data)
FrameData frameData = setData(ID,frameType,role,Dmode,x,y,angle,Dspeed,Dtime,touch,R,G,B,i,Unknown1,Unknown2,Unknown3);

  //create a pointer towards the frame data
uint8_t *dataptr_dataframe = (uint8_t*)&frameData; 

  //create a request including destination address + dataframe pointer + data length
ZBTxRequest zbTx_dataframe = ZBTxRequest(addr64, dataptr_dataframe, sizeof(frameData)); 

  */
void loop() {
  
  // put your main code here, to run repeatedly:

  
  //xbee.send(zbTx_dataframe);
  //Serial.println("Send data!");
  //delay(10);
  
  readXbee();
  //Serial3.flush();
  while(Serial3.read() >= 0){}
  Serial3.flush();
  delay(50);
  
}

int readFrame() {

  FrameData *frameData = (FrameData*)rxData.getData();

  ID = frameData->ID;
  
  if(frameData->frameType == 1 || frameData->frameType == 2 )
  {
    returnOK();
  }
  else if(frameData->frameType == 3)
  {
    //Serial.println("OK");
  }
  else
  {
    //Serial.println("ERROR DATA TYPE");
  }

  return frameData->frameType;
}


void returnOK()
{
  
  FrameData frameDataOK = setData(2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  
  //XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x409C0220);

  //add Robot address
  /*
  if(ID == 1)
  {
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x409C0220);

  }
  */
  
  uint8_t *dataptr_ok = (uint8_t*)&frameDataOK;
  ZBTxRequest zbTx_ok = ZBTxRequest(addr64,dataptr_ok,sizeof(frameDataOK));
  
  xbee.send(zbTx_ok);
  Serial.println("Send OK!");
  //delay(1000);
}

void readXbee() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
    {
      xbee.getResponse().getZBRxResponse(rxData);
      
      int readResult = readFrame();
    }
    else
    {
      //Serial.println("wrong data");
    }
  }
  else
  {
    //Serial.println("Failed to Receive");
  }
}

void sendframeData(uint32_t msb,uint32_t lsb,uint8_t IDD,uint8_t frameType,uint8_t role,uint8_t Dmode,double x,double y,int angle,int Dspeed,int Dtime,int touch,int R,int G,int B,int i,int Unknown1,int Unknown2,int Unknown3)
{
  FrameData frameData = setData(IDD,frameType,role,Dmode,x,y,angle,Dspeed,Dtime,touch,R,G,B,i,Unknown1,Unknown2,Unknown3);
   
  XBeeAddress64 addr64 = XBeeAddress64(msb,lsb);

  uint8_t *dataptr = (uint8_t*)&frameData;
  ZBTxRequest zbTx = ZBTxRequest(addr64,dataptr,sizeof(frameData));
  
  xbee.send(zbTx);
  Serial.println("Send Data");
}

int curtouch = 0;
FrameData validStatusData;
//the first parameter is the robot's ID
FrameData curStatusData = setData(2,2,1,0,0,0,0,0,0,curtouch,0,0,0,0,0,0,0);

int countcurStatusData = 0;
int countpackage = 0;

void readStatus()
{
   opticalData.CheckAndReadOpticalData();
   curStatusData.x = opticalData.getXcoordinate(); //读取X坐标
   curStatusData.y = opticalData.getYcoordinate(); //读取Y坐标
   curStatusData.angle = opticalData.getAngle(); //读取方向
}

void sendStatus()
{
  
  readStatus();
  //validStatusData = curStatusData;
  
  if(curStatusData.x > 5 && curStatusData.y >5 && curStatusData.x < 1500 && curStatusData.y < 600)
  {
    validStatusData = curStatusData;
  }
  
  countcurStatusData++;
  
  
  if(countcurStatusData > 9)
  {
    countpackage++;
    validStatusData.Unknown1 = countpackage;
    uint8_t *dataptr_statusdata = (uint8_t*)&validStatusData; 
    
    ZBTxRequest zbTx_statusdata = ZBTxRequest(addr64, dataptr_statusdata, sizeof(validStatusData)); 
    
    xbee.send(zbTx_statusdata);
    Serial.println("Send Status Data");
    
    countcurStatusData = 0;
  }
}
