
# Summarize Highlights from Prep Material (Technician)

- Spend approximately 10-15 minutes summarizing highlights from the prep material.
- Do ***NOT*** use outside resources except where/when noted.  The answers should be based only on the group's knowledge.
- Be sure to discuss the content with your group and that everyone agrees on the answers.
- Answers can be brief/informal.


***Q1. What is meant by "floating input"?***
A floating input gate is an input that is not connected to anything. It’s best to either tie it to ground or pull it up to vcc using a 10k resistor.
***Q2. What is meant by "pull-up" resistor?  And why are they often used with buttons?***
 "tie" all unused inputs either high or low, so the circuit will always be in a consistent and predictable state.
 When the button is pressed, the input pin is pulled low.When the button is not pressed, the input pin is pulled high. Its easier to use button to represent the state.
***Q3. Assume that a person has written a sketch that configures `D1` as an output and that it's turned `HIGH` as soon as the sketch starts and left `HIGH`.  They later rewire the Photon and connect `D1` through a button to Ground.  When they plug in the Photon it runs the the previous code before they have a chance to reprogram it.  Assuming the button has a resistance of 1 Ohm, how much current would pass through the output pin if the button is accidentally pushed while the pin is still configured as an output?  Are there any concerns about this happening?:***
I = V/R.  3.3/1 = 3.3A
