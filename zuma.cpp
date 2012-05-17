#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdlib>

// Includes Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "lista.h"
#include "bola.h"

using namespace std;
using namespace Lista;


void carregarMapa(int* &xpos, int* &ypos, int& tamanho, char* filename) {
    FILE* arquivo = fopen(filename, "r");
    int i;

    if (arquivo == NULL) {
        cout << "erro ao abrir o arquivo\n";
        return;
    }

    fscanf(arquivo, "%i", &tamanho);
    xpos = new int[tamanho];
    ypos = new int[tamanho];

    for (i = 0; i < tamanho; ++i) {
        fscanf(arquivo, "%i %i", &xpos[i], &ypos[i]);
    }

    fclose(arquivo);
    
}

ALLEGRO_COLOR corDaBola(int i) {
    if (i == 0) {
        return al_map_rgb(150, 0, 0);
    }
    else if (i == 1) {
        return al_map_rgb(0, 150, 0);
    }
    else if (i == 2) {
        return al_map_rgb(0, 0, 150);
    }
    else
        return al_map_rgb(150, 150, 0);
}

bool colidiu(Bola b1, int x2, int y2, int* x_pos, int* y_pos) {
    int x1 = x_pos[b1.pos];
    int y1 = y_pos[b1.pos];

    int dx = x2 - x1;
    int dy = y2 - y1;

    int radii = 5 + 5;

    if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main() {
    int* x_pos = NULL;
    int* y_pos = NULL;

    float tiro_x = -1;
    float tiro_y = -1;
    bool pode_atirar = false;

    int posicao_x_jogador = 255;
    int posicao_y_jogador = 200;
    
    float coeficiente_angular;

    bool redesenhar = false;
    bool execute = false;
    int tamanho;
    lista<Bola> bolas;
    Bola b;
    Bola bola_tiro;
    Bola bola_tiro_nova;
    b.pos = 0;
    b.cor = 3;
    bola_tiro.pos = 0;
    bola_tiro.cor = 0;
    bola_tiro_nova.cor = 0;

    ALLEGRO_DISPLAY* janela = NULL;
    ALLEGRO_EVENT_QUEUE* evento = NULL; 
    ALLEGRO_TIMER* timer = NULL;


    if (!al_init()) {
        cout << "Nao foi possivel iniciar o allegro\n";
        return -1;
    }

    if(!al_install_mouse()) {
        cout << "erro com o rato!\n";
        return -1;
    }

    al_init_primitives_addon();
    carregarMapa(x_pos, y_pos, tamanho, "mapa1.txt");

    timer  = al_create_timer(1.0 / 60.0);
    janela = al_create_display(500, 500);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(janela));
    al_register_event_source(evento, al_get_timer_event_source(timer));
    al_register_event_source(evento, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

    int incrementar = -1;
    bool desenhar_tiro = false;
    pode_atirar = true;
    tiro_x = -1;
    tiro_y = -1;

    int novacor = 0;
    int pos_bola = 0;

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(evento, &ev);

        //atualiza as informacoes do jogo
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redesenhar = true;
            ++novacor;

            //atualiza as coordenadas do tiro
            if (pode_atirar == false) {
                if (incrementar == 0) {
                    tiro_y += 3;
                    tiro_x = (int)((tiro_y - posicao_y_jogador + coeficiente_angular * posicao_x_jogador) / coeficiente_angular);
                }
                else if (incrementar == 1) {
                    tiro_x += 3;
                    tiro_y = (int) (coeficiente_angular * (tiro_x - posicao_x_jogador) + posicao_y_jogador);
                }
                else if (incrementar == 2) {
                    tiro_y += 3;
                    tiro_x = (int)((tiro_y - posicao_y_jogador + coeficiente_angular * posicao_x_jogador) / coeficiente_angular);
                }
                else if (incrementar == 3) {
                    tiro_x -= 3;
                    tiro_y = (int) (coeficiente_angular * (tiro_x - posicao_x_jogador) + posicao_y_jogador);
                }
                else if (incrementar == 4) {
                    tiro_y -= 3;
                    tiro_x = (int)((tiro_y - posicao_y_jogador + coeficiente_angular * posicao_x_jogador) / coeficiente_angular);
                }
                else if (incrementar == 5) {
                    tiro_x -= 3;
                    tiro_y = (int) (coeficiente_angular * (tiro_x - posicao_x_jogador) + posicao_y_jogador);
                }
                else if (incrementar == 6) {
                    tiro_y -= 3;
                    tiro_x = (int)((tiro_y - posicao_y_jogador + coeficiente_angular * posicao_x_jogador) / coeficiente_angular);
                }
                else if (incrementar == 7) {
                    tiro_x += 3;
                    tiro_y = (int) (coeficiente_angular * (tiro_x - posicao_x_jogador) + posicao_y_jogador);
                }
            }

            if (tiro_x > 500 || tiro_x < 0 || tiro_y > 500 || tiro_y < 0) {
                desenhar_tiro = false;
                pode_atirar = true;
            }
            else {
                desenhar_tiro = true;
                pode_atirar = false;
            }

            //atualizar as coordenadas das bolas
            for (int i = 0; i < bolas.getTamanho(); ++i) {
                b = bolas.getData(i);
                b.pos += 1;

                if (b.pos >= tamanho) {
                    bolas.remover(i);
                }
                else {
                    bolas.setData(i, b);
                }
            }

            //verifica se esta na hora de colocar uma nova bola na lista
            if (pos_bola % 10 == 0 && pos_bola < 150) {
                b.pos = 0;
                b.cor = rand() % 4;
                bolas.inserir_frente(b);
                cout << pos_bola << endl;
            }
            
            pos_bola++;
            

            //verifica se o tiro colidiu com alguma bola
            //so verifica se tiver atirado!
            if (pode_atirar == false) {
                int posicao_inserida;
                int contador = 0;
                int i;
                for (i = 0; i < bolas.getTamanho(); ++i) {
                    b = bolas.getData(i);
                    
                    if (colidiu(b, tiro_x, tiro_y, x_pos, y_pos) == true) {
                        //o tiro passa a ocupar a posicao da bola
                        bola_tiro.pos = b.pos;
                        cout << "colidiu!\n";
    
                        bolas.insere(i, bola_tiro);
                        posicao_inserida = i;
                        tiro_x = -1;
                        tiro_y = -1;
                        desenhar_tiro = false;
                        pode_atirar = true;
                
                        //empurra o resto das bolas para frente
                        for (i = i + 1; i < bolas.getTamanho(); ++i) {
                            b = bolas.getData(i);
                            b.pos += 10;
                            bolas.setData(i, b);
                        }
                        break;
                    }
                }

                //agora verifica se pode destruir uma sequencia de bolas
                //procurando para frente
                i = posicao_inserida;
                int inicio;
                int fim;
                while (true) {
                    if (i >= bolas.getTamanho()) break;
                    b = bolas.getData(i);
                    if (bola_tiro.cor == b.cor) {
                        contador++;
                        fim = i;
                        ++i;
                    }
                    else {
                        break;
                    }
                }

                //procurando para tras
                i = posicao_inserida - 1;
                while (true) {
                    if (i < 0) break;
                    b = bolas.getData(i);
                    if (bola_tiro.cor == b.cor) {
                        contador++;
                        inicio = i;
                        --i;
                    }
                    else {
                        break;
                    }
                }

                //agora ve se da pra deletar bolas
                if (contador > 2) {
                    for (i = inicio; i != fim; ++i) {
                        bolas.remover(i);
                    }

                    //atualizar as posicoes
                    for (i = fim + 1; i < bolas.getTamanho(); ++i) {
                        b = bolas.getData(i);
                        b.pos = b.pos - contador * 10;
                        bolas.setData(i, b);
                    }
                }

            }

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (pode_atirar == true) {
                pode_atirar = false;
                tiro_x = ev.mouse.x;
                tiro_y = ev.mouse.y;
                coeficiente_angular = ((float)(tiro_y - posicao_y_jogador)) / (tiro_x - posicao_x_jogador);

                //determina se deve incrementar tiro_x ou tiro_y
                //primeiro quadrante
                if (tiro_y - posicao_y_jogador >= 0 && tiro_x - posicao_x_jogador >= 0) { 
                    incrementar = coeficiente_angular > 1.0 ? 0 : 1;
                }
                //segundo quadrante
                else if (tiro_y - posicao_y_jogador >= 0 && tiro_x - posicao_x_jogador < 0) {
                    incrementar = coeficiente_angular < -1.0 ? 2 : 3;
                }
                //terceiro quadrante
                else if (tiro_y - posicao_y_jogador < 0 && tiro_x - posicao_x_jogador < 0) {
                    incrementar = coeficiente_angular > 1.0 ? 4 : 5;
                }
                //quarto quadrante
                else {
                    incrementar = coeficiente_angular < -1.0 ? 6 : 7;
                }

                bola_tiro = bola_tiro_nova;
                bola_tiro_nova.cor = novacor % 4;
                tiro_x = posicao_x_jogador;
                tiro_y = posicao_y_jogador;
            }
        }

        if (redesenhar && al_is_event_queue_empty(evento)) {
            //desenhar as bolas
            redesenhar = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));

            //desenha a posicao do jogador
            al_draw_filled_circle(posicao_x_jogador, posicao_y_jogador, 10.0, al_map_rgb(77, 77, 77));

            //desenha o caminho
            for (int i = 0; i < tamanho; ++i) {
                al_draw_filled_circle(x_pos[i], y_pos[i], 1.0, al_map_rgb(0, 0, 0));
            }

            //desenha o buraco
            al_draw_circle(x_pos[tamanho - 1], y_pos[tamanho - 1], 7.0 ,al_map_rgb(0, 0, 0), 1.0);

            //desenha o tiro
            if (desenhar_tiro == true) {
                al_draw_filled_circle(tiro_x, tiro_y, 5.0, corDaBola(bola_tiro.cor));
            }
            
            //desenha nova bola a ser atirada
            al_draw_filled_circle(posicao_x_jogador, posicao_y_jogador, 5.0, corDaBola(bola_tiro_nova.cor));
            

            //desenha as bolas
            for (int i = 0; i < bolas.getTamanho(); ++i) {
                b = bolas.getData(i);
                al_draw_filled_circle(x_pos[b.pos], y_pos[b.pos], 5.0, corDaBola(b.cor));
            }

            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(evento);

    return 0;
}
    		
    	



