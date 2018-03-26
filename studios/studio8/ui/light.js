
/*
  An object representing a remote, Wi-Fi controle IoT light.
  Features include:
     Ability to control RGB color.
     Ability to control Power
*/

// TODO: Add the access token and device ID
var myParticleAccessToken = "46b6f8b4285cd757dcb5eddf3035b0051577dbcb"
var myDeviceId =            "17002e000247353138383138"
var topic =                 "cse222Lights/thisLamp/color"

// NOTE: This callback is NOT in the light object to avoid mishandeling of "this"
// Consequently it explicitly changes properties of the global "light" object
// (This approach does not work well when there are multiple objects being interacted with)
function newLightEvent(objectContainingData) {
      // TODO: Parse the incoming state and update any listeners
      // Hints:
      //    1. Use console.dir() to show the state object on the console.
      //    2. Consider JSON.parse, but be aware that proper JSON enclosed property
      //       names in DOUBLE quotes ("proper":value)


      // DONE: Publish the state to any listeners
      light.stateChange()
    }


// Declare the light object
var light = {
    // state variables for the remote light
    r: 0,
    g: 100,
    b: 0,

    powered: false,

    // Variable used to track listener function
    stateChangeListener: null,

    // NOTE: A new object to access particle JavaScript functions
    particle: null,

    // ****** Simple setter functions *******
    setColor: function(color) {
        // TODO: Finish this function that will
        // Create an object with all the detals of the function call

    },

    setPowered: function(power) {
      // DONE: This is an example of calling a function
      this.powered = power
      var functionData = {
           deviceId:myDeviceId,
           name: "setLampPower",
           argument: ""+this.powered,
           auth: myParticleAccessToken
      }
      // Include functions to provide details about the process.
      function onSuccess(e) { console.log("setPower call success") }
      function onFailure(e) { console.log("setPowercall failed")
                             console.dir(e) }
      particle.callFunction(functionData).then(onSuccess,onFailure)
    },

    setStateChangeListener: function(aListener) {
      // DONE
      this.stateChangeListener = aListener;
    },

    stateChange: function() {
      // DONE
      // If there's a listener, call it with the data
      if(this.stateChangeListener) {
        var state = { r:this.r,
                      g:this.g,
                      b:this.b,
                      powered:this.powered};
          this.stateChangeListener(state);
      }
    },

    // NOTE: New setup function to do initial setup
    setup: function() {
      // Create a particle object
      particle = new Particle();

      // Get ready to subscribe to the event stream
      function onSuccess(stream) {
        // DONE:  This will "subscribe' to the stream and get the state"
        console.log("getEventStream success")
        stream.on('event', newLightEvent)

        // TODO: Get the initial state.  Call your function that will publish the state
        // NOTE: This is here in the callback to the subscribe --- it will request the state
        //       once successbully subscribed.
        var functionData = {
             deviceId:myDeviceId,
             name: "publishState",
             argument: "",
             auth: myParticleAccessToken
        }
        // Include functions to provide details about the process.
        particle.callFunction(functionData);
      }
      function onFailure(e) { console.log("getEventStream call failed")
                              console.dir(e) }
      // Subscribe to the stream
      particle.getEventStream( { name: topic, auth: myParticleAccessToken }).then(onSuccess, onFailure)
    }
}
