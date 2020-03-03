#include <SoftwareSerial.h>
#include <MsTimer2.h>

#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
ZBRxResponse rxData = ZBRxResponse();
ZBTxRequest txRequest = ZBTxRequest();

unsigned long timemillis;
int ID = 1;

struct FrameData
{
  uint8_t ID;
  uint8_t frameType;
  uint8_t role;
  uint8_t mode;
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

struct FrameData setData(uint8_t ID,uint8_t frameType,uint8_t role,uint8_t mode,double x,double y,int angle,int Dspeed,int Dtime,int touch,int R,int G,int B,int i,int Unknown1,int Unknown2,int Unknown3)
{
  FrameData frameData;
  
  frameData.ID = ID;
  frameData.frameType = frameType;
  frameData.role = role;
  frameData.mode = mode;
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


int readFrame() {

  FrameData *frameData = (FrameData*)rxData.getData();

  ID = frameData->ID;
  
  Serial.print("ID=");
  Serial.println(frameData->ID);
  Serial.print("x=");
  Serial.println(frameData->x);
  Serial.print("y=");
  Serial.println(frameData->y);
  Serial.print("angle=");
  Serial.println(frameData->angle);
  Serial.println("----------------");
  Serial.print(ID);
  Serial.print("send packages = ");
  Serial.println(frameData->Unknown1);
  
  if(frameData->frameType == 1 || frameData->frameType == 2 )
  {
    returnOK();
  }
  else if(frameData->frameType == 3)
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("ERROR DATA TYPE");
  }

  return frameData->ID;
}


void returnOK()
{
  
  FrameData frameData = setData(ID,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x409C0154);

  //add Robot address
  if(ID == 1)
  {
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x409C0154);
  }
  else if(ID == 2)
  {
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x40991E5A);
  }
  else if(ID == 3)
  {
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x40b7798A);
  }
  else if(ID == 5)
  {
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x4091BE1D);
  }
  
  uint8_t *dataptr_ok = (uint8_t*)&frameData;
  ZBTxRequest zbTx_ok = ZBTxRequest(addr64,dataptr_ok,sizeof(frameData));
  
  xbee.send(zbTx_ok);
  Serial.println("Send OK!");
  //delay(1000);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  xbee.setSerial(Serial1);

}


void loop() {
  // put your main code here, to run repeatedly:
 
  readXbee();
  Serial1.flush();
  while(Serial1.read() >= 0){}
  timemillis = millis();
  /*
  if(timemillis >= 60000)
  {
    delay(10000);
  }
  */
  delay(25);
}

int countsum = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;

void readXbee() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    //countsum++;
    //Serial.print("???");
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
    {
      xbee.getResponse().getZBRxResponse(rxData);
      countsum++;
      
      int readResult = readFrame();

      if(readResult == 1)
      {
        count1++;
      }
      else if(readResult == 2)
      {
        count2++;
      }
      else if(readResult == 3)
      {
        count3++;
      }
      
      //readStatus();

      Serial.print("sum = ");
      Serial.println(countsum);
      Serial.print("receive from 1 = ");
      Serial.println(count1);
      Serial.print("receive from 2 = ");
      Serial.println(count2);
      Serial.print("receive from 3 = ");
      Serial.println(count3);
      
      Serial.println("----------------");
    }
    else
    {
      Serial.println("wrong data");
    }
  }
  else
  {
    //Serial.println("Failed to Receive");
    
  }
}
