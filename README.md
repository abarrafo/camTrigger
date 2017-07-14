# camTrigger
Particle Photon as an external trigger for Zoneminder recordings. 

See my space for full tutorial: (link coming soon)

Triggering Zoneminder Camera Recordings with a Particle Photon and Optex Motion Detector.

Introduction:
If your reading this, then chances are you-like me are frustrated with the number of false-triggers that are filling up your hard-drives with footage of spiders and shadows from your outdoor cams. I have been running security cameras, inside and out, of my home for the past 6 years. I have run software on Windows by BlueIris, I had a brief stint using the Netgear’s Arlo solution, the batteries killed me, before I decided that was not for me. Most recently I set up a Centos7 server to double up as my media server and to handle my cameras using Zoneminer. So far, I have enjoyed using Zoneminder coupled with the ZmNinja client the most, well in full disclosure the last version of BlueIris I ran was released in 2010, they had some good stuff going too. 

My setup, I have 4 Reolink RLC-410 Outdoor cameras, coupled with 4 mixed-brand internal ip/wifi cameras. This is generating an astonishing terabyte per month of video recording! Yikes! Even with a 2TB HDD, couple the other things I want my server to do, well can lead to some performance issues across all applications. The first temporary patch I did, was I wrote a bash script on my server that zip’s and pushes all Triggered recordings to Amazon S3. Then I set Zoneminder, using the Filter option to trigger the script on its batch cycle to match any recent events, and after the push to s3 put move those events to Archived. Lastly I created another  filter to delete all Archived events after a week. This has kept Zoneminder under control from blowing up my local HDD, but Comcast is certain to start to send me letters about overages. Not to mention my S3 bill has been steadily rising. 

I do like my S3 cloud presence now that I have it, but, I really hate the volume. I decided to get a real motion detector, and use that to trigger my recording rather than relying on pixels and blobs that inherently have a high degree of error in an outdoor, rural environment. I poked around the internet for a while looking at motion detectors and forums about what others have done, there was one forum that had a suggestion to use an Arduino, that seemed cool. That led me to look at Arduino, and eventually the Particle Photon. Yes! Particle Photon had everything I needed for a super smooth price point $19.00. 

Parts: 
1.	Particle Photon ~$19.00
2.	Small Bread Board ~$7.99 (you can get a kit with both).
3.	Optex LX-402 Motion Detector. ~71.00
4.	A Digital Multimeter (not necessary but can be helpful).
5.	Some wire. I have lots and lots of Cat5E cable to tinker with so that’s what I will use to both power the Optex device, and to run back the NC/NO wires. Optex does have recommended gauges in their docs depending on expected install length, so you should follow that if you’re running the power wire over a long distance (over 500ft). 

I probably could of went with a cheaper motion sensor and in another use case I probably would have. Here I plan to install the motion sensor ~10 feet up, outdoors in New Hampshire (needs to have some sort of weather proofing), and have a large’ish area (my driveway) that I wanted covered. The 40ft x 50ft coverage, built for outdoors, and the NO/NC out available made this an easy choice for me.

The code in this repo is the code used to program my Particle Photon device to trigger my camera recodings, and eventually I would like it to do more things, like respond to txt to turn off triggers or turn on triggers, or turn on/off email notifications. All cool stuff that shoud be easily done on this little device. 
