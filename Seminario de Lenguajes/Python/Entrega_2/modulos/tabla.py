# -*- coding: utf-8 -*-

import os
import persistencia

class Jugador:
	"clase para los jugadores"
	def __init__(self,nombre,fecha,puntaje=0):
		self.__nombre = nombre
		self.__fecha = fecha
		self.__puntaje = puntaje

	def __cmp__(self,otro) :
		if int(self.__puntaje) > int(otro.__puntaje): return -1
		elif int(self.__puntaje) < int(otro.__puntaje): return 1
		else: return 0

	def imprimir(self):
		return [str(self.__nombre),str(self.__fecha),str(self.__puntaje)]

class TablaDePosiciones:
	"clase para la tabla de posiciones"
	def __init__(self):
		self.__jugadores = []
		self.__cargar()

	def agregarJugador(self,jug):
		self.__jugadores.append(jug)
		self.__jugadores.sort()
		if len(self.__jugadores) > 5:
			self.__jugadores.pop()	
		self.guardar()

	def imprimir(self):
		t = []
		for j in self.__jugadores:
			t.append(j.imprimir())
		return t

	def guardar(self):
		path = os.path.join('Textos','tabla.txt')		
		persistencia.guardar(self.imprimir(),path)

	def __cargar(self):
		path = os.path.join('Textos','tabla.txt')
		if (not os.path.exists(path)):
			est = []
			persistencia.crear(est,path)
		t = persistencia.cargar(path)
		for i in range(len(t)):
			t[i] = Jugador(t[i][0],t[i][1],t[i][2])
		self.__jugadores = t