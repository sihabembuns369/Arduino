const char home[]PROGMEM=R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>

    <style>
        html,
        body {

            padding: 0;
            margin: 0;
        }

        .section-navbar {
            background-color: green;
        }

        .navbar-nav {
            padding: 1rem 1rem;
            /* display: flex; */
            justify-content: space-between;
            align-items: right;
        }

        .ul-tab-2 {
            display: flex;
            /* justify-content: space-between; */
            list-style: none;
        }

        .ul-tab-2 li a {
            color: lavender;
            margin-right: 2rem;
            /* list-style: none; */
            text-decoration: none;
        }

        .ul-tab-2 li a:hover {
            display: flex;
            border-bottom: 2px solid;
            color: black;

        }

        /* Float four columns side by side */
        .column {
            float: left;
            width: 25%;
            padding: 0 10px;
            margin: 3rem 1rem;
        }

        /* Remove extra left and right margins, due to padding */
        .row {
            margin: 0 -5px;
        }

        /* Clear floats after the columns */
        .row:after {
            content: "";
            display: table;
            clear: both;
        }
        .clock {
        font-size: 30px;
        margin-bottom: -200px;
        background: -webkit-linear-gradient(green, green);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        /* font-weight: 500; */
        /* display: block; */
        width: auto;
        height: auto;
        display: inline;
        padding: 10px 1px;
      }

        /* Responsive columns */
        @media screen and (max-width: 600px) {
            .column {
                width: 100%;
                display: block;
                padding: 0;
                margin: 0;
                margin-bottom: 30px;
            }
        }

        /* Style the counter cards */
        .card {
            box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2);
            padding: 16px;
            text-align: center;
            background-color: #f1f1f1;
        }

        footer {
            background-color: black;
            text-align: center;
            color: blanchedalmond;
            margin: 4rem 0;
            padding: 2rem;
        }
    </style>
</head>

<body>
    <div class="wrapper-content"></div>
    <section class="section-navbar">
        <nav class="navbar-nav">
            <ul class="ul-tab-2">
                <li><a href="/">Setting jam</a></li>
                <li><a href="/setwarna">Setting warna</a></li>
                <li><a href="/setalarm">Setting alarm</a></li>
                <li><a href="/setwifi">Setting wifi</a></li>
            </ul>
        </nav>
    </section>

    <section>


        <div class="row">
            <div class="column">
                <div class="card">
                   
                        <h3>Jam sekarang:</h3>
                        <p id="jam" class="clock" value="jam" name="jam"></p>
                        <p id=":" class="clock">:</p>
                        <p id="menit" class="clock" name="menit"></p>
                        <p id=":" class="clock">:</p>
                        <p id="detik" class="clock" name="detik"></p><br>
                        <button class="" onclick="updatejam()">Update jam otomatis</button>
             
                </div>
            </div>

            <div class="column">
                <div class="card">
                    <h3>Setting jam</h3><br>
                    <form action="/setjam">
                        <input type="number" name="jam" class="inp" id="jam" placeholder="Set jam disini"><br>
                        <input type="number" name="menit" class="inp" id="menit" placeholder="Set menit disini"></br>
                        
                        <button name="klik" value="1" onclick="updatemanual()"> Update jam manual </button><br>
                    </form>
                </div>
            </div>

            <div class="column">
                <div class="card">
                    <h3>Setting kecerahan</h3><br>
                    <form action="">
                        <input type="range" min="0" max="255" value="0" class="slider" id="kecerahan">
                        <p>Kecerahan : <span id="demo"></span></p>  

                    </form>
                </div>
            </div>
        </div>

        <footer>
            <h3>Aplikasi Pengaturan jam RGB v1.0</h3><br>
            <h2>@copyright Riski Sihab</h2>
        </footer>

    </section>


    <script>


        var slider = document.getElementById("kecerahan");
        var output = document.getElementById("demo");
        output.innerHTML = slider.value;
    
        slider.oninput = function () {
          output.innerHTML = this.value;
          console.log(output.innerHTML = this.value);
          var xhttp = new XMLHttpRequest();
          xhttp.open("GET", "setcerah?cerah=" + output.innerHTML, false);
          xhttp.send(null);
    
        }
    
    
        function updatemanual() {
          x = document.getElementById("jam").value
          y = document.getElementById("menit").value
          z = document.getElementById("klik").value
          //  nocache = \"/&nocache=\" + Math.random() * 1000000;
          var request = new XMLHttpRequest();
          request.open("GET", + x + y + z, false);
          request.send(null);
    
        }
    
    
        setInterval(customClock, 500);
        function customClock() {
          var time = new Date();
          var hrs = time.getHours();
          var min = time.getMinutes();
          var sec = time.getSeconds();
    
          //  document.getElementById('clock').innerHTML = hrs + ":" + min + ":" + sec; 
          document.getElementById('jam').innerHTML = hrs;
          document.getElementById('menit').innerHTML = min;
          document.getElementById('detik').innerHTML = sec;
        }
    
        function updatejam() {
          x = document.getElementById("jam").innerHTML
          y = document.getElementById("menit").innerHTML
          z = document.getElementById("detik").innerHTML
          
          console.log(z);
          request = new XMLHttpRequest();
          request.open("GET", 'setjam?jam='+ x +'&menit='+ y +'&detik='+ z, false);
          request.send(null);
        }
    
    //    var colorWell;
    //    var defaultColor = "#0000ff";
    //
    //    window.addEventListener("load", startup, false);
    //
    //function startup() {
    //  colorWell = document.querySelector("#colorWell");
    //  colorWell.value = defaultColor;
    //  colorWell.addEventListener("input", updateFirst, false);
    //  colorWell.addEventListener("change", updateAll, false);
    //  colorWell.select();
    //}
    
    //function updateFirst(event) {
    //  var p = document.querySelector("p");
    //
    //  if (p) {
    //    p.style.color = event.target.value;
    //  }
    ////  alert( p.style.color)
    //  var warna = p.style.color.substr(3)
    //   request = new XMLHttpRequest();
    //      request.open("GET", "setcolor?warna=" + warna, true);
    //      request.send(null);
    //}
      </script>
</body>

</html>

)=====";
