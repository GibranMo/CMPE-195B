// ### JOGO DESENVOLVIDO POR BRUNO CALOU ALVES ### //

#include "SDL/SDL.h"
#include <cstdlib>
#include <ctime>
int aleatorio()
{
    srand(time(0));
    int valor = rand()%15;
    if (valor == 0)//1/15 de chance de dar zero
    {
        return 0;
    }
    return 1;

}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destino)
{
    SDL_Rect retangulo;//posicao na verdade, por que so foram definidos x e y
    retangulo.x = x;
    retangulo.y = y;

    SDL_BlitSurface(source, NULL, destino, &retangulo);//atualiza a tela
}

int main( int argc, char* args[] )
{
    //variaveis
    bool rodando = true;
    SDL_Event evento;
    int D = 4;//variavel para regular a velocidade do jogo
    bool comecar = false;
    bool primeiravez = false;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption("Pong", NULL);


    //Janela
    SDL_Surface *janela;
    janela = SDL_SetVideoMode(721,481,24,SDL_HWSURFACE);

    //Tela inicial
    SDL_Surface *inicio;
    inicio = SDL_LoadBMP("inicio.bmp");

    //fundo
    SDL_Surface *fundo;
    fundo = SDL_LoadBMP("Fundo.bmp");

    //Raquete do jogador
    SDL_Surface *jogador = NULL;
    jogador = SDL_LoadBMP("Raquete1.bmp");
    SDL_Rect posicaoj;
    posicaoj.x = 0;
    posicaoj.y = 225.5;

    //Raquete do pc
    SDL_Surface *pc;
    pc = SDL_LoadBMP("Raquete2.bmp");
    SDL_Rect posicaopc;
    posicaopc.x = 711;
    posicaopc.y = 225.5;

    //Bola
    SDL_Surface *bola;
    bola = SDL_LoadBMP("bola.bmp");
    SDL_Rect posicaob;
    posicaob.x = 350.5;
    posicaob.y = 232.5;
    float velx = 2.0;
    float vely = 2.0;

    //pontuacao jogador
    SDL_Surface *pontos;
    pontos = SDL_LoadBMP("Numeros.bmp");
    SDL_Rect posicaonum;
    posicaonum.x = 300;
    posicaonum.y = 200;

    SDL_Rect pontuacao1;
    pontuacao1.x = 0;
    pontuacao1.y = 0;
    pontuacao1.h = 33;
    pontuacao1.w = 44;

    int contador1 = 0;
    //pontuacao pc
    SDL_Surface *pontospc;
    pontospc = SDL_LoadBMP("Numeros.bmp");
    SDL_Rect posicaonumpc;
    posicaonumpc.x = 377.0;
    posicaonumpc.y = 200;

    SDL_Rect pontuacao2;
    pontuacao2.x = 0.0;
    pontuacao2.y = 0;
    pontuacao2.h = 33;
    pontuacao2.w = 44;

    int contador2 = 0;

    //Fim de jogo
    SDL_Rect posicaof;
    posicaof.x = 185.5;
    posicaof.y = 100;
    SDL_Surface *perdedor;
    perdedor = SDL_LoadBMP("perdedor.bmp");
    SDL_Surface *vencedor;
    vencedor = SDL_LoadBMP("vencedor.bmp");


    if(janela==NULL)
    {
        rodando = false;
    }

    //Jogo rodando

    while(rodando)
    {
        SDL_PollEvent(&evento);//evento eh atualizado com o evento que ocorre

        //Sair
        if(evento.type == SDL_QUIT)
        {
            rodando = false;
        }

        if(comecar == false)
        {
            apply_surface(0,0,inicio, janela);
            SDL_Flip(janela);
            Uint8 *opcao = SDL_GetKeyState(NULL);
            if(opcao[SDLK_SPACE])
            {
                comecar = true;
                primeiravez = true;
            }
            continue;
        }


            //pega a informacao de continuidade do jogo
        if(contador2 == 10 || contador1 == 10)
        {
                Uint8 *opcao = SDL_GetKeyState(NULL);
                if(opcao[SDLK_s])
                {
                    //zera o jogo
                        posicaopc.y = 225.5;
                        posicaoj.y = 225.5;
                        posicaonumpc.x =377;
                        posicaonum.x = 300;
                        pontuacao2.x = 0;
                        posicaonum.x = 300;
                        pontuacao1.x = 0;
                        contador2 = 0;
                        contador1 = 0;
                        D = 4;
                }
                if(opcao[SDLK_n])
                {
                    rodando = false;
                    contador2 = 0;
                    contador1 = 0;
                    break;
                }
                continue;
            }

        //Movimento da bola
        posicaob.x -= velx;
        posicaob.y += vely;
        if(posicaob.y > 451 )
        {
            posicaob.y = 451;
        }
        if (posicaob.y < 20)
        {
            posicaob.y = 20;
        }

        SDL_Delay(D);
        //reflexao da bola nas paredes
        if(posicaob.y == 20 or posicaob.y == 451)
        {vely *= -1;}
        //reflexao da bola no jogador
        if(posicaob.y >= posicaoj.y -19 && posicaob.y < posicaoj.y + 59 && posicaob.x <= posicaoj.x + 11)
        {
            if(posicaob.x == posicaoj.x + 11)
            {posicaob.x -=1;}
            if(posicaob.x == posicaoj.x + 10)
            {velx *= -1;}
        }
        //reflexao da bola no pc
        if(posicaob.y >= posicaopc.y -19 && posicaob.y < posicaopc.y + 59 && posicaob.x >= posicaopc.x - 21)
        {
            if(posicaob.x == posicaopc.x - 21)
            {posicaob.x += 1;}
            if(posicaob.x == posicaopc.x - 20)
            {velx *= -1; }
            if (D > 1)
            {
                D -=1;
            }
        }
        //pontuacao
        if (posicaob.x < -21)
           {
            //atualiza a pontuacao
            posicaonumpc.x -= 1;
            pontuacao2.x += 44;
            contador2 +=1;

            //comeca um novo jogo
            posicaob.x = 350.5;
            posicaob.y = 232.5;
            posicaoj.y = 225.5;
            posicaopc.y = 225.5;
            D = 4;
            SDL_Delay(500);
           }

           if (posicaob.x > 742)
           {
            //atualiza a pontuacao
            posicaonum.x -= 1;
            pontuacao1.x += 44;
            contador1 += 1;

            //comeca um novo jogo
            posicaob.x = 350.5;
            posicaob.y = 232.5;
            posicaoj.y = 225.5;
            posicaopc.y = 225.5;
            D = 4;
            SDL_Delay(500);
           }

        //Movimento do pc
        if(velx < 0 && vely > 0 && posicaob.y <= posicaopc.y && posicaopc.y < 401)
        {
            posicaopc.y += 2*aleatorio();
        }
        if(velx < 0  && vely < 0 && posicaob.y >= posicaopc.y && posicaopc.y > 20)
        {
            posicaopc.y -= 2*aleatorio();
        }
        if(velx < 0 && vely > 0 && posicaob.y >= posicaopc.y && posicaopc.y < 401)
        {
            posicaopc.y += 2*aleatorio();
        }
        if(velx < 0  && vely < 0 && posicaob.y <= posicaopc.y && posicaopc.y > 20)
        {
            posicaopc.y -= 2*aleatorio();
        }


        //Movimentos do jogador
        Uint8 *tecla = SDL_GetKeyState(NULL);
        if(tecla[SDLK_UP] && posicaoj.y > 20)
        {
            posicaoj.y -= 2;
        }
        if(tecla[SDLK_DOWN] && posicaoj.y < 401)
        {
            posicaoj.y += 2;
        }

       /* //Preenchendo a tela
        SDL_FillRect(janela,NULL, 0);
        SDL_BlitSurface(fundo, NULL, janela, NULL);
        SDL_BlitSurface(jogador, NULL, janela, &posicaoj);
        SDL_BlitSurface(pc, NULL, janela, &posicaopc);
        SDL_BlitSurface(bola, NULL, janela, &posicaob);
        //Atualizando a tela*/ //DESSA MANEIRA NAO TINHA COMO TER VALORES DE X E Y NEGATIVOS



        //Preenchendo a tela
        apply_surface(0,0, fundo, janela);
  //      apply_surface(posicaonum.x, posicaonum.y, pontos, janela);
        SDL_BlitSurface(pontos, &pontuacao1, janela, &posicaonum);
        SDL_BlitSurface(pontospc, &pontuacao2, janela, &posicaonumpc);
        apply_surface(posicaoj.x,posicaoj.y,jogador, janela);
        apply_surface(posicaopc.x,posicaopc.y,pc, janela);
        apply_surface(posicaob.x,posicaob.y,bola, janela);

        if(contador1 ==10)
            {
                //mensagem de um novo jogo
                apply_surface(posicaof.x, posicaof.y, vencedor, janela);
            }
        if(contador2 == 10)
            {
                //mensagem de um novo jogo
                apply_surface(posicaof.x, posicaof.y, perdedor, janela);
            }


        //Atualizando a tela
        SDL_Flip(janela);

        if(primeiravez)
        {
            SDL_Delay(800);
            primeiravez = false;
        }
    }


    SDL_FreeSurface(inicio);
    SDL_FreeSurface(fundo);
    SDL_FreeSurface(jogador);
    SDL_FreeSurface(pc);
    SDL_FreeSurface(bola);
    SDL_FreeSurface(pontos);
    SDL_FreeSurface(pontospc);
    SDL_FreeSurface(janela);

    //Quit SDL
    SDL_Quit();

    return 0;
}
