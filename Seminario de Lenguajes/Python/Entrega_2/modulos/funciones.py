# -*- coding: utf-8 -*-

from pygame.locals import *
import pygame
import os

def cargarImagen(nom, trans=False):
	"funcion para cargar imagenes"
	path = os.path.join('Imagenes',nom)
	try:
		img = pygame.image.load(path)
		img.convert()
		if trans:
			key = img.get_at((0,0))
			img.set_colorkey(key,RLEACCEL)
		return img
	except (pygame.error):
		print 'No se pudo cargar la imagen',nom
		raise SystemExit

def cargarFuente(nom,tam):
	"funcion para cargar fuentes"
	path = os.path.join('Fuentes',nom)
	try: 
		font = pygame.font.Font(path,tam)
	except (IOError): 
		font = pygame.font.SysFont(None,tam)
	return font

def cargarTexto(nom):
	"funcion para cargar archivos de texto"
	path = os.path.join('Textos',nom)
	try:
		return open(path,'r').readlines()
	except (IOError):
		print 'No se pudo cargar el archivo',nom
		raise SystemExit

def abrirArchivo(nom,modo='r'):
	"funcion para abrir archivos"
	try:
		return open(nom,modo)
	except (IOError):
		print 'No se pudo cargar el archivo',nom