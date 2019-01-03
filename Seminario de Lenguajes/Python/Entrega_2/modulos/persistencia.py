# -*- coding: utf-8 -*-

import funciones
import pickle

def crear(datos,nom):
	encriptarEstructura(datos)
	a = open(nom,'w')
	pickle.dump(datos,a)
	a.close()	
	
def guardar(datos,nom):
	encriptarEstructura(datos)
	f = funciones.abrirArchivo(nom,'w')
	pickle.dump(datos,f)
	f.close()

def cargar(nom):	
	f = funciones.abrirArchivo(nom)
	datos = pickle.load(f)
	f.close()	
	desencriptarEstructura(datos)
	return datos

def encriptar(e):
	aux = ''
	for i in e:
		nuevoOrd = ord(i) + 30
		aux = aux + chr(nuevoOrd)
	return aux

def desencriptar(e):
	aux = ''
	for i in e:
		nuevoOrd = ord(i) - 30
		aux = aux + chr(nuevoOrd)
	return aux

def encriptarEstructura(est):
	for i in range(len(est)):
		if (type(est[i]) == str): 
			est[i] = encriptar(est[i])
		else: 
			encriptarEstructura(est[i])

def desencriptarEstructura(est):
	for i in range(len(est)):
		if (type(est[i]) == str): 
			est[i] = desencriptar(est[i])
		else: 
			desencriptarEstructura(est[i])