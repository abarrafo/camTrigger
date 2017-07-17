/*
 * Project camTrigger
 * Description: Trigger Zoneminder camera recordings from Particle Photon
 * Author: Andrew Barraford
 * Date: 07/17/2017
 */

byte server[] = { 192, 168, 1, 88 };
//ZM telnet port
int port = 6802;
int cam9 = 0;
TCPClient client;

void setup() {
    Serial.begin(9600);
    Particle.variable("analogSignal", &cam9, INT);
    //Assign the pin as an input.
    pinMode(A0, INPUT);
      // if you get a connection, report back via serial:
    if (client.connect(server, port)) {
        Serial.printlnf("connected”);
        Particle.publish("connected");
    }
    else {
        // if you didn't get a connection to the server:
        Serial.printlnf("connection failed”);
        Particle.publish("connection failed");
    }
}

void loop() {
    cam9 = analogRead(A0); // Get a reading
    if (cam9 < 1000) {
        Serial.printlnf("close %d", cam9;
        delay(200);
    } else {
        Serial.printlnf("open %d, trigger camera and delay 60s", cam9);

        //****************************************************************************
        //****************************************************************************
        // Send telnet command to trigger zoneminder to record on for 30s.
        // Following /usr/bin/zmtrigger.pl readme:

        // B<id>|B<action>|B<score>|B<cause>|B<text>|B<showtext>
        // =item B<id> is the id number or name of the ZM monitor.

        // =item B<action>
        //   Valid actions are 'on', 'off', 'cancel' or 'show' where
        //   'on' forces an alarm condition on;
        //   'off' forces an alarm condition off;
        //   'cancel' negates the previous 'on' or 'off';
        //   'show' updates the auxiliary text represented by the %Q
        //   placeholder, which can optionally be added to the affected monitor's
        //   timestamp label format.

        //   Ordinarily you would use 'on' and 'cancel', 'off' would tend to be
        //   used to suppress motion based events. Additionally 'on' and 'off' can
        //   take an additional time offset, e.g. on+20 which automatically
        //   cancel's the previous action after that number of seconds.

        // =item B<score>
        //   is the score given to the alarm, usually to indicate it's
        //   importance. For 'on' triggers it should be non-zero, otherwise it should
        //   be zero.

        // =item B<cause>
        //   is a 32 char max string indicating the reason for, or source of
        //   the alarm e.g. 'Relay 1 open'. This is saved in the 'Cause' field of the
        //   event. Ignored for 'off' or 'cancel' messages.

        // =item B<text>
        //   is a 256 char max additional info field, which is saved in the
        //   'Description' field of an event. Ignored for 'off' or 'cancel' messages.

        // =item B<showtext>
        //   is up to 32 characters of text that can be displayed in the
        //   timestamp that is added to images. The 'show' action is designed to
        //   update this text without affecting alarms but the text is updated, if
        //   present, for any of the actions. This is designed to allow external input
        //   to appear on the images captured, for instance temperature or personnel
        //   identity etc.

        // =back
        // Note that multiple messages can be sent at once and should be LF or CRLF
        // delimited. This script is not necessarily intended to be a solution in
        // itself, but is intended to be used as 'glue' to help ZoneMinder interface
        // with other systems.

        // EXAMPLE 3|on+10|1|motion|text|showtext
        // Triggers "alarm" on camera #3 for 10 seconds with score=1, cause="motion".
        //****************************************************************************
        //****************************************************************************
        //Trigger my camera 9 to record for 30s, delay triggers for 30s

        //un-comment to trigger cam 9
        //client.print("9|on+30|1|motion|photon-triggered|photon-triggered");
        delay(30000);
    }
}
