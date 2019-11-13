const char MAIN_page[] PROGMEM = R"=====(
<html>
<!DOCTYPE html>
<style type="text/css">
#portal {
   display: block;
   min-height: 100vh;
   background: rgb(0,31,42);
   background: linear-gradient(207deg, rgba(0,31,42,1) 0%, rgba(102,79,169,1) 50%, rgba(90,142,208,1) 100%);
}
#portal .c {
   display: block;
   width: 100%;
   padding: 0 1.5em;
}
.head {
   padding: 15px 0;
   display: block;
   color: #fff;
   text-align: center;
}
.head h3 {
   font-weight: 700;
   margin: 1em 0 0;
   font-size: 1.35em;
}
.logo {
}
.logo img {
   display: block;
   height: 3em;
   margin: 1em auto;
}
.head.form {
   background: #0e2338;
}
.head.form .logo {
   display: inline-block;
}
.head.form .logo img {
   display: inline-block;
   height: 1.5em;
   margin: 0;
   vertical-align: top;
}
.head.form h3 {
   font-size: 1.15em;
   margin: 0 0 0 .5em;
   display: inline-block;
   vertical-align: top;
   line-height: 1.5em;
}
.body {
   padding: 1.5em 0;
   display: block;
}
.body.on {
   display: block;
}
.body.off {
   display: none;
}
.body p {
   color: #fff;
   margin: 0 0 1em;
}
.body h4 {
   font-size: 1.25em;
   color: #fff;
   font-weight: 600;
   margin: 1em 0 .5em;
}
.body.form {
   padding: 0;
   background: #e2e2e2;
}
.b {
   display: block;
   padding: 20px;
   text-align: center;
   cursor: pointer;
}
.b:hover {
   opacity: .7;
}
.lang, .details, .update, .home {
   display: block;
   color: #fff;
   border: 1px solid #fff;
   font-size: 1.25em;
   font-weight: 600;
   line-height: 1.5em;
   margin-bottom: 1em;
}
.details {
   background: #0f253a;
   border: 0;
}
.update {
   border: 0;
   background: #fe5454;   
}
.body p.disclaimer {
   font-size: .9em;
   text-align: center;
}
.sos {
   font-size: 2em;
   color: #fff;
   letter-spacing: 3px;
   background: #fe5454;
   font-weight: 600;
}
.ch-c {
   margin-bottom: 1em;
}
.ch-c p {
   font-size: 1.25em;
   line-height: 2.15em;
   margin: 0;
   display: inline-block;
   vertical-align: top;
}
.ch-c input[type=checkbox] {
   display: inline-block;
   width: 2em;
   height: 2em;
   vertical-align: top;
   margin-left: 0;
}
.gps {
   display: block;
   padding: 1em;
   background: rgba(255,255,255,.75);
   text-align: center;
   font-size: 1.25em;
   line-height: 1.5em;
   letter-spacing: 1px;
}
.gps h4 {
   color: #111;
   font-size: 1.35em;
}
.gps h5 {
   color: #111;
   font-size: 1.15em;
}
.gps p {
   color: #111;
   font-size: 1em;
   letter-spacing: 2px;
}
#portal .body.form .c {
}
#portal .body.form .c .s {
   padding: 1em 0;
   border-bottom: 1px solid rgba(0,0,0,.15);
}
#portal .body.form .c .s:after {
   content: "";
   display: block;
   clear: both;
}
#portal .body.form .c .s:last-child {
   border: 0;
}
.body.form .gps {
   text-align: left;
   background: #fff;
}
.body.form .ch-c {
   display: inline-block;
   width: 48%;
}
.body.form .ch-c input[type=checkbox] {
   background: #fff;
}
.body.form .ch-c:nth-child(even) {
   width: 43%;
}
.body.form .ch-c:nth-child(odd) {
   width: 55%;
}
.body.form .ch-c p {
   color: #111;
   margin-left: .35em;
}
.body.form h4 {
   color: #111;
   display: inline-block;
   vertical-align: top;
   margin: 0 0 .25em;
   line-height: 1.5em;
}
.body.form input.other-input {
   display: block;
   width: 100%;
   margin-bottom: 1em;
   padding: 1em .5em;
   font-size: 16px;
}
.body.form input.num-input {
   display: inline-block;
   vertical-align: top;
   width: 20%;
   margin-bottom: 1em;
   padding: 1em .5em;
   float: right;
   font-size: 16px;
}
.body.form input.name-input, .body.form input.phone-input, .body.form input.address-input {
   display: block;
   width: 100%;
   margin-bottom: 1.5em;
   padding: 1em .5em;
   font-size: 16px;
}
.body.form textarea.message-input {
   display: block;
   width: 100%;
   min-height: 5em;
   vertical-align: top;
   margin-bottom: 1em;
   padding: 1em .5em;
   font-size: 16px;
}
.body .change {
   color: #fff;
   font-size: 1.15em;
   line-height: 1.5em;
}
.body .optional {
   background: #4ec1b5;
   font-size: 1em;
   line-height: 1.5em;
   padding: 1em 0;
   color: #fff;
   text-align: center;
   font-weight: 600;
}
</style>
<div id="portal">
   <div class="head">
      <div class="c">
         <div class="logo"><img src="/assets/owl_logo_v2_light.png" /></div>
         <h3>OWL Emergency Network</h3>
      </div>
   </div>
   <div class="body on intro">
      <div class="c">
         <div class="b lang">En Español</div>
         <p>Se ha conectao a la Red de Emergencia OWL. Al enviar una solicitud de ayuda, estaremos enviando las coordenadas GPS de su localización a los Primeros Respondedores y Manejo de Emergencias. Puede enviar una solicitud de ayuda rápida o añadir detalles relacionados a su emergencia. Los campos son opcionales.</p>
         <p><b>El lugar de ayuda más cercana a usted está en:</b><br>Pedro Montañez Municipal Baseball Stadium.</p>
         <br>
         <h4>Su localización GPS</h4>
         <div class="gps"><b>49&deg; 15&#39;42&#34; N 123&deg; 8&#39; 18&#34;W</b><br>Vancouver, BC, Canada</div>
         <div class="b sos">SOS</div>
      </div>
   </div>
   <div class="body off send">
      <div class="c">
         <div class="b lang">En Español</div>
         <br><br>
         <h4>Your GPS Location</h4>
         <div class="gps"><b>49&deg; 15&#39;42&#34; N 123&deg; 8&#39; 18&#34;W</b><br>Vancouver, BC, Canada</div>
         <div class="b sos">AYUDA</div>
         <br><br><br>
         <div class="b details more">Añadir Eetalles Antes de Enviar</div>
      </div>
   </div>
   <div class="body off sent">
      <div class="c">
         <div class="b home">Inicio</div>
         <div class="gps"><h4>Mensaje Enviado</h4><h5>6 de marzo de 2019 @ 11:02 PM</h5><p># de ID de su mensaje: 9XP002</p></div>
         <br><br><br><br>
         <p class="disclaimer">Si su situación cambió, por favor envíe una actualización.
         <div class="b update">ACTUALIZAR</div>
         <div class="change" style="width: 90%; display: inline-block;float: left;"><b>Actualizar mi condición</b><br>Ya no necesito ayuda</div>
         <input type="checkbox" style="width: 30px; height: 30px; display: inline-block;float: left;">
      </div>
   </div>
   <div class="body off form">
      <div class="optional">Todos los campos son opcionales</div>
      <div class="gps"><b>Su localización GPS</b><br>49&deg; 15&#39;42&#34; N 123&deg; 8&#39; 18&#34;W</div>
      <div class="c">
         <div class="s">
            <h4>Teléfono</h4>
            <input type="text" placeholder="123-456-7891" class="phone-input">
            <h4>Nombre y Apellido</h4>
            <input type="text" placeholder="Jess Smith" class="name-input">
            <h4>¿Dónde se encuentra?</h4>
            <input type="text" placeholder="Closest address, intersection, description" class="address-input">
         </div>
         <div class="s">
            <h4>¿Cuál es su emergencia?</h4>
            <div class="ch-c"><input type="checkbox"><p>√</p></div>
            <div class="ch-c"><input type="checkbox"><p>Fuego / Explosión</p></div>
            <div class="ch-c"><input type="checkbox"><p>Inundación</p></div>
            <div class="ch-c"><input type="checkbox"><p>Violencia</p></div>
            <div class="ch-c"><input type="checkbox"><p>Derrumbe</p></div>
            <div class="ch-c"><input type="checkbox"><p>Estructura Colapsada</p></div>
            <div class="ch-c"><input type="checkbox"><p>Atrapado</p></div>
            <div class="ch-c"><input type="checkbox"><p>Muerte</p></div>
            <input type="text" placeholder="Other emergency" class="other-input">
         </div>
         <div class="s">
            <h4>¿Qué necesita en las próximas 24 hrs?</h4>
            <div class="ch-c"><input type="checkbox"><p>Primeros Aux</p></div>
            <div class="ch-c"><input type="checkbox"><p>Refugio</p></div>
            <div class="ch-c"><input type="checkbox"><p>Alimentos</p></div>
            <div class="ch-c"><input type="checkbox"><p>Ayuda Financiera</p></div>
            <div class="ch-c"><input type="checkbox"><p>Comida</p></div>
            <div class="ch-c"><input type="checkbox"><p>Evacuación</p></div>
            <div class="ch-c"><input type="checkbox"><p>Ropa</p></div>
            <div class="ch-c"><input type="checkbox"><p>Productos de Higiene</p></div>
            <input type="text" placeholder="Other" class="other-input">
         </div>
         <div class="s">
            <h4>¿Qué peligros hay a su alrededor?</h4>
            <div class="ch-c"><input type="checkbox"><p>Eléctricas Arbol</p></div>
            <div class="ch-c"><input type="checkbox"><p>Carretera Cerrada</p></div>
            <div class="ch-c"><input type="checkbox"><p>Caido</p></div>
            <div class="ch-c"><input type="checkbox"><p>Quimicos</p></div>
            <div class="ch-c"><input type="checkbox"><p>Huma/Fuego</p></div>
            <div class="ch-c"><input type="checkbox"><p>Animales</p></div>
            <div class="ch-c"><input type="checkbox"><p>Golpe de Agua</p></div>
            <div class="ch-c"><input type="checkbox"><p>Explosivos</p></div>
            <input type="text" placeholder="Other" class="other-input">
         </div>
         <div class="s">
            <h4>¿Cuántas personas?</h4>
            <input type="text" placeholder="0" class="num-input">
         </div>
         <div class="s">
            <h4>¿Cuántas mascotas?</h4>
            <input type="text" placeholder="0" class="num-input">
         </div>
         <div class="s">
            <h4 style="width: 90%; float: left; display: inline-block;">¿Usted o a alguien en su grupo se le hace imposible moverse?</h4>
            <input type="checkbox" style="width: 30px; height: 30px; display: inline-block;float: left;">
         </div>
         <div class="s">
            <h4 style="width: 90%; float: left; display: inline-block;">¿Autoriza a que su información se haga publica para que sus familiares o amigos sepan que se encuentra bien??</h4>
            <input type="checkbox" style="width: 30px; height: 30px; display: inline-block;float: left;">
         </div>
         <div class="s">
            <h4>Mensaje (300 caracteres)</h4>
            <textarea type="text" placeholder="More information about your situation" class="message-input"></textarea>
         </div>
         <div class="s">
            <!-- <h4>Change my status:<br>I no longer need help</h4> -->
            <div class="b sos">PEDIR AYUDA</div>
         </div>
      </div>
   </div>
</div>
<script type="text/javascript">
   
   $(".body.intro .b.sos").on("click",function() {
      $(".body.send").addClass("on").removeClass("off")
      $(".body.intro").removeClass("on").addClass("off")
   })
   $(".body.send .b.sos").on("click",function() {
      $(".body.sent").addClass("on").removeClass("off")
      $(".body.send").removeClass("on").addClass("off")
   })
   $(".body.send .b.details.more").on("click", function() {
      $(".head").addClass("form")
      $(".body.form").addClass("on").removeClass("off")
      $(".body.send").removeClass("on").addClass("off")
   })
   $(".body.sent .b.update").on("click", function() {
      $(".head").addClass("form")
      $(".body.form").addClass("on").removeClass("off")
      $(".body.sent").removeClass("on").addClass("off")
   })
   $(".body.form .b.sos").on("click", function() {
      $(".head").removeClass("form")
      $(".body.sent").addClass("on").removeClass("off")
      $(".body.form").removeClass("on").addClass("off")
   })
   $(".body.sent .b.home").on("click", function() {
      $(".body.intro").addClass("on").removeClass("off")
      $(".body.sent").removeClass("on").addClass("off")
   })
</script>
</html>

)=====";
