# -*- coding: utf-8 -*-

import pygame
import funciones
from pygame.locals import *

class Texto(pygame.sprite.Sprite):
	"clase base de texto"
	def __init__(self,text,font,col,size,pos,ID=None):
		pygame.sprite.Sprite.__init__(self)
		self.__text = text
		self.__font = font
		self.__color = col
		self.__size = size
		self.__pos = pos
		self.__rect = None
		self.__ID = ID
		self.setFuente(font)

	def getTexto(self):
		return self.__text

	def setTexto(self,txt):
		self.__text = txt

	def getFuente(self):
		return self.__font

	def setFuente(self,font):
		self.__font = font
		self.__objFont = funciones.cargarFuente(self.getFuente(),self.getTamanio())

	def getColor(self):
		return self.__color

	def setColor(self,col):
		self.__color = col

	def getTamanio(self):
		return self.__size

	def setTamanio(self,size):
		self.__size = size
		self.setFuente (self.getFuente())

	def getPosicion(self):
		return self.__pos

	def setPosicion(self,pos):
		self.__pos = pos

	def getObjFont(self):
		return self.__objFont

	def setRect(self,rect):														
		self.__rect = rect

	def getRect(self):
		return self.__rect
	
	def setID(self,ID):
		self.__ID = ID
		
	def getID(self):
		return self.__ID

	def isOver(self,point):
		try: return self.__rect.collidepoint(point)
		except: return False

	def negrita(self,boolean):
		self.__objFont.set_bold(boolean)

	def imprimir(self,surf,t):
		p = t.get_rect()
		if (self.getPosicion()[0] == None): p.centerx = surf.get_width()/2
		else: p.left = self.getPosicion()[0]
		if (self.getPosicion()[1] == None): p.centery = surf.get_height()/2
		else: p.top = self.getPosicion()[1]
		self.setRect(surf.blit(t,p))

class Linea(Texto):
	"clase para una linea de texto"
	def __init__(self,text,font,col,size,pos,ID=None):
		Texto.__init__(self,text.decode('utf-8'),font,col,size,pos,ID)

	def setTexto(self,text):		
		Texto.setTexto(self,text.decode('utf-8'))

	def imprimir(self,surf):
		f = self.getObjFont()
		t = f.render(self.getTexto(),1,self.getColor())
		Texto.imprimir(self,surf,t)

class Parrafo(Texto):
	"clase para un parafo de texto"
	def __init__(self,text,font,col,size,pos,ID=None):
		Texto.__init__(self,None,font,col,size,pos,ID)
		self.setTexto(text)

	def setTexto(self,text):
		for i in range(len(text)):			
			text[i] = text[i].decode('utf-8')
		Texto.setTexto(self,text)

	def imprimir(self,surf):
		f = self.getObjFont()
		h = len(self.getTexto()) * self.getTamanio()
		w = 0
		for l in self.getTexto():
			if (f.size(l)[0] > w): w = f.size(l)[0]
		s = pygame.Surface((w,h))
		s.set_colorkey(s.get_at((0,0)),RLEACCEL)
		p = pygame.Rect(0,0,0,0)
		for l in self.getTexto():
			t = f.render(l,1,self.getColor())
			s.blit(t,p)
			p.move_ip(0,self.getTamanio())
		Texto.imprimir(self,surf,s)