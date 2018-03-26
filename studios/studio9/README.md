# Studio Questions / Replies

***Q1. Paste the code for your solution (re-creating the diagram) here:***

```
# Code here:
title Physically Turn Lamp Off

participant App
participant Particle.io
participant Lamp
participant User

User->Lamp: Pushes button
Lamp->Particle.io: state
Particle.io->App: state

note right of Particle.io
Full state is sent to
"cse222Lights/thisLamp/color"
end note

```

***Q2. Paste the code for your solution here (the sequence of events for setting a color and updates for a "fade"):***

```
# Code here:

```

***Q3.1. What ways can ThingSpeak interact/react to the world?  Summarize the options at: [https://thingspeak.com/apps](https://thingspeak.com/apps).***
It can provide matlab analysis and visulizations, connect a device to twitter and send alerts, perform actions at predetermined times, communicate with web services and apis.




***Q3.2. The [ThingSpeak home page](https://thingspeak.com/) has a set of four featured projects.  Review at least one and explain how it's using ThingSpeak.***

The car counter project utilizes thinkspeak to analyze data to figure out a traffic pattern. It accepts raw data from rasperry pi and analyze the data using functions from thinkspeak toolbox. They plot the daily mean density traffic data and see the trend to analyze and predict traffic patterns.

***Q4.1. How frequently will colors be updated in the initial version of the app?***

5 seconds

***Q4.2. What is the channel number used by Cheer Lights?***

1417

***Q4.3. How are CheerLights using ThingSpeak to provide indications of the performance of the lights?***

It receive tweets containing colors and adjust the color of light accordingly.

***Q4.4. What is the "id" for each field and what is it's meaning?***

CheerLights uses the TweetControl App from ThingSpeak to listen to Twitter for the keyword “cheerlights” in real-time. When a Tweet matches, TweetControl updates the CheerLights ThingSpeak Channel with the last color received. Since CheerLights uses ThingSpeak to collect our color values, we can use the ThingSpeak Channel API to read our data. CheerLights uses channel 1417 and stores the color name in field1 and the HEX color value in field2.

***Q5.1  The Technician should put the final code (for writing to a ThingSpeak channel) in `ThingSpeakWrite/ThingSpeakWrite.ino` and commit it (you won't be able to compile it locally without the libraries.  Complete work using the cloud IDE then copy/paste the final files in the repo).***

```
// Code here:

```
