var loadingSign
var loginPg
var registerPg
var mainPg
var advancedPg
var registerPg
var loginPg
var mainPg
var advancedPg

var doorStatus
var lightStatus
var garageAutoCloseCheckbox
var garageShutTimeSlider
var garageTimeDetailedText

var lightAutoCheckbox
var lightShutTimeSlider
var lightTimeText
var brightnessRange

var submitDoorBtn
var submitLightBtn
var submitBrightBtn

var firstLoad = true


var stateString

function setStatHtml(id,message){
    document.getElementById(id).innerHTML = message
}

function warning(){
    garage.setup()
}

// On startup:  Things to do once the page is fully loaded and the DOM is configured
window.addEventListener("load",function(event) {
    firstLoad = true;

    console.log("Document Loaded")
    loginPg = document.getElementById("loginPg")
    registerPg = document.getElementById("registerPg")
    mainPg = document.getElementById("mainPg")
    mainPg.hidden = false
    advancedPg = document.getElementById("advancedPg")
    var register_button = document.getElementById("register_button")
    var login_button = document.getElementById("login_button")
    var clear_button = document.getElementById("clear_button")
    loadingSign = document.getElementById("loading")
    register_button.addEventListener("click",function(){
        changePage("loginPg","registerPg");
    })
    login_button.addEventListener("click", function(){
        changePage("loginPg","mainPg")
        //from login to main, need to get garage status
        getInitialGarage()
    })
    loginPg.hidden = true;
    registerPg.hidden = true
    mainPg.hidden = true
    advancedPg.hidden = true
    loadingSign.hidden = true
   // window.onbeforeunload = warning;

    clear_button.addEventListener("click",function(){
        window.location.reload(false)
    })

    var cancel_button_reg = document.getElementById("cancel_button_reg")
    cancel_button_reg.addEventListener("click",function(){
        changePage("registerPg","loginPg")
    })

    var register_button_reg = document.getElementById("register_button_reg")
    register_button_reg.addEventListener("click",function(){
        changePage("registerPg","mainPg")
        getInitialGarage()
    })

    var advanced_button = document.getElementById("advanced_button")
    advanced_button.addEventListener("click",function(){
        changePage("mainPg","advancedPg")
    })

    var logout_button = document.getElementById("logout_button")
    logout_button.addEventListener("click",function(){
        changePage("mainPg","loginPg")
        garage.reset()
    })

    var advanced_to_main = document.getElementById("advanced_to_main")
    advanced_to_main.addEventListener("click",function(){
        changePage("advancedPg","mainPg")
    })


    //below are variables fr main page data sections -->
    // regular door button

    //set up garage onject and configure webpage based on states
    garage.setStateChangeListener(stateUpdate)
    garage.setup()
    doorStatus = document.getElementById("doorStatus")
    lightStatus = document.getElementById("lightStatus")



    var changeDoor = document.getElementById("changeDoor")
    changeDoor.addEventListener("click",function(){
        // when pressing on the door's control button, call garage change door state with old door state string
        garage.changeDoorSt();

    })

    var changeLight = document.getElementById("changeLight")
    changeLight.addEventListener("click",function(){
        garage.changeLightSt()
    })

    // below are variables fr advanced feature pages
    garageAutoCloseCheckbox = document.getElementById("garageAutoClose")
    garageShutTimeSlider = document.getElementById("garageShutTime")
    garageShutTimeSlider.addEventListener("change" ,garageTimeChange)
    garageTimeDetailedText = document.getElementById("garageTimeDetailed")
    garageTimeDetailedText.addEventListener("change",garageTimeTextChange)

    lightAutoCheckbox = document.getElementById("lightAuto")
    lightShutTimeSlider = document.getElementById("lightShutTime")
    lightShutTimeSlider.addEventListener("change",lightTimeChange)
    lightTimeText = document.getElementById("lightDetailedTime")
    lightTimeText.addEventListener("change",lightTimeTextChange)
    brightnessRange = document.getElementById("brightnessRange")

    submitDoorBtn = document.getElementById("submitDoor")
    submitDoorBtn.addEventListener("click",sbmtDoor)

    submitLightBtn = document.getElementById("submitLight")
    submitLightBtn.addEventListener("click",sbmtLight)

    submitBrightBtn = document.getElementById("submitBrightness")
    submitBrightBtn.addEventListener("click",sbmtBrightness)

})

// below are helper method to display correct values on the advanced page

function garageTimeChange(){
    garageTimeDetailedText.value = garageShutTimeSlider.value
    garageAutoCloseCheckbox.checked = true
}
function lightTimeChange(){
    lightTimeText.value=lightShutTimeSlider.value
    lightAutoCheckbox.checked = true
}
function garageTimeTextChange(){
    garageShutTimeSlider.value = garageTimeDetailedText.value
    garageAutoCloseCheckbox.checked = true
}
function lightTimeTextChange(){
    lightShutTimeSlider.value = lightTimeText.value
    lightAutoCheckbox.checked = true
}

function getInitialGarage(){
    console.log("getting the initial state for garage ")
    loadingPage(true)
    garage.getState(stateUpdate)

}
/**
 *
 *
 * @type advfeature
 * @param none
 * submit the advanced feature data to the garage object
 *
 */
function sbmtDoor(){

    garage.setDoorAutoClose(garageAutoCloseCheckbox.checked,garageShutTimeSlider.value)
}

function sbmtLight(){
    garage.setLightAutoClose(lightShutTimeSlider.value)
}

function sbmtBrightness(){
    garage.setLightBrightness(brightnessRange.value)
}



/**
 *
 *
 * @type UIinteract
 * @param status code of the door
 * change the priting of door status
 *
 */
function printDoorStat(statCode){
    switch(statCode) {
        case 0:
            doorStatus.innerHTML="closed"
            break;
        case 1:
            doorStatus.innerHTML="opening"
            break;
        case 2:
            doorStatus.innerHTML="open Fault"
            break;
        case 3:
            doorStatus.innerHTML="opened"
            break;
        case 4 :
            doorStatus.innerHTML = "closing"
            break;
        case 5 :
            doorStatus.innerHTML = "close fault"
            break;
        case 6:
            doorStatus.innerHTML = "close prepare "
            break;
        case 7 :
            doorStatus.innerHTML = "open prepare"
            break;
        default:
            doorStatus.innerHTML="closed"
    }
}

/**
 * update the UI using the new state
 *
 * @type updateUI
 * @param newState
 *
 */

function stateUpdate(newState) {

    console.log(firstLoad + "this is first log  or not ")

    console.log("StateUpdate function in garageapp")
    console.dir(newState);
    // loadingPage(false)
    printDoorStat(newState.doorStats)


    lightStatus.innerHTML = newState.lightStats ? "on" : "off"
    garageAutoCloseCheckbox.checked = newState.autoClose
    garageShutTimeSlider.value = newState.autoCloseTime
    garageTimeDetailedText.innerHTML = newState.autoCloseTime


    lightAutoCheckbox.checked = newState.lightAutoOff
    lightShutTimeSlider.value= newState.lightAutoOffTime
    lightTimeText.innerHTML = newState.lightAutoOffTime
    brightnessRange.value=newState.lightBrightness

    // if (firstLoad){
        mainPg.hidden = false
    //     firstLoad = false
    // }

}

/**
 * update the UI to shift from old to new page
 *
 * @type updateUI
 * @param previous page name
 * @param target page name
 *
 */

function changePage(previous, target){
    document.getElementById(previous).hidden=true;
    document.getElementById(target).hidden = false;
}




function showPwd() {
    var x = document.getElementById("pwdinput");
    if (x.type === "password") {
        x.type = "text";
    } else {
        x.type = "password";
    }
}