// Br.cpp: Vargas Mejia Arnulfo
// Este programa tiene un battle royale random 
//

#include <iostream>
#include <string>
#include <Windows.h>

// se crea el objeto de jugadores que tendra la vida, velocidad que le permitira huir de combates
// agilidad para esquivar ataques, ataque que con junbto a la defensa, determinara el daño dado o recibido
struct Jugadores {
public:
    std::string nombre = "";
    int vida = 0;
    int velocidad = 0;
    int agilidad = 0;
    int ataque = 0;
    int defensa = 0;
};

int main()
{
    bool combate;
    int jugadoresVivos = 20, eliminadosIndice = 0, jugadorPorPelear1 = 0, jugadorPorPelear2 = 0, agilidadComparador = 0, velocidadComparador = 0, timer = 1000;
    Jugadores* rivales[20];
    
    std::string nombresRivales[20] = { "Paul", "Julio", "Juanfer", "Pepe Ochoa","Yess","Cat","Jose Juan", "Mau","Tadeo", "Daniel Callejas", "Ulises", "Rafa","Emma", "Iker",
    "Daniel Medina", "Kevin", "Fernando", "D", "Pompa","Betsa"};
    std::string textos[5] = {" se ha encontrado a ", " quiere atacar a ", " ataco a ", " esta por pelear contra ", " le cayo mal "};
    std::string textosDeMuerte[5] = {" creyo que podia revelar los casos de corrupcion del pais, y no pudo", " estiro la pata", " se petatio", " fue a un concierto de Valentin Elizalde"
                                     , " fue a ver como crecen las flores desde abajo"};
    std::string textosHuida[3] = { " le dio miedo y corrio", " fue lo suficientemente rapido para correr", " huyo" };

    srand(time(0));
    //Asignacion de valores a cada peleador
    for (int i = 0; i < 20; i++) {
        rivales[i] = new Jugadores();
        rivales[i]->nombre = nombresRivales[i];
        rivales[i]->vida = ((rand() % 10) + 1)*5;
        rivales[i]->velocidad = (rand() % 50) + 1;
        rivales[i]->agilidad = (rand() % 50) + 1;
        rivales[i]->ataque = (rand() % 50) + 1;
        rivales[i]->defensa = (rand() % 50) + 1;
    }
    
    do {
        //Escoge jugadores optimos
        jugadorPorPelear1 = rand() % 20;
        jugadorPorPelear2 = rand() % 20;

        if (rivales[jugadorPorPelear1]->vida<=0) {
            do {
                jugadorPorPelear1 = rand() % 19;
            } while (rivales[jugadorPorPelear1]->vida <=0);
        }
        
        while (rivales[jugadorPorPelear2]->vida <=0) {
            jugadorPorPelear2 = rand() % 19;
            if (jugadorPorPelear2 == jugadorPorPelear1)
                jugadorPorPelear1 = rand() % 19;
        }
        
        //Muestra combatientes
        std::cout << rivales[jugadorPorPelear1]->nombre << textos[rand() % 5] <<rivales[jugadorPorPelear2]->nombre << std::endl;

        combate = true;

        //Logica del combate
        do 
        {
            //Compara el ataque para definir quien atacara a quien
            if (rivales[jugadorPorPelear1]->ataque > rivales[jugadorPorPelear2]->ataque) 
            {

                agilidadComparador = rand() % 50;
                velocidadComparador = rand() % 50;
                
                //Opcion de huida
                if (velocidadComparador <= rivales[jugadorPorPelear2]->velocidad/2)
                {
                    Sleep(rand() % timer);
                    rivales[jugadorPorPelear2]->velocidad - rivales[jugadorPorPelear2]->velocidad -5;
                    std::cout << rivales[jugadorPorPelear2]->nombre << textosHuida[rand() % 3] << std::endl;
                    combate = false;
                    break;
                }

                //esquive
                if (agilidadComparador <= rivales[jugadorPorPelear2]->agilidad)
                {
                    Sleep(rand() % timer);
                    std::cout << rivales[jugadorPorPelear2]->nombre << " ha esquivado el ataque" << std::endl;
                    rivales[jugadorPorPelear2]->agilidad = rivales[jugadorPorPelear2]->agilidad- 3;
                }

                
                if (rivales[jugadorPorPelear1]->ataque < rivales[jugadorPorPelear2]->vida) 
                {
                    if (rivales[jugadorPorPelear1]->ataque < rivales[jugadorPorPelear2]->defensa)
                    {
                        Sleep(rand() % timer);
                        
                        //muerte
                        if (rivales[jugadorPorPelear2]->vida <= 20) {
                            std::cout << rivales[jugadorPorPelear1]->nombre << " ha atacado" << std::endl;
                            Sleep(rand() % (timer/2));
                            rivales[jugadorPorPelear2]->vida = 0;
                            std::cout << rivales[jugadorPorPelear2]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                            eliminadosIndice++;
                            jugadoresVivos--;
                            combate = false;
                            jugadorPorPelear2 = jugadorPorPelear1;
                            break;
                        }
                        
                        //pelea
                        else
                        {
                            std::cout << rivales[jugadorPorPelear1]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear2]->vida = rivales[jugadorPorPelear2]->vida - 20;
                        }
                    }
                    else
                    {
                        Sleep(rand() % timer);
                        
                        //pelea
                        if (rivales[jugadorPorPelear2]->vida > 30)
                        {
                            std::cout << rivales[jugadorPorPelear1]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear2]->vida = rivales[jugadorPorPelear2]->vida - 30;
                        }
                        
                        //muerte
                        else if (rivales[jugadorPorPelear2]->vida <= 30)
                        {
                            std::cout << rivales[jugadorPorPelear1]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear2]->vida = 0;
                            Sleep(rand() % (timer/2));
                            std::cout << rivales[jugadorPorPelear2]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                            eliminadosIndice++;
                            jugadoresVivos--;
                            combate = false;
                            jugadorPorPelear2 = jugadorPorPelear1;
                            break;
                        }
                    }
                }
                
                //muerte
                else if (rivales[jugadorPorPelear1]->ataque >= rivales[jugadorPorPelear2]->vida) 
                {
                    Sleep(rand() % timer);
                    std::cout << rivales[jugadorPorPelear1]->nombre << " ha atacado" << std::endl;
                    rivales[jugadorPorPelear2]->vida = 0;
                    Sleep(rand() % (timer/2));
                    std::cout << rivales[jugadorPorPelear2]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                    eliminadosIndice++;
                    jugadoresVivos--;
                    combate = false;
                    jugadorPorPelear2 = jugadorPorPelear1;
                    break;
                }
            }
            
            //el indice 2 fue el que atacara
            else
            {
                agilidadComparador = rand() % 50;
                velocidadComparador = rand() % 50;
                
                //opcion de huida
                if (velocidadComparador <= (rivales[jugadorPorPelear1]->velocidad/2))
                {
                    Sleep(rand() % timer);
                    rivales[jugadorPorPelear1]->velocidad - rivales[jugadorPorPelear1]->velocidad -5;
                    std::cout << rivales[jugadorPorPelear1]->nombre << textosHuida[rand() % 3] << std::endl;
                     break;
                }
                
                //esquive
                if (agilidadComparador <= rivales[jugadorPorPelear1]->agilidad)
                {
                    Sleep(rand() % timer);
                    std::cout << rivales[jugadorPorPelear1]->nombre << " ha esquivado el ataque" << std::endl;
                    rivales[jugadorPorPelear1]->agilidad = rivales[jugadorPorPelear1]->agilidad - 3;
                }
                else if (rivales[jugadorPorPelear2]->ataque < rivales[jugadorPorPelear1]->vida)
                {
                    
                    if (rivales[jugadorPorPelear2]->ataque < rivales[jugadorPorPelear1]->defensa)
                    {
                        Sleep(rand() % timer);
                        
                        //muerte
                        if (rivales[jugadorPorPelear1]->vida <= 20)
                        {
                            std::cout << rivales[jugadorPorPelear2]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear1]->vida = 0;
                            Sleep(rand() % (timer/2));
                            std::cout << rivales[jugadorPorPelear1]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                            eliminadosIndice++;
                            jugadoresVivos--;
                            combate = false;
                            jugadorPorPelear1 = jugadorPorPelear2;
                            break;
                        }
                        
                        //pelea
                        else
                        {
                            std::cout << rivales[jugadorPorPelear2]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear1]->vida = rivales[jugadorPorPelear1]->vida - 20;
                        }
                    }
                    else
                    {
                        Sleep(rand() % timer);
                        
                        //pelea
                        if (rivales[jugadorPorPelear1]->vida > 30)
                        {
                            std::cout << rivales[jugadorPorPelear2]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear1]->vida = rivales[jugadorPorPelear1]->vida - 30;
                        }
                        //muerte
                        else if (rivales[jugadorPorPelear1]->vida <= 30)
                        {
                            std::cout << rivales[jugadorPorPelear2]->nombre << " ha atacado" << std::endl;
                            rivales[jugadorPorPelear1]->vida = 0;
                            Sleep(rand() % (timer/2));
                            std::cout << rivales[jugadorPorPelear1]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                            eliminadosIndice++;
                            jugadoresVivos--;
                            combate = false;
                            jugadorPorPelear1 = jugadorPorPelear2;
                            break;
                        }
                    }
                }
                //muerte
                else if (rivales[jugadorPorPelear2]->ataque >= rivales[jugadorPorPelear1]->vida) 
                {
                    Sleep(rand() % timer);
                    std::cout << rivales[jugadorPorPelear2]->nombre << " ha atacado" << std::endl;
                    rivales[jugadorPorPelear1]->vida = 0;
                    Sleep(rand() % (timer/2));
                    std::cout << rivales[jugadorPorPelear1]->nombre << textosDeMuerte[rand() % 5] << std::endl;
                    eliminadosIndice++;
                    jugadoresVivos--;
                    combate = false;
                    jugadorPorPelear1 = jugadorPorPelear2;
                    break;
                }
            }
            //comprueba si alguien no huyo
        }while(combate);
        std::cout << std::endl ;

        //comprueba que quede mas de un jugador vivo
    }while (jugadoresVivos > 1);

    //si solo queda un jugador vivo, se muestra el ganador
    std::cout << std::endl << "--- EL GANADOR ES: " << rivales[jugadorPorPelear1]->nombre << " ---";
}
