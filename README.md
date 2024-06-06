# TC_1030_ABA
# Simulador de Combates Epicos
Este proyecto esta basado en el juego Your Only Move is Hustle, un juego de pelea basado en turnos. En el Proyecto el usuario elige sus movimientos con comandos en la consola al enfrentarse a un enemigo que aun no cuenta con movimientos. Se cuenta con 2 clases basadas en personajes del juego, cada una con sus propios movimientos distintos, asi como una clase para los proyectiles, una para controlar la escena  y una para manejar todo lo relacionado a la interaccion con el usuario.

### Personajes
El ninja es una clase de corto alcance, pero de ataques rapidos y con prioridad (No implementado aun)
El Cowboy es una clase basada principalmente en ataques cuerpo a cuerpo con espada de mediano a largo alcance, cuenta tambien con una pistola con 6 balas (No implementado Aun)
El Mago es una clase que recompensa prepararse unos turnos con proyectiles de largo alcance (proyectiles aun no implementados)
El Robot es una clase basada en agarres y ataques mas pesados y lentos 

## Funcionamiento
El programa solo acepta comandos validos para la situacion en la que se esté (obviamente), por ejemplo, un movimiento aereo no podra ser ejecutado si el personaje esta en el suelo. Cuando el programa pide una entrada numerica y no se le es dada, el programa fallara. En caso de que una accion que se desea tomar no este implementada, el juego hara que el personaje del jugador no haga nada por ese turno (esperar)

## Instrucciones y Mas
Solo hace falta escribir en la consola:

g++ main.cpp 

Para generar el archivo ejecutable. 
Al ejecutar se muestra un menu de selccion de personaje, se elige primero al personaje del jugador y luego al enemigo.

# Gameloop
En cada turno se pedira al jugador que eliga un movimiento que hacer de los que se muestran en la pantalla, en caso de no elegir un movimiento valido, el movimiento predeterminado será "wait". Al terminar la eleccion se procede a la etapa de "simulacion". Cada movimiento tiene una cantidad de "frames" que toma para ser completado y poder volver a permitir al usuario escojer otro movimiento. Para los ataques existe un Hitbox que busca una colision con el jugador enemigo en los ultimos "frames" del movimiento. ( por ejemplo, un ataque puede tener duracion de 12 frames y 5 frames de ataque, eso significa que de los frames 1 a 7 del movimiento no se checa la colision, es solo hasta los ultimos 5 en donde se puede dañar al enemigo).
Cada frame actualiza cada objeto en el juego ( personajes y proyectiles ), cambiando su posicion de acuerdo al momentum, y verficando si hay daño tomado si asi es requerido. Los frames dejan de "correr" cuando el numero de frames de espera de ambos personajes llegue a 0 o hasta que uno sea golpeado. Un frame representa alrededor de 0.1 segundos.
Una vez termina la simulacion, se vuelve a la fase de eleccion de movimiento.

# Super Ataques
Cada frame se va aumentando el SuperNivel, una vez se llega a la cantidad adecuada de SuperNivel, se mostraran mas opciones de ataques que gastaran carga del mismo. Cada personaje tiene sus propios Super Ataques.

# Guia Rapida
A continuacion un pequeño resumen de cada movimiento que se encuentra implementado:
(Cada personaje mide 3 unidades de alto por 2 de ancho)

Wait:
No hace nada, espera 5 frames

Jump:
Le pedira al jugador valores para un vector unitario 2d, luego el personaje saltara en esa direccion

Dash:
Acerca al personaje al enemigo

SuperDash
Acerca al personaje al enemigo aun mas rapido, ademas de añadir un salto

Block:
Bloquea todo tipo de ataque

Robot : BoundsCheck
Se impulsa hacia adelante para tomar el enemigo y dañarlo

Robot : Punch
Golpe de corto alcance, pero mucho daño

Robot : Grab
Ataque de largo alcance y buen daño

Robot : TryCatch
Ataque enfocado a ser un antiaereo, pero con buena covertura

Robot : LOIC (SuperAtaque)
Selecciona cualquier punto de la escena para lanzar un rayo, tiene alcance vertical maximo. Se mueve con el personaje

Wizzard : TomeSlap
Ataque rapido de corto alcance

Wizzard : Missile Form
Pedira al jugador compenentes de un vector unitario 2d, luego lanzara al personaje en esa direccion, dañando al enemigo si lo toca

Wizzard : Geyser
Ataque de Gran alcance, pero un tanto lento.

