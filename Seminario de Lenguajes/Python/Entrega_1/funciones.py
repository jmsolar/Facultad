#-*- coding: utf-8 -*-
import pickle, os, datetime, sys

# Imprime por la salida estándar un string pasado por argumento
def imprimirCartel(cad):
    sys.stdout.write(cad)

# Lee desde la entrada estándar un string y lo retorna
def leer():
    return quitarSalto(sys.stdin.readline())

# Elimina el salto de línea del string leído desde la entrada estándar 
def quitarSalto(cad):
    return cad[:-1]
    
# Retorna un calendario cargado con la información de un archivo de texto    
def cargar(nom):
    archivo = open(nom);
    c = pickle.load(archivo);
    archivo.close()
    return c

# Almacena en un archivo de texto la información contenida en el calendario
def guardar(nom,cal):    
    archivo = open(nom,'w')
    pickle.dump(cal, archivo)
    archivo.close()
    return cal

# Instancia una fecha con los datos pasados en un string
def instanciarFecha(fe):
    try:
        dia = int(fe[:2])
        mes = int(fe[3:5])
        anio = int(fe[6:])
        miFecha = datetime.datetime(anio,mes,dia)
    except (ValueError, AttributeError):
        return False
    return miFecha

# Verifica la existencia de un archivo
def existeRuta(nom):
    return os.path.exists(nom) 

# Crea la estructura del calendario desde un archivo (en caso de que exista)
def iniciar():
    nombre = 'MiCalendario.txt'    
    if (not existeRuta(nombre)):
        calendario = {}
        guardar(nombre,calendario)        
    else:    
        calendario = cargar(nombre)        
    return calendario

# Se muestra en pantalla las opciones posibles y se retorna la elegida
def seleccionDeOpcion(tit, opcs):
    sys.stdout.write(tit)
    sys.stdout.write(opcs)    
    sys.stdout.write('\nOPCION: ')
    return leer()  