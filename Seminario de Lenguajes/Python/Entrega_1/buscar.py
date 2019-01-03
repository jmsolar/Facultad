# -*- coding: utf-8 -*-
import funciones, cargar, conversor

# Busca en una lista de claves el valor pasado por parametro
def existeClave(ind,c,dato):
    existe = False
    try:
        for i in c.keys():
            if i[ind] == dato:
                existe = True
                break          
    except (IndexError):
        raise IndexError
    finally:
        return existe

# Devuelve un formato de string segun los parametros recibidos
def asignoStrings(n,j,f):
    if n == 0:
        cadena1 = 'Tipo de contacto: ' + j[0]
        cadena2 = ', Medio de contacto: '+ j[1] + '\n' 
    else:
        funciones.imprimirCartel('\nFecha de cumpleaños: ' + f)
        cadena1 = ', Tipo de contacto: ' + j[0]
        cadena2 = ', Medio de contacto: '+ j[1] + '\n'
    return cadena1, cadena2

# Se muestran en pantalla los datos pertenecientes a cumpleañeros que cumplan cierta condicion (fecha o nombre) 
def imprimirParaDato(dato,c,num):
    for i in c.keys():
        if i[num] == dato:
            if (num == 0):
                funciones.imprimirCartel('\nNombre: ' + i[1] + ' ')
            for j in c[i]:
                cad = asignoStrings(num,j,i[0])
                funciones.imprimirCartel(cad[0])
                funciones.imprimirCartel(cad[1])                        
            funciones.imprimirCartel('\n--------------------------------------------------------------------\n')
    funciones.imprimirCartel('\n')         

# Se realiza la busqueda por fecha de cumpleañero
def busquedaPorFecha(c):
    aux = conversor.desencriptarDatos(c)
    fecha = cargar.validarFecha()
    try:
        if existeClave(0,aux,fecha):
            funciones.imprimirCartel('\nLas personas que cumplieron años en la fecha ' + fecha + ', son:\n')        
            imprimirParaDato(fecha,aux,0)
        else:
            funciones.imprimirCartel('\nLa fecha ' + fecha + ' no existe.\n')            
    except (IndexError):
        funciones.imprimirCartel('\nLa fecha ' + fecha + ' no existe.\n')    

# Se realiza la busqueda por nombre de cumpleañero
def busquedaPorNombre(c):
    aux = conversor.desencriptarDatos(c)
    funciones.imprimirCartel('\nPor favor ingrese el nombre a buscar: ')    
    nombre = funciones.leer()
    try:        
        if existeClave(1,aux,nombre):
            funciones.imprimirCartel('\nLas personas con nombre ' + nombre + ' registradas, son:\n')
            imprimirParaDato(nombre,aux,1)
        else:
            funciones.imprimirCartel('\nEl nombre ' + nombre + ' no existe.\n')
    except (IndexError):
        funciones.imprimirCartel('\nEl nombre ' + nombre + ' no existe.\n')
        
        
# Se muestra en pantalla un menu con opciones para elegir
def buscarCumpleanios(cal):
    titulo = '\n** BUSCAR UN CUMPLEAÑOS **\n'
    opciones = '1 - Busqueda por fecha de cumpleaños.\n2 - Busqueda por nombre del cumpleañero.\n0 - Volver al menú anterior.\n\nPor favor, ingrese una opción.'
    opcion = funciones.seleccionDeOpcion(titulo, opciones)    
    while (opcion != '0'):
        try:
            miOpcion = int(opcion)                        
            if (miOpcion == 1):
                busquedaPorFecha(cal)                
            elif (miOpcion == 2):
                busquedaPorNombre(cal)                
            else:
                raise ValueError
        except (ValueError):
            funciones.imprimirCartel('\n¡ERROR!: La opción ingresada no es válida. Vuelva a intentarlo.\n')
        finally:
            opcion = funciones.seleccionDeOpcion(titulo,opciones)  
    funciones.imprimirCartel('\n...Volviendo al menú anterior...\n\n')