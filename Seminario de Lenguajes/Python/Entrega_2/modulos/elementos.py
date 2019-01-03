# -*- coding: utf-8 -*-

import pygame
import funciones
import os
import random

class Elemento(pygame.sprite.Sprite):
	"clase base para todos los elementos"
	def __init__(self,img,pos=(0,0),ID=None):
		pygame.sprite.Sprite.__init__(self)
		self.image = funciones.cargarImagen(img,1)
		self.rect = self.image.get_rect(topleft=pos)
		self.__ID = ID				

	def getPosicion(self):
		return (self.rect.left,self.rect.top)

	def setPosicion(self,pos):
		self.rect.left = pos[0]
		self.rect.top = pos[1]

	def isOver(self,point):
		try: return self.rect.collidepoint(point)
		except: return False

	def getID(self):
		return self.__ID
	
	def getRect(self):
		return self.rect	
		
class Boton(Elemento):
	"clase para botones"
	def __init__(self,img,pos=(0,0),ID=None):
		Elemento.__init__(self,img,pos,ID)

	def click(self,point):
		return self.isOver(point)

class Tipito(Elemento):
	"clase para los tipitos"
	def __init__(self,pos=(0,0)):
		Elemento.__init__(self,'tipito.png',pos)		


class Contenedor(Elemento):
	"clase para los contenedores de cuentas y objetos"
	def __init__(self,img,pos,ID):
		Elemento.__init__(self,img,pos,ID)		
		self.__cuentas = pygame.sprite.Group()		

	def getCuentas(self):
		return self.__cuentas	

	def agregarCuenta(self,cuenta):
		self.__cuentas.add(cuenta)