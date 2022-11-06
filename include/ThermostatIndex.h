const char ThermostatIndex[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<link href='https://fonts.googleapis.com/css?family=Audiowide' rel='stylesheet'>
<title>Thermostat</title>
</head>
<body style = "background-color:#cccccc; font-family: Arial, Helvetica, Sans-Serif; Color:#000088; font-size:40px">
<h1 align = "center">Thermostat</h1>

<div align = "center">Temperature: <span id = "temperature"> ? </span>&#176;F</div>
<div align = "center">Set Temp: <span id = "SetTemp"> ? </span>&#176;F</div>

<div align = "center"> <button type = "button" style = "font-size:40px; height:250px; width:40%;" id = "btnIncrease" onClick = "increaseSetpoint()">+</button></div>
<div align = "center"> <button type = "button" style = "font-size:40px; height:250px; width:40%;" id = "btnDecrease" onClick = "decreaseSetpoint()">-</button></div>
<br>
<div align = "center">Quick Set</div>
<div align = "center"> <button type = "button" style = "font-size:40px; height:100px; width:25%;" id = "startup" onClick = "setSetpoint(75)">75</button>
<button type = "button" style = "font-size:40px; height:100px; width:25%;" id = "shutdown" onClick = "setSetpoint(85)">85</button></div>
      
    <script>
    setInterval(function() {
      // Call a function repetatively
              getTemperature();
    }, 30000); //60000ms update rate

    function getTemperature() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temperature").innerHTML =  this.responseText;
        }
      };
      xhttp.open("GET", "getTemperature", true);
      xhttp.send();
    }

    function getSetpoint() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("SetTemp").innerHTML =  this.responseText;
        }
      };
      xhttp.open("GET", "getSetpoint", true);
      xhttp.send();
    }

    function increaseSetpoint(){
    var value = parseInt(document.getElementById("SetTemp").innerHTML) + 1;
    setSetpoint(value);
    }

    function decreaseSetpoint(){
    var value = parseInt(document.getElementById("SetTemp").innerHTML) - 1;
    setSetpoint(value);
    }

    function setSetpoint(setpoint) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("SetTemp").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "setSetpoint?setpoint="+setpoint, true);
      xhttp.send();
    }
    
    getTemperature();
    getSetpoint();
    </script>
  </body>
</html>
)=====";
