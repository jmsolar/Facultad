# -*- coding: utf-8 -*-
import conversor, funciones

def validarFecha():
    formato = '%d/%m/%Y'
    funciones.imprimirCartel('\nRespetando el formato "dd/mm/aaaa", ingrese la fecha del cumpleañero: ')
    try:
        stringFecha = funciones.leer()
        fecha = funciones.instanciarFecha(stringFecha).strftime(formato)
        if fecha == False:
            raise AttributeError
        else:
            return fecha
    except (AttributeError):
        funciones.imprimirCartel('\n¡ERROR!: La fecha es inválida. Vuelva a intentarlo.\n\n') 
        raise AttributeError   

def existeCumpleanios(claves, t):
    encontre = False
    for i in range(len(claves)):
        if claves[i] == t:
            encontre = True
            break
    return encontre 

def existeMedioContacto(c, l):
    encontre = False
    for i in c:       
        for j in c[i]:
            if (j == l):
                encontre = True
                break
    return encontre

def agregarCumpleanios(c, lis, t):
    if (len(c) == 0) | (not existeCumpleanios(c.keys(), t)):
        l = []
        c[t] = l
    elif (existeMedioContacto(c, lis)):
        funciones.imprimirCartel('\n¡ERROR!: El medio de contacto (tipo y medio de contacto) debe ser único. Vuelva a intentarlo.\n\n')
        return False    
    c[t].append(lis)
    return True    
                
def obtenerDatos(c):
    clave = []    
    funciones.imprimirCartel('\n**  CARGAR UN CUMPLEAÑOS  **\n')
    try:
        fe = validarFecha()
        clave.append(fe)
    except (UnboundLocalError, AttributeError):
        return c 
    funciones.imprimirCartel('\nNombre del cumpleañero: ')
    clave.append(funciones.leer())
    tupla = (clave[0], clave[1])    
    funciones.imprimirCartel('\nTipo de contacto: ')
    tipoContacto = funciones.leer()
    funciones.imprimirCartel('\nMedio de contacto: ')
    medioContacto = funciones.leer()
    lis = [tipoContacto, medioContacto]
    if (agregarCumpleanios(c, lis, tupla)):
        funciones.imprimirCartel('\nSe agrego correctamente.\n\n')
    return c    
        
def cargarCumpleanios(calendario):
    nombre = 'MiCalendario.txt'
    calendario = funciones.cargar(nombre)    
    calendario = conversor.desencriptarDatos(calendario)    
    calendario = conversor.encriptarDatos(obtenerDatos(calendario))    
    funciones.guardar(nombre,calendario)
    return calendario