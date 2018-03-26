# Studio Questions / Replies

***Q1.1 There are two aspects to configuring a sketch to use a particle function:  defining a function with an appropriate signature and configuring it so it will act as a Particle function.  Explain each of these steps based on your review of the API:***

* The first step is to create a function that takes in a string value and returns an int. This is the cloud function.
* The second step is to define this function in the setup() of the function so that it will be read as a Particle cloud function.

***Q1.2 Discuss the meaning of each of the parameters/arguments to functions described above (there should be two functions: a user created one and one that is part of the Particle API)***

* The user created function is the function setLampPower(). 
* The one that is part of ParticleAPI is Particle.function("led", setLampPower);

***Q2. In your own words, explain the parameters/arguments given to `Particle.variable()`***
* Particle.variable() takes in two parameters.
* The first one is a string, and this is likely what the cloud variable name will be called.
* The second one is a reference to an already-defined variable.

***Q3. "When accessing variables through Particle Dev or the on-line Console, polling is triggered by a person".  Explain what that previous sentence refers to (how does the person trigger the polling):***
* The program waits for the person to enter values / trigger an event.
* Otherwise, if there is no person, nothing will ever run.

***Q4. Many particle functions, like `Particle.function()` and `Particle.variable()`, require both a string and another parameter.  Explain how each relates to what is externally visible (accessible from the internet) vs. what is relevant internal to the sketch.  Make changes to verify your understanding as necessary***.
* In terms of Particle.variable() and Particle.function() the string is externally visible as this is the name you see associated with the variable/function when accessing it from the cloud.
* The function inner working are hidden, only the return value is then returned to the cloud function as output. 
