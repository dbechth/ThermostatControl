const char ThermostatIndexNew[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
	<head>
		<title>BBQ Controller</title>
	</head>
	<body style="background-color:#cccccc; font-family: Arial, Helvetica, Sans-Serif; Color:#000088; font-size:50px">
		<h1 align="center">&#127830;BBQ&#127830;<br>
		CONTROLLER</h1>

		<p>Smoker Temp: <span id="smokerTemp">?</span>&#176;F</p>
		
		Set Point:
		<br>
		<input type="text" style="font-size:50px; height:125px; width:49%" id="mashTempF" value="?"/>
		<button type="button" style="font-size:50px; height:125px; width:49%" onClick="set(&quot;mashTempF&quot;)">Set</button>
		<br>
		TempF to Pulse Heat (boilMode Only):
		<br>
		<input type="text" style="font-size:50px; height:125px; width:49%" id="pulseHeat" value="?"/>
		<button type="button" style="font-size:50px; height:125px; width:49%" onClick="set(&quot;pulseHeat&quot;)">Set</button>
		<br>
		Boil On Time :
		<br>
		<input type="text" style="font-size:50px; height:125px; width:49%" id="boilOnTime" value="?"/>
		<button type="button" style="font-size:50px; height:125px; width:49%" onClick="set(&quot;boilOnTime&quot;)">Set</button>
		<br>
		Boil Off Time :
		<br>
		<input type="text" style="font-size:50px; height:125px; width:49%" id="boilOffTime" value="?"/>
		<button type="button" style="font-size:50px; height:125px; width:49%" onClick="set(&quot;boilOffTime&quot;)">Set</button>
		<br>
		Correction Value :
		<br>
		<input type="text" style="font-size:50px; height:125px; width:49%" id="correctionValue" value="?"/>
		<button type="button" style="font-size:50px; height:125px; width:49%" onClick="set(&quot;correctionValue&quot;)">Set</button>
		
		<script>
		
				setInterval(function() {
					getBtn("heatON");
					getBtn("heatOFF");
					getBtn("mashMode");
					getBtn("boilMode");
					get("upTime");
					get("kettleTemp");

					//Commenting out to avoid changing data on the user. Refresh the whole page if needed.
					//get("mashTempF");
					//get("pulseHeat");
					//get("boilOnTime");
					//get("boilOffTime");
					//get("correctionValue");
					}, 5000); //60000ms update rate
			function set(id){
				var xhttp = new XMLHttpRequest();
				var value = document.getElementById(id).value;
				document.getElementById(id).value = "?";
				xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
					get("mashTempF");
					get("pulseHeat");
					get("boilOnTime");
					get("boilOffTime");
					get("correctionValue");
				}
				};
				xhttp.open("GET", "set?"+id+"="+value, true);
				xhttp.send();
				
			}
			function get(id) {
				var xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
				document.getElementById(id).innerHTML =  this.responseText;
				document.getElementById(id).value =  this.responseText;
				}
				};
				xhttp.open("GET", "get?"+id, true);
				xhttp.send();
			}
			
			function setBtn(id){
				var xhttp = new XMLHttpRequest();
				var value = document.getElementById(id).value;
				document.getElementById(id).style.backgroundColor = "#CB2717";
				xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
					getBtn("heatON");
					getBtn("heatOFF");
					getBtn("mashMode");
					getBtn("boilMode");
				}
				};
				xhttp.open("GET", "set?"+id, true);
				xhttp.send();
				
			}
			function getBtn(id) {
				var xhttp = new XMLHttpRequest();
				xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
					if(this.responseText=="0"){
						document.getElementById(id).style.backgroundColor = "#CFCFCF";
					}
					else if(this.responseText=="1"){
						document.getElementById(id).style.backgroundColor = "#61CB17";
					}
					else{
						document.getElementById(id).style.backgroundColor = "#CB2717";
					}
				}
				};
				xhttp.open("GET", "get?"+id, true);
				xhttp.send();
			}
			
			get("upTime");
			get("kettleTemp");
			get("mashTempF");
			get("pulseHeat");
			get("boilOnTime");
			get("boilOffTime");
			get("correctionValue");
			getBtn("heatON");
			getBtn("heatOFF");
			getBtn("mashMode");
			getBtn("boilMode");
		</script>
	</body>
</html>
)=====";
