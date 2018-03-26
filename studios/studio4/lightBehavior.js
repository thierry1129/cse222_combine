

// Setup variables to access commonly used DOM elements
function wait(timeInSeconds) {
  var start = Date.now();
  var endTime = start + timeInSeconds*1000;
  while(Date.now()<endTime);
}

// Create an object representing the light
// Light is remote.  We send it RGB tuple as a string.
// Get initial state (Array of properties: on/off, color tuple, Auto Off time, Auto off on/off)
// Callbacks return: status ("on" or "off") and RGB color as an RGB tuple
// Calls can set state: On, off, color, autoOff(on/off),
var light = {
    // state variables for simulated lamp
    r: 0,
    g: 0,
    b: 0,
    powered: true,
    autoOffEnabled: true,
    autoOffTime: 30,
    stateChangeHandler: null,

    // getState: Get the initial state and eventually pass it to the "callback" function
    getState: function(callback) {
      var state = { "r":this.r,
                    "g":this.g,
                    "b":this.b,
                    "powered":this.powered,
                    "autoOffEnabled":this.autoOffEnabled,
                    "autoOffTime":this.autoOffTime};
      console.log("getState")
       setTimeout(function () {callback(state)},  1000);
    },

    // ****** Simple setter functions *******
    setColor: function(color) {
      this.r = color.r;
      this.g = color.g;
      this.b = color.b;

      this.stateChange();
    },
    setPowered: function(power) {
      this.powered = power;
      if(this.powered && this.autoOffEnabled) {
        var autoOff = this;
        setTimeout(function() {  autoOff.autoOff() }, 1000)
      }
      this.stateChange();
    },
    autoOff: function() {
      this.powered = false
      this.stateChange()
    },
    setAutoOffEnabled: function(enabled) {
      this.autoOffEnabled = enabled
      this.stateChange()
    },
    setAutoOffTime: function(time) {
      this.autoOffTime = enabled
      this.stateChange()
    },
    setStateChangeHandler: function(handler) {
      this.stateChangeHandler = handler;
      this.stateChange();
    },
    stateChange: function(callback) {

        var state = { "r":this.r,
            "g":this.g,
            "b":this.b,
            "powered":this.powered,
            "autoOffEnabled":this.autoOffEnabled,
            "autoOffTime":this.autoOffTime};
        console.log("getStatechange")
        currentColor.style.background = rgb(this.r, this.g, this.b)
        setTimeout(function () {callback(state)},  1000);
      }
    }


// Variables representing elements on the "Basic" screen
var currentColor
var targetColor
var redSlider
var redLabel
var greenSlider
var greenLabel
var blueSlider
var blueLabel
var onOffSwitch
var onOffSwitchLabel

// Variables representing elements on the "Settings" screen
var autoOffSwitch
var autoOffSwitchLabel
var autoOffTimeSlider


// Utility Function: Convert an RGB values (in tegers) to a string for use in HTML/CSS styles.
function rgb(r,g,b) {
  return "rgb(" + r + "," + g + "," + b + ")";
}

// Update the current color to reflect the positions of the sliders
function updateTargetColor() {
  var red = Math.round(redSlider.value*255/100)
  var green = Math.round(greenSlider.value*255/100)
  var blue = Math.round(blueSlider.value*255/100)
  targetColor.style.background = rgb(red, green, blue)
}

function setColorClicked(event) {
  var red = Math.round(redSlider.value*255/100)
  var green = Math.round(greenSlider.value*255/100)
  var blue = Math.round(blueSlider.value*255/100)
    light.setColor(rgb(red,green,blue))
    currentColor.style.background = rgb(red, green, blue)
  // TODO: Pass the choice of colors to the light.
}

function redSliderChange(event) {
  redLabel.innerText = redSlider.value
  updateTargetColor()
}
function greenSliderChange(event) {
  greenLabel.innerText = greenSlider.value
  updateTargetColor()
}
function blueSliderChange(event) {
  blueLabel.innerText = blueSlider.value
  updateTargetColor()
}

function autoOffSliderChange(event) {
  autoOffTimeLabel.innerText = autoOffTimeSlider.value + "s"
}

function autoOffUpdate() {
  if(autoOffSwitch.checked) {
    autoOffTimeSlider.disabled = false;
  } else {
    autoOffTimeSlider.disabled = true;
  }
  // Send to light
  light.setAutoOffEnabled(autoOffSwitch.checked)
}

function onOffUpdate() {
  light.setPowered(onOffSwitch.checked)
}

function stateUpdate(newState) {
  console.log("New State")
  console.dir(newState);

  loadingPage(false)

  // Adjust state elements that may be changed on light / come from light
  autoOffSwitch.checked = newState.autoOffEnabled;

  // Note "change" function
  autoOffTimeSlider.value = newState.autoOffTime;
  autoOffTimeLabel.innerText = autoOffTimeSlider.value + "s"
  onOffSwitch.checked = newState.powered;
  currentColor.style.background = rgb(newState.r, newState.g, newState.b)
}

function loadingPage(value) {
  document.getElementById("loading").hidden = !value;
  document.getElementById("allControls").hidden = value;
}

// On startup:  Things to do once the page is fully loaded and the DOM is configured
document.addEventListener("DOMContentLoaded", function(event) {
  console.log("Document Loaded")
  currentColor = document.getElementById("currentColor")
  targetColor = document.getElementById("targetColor")
  redSlider = document.getElementById("redSlider")
  redLabel = document.getElementById("redLabel")
  greenSlider = document.getElementById("greenSlider")
  greenLabel = document.getElementById("greenLabel")
  blueSlider = document.getElementById("blueSlider")
  blueLabel = document.getElementById("blueLabel")
  onOffSwitch = document.getElementById("onOffSwitch")
  onOffSwitchLabel = document.getElementById("onOffSwitchLabel")

  // Variables representing elements on the "Settings" screen
  autoOffSwitch = document.getElementById("autoOffSwitch")
  autoOffSwitchLabel = document.getElementById("autoOffSwitchLabel")
  autoOffTimeSlider = document.getElementById("autoOffTimeSlider")

  // Event handlers
  document.getElementById("setColorButton").addEventListener("click", setColorClicked)
  document.getElementById("redSlider").addEventListener("change", redSliderChange)
  document.getElementById("greenSlider").addEventListener("change", greenSliderChange)
  document.getElementById("blueSlider").addEventListener("change", blueSliderChange)
  autoOffTimeSlider.addEventListener("change", autoOffSliderChange)
  autoOffSwitch.addEventListener("click", autoOffUpdate)
  onOffSwitch.addEventListener("click", onOffUpdate)

  // Getting the initial state
  console.log("Getting Initial State")
  loadingPage(true)
  light.getState(stateUpdate)
  updateTargetColor()
})
