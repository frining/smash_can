const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>


<div>
	 <span id="ADCValue">0</span><br>
</div>
<script>

setInterval(function() {
  getData();
}, 5000); 

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
</script>

</body>
</html>
)=====";
