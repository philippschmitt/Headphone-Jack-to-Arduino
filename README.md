# Headphone to Arduino

This setup allows you to trigger a camera flash from your phones' headphone jack with a short sound impulse.

[add project url]


## Setup

![image](setup.jpg)

An ATtiny 85 microprocessor is used to listen for audio input (voltage changes) from a phone headphone jack.

Using Javascript and the Web Audio API, 50ms long sound impulses are sent from a webpage running on the phone.

To trigger the flash, you have to close the circuit of a synchron cable connected to your setup. Because these flash circuits usually carry high voltages (180V in my case), the circuit has to be isolated from your microprocessor and headphone jack. This is accomplished by using a relay.

Because the flash needs some seconds to reload after it has been triggered, impulses arriving in the meantime are added to a flash queue. The LED is on as long as there are impulses waiting in the queue.





## Parts needed
- Camera Flash with synchron cable (I'm using an Unomat 20B auto)
- ATtiny 85 microprocessor, Arduino or similar
- Power supply, e.g. LIPO 3.7V 110mAh battery
- Transistor, e.g. BD 137-16
- Relay, e.g. FRS1B-S
- audio cable that fits your phone's audio output


## Circuit Design
add instructions

![image](circuit-breadboard.png)

![image](circuit.png)


Author: Philipp Schmitt  
Contact: mail@philippschmitt.com
