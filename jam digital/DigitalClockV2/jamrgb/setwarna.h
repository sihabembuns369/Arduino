const char setwarna[]PROGMEM=R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pengaturan warna</title>

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
                    <h3>Setting warna</h3>
                    <form action="/aturwarna" method="post">
                        
                       warna = <select name="warna" id="efk">
                             <option value="1">merah</option>
                             <option value="2">hijau</option>
                             <option value="3">biru</option>
                             <option value="4">kuning</option>
                             <option value="5">ungu</option>
                             <option value="6">coklat</option>
                             <option value="7">putih</option>
                         </select>
                     <br> 
                         <input type="checkbox" name="cek_warna" id="cek_warna" value="1">random</input><br></br>
                         <input type="checkbox" name="efek1" id="efek1" value="2">efek1</input><br></br>
                         <button onclick="gantiwarna()">Ganti warna</button>
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
        function gantiwarna(){
 
         var eID = document.getElementById("efk");
         p = eID.options[eID.selectedIndex].value;
         q = document.getElementById("cek_warna").value
         r = document.getElementById("efek1").value
 //        nocache = \"/&nocache=\" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
    request.open("POST",+ p + q + r , false);
    request.send(null);
      
        }
 
    </script>
</body>

</html>
)=====";
