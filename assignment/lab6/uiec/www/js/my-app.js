// Initialize app
var myApp = new Framework7();
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

// If we need to use custom DOM library, let's save it to $$ variable:
var $$ = Dom7;

// Add view
var mainView = myApp.addView('.view-main', {
    // Because we want to use dynamic navbar, we need to enable it for this view:
    dynamicNavbar: true
});

// Handle Cordova Device Ready Event
$$(document).on('deviceready', function() {
    console.log("Device is ready!");

    // Do something here for "about" page
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

    doorStatus = document.getElementById("doorStatus")
    lightStatus = document.getElementById("lightStatus")

    garage.setStateChangeListener(stateUpdate)
    garage.setup()

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
});


// Now we need to run the code that will be executed only for About page.

// Option 1. Using page callback for page (for "about" page in this case) (recommended way):
myApp.onPageInit('index', function (page) {
    console.log("haha this is on page int")


})
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
// Option 2. Using one 'pageInit' event handler for all pages:
$$(document).on('pageInit', function (e) {
    // Get page data from event data
    var page = e.detail.page;
    console.log(page)

    if (page.name === 'main') {
        // Following code will be executed for page with data-page attribute equal to "about"
        myApp.alert('Here comes main page');
    }
})

// Option 2. Using live 'pageInit' event handlers for each page
$$(document).on('pageInit', '.page[data-page="about"]', function (e) {
    // Following code will be executed for page with data-page attribute equal to "about"
    myApp.alert('Here comes About page');
})