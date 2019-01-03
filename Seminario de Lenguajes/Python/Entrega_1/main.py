# -*- coding: utf-8 -*-
import funciones, buscar, cargar, borrar, exportar

# PROGRAMA PRINCIPAL
calendario = funciones.iniciar()
titulo = '// CALENDARIO DE CUMPLEAÑOS //\n'
opciones = '\n1 - Cargar un nuevo cumpleaños.\n2 - Borrar un cumpleaños.\n3 - Buscar un cumpleaños por fecha o nombre de cumpleaños.\n4 - Exportar calendario.\n0 - Salir.\n\nPor favor, ingrese una opción.'
opcion = funciones.seleccionDeOpcion(titulo, opciones)
while (opcion != '0'):
    try:
        miOpcion = int(opcion)
        if (miOpcion == 1):            
            calendario = cargar.cargarCumpleanios(calendario)
        elif (miOpcion == 2):
            calendario = borrar.borrarCumpleanios(calendario)
        elif (miOpcion == 3):          
            buscar.buscarCumpleanios(calendario)
        elif(miOpcion == 4):
            exportar.exportarCalendario(calendario)
        else:
            raise ValueError
    except (ValueError):
        funciones.imprimirCartel('\n¡ERROR!: La opción ingresada no es válida. Vuelva a intentarlo.\n\n')        
    finally:
        opcion = funciones.seleccionDeOpcion(titulo, opciones)
funciones.imprimirCartel('\n...Cerrando el programa...')
# FIN DEL PROGRAMA PRINCIPAL