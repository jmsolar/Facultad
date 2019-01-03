# -*- coding: utf-8 -*-

import funciones, conversor, time
from icalendar import Calendar, Event, vRecur

# Crea el evento de un cumpleaños
def crearEvento(fe, nom, desc):
    evento = Event()
    time.sleep(0.10) # Genero un retardo para que aquellos cumpleaños con misma fecha puedan almacenarse correctamente
    evento.add('summary', 'Cumpleaños de ' + nom)
    evento.add('dtstart', fe)
    evento.add('dtend', fe)
    evento.add('rrule', vRecur(freq='yearly'))
    evento.add('description', desc)
    return evento

# Obtiene desde el calendario los datos de los cumpleañeros y los agrega a la estructura que generara el archivo iCal
def obtenerDatos(c, miCal):
    for i in c.keys():        
        fecha = funciones.instanciarFecha(i[0])
        nombre = i[1]        
        for j in c[i]:
            tipo = j[0]            
            medio = j[1]
            desc = tipo + ':  ' + medio
            e = crearEvento(fecha,nombre,desc)
            miCal.add_component(e)
    return miCal

# Escribe el archivo iCal con la informacion pasada por parametro
def cargarArchivoExportado(miCal):
    f = open('exportado.iCal','wb')    
    f.write(miCal.as_string())
    f.close()

# Genera el archivo iCal
def creacionArchivo(cal):
    aux = conversor.desencriptarDatos(cal)
    if (len(aux) != 0):
        miCal = Calendar()    
        miCal = obtenerDatos(aux,miCal)    
        cargarArchivoExportado(miCal)
        funciones.imprimirCartel('\nCalendario exportado correctamente.\n')
    else:
        funciones.imprimirCartel('\nNo puede generarse el archivo ya que no hay cumpleaños en el calendario.\n')    

# Se muestra en pantalla el menu de opciones a elegir
def exportarCalendario(cal):
    titulo = '\n// EXPORTAR CUMPLEAÑOS //'
    opciones = '\n1 - Exportar cumpleaños.\n0 - Volver al menú anterior.\n\nPor favor, ingrese una opción.'
    opcion = funciones.seleccionDeOpcion(titulo,opciones)
    while (opcion != '0'):
        try:        
            miOpcion = int(opcion)
            if (miOpcion == 1):
                creacionArchivo(cal)
                print cal
            else:
                raise ValueError
        except (ValueError):
            funciones.imprimirCartel('\n¡ERROR!: La opción ingresada no es válida. Vuelva a intentarlo.\n')
        finally:
            opcion = funciones.seleccionDeOpcion(titulo,opciones) 
    funciones.imprimirCartel('\n...Volviendo al menú anterior...\n\n')