# -*- coding: utf-8 -*-
import funciones, buscar, cargar, conversor

# Elimina un cumpleaños
def eliminar(c):
    c = conversor.desencriptarDatos(c)
    fecha = cargar.validarFecha()
    try:
        buscar.existe(buscar.busqueda(0, c.keys()),fecha)
        clave = []       
        funciones.imprimirCartel('\nNombre del cumpleañero: ')        
        clave.append(fecha)
        clave.append(funciones.leer())
        tupla = (clave[0],clave[1])
        funciones.imprimirCartel('\nTipo de contacto: ')        
        tipoContacto = funciones.leer()
        funciones.imprimirCartel('\nMedio de contacto: ')        
        medioContacto = funciones.leer()
        lis = [tipoContacto,medioContacto]        
        if len(c[tupla]) <= 1:
            c.pop(tupla)
        else:            
            c[tupla].remove(lis)       
        funciones.imprimirCartel('\nSe elimino correctamente.\n')        
    except (KeyError, IndexError, AttributeError):
        funciones.imprimirCartel('\n¡ERROR!: La fecha ingresada no existe. Vuelva a intentarlo.\n')
    finally:
        c = conversor.encriptarDatos(c)      
        funciones.guardar('MiCalendario.txt',c)
    return c

# Se muestra en pantalla un menú para la eliminación de un cumpleaños
def borrarCumpleanios(cal):
    titulo = '\n** BORRAR UN CUMPLEAÑOS **'
    opciones = '\n1 - Borrar un cumpleaños.\n0 - Volver al menú anterior.\n\nPor favor ingrese una opción'
    opcion = funciones.seleccionDeOpcion(titulo, opciones)    
    while (opcion != '0'):
        try:
            miOpcion = int(opcion)            
            if (miOpcion == 1):            
                cal = eliminar(cal)    
            else:
                raise ValueError
        except (ValueError):
            funciones.imprimirCartel('\n¡ERROR!: La opción ingresada no es válida. Vuelva a intentarlo.')
        finally:
            opcion = funciones.seleccionDeOpcion(titulo, opciones)
    funciones.imprimirCartel('\n...Volviendo al menú anterior...\n\n')
    return cal