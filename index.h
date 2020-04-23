const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>


<div>
    <a>Human distance: </a>
   <span id="ADCValue">0</span><br>
</div>

<div>
    <a>Battery level: </a>
   <span id="BATValue">0</span><br>
</div>

<div>
    <a>Rubbish distance: </a>
   <span id="RUBValue">0</span><br>
</div>
<script>

setInterval(function() {
  getData();
  getData1();
  getData2();
}, 1000); 

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}


function getData1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("BATValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "batLevel", true);
  xhttp.send();
}


function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("RUBValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "rubLevel", true);
  xhttp.send();
}
</script>

</body>
</html>
)=====";
