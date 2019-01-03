# -*- coding: utf-8 -*-

import pygame
import sys
import os
import funciones
import elementos
import texto
import tabla
import random
import datetime
from pygame.locals import *

ANCHO = 1000
ALTO = 700
TIEMPO_DE_JUEGO = 90000

pygame.init()
pygame.display.set_mode((ANCHO,ALTO))
pygame.display.set_caption('Matemáticas')

#Clase Pantalla
class Pantalla():
	def __init__(self):
		self.__surface = pygame.Surface(pygame.display.get_surface().get_size()).convert()
		self.__sprites = pygame.sprite.Group()
		self.__buttons = pygame.sprite.Group()
		self.__text = []
		self.__cargarTexto()

	def setFondo(self,img):
		img = funciones.cargarImagen('FONDOS'+os.sep+img)
		x = self.__surface.get_width() / 2
		y = self.__surface.get_height() / 2
		pos = img.get_rect(centerx = x,centery = y)
		self.__surface.blit(img,pos)
		
	def getSurface(self):
		return self.__surface

	def getTexto(self):
		return self.__text

	def agregarTexto(self,text):
		if (isinstance(text,texto.Texto)):
			self.__text.append(text)

	def eliminarTexto(self,text):
		self.__text.remove(text)

	def __cargarTexto(self):
		pass

	def getSprites(self):
		return self.__sprites.sprites()

	def agregarSprites(self,*sprites):
		self.__sprites.add(sprites)

	def eliminarSprites(self,*sprites):
		self.__sprites.remove(sprites)

	def getBotones(self):
		return self.__buttons.sprites()

	def agregarBotones(self,*buttons):
		self.__buttons.add(buttons)

	def eliminarBotones(self,*buttons):
		self.__buttons.remove(buttons)

	def update(self):
		screen = pygame.display.get_surface()
		screen.blit(self.__surface,(0,0))
		for t in self.getTexto():
			t.imprimir(screen)
		self.__buttons.draw(screen)
		self.__sprites.draw(screen)			
		pygame.display.update()

	def abrir(self):
		self.update()
		while True:
			for evento in pygame.event.get():
				if evento.type==QUIT:
					pygame.quit(); sys.exit()
				elif evento.type==KEYDOWN and evento.key==K_ESCAPE:
					self.cerrar()
				else:
					self.eventos(evento)
					self.update()

	def eventos(self,evento):
		pass

	def cerrar(self):
		sys.exit()

#Clase MenuPrincipal
class MenuPrincipal(Pantalla):
	def __init__(self):
		Pantalla.__init__(self)
		self.setFondo('menuPrincipal.jpg')
		self.__cargarTexto()	

	def __cargarTexto(self):
		self.agregarTexto(texto.Linea('NUEVO JUEGO','Circus.ttf',(0,0,0),25,(500,125)))
		self.agregarTexto(texto.Linea('REGLAS DE JUEGO','Circus.ttf',(0,0,0),25,(550,165)))
		self.agregarTexto(texto.Linea('TABLA DE POSICIONES','Circus.ttf',(0,0,0),25,(600,205)))
		self.agregarTexto(texto.Linea('CREDITOS','Circus.ttf',(0,0,0),25,(650,245)))
		self.agregarTexto(texto.Linea('SALIR','Circus.ttf',(0,0,0),25,(700,285)))		
		
	def __abrirSubpantalla(self,n):
		if n == 0: PantallaDeJuego().abrir()
		elif n == 1: ReglasDeJuego().abrir()
		elif n == 2: PantallaTabla().abrir()
		elif n == 3: Creditos().abrir()
		else: self.cerrar()

	def eventos(self,evento):
		if evento.type==MOUSEMOTION:
			for t in self.getTexto():
				if t.isOver(pygame.mouse.get_pos()):				
					t.setColor((100,100,100))
				else:
					t.setColor((0,0,0))
		elif evento.type==MOUSEBUTTONDOWN and evento.button==1:
			t = self.getTexto()
			for i in range(len(t)):
				if t[i].isOver(evento.pos): self.__abrirSubpantalla(i)

#Clase Subpantalla
class Subpantalla(Pantalla):
	def cerrar(self):
		MenuPrincipal().abrir()

#Clase ReglasDeJuego
class ReglasDeJuego(Subpantalla):
	def __init__(self):
		Subpantalla.__init__(self)
		self.setFondo('imagen3.jpg')		
		self.agregarTexto(texto.Parrafo(funciones.cargarTexto('reglas.txt'),'Cinnamon Cake.ttf',(255,255,255),17,(20,105)))
		self.agregarBotones(elementos.Boton('atras.png',(10,640)))
		self.__cargarTexto()

	def __cargarTexto(self):
		self.agregarTexto(texto.Linea('REGLAS GENERALES','Circus.ttf',(200,200,200),40,(None,50)))

	def eventos(self,evento):
		if evento.type==MOUSEBUTTONDOWN and evento.button==1:
			if self.getBotones()[0].click(evento.pos):
				self.cerrar()
												
#Clase Creditos
class Creditos(Subpantalla):
	def __init__(self):
		Subpantalla.__init__(self)
		self.setFondo('imagen2.jpg')
		self.agregarTexto(texto.Parrafo(funciones.cargarTexto('creditos.txt'),'Cinnamon Cake.ttf',(255,255,255),33,(None,125)))
		self.agregarBotones(elementos.Boton('atras.png',(10,640)))
		self.__cargarTexto()
		
	def __cargarTexto(self):
		self.agregarTexto(texto.Linea('CREDITOS','Circus.ttf',(200,200,200),40,(None,50)))

	def eventos(self,evento):
		if evento.type==MOUSEBUTTONDOWN and evento.button==1:
			if self.getBotones()[0].click(evento.pos):
				self.cerrar()

#Clase PantallaTabla
class PantallaTabla(Subpantalla):
	def __init__(self):
		Subpantalla.__init__(self)
		self.setFondo('imagen4.jpg')
		self.agregarBotones(elementos.Boton('atras.png',(10,640)))
		self.__cargarTexto()
		self.imprimirTabla()

	def __cargarTexto(self):
		self.agregarTexto(texto.Linea('POSICIONES','Circus.ttf',(200,200,200),40,(None,50)))
		self.agregarTexto(texto.Linea('Nombre','Bubbleboy.ttf',(100,100,100),20,(160,160)))
		self.agregarTexto(texto.Linea('Fecha','Bubbleboy.ttf',(100,100,100),20,(480,160)))
		self.agregarTexto(texto.Linea('Puntos','Bubbleboy.ttf',(100,100,100),20,(730,160)))

	def imprimirTabla(self):
		y = 200
		for i in tabla.TablaDePosiciones().imprimir():
			x=150
			for j in range(len(i)):
				self.agregarTexto(texto.Linea(i[j],'SF Beaverton.ttf',(160,160,160),20,(x,y)))
				x += 300
			y+=80; 

	def eventos(self,evento):
		if ((evento.type==MOUSEBUTTONDOWN) and (evento.button==1)):
			if self.getBotones()[0].click(evento.pos):
				self.cerrar()

#Clase PantallaDeJuego
class PantallaDeJuego(Subpantalla):
	def __init__(self):
		Subpantalla.__init__(self)
		self.setFondo('imagen2.jpg')
		self.__tiempo = 0
		self.__puntaje = 0
		self.__cargarTexto()		
		
	def __getErrores(self):
		return self.__contenedores[3]

	def __cargarTexto(self):
		self.agregarTexto(texto.Linea('Nivel','Airstrip Four.ttf',(255,255,255),18,(5,10)))
		self.agregarTexto(texto.Linea('Puntos','Airstrip Four.ttf',(255,255,255),18,(120,10)))
		self.agregarTexto(texto.Linea('Tiempo','Airstrip Four.ttf',(255,255,255),18,(860,10)))
		self.agregarTexto(texto.Linea('Unidades','Airstrip Four.ttf',(255,255,255),14,(97,677)))
		self.agregarTexto(texto.Linea('Decenas','Airstrip Four.ttf',(255,255,255),14,(452,677)))
		self.agregarTexto(texto.Linea('Centenas','Airstrip Four.ttf',(255,255,255),14,(800,677)))	
		self.agregarTexto(texto.Linea('','Airstrip Four.ttf',(255,255,255),25,(75,10))) #NIVEL
		self.agregarTexto(texto.Linea('','Airstrip Four.ttf',(255,255,255),25,(220,10))) #PUNTOS
		self.agregarTexto(texto.Linea('','Airstrip Four.ttf',(255,255,255),25,(960,10))) #TIEMPO		

	def __crearElementos(self,nivel):		
		self.__contenedores = [elementos.Contenedor('azul.png',(100,590),'unidades'),
		elementos.Contenedor('verde.png',(450,590),'decenas'),
		elementos.Contenedor('rojo.png',(800,590),'centenas'),[]]
		
		self.__tipitos = [elementos.Tipito((280,10)),elementos.Tipito((300,10)),elementos.Tipito((320,10))]
		self.eliminarSprites(self.getSprites())
		self.agregarSprites(self.__contenedores,self.__tipitos)
		self.__agregarCuentas(nivel)		
		
	def __seleccionarColor(self):
		azul = (0,38,255)
		verde = (38,127,0)		
		rojo = (255,0,0)		
		colores = [azul,verde,rojo]
		return colores[random.randint(0,2)]
	
	def __cargarErrores(self):
		path = os.path.join('Textos'+os.sep+'Datos'+os.sep+'errores.txt')
		archivo = funciones.abrirArchivo(path)		
		for error in archivo.readlines():
			miTexto = texto.Linea(error.rstrip(), 'Airstrip Four.ttf', self.__seleccionarColor(), 20, (random.randint(10,ANCHO-100), 35),'error')
			cuenta = miTexto.getObjFont().render(miTexto.getTexto(), 1, miTexto.getColor())  # LA PALABRA!				
			miTexto.setRect(cuenta.get_rect())
			miTexto.getRect().top = miTexto.getPosicion()[0]
			miTexto.getRect().left = miTexto.getPosicion()[1]
			self.__getErrores().append(miTexto)			
				
	def __agregarCuentas(self,niv):
		paths = ['unidades.txt','decenas.txt','centenas.txt']		
		for i in range(3):
			path = os.path.join('Textos'+os.sep+'Datos'+os.sep+paths[i])		
			a = funciones.abrirArchivo(path)		
			for miCuenta in a.readlines():
				miTexto = texto.Linea(miCuenta.rstrip(), 'Airstrip Four.ttf', (255, 255, 255), 20, (random.randint(10,ANCHO-100), 35),self.__contenedores[i].getID())
				if (niv >= 2):
					miTexto.setColor(self.__seleccionarColor())									
				cuenta = miTexto.getObjFont().render(miTexto.getTexto(), 1, miTexto.getColor())  # LA PALABRA!				
				miTexto.setRect(cuenta.get_rect())
				miTexto.getRect().top = miTexto.getPosicion()[0]
				miTexto.getRect().left = miTexto.getPosicion()[1]	
				self.__contenedores[i].agregarCuenta(miTexto)				
			if (niv == 3):
				self.__cargarErrores()		

	def __inicializarNivel(self,nivel):
		self.__crearElementos(nivel)		
		self.getTexto()[6].setTexto(str(nivel))
		self.getTexto()[7].setTexto(str(0))		
		
	def __tomarTotal(self):		
		cantidad = 0
		valores = [0,1,2,3]
		while (cantidad < 4):
			n = valores[random.randint(0,len(valores)-1)]									
			if (n != 3):
				cant = len(self.__contenedores[n].getCuentas().sprites())				
				try:
					res = self.__contenedores[n].getCuentas().sprites()[random.randint(0,cant-1)]
					break			
				except (IndexError, ValueError):
					cantidad += 1
				finally:
					valores.remove(n)
			else:				
				cant = len(self.__getErrores())
				try:
					res = self.__getErrores()[random.randint(0,cant-1)]					
					self.__getErrores().remove(res)
					break
				except (IndexError,ValueError):
					cantidad += 1
				finally:
					valores.remove(n)
		if (cantidad == 4):			
			print 'No existen más cuentas para cargar'
			raise SystemExit					
		else:
			self.agregarTexto(res)			
			return res,n
		
	def __tomarParcial(self):						
		cantidad = 0		
		valores = [0,1,2]		
		while (cantidad < 3):
			n = valores[random.randint(0,len(valores)-1)]
			cant = len(self.__contenedores[n].getCuentas().sprites())
			try:								
				res = self.__contenedores[n].getCuentas().sprites()[random.randint(0,cant-1)]								
				break
			except (IndexError, ValueError):
				cantidad += 1
			finally:
				valores.remove(n) # elimino un contenedor		
		if (cantidad == 3):			
			print 'No existen más cuentas para cargar'
			raise SystemExit				
		else:
			self.agregarTexto(res)			
			return res,n	

	def __tomarCuenta(self,nivel):		
		if (nivel == 3):
			return self.__tomarTotal()
		else:
			return self.__tomarParcial() 			
	
	def __cantidadCuentas(self, nivel):
		paths = ['unidades.txt','decenas.txt','centenas.txt']
		if (nivel == 3):
			paths.append('errores.txt')				
		cantidad = 0		
		for i in range(len(paths)):
			path = os.path.join('Textos'+os.sep+'Datos'+os.sep+paths[i-1])		
			a = funciones.abrirArchivo(path)		
			for j in a.readlines():
				cantidad += 1			
		return cantidad	
	
	def __controlarTeclas(self,k,cue):
		if k == K_p: self.__pausa()
		elif k == K_ESCAPE: self.cerrar()
		elif k == K_RIGHT: 
			if (cue.getRect().right < self.getSurface().get_rect().right):
				cue.setPosicion((cue.getPosicion()[0]+5,cue.getPosicion()[1])) 
		elif k == K_LEFT: 
			if (cue.getRect().left > self.getSurface().get_rect().left):
				cue.setPosicion((cue.getPosicion()[0]-5,cue.getPosicion()[1]))
		elif k == K_UP: 
			if (cue.getRect().top > self.getSurface().get_rect().top):
				cue.setPosicion((cue.getPosicion()[0],cue.getPosicion()[1]-15))
		elif k == K_DOWN: 
			if (cue.getRect().bottom < self.getSurface().get_rect().bottom):
				cue.setPosicion((cue.getPosicion()[0],cue.getPosicion()[1]+5))
		
	def __colision(self,cue,num,puntos):			
		
		if (cue.getID() != 'error') and (cue.getRect().colliderect(self.__contenedores[num])): # es una cuenta y encesto bien			
			puntos += 7
		elif (cue.getID() != 'error') and (not cue.getRect().colliderect(self.__contenedores[num])): # es una cuenta y encesto mal
			puntos -= 5
		elif (cue.getID() == 'error'): # es un error y encesto
			puntos -= 3
			try:		
				if (len(self.__tipitos) == 1) and (puntos <= 0):
					JuegoTerminado().abrir()			
				self.eliminarSprites(self.__tipitos.pop())
			except (IndexError):				
				JuegoTerminado().abrir()		#PERDIO				
		return puntos
		
	def __fueraDeAltura(self,cue,puntos):		
		if (cue.getID() != 'error'):
			try:
				if (len(self.__tipitos) == 1) and (puntos <= 0):
					JuegoTerminado().abrir() 
				self.eliminarSprites(self.__tipitos.pop())
			except (IndexError): 
				JuegoTerminado().abrir()		#PERDIO			
			
	def __sinCuentas(self, cantidad):
		if (cantidad <= 0):					
			return True
		else:			
			return False
		
	def __huboColision(self,cue):
		return (cue.getRect().colliderect(self.__contenedores[0])) or (cue.getRect().colliderect(self.__contenedores[1])) or (cue.getRect().colliderect(self.__contenedores[2]))

	def __nivel(self,nivel):		
		self.__inicializarNivel(nivel)
		puntos = 0
		tiempo = TIEMPO_DE_JUEGO
		reloj = pygame.time.Clock()
		cue,n = self.__tomarCuenta(nivel)
		cantidad = self.__cantidadCuentas(nivel) - 1 
		while tiempo > 0:			
			tiempo -= reloj.tick(24)			
			self.getTexto()[8].setTexto(str(tiempo/1000))			
			e = pygame.event.poll()
			if e.type == KEYDOWN:
				self.__controlarTeclas(e.key,cue)				
			elif e.type == QUIT: sys.exit()				
			pygame.event.clear()				
			
			if (self.__huboColision(cue)):
				puntos = self.__colision(cue,n,puntos) # CONTROLO QUE ENCEST0
				cue.kill(); self.getTexto()[7].setTexto(str(puntos))
				if self.__sinCuentas(cantidad):
					break
				else:
					cantidad -= 1
				self.getTexto().pop(9)
				cue,n = self.__tomarCuenta(nivel)							
			elif(cue.getPosicion()[1] >= 620):					
				self.__fueraDeAltura(cue,puntos) #CONTROLO POR NO HABER ENCESTADO
				cue.kill(); self.getTexto()[7].setTexto(str(puntos))
				if self.__sinCuentas(cantidad):
					break	
				else:
					cantidad -= 1
				self.getTexto().pop(9)
				cue,n = self.__tomarCuenta(nivel)						
			cue.setPosicion((cue.getPosicion()[0],cue.getPosicion()[1]+2))				
			self.update()
		self.getTexto().pop(9)	
		cue.kill()		
		self.__puntaje += puntos
		self.__tiempo += tiempo

	def abrir(self):
		for i in range(3):
			self.__esperar(i+1); self.__nivel(i+1)			
		IngresarJugador(self.__puntaje).abrir()

	def __pausa(self):
		screen = pygame.display.get_surface()
		screen.blit(funciones.cargarImagen('FONDOS'+os.sep+'imagen5.jpg'),(0,0))
		texto.Linea('juego pausado','Airstrip Four.ttf',(255,255,255),40,(None,250)).imprimir(screen)
		texto.Linea('presione cualquier tecla para continuar','Airstrip Four.ttf',(255,255,255),40,(None,400)).imprimir(screen)
		pygame.display.update()
		while pygame.event.poll().type != KEYDOWN: 
			pass
		
	def __esperar(self,nivel):
		screen = pygame.display.get_surface()
		screen.blit(funciones.cargarImagen('FONDOS'+os.sep+'imagen5.jpg'),(0,0))
		texto.Linea('Presione una tecla para comenzar el nivel '+str(nivel),'Airstrip Four.ttf',(255,255,255),40,(None,None)).imprimir(screen)
		pygame.display.update()		
		pygame.display.update()
		while pygame.event.poll().type != KEYDOWN: 
			pass

#Clase IngresarJugador
class IngresarJugador(Subpantalla):
	def __init__(self,puntaje):
		Subpantalla.__init__(self)
		self.setFondo('imagen1.jpg')
		self.__puntaje = puntaje		
		self.agregarTexto(texto.Linea('Ingrese su nombre y presione <Enter>','Airstrip Four.ttf',(255,255,255),25,(None,200)))				
		self.agregarTexto(texto.Linea('','Airstrip Four.ttf',(255,255,255),25,(None,None)))

	def eventos(self,evento):
		if evento.type == KEYDOWN:
			if evento.key>=K_a and evento.key<=K_z and len(self.getTexto()[1].getTexto())<10:
				if pygame.key.get_pressed()[K_CAPSLOCK] or pygame.key.get_pressed()[K_RSHIFT] or pygame.key.get_pressed()[K_LSHIFT]:
					self.getTexto()[1].setTexto(self.getTexto()[1].getTexto()+pygame.key.name(evento.key).upper())
				else:
					self.getTexto()[1].setTexto(self.getTexto()[1].getTexto()+pygame.key.name(evento.key))
			elif evento.key == K_RETURN:
				self.cerrar()

	def cerrar(self):
		fecha = datetime.date.today()
		j = tabla.Jugador(self.getTexto()[1].getTexto(),str(fecha.day)+'/'+str(fecha.month)+'/'+str(fecha.year),self.__puntaje)
		tabla.TablaDePosiciones().agregarJugador(j)
		Subpantalla.cerrar(self)
							
#Clase JuegoTerminado
class JuegoTerminado(Subpantalla):
	def __init__(self):
		Subpantalla.__init__(self)
		self.setFondo('imagen5.jpg')
		self.agregarTexto(texto.Linea('juego terminado','Airstrip Four.ttf',(255,255,255),40,(None,200)))
		self.agregarTexto(texto.Linea('volve a intentarlo','Airstrip Four.ttf',(255,255,255),40,(None,400)))

	def eventos(self,evento):
		if evento.type == KEYDOWN:
			self.cerrar()