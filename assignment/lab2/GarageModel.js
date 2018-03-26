var doorStats = {
    closing: 3,
    closed : 0,
    opening :1,
    opened : 2,
    autoClose:false,
    autoCloseTime:0,



};
var lightStatas = {
    ifOn: false,
    brightness: 0,
    autoOff: false,
    autoOffTime: 0,


};


var garage = {
    doorStats: doorStats.closed, // door is default closed
    lightStats: lightStatas.ifOn,
    lightBrightness: lightStatas.brightness,
    lightAutoOff : lightStatas.autoOff,
    lightAutoOffTime: lightStatas.autoOffTime,


    autoClose: doorStats.autoClose,
    autoCloseTime: doorStats.autoCloseTime,

    getState: function(callback) {

        var state = { "doorStats":this.doorStats,
            "lightStats":this.lightStats,
            "lightBrightness":this.lightBrightness,
            "lightAutoOff":this.lightAutoOff,
            "lightAutoOffTime":this.lightAutoOffTime,
            "autoClose":this.autoClose,
            "autoCloseTime": this.autoCloseTime};

        console.log("getState")

        setTimeout(function () {callback(state)},  1000);
    },

    setLightPowered: function(power) {
        this.lightStats = power

        if(this.lightStats && this.lightAutoOff) {
            var autoOff = this;
            setTimeout(function() {  autoOff.autoOff() }, autoOff.lightAutoOffTime)
        }
        //this.stateChange();
    },
    setBrightness: function(bright){
        this.lightBrightness = bright

    },
    // automatically turn off the light after time
    autoOff: function() {
        this.lightStats = false
       // this.stateChange()
    },
    setLightAutoOffEnabled: function(enabled) {
        this.lightAutoOff = enabled
        //this.stateChange()
    },
    setAutoOffTime: function(time) {
        this.lightAutoOffTime = time
        //this.stateChange()
    },
    checkDoorStatus: function (state){
        switch(state){

            case 0:
                this.doorStats++;
                break;

            case 2:
                this.doorStats=0;
                break;
            default:
                break;
        }
    },

    changeDoorStat: function(previousState){
        // so previousState is the number passed in indicating the current door status
        var newState = (previousState+1)%4
        this.doorStats = newState
        this.lightStats = true

    },

    autoCloseFunc: function(){
        // ensure that right now the door is at fully opened status
        console.log("trying to autoclose the door ")
        if (this.doorStats!=2){
            alert("something is wrong with auto close feature ")
        }
        this.doorStats++;
        this.lightStats = true

    },
    setDoorAutoClose:function(enabled2){
        this.autoClose = enabled2
        //this.stateChange()

    },
    setDoorAutoCloseTime: function(time){
        this.autoCloseTime = time
        //this.stateChange()
    },

    stateChange: function(callback) {

        var state = { "doorStats":this.doorStats,
            "lightStats":this.lightStats,
            "lightBrightness":this.lightBrightness,
            "lightAutoOff":this.lightAutoOff,
            "lightAutoOffTime":this.lightAutoOffTime,
            "autoClose":this.autoClose,
            "autoCloseTime": this.autoCloseTime};

        console.log("stateChange")


        setTimeout(function () {callback(state)},  1000);
    },
    reset: function(){
        this.doorStats = doorStats.closed,
            this.lightStats = lightStatas.ifOn
        this.lightBrightness = lightStatas.brightness
        this.lightAutoOff = lightStatas.autoOff
        this.lightAutoOffTime = lightStatas.autoOffTime
        this.autoClose = doorstats.autoClose
        this.autoCloseTime = doorstats.autoCloseTime



    }

}











