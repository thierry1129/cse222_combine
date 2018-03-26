# Studio Questions / Replies

***Q1.1 The "Basic" page initially just shows default values from HTML. If this app were interacting with an actual light, what values would have to be retrieved from the light initially rather than using the defaults?***
* Initially, the app must retrieve the current color of the light and reflect this on the web page.
* Must also know if the light is on or off.

***Q1.2 What values are "out-of-sync" on the Basic tab. I.e., the values shown are inconsistent with the expected behavior of the app?***
* Moving the slider does not change the number. 
* Also target color does not change.

***Q1.3 What values are "out-of-sync" on the Settings tab. I.e., the values shown are inconsistent with the expected behavior of the app?***
* The slider does not update the relevant numerical value.

***2.1 Explain what functions appear to be supported by the initial source code.***
* updateCurrentColor takes values from sliders and displays a hex color
* setColorClicked changes the background color to the target color
* redSliderChange shows numerical value for slider position

***2.2 The initial code shows two approaches to creating functions, which are both common in JavaScript.  One approach creates _named_ functions, while the other creates an "anonymous" . Show the signifiant aspects of each syntax:***
* first way is function name () something something
* second way is to add an event listener

***2.3 This app simplifies the lifecycle to just two parts: a) configuration when the application starts (and all screens are loaded) and b) reacting to changes in the UI.  Which part of the code handles the "start"?***
* addEventListener DOM content loaded
