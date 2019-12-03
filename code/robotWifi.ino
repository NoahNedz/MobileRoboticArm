#include <ESP8266WiFi.h>
#include <Servo.h>


/*
 * If you have no idea about this library, you can watch the tutorial below
 * NodeMCU ESP8266 Tutorial 01: Programming NodeMCU ESP-12E Using Arduino IDE
 * https://youtu.be/NtyFx1frYB0
 */

/* define port */
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "RobotRouter"; /* change with your ssid */
const char* password = "password"; /* change with your password */

/* data received from application */
String  data =""; 


/* define L298N or L293D motor control pins */

/* 1st H-BRIGDE */
Servo leftWheel;
Servo rightWheel;
Servo base;
Servo main;
Servo second;
Servo fork;

int mainVal = 175;
int secondVal = 50;
int baseVal = 90;
int forkVal = 90;


int WheelVal = 0;


void setup()
{
  /* initialize motor control pins as output */
  leftWheel.attach(16);
  rightWheel.attach(5);
  base.attach(4);//d2
  main.attach(0);//d3
  second.attach(2);//d4
  fork.attach(14);//d5
  delay(2000);
  base.write(baseVal);
  delay(2000);
  second.write(secondVal);
  delay(2000);
  main.write(mainVal);
  delay(2000);
  
  fork.write(forkVal);
  delay(500);
  
 /* initilize serial communication */
  Serial.begin(9600);

  /* Connect to wifi*/
  connectWiFi();

  /* start server communication */
  server.begin();
}

void loop()
{

    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (client){ 
      data = checkClient ();
    }
    //Serial.println("data " + String(data));
/************************ Run function according to incoming data from application *************************/

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if (data == "backward") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "left") TurnRight();
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "right") TurnLeft();
    
    else if (data == "leftforward") mainForward();
    else if (data == "rightforward") secondBackward();
    else if (data == "leftbackward") mainBackward();
    else if (data == "rightbackward") secondForward();

    else if (data == "stop") stopMov();

    else if (data == "stophand") stopMov();

    
    else if (data == "leftcw") forkDown();
    else if (data == "leftccw") baseLeft();
    else if (data == "rightcw") forkUp();
    else if (data == "rightccw") baseRight();
    delay(25);
    

    
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
 Serial.println("driving forward");
 leftWheel.write(80);
 rightWheel.write(100); 

  
// for(int i=0; i<sizeof buff; i++){  /* transfer buff data per second */
//      buff[i] = wheelForward[i];
//      SPI.transfer(buff[i]);
//    }
  
 
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
 leftWheel.write(100);
  rightWheel.write(80); 
  WheelVal = 1; 
}


void mainForward(void)   
{
   mainVal += 1;
   if(mainVal > 180) mainVal = 180;
   main.write(mainVal);   
}

void secondForward(void)   
{
  secondVal +=1;
  if(secondVal >180){secondVal = 180;}
  second.write(secondVal);
  
}

void mainBackward(void)   
{
   mainVal -= 1;
   if(mainVal < 0)mainVal = 0;
   main.write(mainVal);

}

void secondBackward(void)   
{
  secondVal -=1;
  if(secondVal < 0){secondVal = 0;}
    second.write(secondVal);
    
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{ 
  leftWheel.write(100);
  rightWheel.write(100);
  WheelVal = 1; 
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  leftWheel.write(80);
  rightWheel.write(80);
  WheelVal = 1; 
}


void forkDown(void)   
{
  forkVal -= 1;
  if(forkVal < 0)forkVal = 0;
  fork.write(forkVal);
}

void forkUp(void)   
{
  forkVal += 1;
  if(forkVal > 180)forkVal= 180;
  fork.write(forkVal);
}

void baseLeft(void)   
{
  baseVal += 1;
  if(baseVal > 180)baseVal=180;
  base.write(baseVal);
}

void baseRight(void)   
{
  baseVal -= 1;
  if(baseVal < 0)baseVal = 0;
  base.write(baseVal);
}

void stopMov(void)
{
  leftWheel.write(90);
  rightWheel.write(90);

  
//   for(int i=0; i<sizeof buff; i++){  /* transfer buff data per second */
//      buff[i] = wheelStop[i];
//      SPI.transfer(buff[i]);
//    }
  
  WheelVal = 0; 
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
