# Studio Questions / Replies

***Q1. How can Particle's Cloud Console assist debugging and development of publish-subscribe:***
If you publish state to the stream whenever state is changed, as done in the studio, then you should be able to see the state of the device through the particle cloud console in the events-log section. This is analogous to Javascript console.log(state) whenever the state is changed in a callback function.

***Q2. Explain what the existing code does and how it works:***
setPowered() takes in an argument, and appends that to argument in functionData. We have two functions for success and failure that are described. Then we call the function described in functionData, and then the promises take care of the results. The setup function is a stream for getting the states as the are pushed.

***Q3. Why is the publish-subscribe approach a better choice for updating the UI than calling a function?:***
In the publish-subscribe method the publishers do not need to program the messages to be sent directly to specific receivers. In regards to updating the UI, the publish-subscribe method allows UI to just subscribe to state change events, and the publishers can just send out states. It is much easier and more efficient than linking each sender and receiver directly.
