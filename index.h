const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>Light Theme</title>
	</head>
	<body>
		<!-- Main Container -->
		<div class="container"> 
			<!-- Header -->
			<header class="header">
				<h4 class="logo">SMART HOME<br>
				</h4>
			</header>
			<div class="controlBox">
				<div class="tab">
					<button class="tablinks" onclick="location.href='http://192.168.1.72'">Bedroom</button>
					<button class="tablinks active" onclick="openCity(event, 'Workingroom')">Working Room</button>
					<button class="tablinks" onclick="openCity(event, 'Kitchen')">Kitchen</button>
				</div>

				<div id="Bedroom" class="tabcontent">
					<h3>Bedroom</h3>
				</div>
			</div>

			<div id="Workingroom" class="tabcontent">					
				<center>
					<h3><div id="temp"></div></h3>
					<table class="tg">
					  <tr>
						<th class="tg-0lax">Room</th>
						<td class="tg-0lax">
							<div class="onoffswitch">
								<input type="checkbox" name="onoffswitch" class="onoffswitch-checkbox" onclick="sendData1()" id="myonoffswitch1">
								<label class="onoffswitch-label" for="myonoffswitch1">
									<span class="onoffswitch-inner"></span>
									<span class="onoffswitch-switch"></span>
								</label>
							</div>
						</td>
					  </tr>
					  <tr>
					  </tr>
					  <tr style="margin-top:10px">
						<th class="tg-0lax">Hole</th>
						<td class="tg-0lax">
							<div class="onoffswitch">
								<input type="checkbox" name="onoffswitch2" class="onoffswitch-checkbox" onclick="sendData2()" id="myonoffswitch2">
								<label class="onoffswitch-label" for="myonoffswitch2">
									<span class="onoffswitch-inner"></span>
									<span class="onoffswitch-switch"></span>
								</label>
							</div>
						</td>
					  </tr>
					</table>
				</center>
			</div>

			<div id="Kitchen" class="tabcontent">
				<h3>Kitchen</h3>
				<div class="onoffswitch">
					<input type="checkbox" name="onoffswitch3" class="onoffswitch-checkbox" id="myonoffswitch3" checked>
					<label class="onoffswitch-label" for="myonoffswitch3">
						<span class="onoffswitch-inner"></span>
						<span class="onoffswitch-switch"></span>
					</label>
				</div>
				<div class="onoffswitch">
					<input type="checkbox" name="onoffswitch4" class="onoffswitch-checkbox" id="myonoffswitch4" checked>
					<label class="onoffswitch-label" for="myonoffswitch4">
						<span class="onoffswitch-inner"></span>
						<span class="onoffswitch-switch"></span>
					</label>
				</div>
			</div>

			<script>
				document.getElementById("Workingroom").style.display = "block";
				function openCity(evt, cityName) {
					var i, tabcontent, tablinks;
					tabcontent = document.getElementsByClassName("tabcontent");
					for (i = 0; i < tabcontent.length; i++) {
						tabcontent[i].style.display = "none";
					}
					tablinks = document.getElementsByClassName("tablinks");
					for (i = 0; i < tablinks.length; i++) {
						tablinks[i].className = tablinks[i].className.replace(" active", "");
					}
					document.getElementById(cityName).style.display = "block";
					evt.currentTarget.className += " active";
				}

				function sendData1() {
					var xhttp = new XMLHttpRequest();
					xhttp.onreadystatechange = function() {
						if (this.readyState == 4 && this.status == 200) {
							this.responseText;
						}
					};
					if(document.getElementById("myonoffswitch1").checked == true)
						xhttp.open("GET", "setLED?LEDstate=0&LEDtype=1", true);
					else if(document.getElementById("myonoffswitch1").checked == false)
						xhttp.open("GET", "setLED?LEDstate=1&LEDtype=1", true);
					xhttp.send();
				}

				function sendData2() {
					var xhttp = new XMLHttpRequest();
					xhttp.onreadystatechange = function() {
					if (this.readyState == 4 && this.status == 200) {
						this.responseText;
					}
					};
					if(document.getElementById("myonoffswitch2").checked == true)
						xhttp.open("GET", "setLED?LEDstate=0&LEDtype=2", true);
					else if(document.getElementById("myonoffswitch2").checked == false)
						xhttp.open("GET", "setLED?LEDstate=1&LEDtype=2", true);
					xhttp.send();
				}

				setInterval(function() {
					// Call a function repetatively with 2 Second interval
					getData1();
					getData2();
					getHumi();
				}, 2000); //2000mSeconds update rate

				function getData1() {
					var xhttp = new XMLHttpRequest();
					xhttp.onreadystatechange = function() {
						if (this.readyState == 4 && this.status == 200) {
							if(this.responseText==1)
								document.getElementById("myonoffswitch1").checked = true;
							else if(this.responseText==0)
								document.getElementById("myonoffswitch1").checked = false;
						}
					};
					xhttp.open("GET", "readADC?LEDtype=1", true);
					xhttp.send();
				}

				function getData2() {
					var xhttp = new XMLHttpRequest();
					xhttp.onreadystatechange = function() {
						if (this.readyState == 4 && this.status == 200) {
							if(this.responseText==1)
								document.getElementById("myonoffswitch2").checked = true;
							else if(this.responseText==0)
								document.getElementById("myonoffswitch2").checked = false;
						}
					};
					xhttp.open("GET", "readADC?LEDtype=2", true);
					xhttp.send();
				}

				function getHumi() {
					var xhttp = new XMLHttpRequest();
					xhttp.onreadystatechange = function() {
						if (this.readyState == 4 && this.status == 200) {
							document.getElementById("temp").innerHTML  = this.responseText;
						}
					};
					xhttp.open("GET", "handleTemp", true);
					xhttp.send();
				}
			</script>
		</div>
		<style type="text/css">
			/* Body */
			body {
				font-family: Cambria, "Hoefler Text", "Liberation Serif", Times, "Times New Roman", serif;
				background-color: #d2a3ffa3;
				margin: 0;
			}
			/* Container */
			.container {
				width: 97%;
				margin-left: auto;
				margin-right: auto;
			}
			/* Header */
			header {
				height: 50px;
				background-color: #3a9ece;
				border: 1px solid #FFFFFF;
				margin-top: 15px;
				border-radius: 3px;
			}
			.logo {
				color: #fff;
				font-weight: bold;
				margin-left: auto;
				letter-spacing: 5px;
				text-align: center;
				--padding-top: 15px;
				line-height: 2.5em;
				font-size: 22px;
				margin-top: 0px;
				margin-right: 0px;
				margin-bottom: 0px;
				margin-left: 0px;
			}
			.hero_header {
				color: #FFFFFF;
				text-align: center;
				margin: 0;
				letter-spacing: 4px;
			}
			.button {
				width: 200px;
				margin-top: 40px;
				margin-right: auto;
				margin-bottom: auto;
				margin-left: auto;
				padding-top: 20px;
				padding-right: 10px;
				padding-bottom: 20px;
				padding-left: 10px;
				text-align: center;
				vertical-align: middle;
				border-radius: 0px;
				text-transform: uppercase;
				font-weight: bold;
				letter-spacing: 2px;
				border: 3px solid #FFFFFF;
				color: #FFFFFF;
				transition: all 0.3s linear;
			}
			.button:hover {
				background-color: #6DC7D0;
				color: #FFFFFF;
				cursor: pointer;
			}
			.copyright {
				text-align: center;
				padding-top: 20px;
				padding-bottom: 20px;
				background-color: #717070;
				color: #FFFFFF;
				text-transform: uppercase;
				font-weight: lighter;
				letter-spacing: 2px;
				border-top-width: 2px;
			}
			footer {
				background-color: #B3B3B3;
				padding-top: 60px;
				padding-bottom: 60PX;
			}
			/* Mobile */
			@media (max-width: 320px) {
				.hero_header {
					padding-left: 10px;
					padding-right: 10px;
					line-height: 22px;
					text-align: center;
					letter-spacing: 1px;
				}
			}

			/* Small Tablets */
			@media (min-width: 321px)and (max-width: 767px) {
				.logo {
					width: 100%;
					text-align: center;
					margin-top: 0px;
					margin-right: 0px;
					margin-bottom: 0px;
					margin-left: 0px;
				}
			}

			/* Small Desktops */
			@media (min-width: 768px) and (max-width: 1096px) {
				.text_column {
					width: 100%;
				}
				.thumbnail {
					width: 48%;
				}
				.text_column {
					width: 90%;
					margin: 0;
					padding: 20px;
				}
				.intro .column p {
					width: 80%;
				}
			}

			/* Style the tab */
			.tab {
				overflow: hidden;
				border: 1px solid #ccc;
				background-color: #f1f1f1;
				border-radius: 3px;
			}

			/* Style the buttons inside the tab */
			.tab button {
				background-color: inherit;
				float: left;
				border: none;
				outline: none;
				cursor: pointer;
				padding: 14px 16px;
				transition: 0.3s;
				font-size: 17px;
			}

			/* Change background color of buttons on hover */
			.tab button:hover {
				background-color: #ddd;
			}

			.tablinks {
				border-radius: 8px;
				width: 33.33%;
			}

			/* Create an active/current tablink class */
			.tab button.active {
				background-color: #ccc;
			}

			/* Style the tab content */
			.tabcontent {
				display: none;
				padding: 6px 12px;
				border: 1px solid #9C0BBC;
				border-top: none;
			}
			/* Style the tab content */
			.controlBox {
				margin-top: 10px;
			}
			.onoffswitch {
				position: relative; width: 90px;
				-webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;
			}
			.onoffswitch-checkbox {
				display: none;
			}
			.onoffswitch-label {
				display: block; overflow: hidden; cursor: pointer;
				border: 2px solid #999999; border-radius: 20px;
			}
			.onoffswitch-inner {
				display: block; width: 200%; margin-left: -100%;
				transition: margin 0.3s ease-in 0s;
			}
			.onoffswitch-inner:before, .onoffswitch-inner:after {
				display: block; float: left; width: 50%; height: 30px; padding: 0; line-height: 30px;
				font-size: 19px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;
				box-sizing: border-box;
			}
			.onoffswitch-inner:before {
				content: "ON";
				padding-left: 10px;
				background-color: #4D9EC7; color: #FFFFFF;
			}
			.onoffswitch-inner:after {
				content: "OFF";
				padding-right: 10px;
				background-color: #EEEEEE; color: #999999;
				text-align: right;
			}
			.onoffswitch-switch {
				display: block; width: 17px; margin: 6.5px;
				background: #FFFFFF;
				position: absolute; top: 0; bottom: 0;
				right: 56px;
				border: 2px solid #999999; border-radius: 20px;
				transition: all 0.3s ease-in 0s; 
			}
			.onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner {
				margin-left: 0;
			}
			.onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch {
				right: 0px; 
			}
    </style>

		<!-- Main Container Ends -->		
	</body>
</html>
)=====";
