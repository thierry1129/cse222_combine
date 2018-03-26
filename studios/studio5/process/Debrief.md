- Answers can be brief/informal.
  
  ***Q1. We will be using the outputs on a 3V microcontroller to turn LEDs on and off. Assume that an LEDs Anode will be connected to the microcontroller and the cathode will be connected through a resistor to ground.  If the LED's forward voltage drop is 2V and it shouldn't pass more than 20mA of current, what's the minimum safe value of the resistor.:***
 -
 +R=V/I=(3-2)V/0.2A =5 Ohm
  
  ***Q2. Just as LEDs have a limit on the current that should pass through them, the pins on the microcontroller also have limits on the amount of current they can supply (i.e., outgoing current) and sink (i.e., incoming current).  Consider the previous problem assuming the microcontroller's individual pins shouldn't pass more than 15mA. How and why does the answer change?***
 -
 +R = V/I = 1V/0.15A = 6.66
 +We need to increase resi
  
  ***Q3. The Photon's I/O specifications are described at [https://docs.particle.io/datasheets/photon-(wifi)/photon-datasheet/#i-o-characteristics](https://docs.particle.io/datasheets/photon-(wifi)/photon-datasheet/#i-o-characteristics). What is the maximum amount of output current the Photon can supply per pin?***
  
 +The maximum amount is 1A.
 +
  ***Q4. The table also provides the total current for input/output. That is, the limits on the sum of currents across all pins. What is the limit?***
 ++/-120mA
  
  ***Q5. The Photon has 8 digital pins and the 6 analog pins can also be used for digital I/O.  How many of the LEDs previously described could the Photon directly drive with pins at maximum brightness?  Explain your answer:***
  
 +6, you may connect the led to both the digital pins and the analog pins. However, in order to let the led reaches the maximum brightness, we can only connect 6 of them.
 +
  ***Q6. What if exactly 8 LEDs are required for a project, the should be driven directly by I/O pins, and the should be as bright as possible without causing damage?***
  
 +it will not reaches the maximum brightness.
 +
  ***Q7. Most people initially find it easiest to consider output pins as supplying power and, hence, controlling on/off is directly due to the output being `HIGH` or `LOW`.  In reality, controlling an LED is just due to a voltage difference across the LED. Consider an LED that is connected to 3V, then through an appropriate resistor, and finally to a pin of the Photon.  When the pin is `LOW`, it's essentially a connection to ground.  When the pin is `HIGH`, it's essentially a connection to 3V.  What will the LED do in each case:***
  
  | Pin State   |   LED Condition   |
  |:------------|:------------------|
 -| `LOW`       |  ???        |
 -| `HIGH`      |  ???       |
 +| `LOW`       |  off        |
 +| `HIGH`      |  on       |
  
  
  ***Q8. RGB LEDs are essentially three LEDs bundled together. They require four wires:  one unique to each color and one that is shared.  There are two common configurations for the shared wire: Common Anode and Common Cathode.   Explain what each means:***
 +
 +common anode: the anode of the leds are connected together.
 +common cathode: the cathod of the leds are connected together.