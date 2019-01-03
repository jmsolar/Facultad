| red usu1 usu2 usu3 usu4 usu5 usu6 usu7 usu8 usu9 usu10 grupo1 grupo2 grupo3 grupo4 foto1 foto2 foto3 foto4 foto5 foto6 foto7 foto8 foto9 foto10 foto11 foto12 foto13 foto14 foto15 fecha1 fecha2 fecha3 fecha4 fecha5 fecha6 | 

"Se instancian los usuarios de la red"
usu1:= Usuario conNombreDeUsuario:'martin' conPassword:'martin'. usu2:= Usuario conNombreDeUsuario:'juan' conPassword:'jua'. usu3:= Usuario conNombreDeUsuario:'analia' conPassword:'ana'. 
usu4:= Usuario conNombreDeUsuario:'pedro' conPassword:'ped'. usu5:= Usuario conNombreDeUsuario:'rosario' conPassword:'ros'. usu6:= Usuario conNombreDeUsuario:'esteban' conPassword:'est'.
usu7:= Usuario conNombreDeUsuario:'uriel' conPassword:'uri'. usu8:= Usuario conNombreDeUsuario:'veronica' conPassword:'ver'. 
usu9:= Usuario conNombreDeUsuario:'gaston' conPassword:'gas'. usu10:= Usuario conNombreDeUsuario:'tamara' conPassword:'tam'. 

"Se instancian los grupos"
grupo1:= Grupo conNombre:'Amigos'. grupo2:= Grupo conNombre:'Facultad'. grupo3:= Grupo conNombre:'Familia'. grupo4:= Grupo conNombre:'Trabajo'.

"Se cargan en la red los usuarios generados anteriormente"
red:= RedSocial conNombre:'Fotos 2.0'.
red agregarUsuario:usu1; agregarUsuario:usu2; agregarUsuario:usu3; agregarUsuario:usu4;  agregarUsuario:usu5; agregarUsuario:usu6; agregarUsuario:usu7; agregarUsuario:usu8; agregarUsuario:usu9; agregarUsuario:usu10.

"Se instancian las fotografias"
foto1:= Foto conNombre:'primera' conUbicacion:'uno.jpg'. foto2:= Foto conNombre:'segunda' conUbicacion:'dos.jpg'. foto3:= Foto conNombre:'tercera' conUbicacion:'tres.jpg'. 
foto4:= Foto conNombre:'cuarta' conUbicacion:'cuatro.jpg'. foto5:= Foto conNombre:'quinta' conUbicacion:'cinco.jpg'. foto6:= Foto conNombre:'sexta' conUbicacion:'seis.jpg'.
foto7:= Foto conNombre:'septima' conUbicacion:'siete.jpg'. foto8:= Foto conNombre:'octava' conUbicacion:'ocho.jpg'. foto9:= Foto conNombre:'novena' conUbicacion:'nueve.jpg'.
foto10:= Foto conNombre:'decima' conUbicacion:'diez.jpg'. foto11:= Foto conNombre:'dec_primera' conUbicacion:'once.jpg'. foto12:= Foto conNombre:'dec_segunda' conUbicacion:'doce.jpg'.
foto13:= Foto conNombre:'dec_tercera' conUbicacion:'trece.jpg'. foto14:= Foto conNombre:'dec_cuarta' conUbicacion:'catorce.jpg'. 
foto15:= Foto conNombre:'dec_quinta' conUbicacion:'quince.jpg'.

"Se instancian fechas"
fecha1:= Date newDay: 8 monthNumber:6 year:1990. fecha2:= Date newDay: 2 monthNumber:2 year:2012. fecha3:= Date newDay: 29 monthNumber:1 year:2001.
fecha4:= Date newDay: 4 monthNumber:5 year:1990. fecha5:= Date newDay: 31 monthNumber:12 year:2010. fecha6:= Date newDay: 2 monthNumber:8 year:2010.

"Se le asigna a las fotografias las fechas instanciadas anteriormente"
foto1 fecha: fecha6. foto2 fecha:fecha5. foto3 fecha:fecha1. foto4 fecha:fecha4. foto6 fecha:fecha3. foto9 fecha:fecha3. foto10 fecha:fecha1. foto13 fecha:fecha2. foto15 fecha:fecha5.

"Se agrega a cada usuario los grupos y sus correspondientes seguidores"
usu1 agregarGrupo:grupo1; agregarGrupo:grupo2; agregarGrupo:grupo4.
usu1 agregarAmigo:usu7 alGrupo:grupo1; agregarAmigo:usu4 alGrupo:grupo2; agregarAmigo:usu5 alGrupo:grupo2; agregarAmigo:usu6 alGrupo:grupo2; agregarAmigo:usu9 alGrupo:grupo2; agregarAmigo:usu2 alGrupo: grupo4; agregarAmigo:usu3 alGrupo:grupo4.
usu1 agregarFoto:foto1 compartiendolaCon:grupo1; agregarFoto:foto3 compartiendolaCon:grupo1; agregarFoto:foto2 compartiendolaCon:grupo1; agregarFoto:foto11 compartiendolaCon:grupo1; agregarFoto:foto14 compartiendolaCon:grupo1; agregarFoto:foto12 compartiendolaCon:grupo2; agregarFoto:foto4 compartiendolaCon:grupo2; agregarFoto:foto9 compartiendolaCon:grupo2; agregarFoto:foto1 compartiendolaCon:grupo4.

usu2 agregarGrupo: grupo3; agregarGrupo: grupo4.
usu2 agregarAmigo: usu8 alGrupo: grupo3; agregarAmigo:usu1 alGrupo:grupo4; agregarAmigo:usu6 alGrupo:grupo4.
usu2 agregarFoto:foto1 compartiendolaCon:grupo3; agregarFoto:foto3 compartiendolaCon:grupo3; agregarFoto:foto9 compartiendolaCon:grupo3; agregarFoto:foto2 compartiendolaCon:grupo4;agregarFoto:foto4 compartiendolaCon:grupo4; agregarFoto:foto5 compartiendolaCon:grupo4; agregarFoto:foto12 compartiendolaCon:grupo4; agregarFoto:foto11 compartiendolaCon:grupo4; agregarFoto:foto7 compartiendolaCon:grupo4.

usu3 agregarGrupo: grupo1; agregarGrupo: grupo2; agregarGrupo: grupo4.
usu3 agregarAmigo:usu2 alGrupo:grupo1; agregarAmigo:usu10 alGrupo:grupo1; agregarAmigo:usu8 alGrupo:grupo2; agregarAmigo:usu4 alGrupo:grupo4; agregarAmigo:usu1 alGrupo:grupo4; agregarFoto:foto12 compartiendolaCon:grupo1; agregarFoto:foto6 compartiendolaCon:grupo1.
usu3 agregarFoto:foto1 compartiendolaCon:grupo2; agregarFoto:foto7 compartiendolaCon:grupo2; agregarFoto:foto8 compartiendolaCon:grupo2; agregarFoto:foto10 compartiendolaCon:grupo2; agregarFoto:foto3 compartiendolaCon:grupo4; agregarFoto:foto2 compartiendolaCon:grupo4; agregarFoto:foto13 compartiendolaCon:grupo4.

usu4 agregarGrupo: grupo4.
usu4 agregarAmigo:usu10 alGrupo:grupo4; agregarAmigo:usu2 alGrupo:grupo4; agregarAmigo:usu3 alGrupo:grupo4.
usu4 agregarFoto:foto6 compartiendolaCon:grupo4; agregarFoto:foto15 compartiendolaCon:grupo4; agregarFoto:foto13 compartiendolaCon:grupo4; agregarFoto:foto8 compartiendolaCon:grupo4.

usu5 agregarGrupo: grupo1; agregarGrupo:grupo3.
usu5 agregarAmigo:usu4 alGrupo:grupo1; agregarAmigo:usu6 alGrupo:grupo1; agregarAmigo:usu2 alGrupo:grupo1; agregarAmigo:usu3 alGrupo:grupo1; agregarAmigo:usu7 alGrupo:grupo1; agregarAmigo:usu1 alGrupo:grupo1; agregarAmigo:usu8 alGrupo:grupo3; agregarAmigo:usu10 alGrupo:grupo3; agregarAmigo: usu9 alGrupo:grupo3.
usu5 agregarFoto:foto1 compartiendolaCon:grupo1; agregarFoto:foto5 compartiendolaCon:grupo1; agregarFoto:foto15 compartiendolaCon:grupo3; agregarFoto:foto10 compartiendolaCon:grupo3; agregarFoto:foto1 compartiendolaCon:grupo3; agregarFoto:foto7 compartiendolaCon:grupo3.

usu6 agregarGrupo: grupo3.
usu6 agregarAmigo:usu1 alGrupo:grupo3.
usu6 agregarFoto:foto9 compartiendolaCon:grupo3; agregarFoto:foto11 compartiendolaCon:grupo3; agregarFoto:foto3 compartiendolaCon:grupo3; agregarFoto:foto15 compartiendolaCon:grupo3.

usu7 agregarGrupo: grupo2; agregarGrupo: grupo4.
usu7 agregarAmigo:usu3 alGrupo:grupo2; agregarAmigo:usu6 alGrupo:grupo2; agregarAmigo:usu1 alGrupo:grupo2; agregarAmigo:usu8 alGrupo:grupo4; agregarAmigo:usu9 alGrupo:grupo4.
usu7 agregarFoto:foto1 compartiendolaCon:grupo4; agregarFoto:foto2 compartiendolaCon:grupo4; agregarFoto:foto3 compartiendolaCon:grupo4; agregarFoto:foto5 compartiendolaCon:grupo4; agregarFoto:foto4 compartiendolaCon:grupo4.

usu8 agregarGrupo: grupo1; agregarGrupo: grupo2; agregarGrupo: grupo3.
usu8 agregarAmigo:usu4 alGrupo:grupo1; agregarAmigo:usu3 alGrupo:grupo2; agregarAmigo:usu6 alGrupo:grupo2; agregarAmigo:usu9 alGrupo:grupo2; agregarAmigo:usu2 alGrupo:grupo3.
usu8 agregarFoto:foto6 compartiendolaCon:grupo2; agregarFoto:foto3 compartiendolaCon:grupo2; agregarFoto:foto10 compartiendolaCon:grupo2;agregarFoto:foto8 compartiendolaCon:grupo3; agregarFoto:foto13 compartiendolaCon:grupo3; agregarFoto:foto1 compartiendolaCon:grupo3; agregarFoto:foto5 compartiendolaCon:grupo3.

usu10 agregarGrupo: grupo1; agregarGrupo:grupo3.
usu10 agregarAmigo:usu1 alGrupo:grupo1; agregarAmigo:usu2 alGrupo:grupo1; agregarAmigo:usu5 alGrupo:grupo1; agregarAmigo:usu4 alGrupo:grupo3; agregarAmigo:usu6 alGrupo:grupo3.
usu10 agregarFoto:foto5 compartiendolaCon:grupo1; agregarFoto:foto3 compartiendolaCon:grupo1; agregarFoto:foto8 compartiendolaCon:grupo1; agregarFoto:foto14 compartiendolaCon:grupo1; agregarFoto:foto9 compartiendolaCon:grupo3; agregarFoto:foto3 compartiendolaCon:grupo3; agregarFoto:foto14 compartiendolaCon:grupo3; agregarFoto:foto5 compartiendolaCon:grupo3.

"Se instancia y llama a la aplicacion"
usu1 iniciarAplicacion: red. 