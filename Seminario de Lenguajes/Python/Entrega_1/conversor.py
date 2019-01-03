#-*- coding: utf-8 -*-

def encriptar(cadena):
    aux = ''
    for i in cadena:
        nuevoOrd = ord(i) + 30
        aux = aux + chr(nuevoOrd)
    return aux

def desencriptar(cadena):
    aux = ''
    for i in cadena:
        nuevoOrd = ord(i) - 30
        aux = aux + chr(nuevoOrd)
    return aux

def convertir(l):    
    nueva = []
    for i in l:        
        nueva.append(encriptar(i))            
    return nueva

def desconvertir(l):
    nueva = ''
    for i in l:        
        nueva = nueva + desencriptar(i)
    return nueva

def encriptarClaves(cl):
    nuevo = []
    for i in cl:
        nuevo.append(encriptar(str(i)))    
    return nuevo

def convertirClaves(cl,c):
    nuevo = {}    
    for i in cl:
        aux = encriptarClaves(i)    
        nuevo[tuple(aux)] = c[i]
    return nuevo

def desconvertirClaves(cl,c):
    nuevo = {}
    for i in cl:
        aux = desencriptarClaves(i)    
        nuevo[tuple(aux)] = c[i]
    return nuevo

def desencriptarClaves(cl):
    claves = []    
    for i in cl:
        nuevo = ''
        for k in i:
            aux = desencriptar(k)           
            nuevo = nuevo + aux
        claves.append(nuevo)
    return claves

def encriptarDatos(c):
    for i in c:        
        for k in range(len(c[i])):
            for l in range(len(c[i][k])):                                          
                c[i][k][l] = convertir(c[i][k][l])
    return convertirClaves(c.keys(), c)

def desencriptarDatos(c):
    for i in c:        
        for k in range(len(c[i])):     
            for l in range(len(c[i][k])):                                
                c[i][k][l] = desconvertir(c[i][k][l])
    return desconvertirClaves(c.keys(),c)