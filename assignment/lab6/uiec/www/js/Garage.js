var doorStats = {
    opened: 3,
    closed: 0,
    opening: 1,
    openFault: 2,
    closing: 4,
    closeFault: 5,
    closePrepare: 6,
    openPrepare: 7,
    autoClose: false,
    autoCloseTime: 0,


};

function newDoorEvent(data) {

    stateString = data.data


    var newDoorState = parseInt(stateString.charAt(0))
    if (stateString.charAt(1)=='t'){
        lightStatas.ifOn = true
        garage.lightStats = lightStatas.ifOn

    }else {
        lightStatas.ifOn = false
        garage.lightStats = lightStatas.ifOn
    }

    if (stateString.charAt(2)=='t'){
        doorStats.autoClose = true;
        doorStats.autoCloseTime = parseInt(stateString.substring(3,stateString.length-1));
        garage.autoClose = doorStats.autoClose
        garage.autoCloseTime = doorStats.autoCloseTime
    }else{
        doorStats.autoClose = false;
        doorStats.autoCloseTime = 0;
        garage.autoClose = doorStats.autoClose
        garage.autoCloseTime = doorStats.autoCloseTime
    }
    garage.doorStats = newDoorState
    garage.stateChange()
}


var token = '5cce400f7230b6f844c47d8a4766bfed00c593e3';
var particle = new Particle();
var usrName = 'terrylu@wustl.edu';
var pswd = 'LSLterry961129';
var deviceId = '280028000d47343438323536'

var lightStatas = {
    ifOn: false,
    brightness: 0,
    autoOff: true,
    autoOffTime: 0,
};


var garage = {
    doorStats: doorStats.closed, // door is default closed
    lightStats: lightStatas.ifOn,
    lightBrightness: lightStatas.brightness,
    lightAutoOff: lightStatas.autoOff,
    lightAutoOffTime: lightStatas.autoOffTime,

    autoClose: doorStats.autoClose,
    autoCloseTime: doorStats.autoCloseTime,

    // lab 4

    stateChangeListener: null,
    particle: null,

    changeDoorSt: function () {
        // this.doorStats = state;
        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: "regButton",
            auth: token
        }).then(function (data) {
            console.log("calling web particle funcion success")
        }, function (err) {
            console.log('An error occurred while pressing change door button on web page ')
        })


    },

    setStateChangeListener: function (aListener) {
        this.stateChangeListener = aListener;
    },

    stateChange: function () {
        if (this.stateChangeListener) {
            var state = {
                doorStats: this.doorStats,
                lightStats: this.lightStats,
                lightBrightness: this.lightBrightness,
                lightAutoOff: this.lightAutoOff,
                lightAutoOffTime: this.lightAutoOffTime,
                autoClose: this.autoClose,
                autoCloseTime: this.autoCloseTime,

            };
            this.stateChangeListener(state);
        }
    },
    setup: function () {

        particle.login({username: usrName, password: pswd}).then(
            function (data) {
                token = data.body.access_token;

            },
            function (err) {
                alert('Could not log in.', err);
            }
        );



        function onSuccess(stream) {
            // DONE:  This will "subscribe' to the stream and get the state"
            console.log("getEventStream success")
            stream.on('State_TEL_PHO', newDoorEvent)


        }

        function onFailure(e) {
            console.log("getEventStream call failed")
            console.dir(e)
        }

        particle.getEventStream({deviceId: deviceId, auth: token}).then(onSuccess, onFailure)

        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: "initialState",
            auth: token
        }).then(function (data) {
            alert("getting initial state success")
        }, function (err) {
            alert('an error occured while getting initial state  ')
        })

    },

    setDoorAutoClose: function (enabled2, time) {
        this.autoClose = enabled2
        this.autoCloseTime = time
        var autoArgument
        if (enabled2){
            autoArgument = "at"+String(time)
        }else{
            autoArgument = "af0"
        }
        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: autoArgument,
            auth: token
        }).then(function (data) {
            alert("calling particle auto close door success")
        }, function (err) {
            alert('An error occurred while calling auto close door on particle ')
        })
        //this.stateChange()

    },

    setLightAutoClose: function (time) {
        this.lightAutoOffTime = time


        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: "o"+time,
            auth: token
        }).then(function (data) {
            alert("calling particle auto close light success")
        }, function (err) {
            alert('An error occurred while calling auto close light on particle ')
        })
        //this.stateChange()

    },
    setLightBrightness: function(bright) {
        this.lightBrightness = bright
        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: "b" + bright,
            auth: token
        }).then(function (data) {
            alert("calling particle change light bright success")
        }, function (err) {
            alert('An error occurred while calling change light bright')
        })
    },


    changeLightSt: function () {
        var lightArgument
        if (garage.lightStats){
            lightArgument = "lf"
        }else{
            lightArgument = "lt"
        }

        console.log("in garage changelight st ")

        particle.callFunction({
            deviceId: deviceId,
            name: 'webRequest',
            argument: lightArgument,
            auth: token
        }).then(function (data) {
            console.log("calling web particle funcion success")
        }, function (err) {
            console.log('An error occurred while pressing change door button on web page ')
        })


    }
}