/*
 * Project camTrigger
 * Description: Trigger Zoneminder camera recordings from Particle Photon
 * Author: Andrew Barraford
 * Date: 07/17/2017
 */
 //Your ZoneMinder Server IP Address
 byte server[] = { 192, 168, 1, 23 };
 int port = 6802;

 //Camera id to monitor and to map to inputs
 int cam9 = 0;
 int cam10 = 0;

 //Counters
 int cam9CloseCnt = 0;
 int cam10CloseCnt = 0;
 int cam9OpenCnt = 0;
 int cam10OpenCnt = 0;

 //Is Trigger Eligible
 bool cam9TriggerEligible = true;
 bool cam10TriggerEligible = true;

 //The TCP Client to send TELNET
 TCPClient client;

 void setup() {
     Serial.begin(9600);
     Particle.variable("analogSignal", &cam9, INT);
     Particle.variable("analogSignal", &cam10, INT);

     //setup pin as input.
     pinMode(A0, INPUT);
     pinMode(A1, INPUT);

     if (client.connect(server, port)) {
         //Publish to the Particl IO console. use sparyingly as pubs are limited to 1 per second.
         Particle.publish("connected");
         Serial.printlnf("connected to server");
     }
     else {
         //Publish to the Particl IO console. use sparyingly as pubs are limited to 1 per second.
         Particle.publish("connection failed");
         Serial.printlnf("connection to server failed");
     }
 }

 void loop() {

     //Input mapping to cams
     cam9 = analogRead(A0); // Get a reading
     cam10 = analogRead(A1); // Get a reading

     //Trigger and Dely CAM 10
     if(cam10 < 1000 && cam10CloseCnt > 500){
             Serial.printlnf("close cam10 %d", cam10);
             cam10CloseCnt = 0;
     }else if(cam10 > 1000 && cam10TriggerEligible) {
         Serial.printlnf("open cam10 %d, trigger camera and delay 30s", cam10);
         // client.print("10|on+30|1|motion|photon-triggered|photon-triggered");
         cam10OpenCnt = 0;
         cam10TriggerEligible = false;
     }


     //Increment cam 10 counters
     cam10CloseCnt++;
     cam10OpenCnt++;

     if(!cam10TriggerEligible && cam10OpenCnt > 30000) {
         cam10TriggerEligible = true;
     }


     //Trigger and delay for cam 9
     if(cam9 < 1000 && cam9CloseCnt > 500) {
         Serial.printlnf("close cam9 %d", cam9);
         cam9CloseCnt = 0;
     }else if (cam9 > 1000 && cam9TriggerEligible){
         Serial.printlnf("open cam9 %d, trigger camera and delay 30s", cam9);
         // client.print("9|on+30|1|motion|photon-triggered|photon-triggered");
         cam9OpenCnt = 0;
         cam9TriggerEligible = false;
     }

     //Increment counters for CAM 9
     cam9CloseCnt++;
     cam9OpenCnt++;

     if(!cam9TriggerEligible && cam9OpenCnt > 30000) {
         cam9TriggerEligible = true;
     }

 }
