const char setalarm[]PROGMEM=R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pengaturan Alarm</title>

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

        footer{
            background-color: black;
            text-align: center;
            color: blanchedalmond;
            margin: 4rem 0;
            padding: 2rem ;
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
                <li><a href="setalarm">Setting alarm</a></li>
                <li><a href="setwifi">Setting wifi</a></li>
            </ul>
        </nav>
    </section>

    <section>
  

        <div class="row">
            <div class="column">
                <div class="card">
                    <h3>Setting Alarm</h3><br>
                    <form action="/aturalarm" method="post">
                        <input type="text" name="jam" id="jam" placeholder="atur jam disini" ></input><br>
                        <input type="text" name="menit" id="menit" placeholder="atur menit disini" ></input><br><br>
                        minggu<input type="checkbox" id="minggu" name="minggu" value="0">
                        senen<input type="checkbox" id="senen" name="senen" value="1">
                        selasa<input type="checkbox" id="selasa" name="selasa" value="2">
                        rabu<input type="checkbox" id="rabu" name="rabu" value="3"><br>
                        kamis<input type="checkbox" id="kamis" name="kamis" value="4">
                        jumat<input type="checkbox" id="jumat" name="jumat" value="5">
                       sabtu <input type="checkbox"  id="sabtu" name="sabtu" value="6"><br><br>


                        alarm aktif <input type="checkbox"  id="alarm" name="alarm" value="1"><br><br><br></br>
                        <button onclick="setalarm()">Set alarm</button>
                
                        </form><br>
             
                </div>
            </div>
        </div>

        <footer>
            <h3>Aplikasi Pengaturan jam RGB v1.0</h3><br>
            <h2>@copyright Riski Sihab</h2>
        </footer>

    </section>

    <script>
    if(kecerahan == 110){
      
      alert("okeh")}

        function setwarna(){
     
     //            var eID = document.getElementById("efk");
                  p =  document.getElementById("jam").value
                   z = document.getElementById("menit").value
                   a = document.getElementById("minggu").value
                   b = document.getElementById("senen").value
                   c = document.getElementById("selasa").value
                   d = document.getElementById("rabu").value
                   e = document.getElementById("kamis").value
                   f = document.getElementById("jumat").value
                   g = document.getElementById("sabtu").value
                   h = document.getElementById("alarm").value
                   
     //             nocache = \"/&nocache=\" + Math.random() * 1000000;
            var request = new XMLHttpRequest();
            request.open("POST",+ p + z  +a+b+c+d+e+f+g+h, false);
             request.send(null);
                      
      }
             </script>
</body>

</html>
)=====";
