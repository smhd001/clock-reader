#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "myheder.h"

unsigned char pic2[2000][2000][3];
int abs(int);
void drawsaat(int a, int b, int c);

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}


int c = 1;

int main()
{
    
    int detcted_saat;
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_native_dialog_addon(), "dialog");

    ALLEGRO_TIMER *timer = al_create_timer(1.0/10);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    int hidth = 720, width = 680;
    ALLEGRO_DISPLAY *disp = al_create_display(width, hidth);
    must_init(disp, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();

    must_init(font, "font");
    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;
    int selected = 1;
    int screen_state = 0;
    int b_learned = 0;
    char path[100];
    /*    
    ALLEGRO_FILECHOOSER *filechooser;
filechooser = al_create_native_file_dialog("./", "Choose a file.", "*.*", 1);
al_show_native_file_dialog(disp, filechooser);

const char* path = al_get_native_file_dialog_path(filechooser, 1);
*/

    /*#define KEY_SEEN 1
#define KEY_RELEASED 2
*/
    unsigned char key[ALLEGRO_KEY_MAX];
    int a = 0, b = 0, d = 0;
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_CHAR:
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                selected--;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                selected++;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                screen_state = selected;
            }

            if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue) && screen_state == 0)
        {
            al_clear_to_color(al_map_rgb(50, 50, 50));
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 20, ALLEGRO_ALIGN_CENTER, "watchdetector");
            al_draw_filled_rectangle(140, 120, 140 + 400, 120 + 120, al_map_rgb(255, (selected == 1) * 100, (selected == 1) * 100));
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 120 + 60, ALLEGRO_ALIGN_CENTER, "learn");
            al_draw_filled_rectangle(140, 280, 140 + 400, 280 + 120, al_map_rgb(255, (selected == 2) * 100, (selected == 2) * 100));
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 280 + 60, ALLEGRO_ALIGN_CENTER, "watch");
            al_draw_filled_rectangle(140, 440, 140 + 400, 440 + 120, al_map_rgb(255, (selected == 3) * 100, (selected == 3) * 100));
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 440 + 60, ALLEGRO_ALIGN_CENTER, "exit");
            if (selected == 4)
            {
                selected = 1;
            }
            if (selected == 0)
            {
                selected = 3;
            }

            al_flip_display();

            redraw = false;
        }
        //bastane safe
        if (screen_state == 3)
        {
            done = true;
        }

        if (al_is_event_queue_empty(queue) && screen_state == 1)
        {
            al_clear_to_color(al_map_rgb(50, 150, 50));
            if(fopen("fixedlearned9.bmp","r"))
            {
              b_learned = 1;  
            }
            if (b_learned)
            {
                al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 100 + 60, ALLEGRO_ALIGN_CENTER, "learned succefuly");
                al_flip_display();
            }
            
            if (selected == 2)
            {
                selected = 0;
            }
            if (selected == -1)
            {
                selected = 1;
            }
            al_draw_filled_rectangle(140, 400, 140 + 400, 400 + 120, al_map_rgb(255, (selected == 1) * 100, (selected == 1) * 100));
            al_draw_filled_rectangle(140, 550, 140 + 400, 550 + 120, al_map_rgb(255, (selected == 0) * 100, (selected == 0) * 100));
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 400 + 60, ALLEGRO_ALIGN_CENTER, "start learn");
            al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 550 + 60, ALLEGRO_ALIGN_CENTER, "main menu");
            al_flip_display();
            if (selected == 1 && event.keyboard.keycode == ALLEGRO_KEY_ENTER && !b_learned)
            {
                printf("strt leaning");
                al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 100 + 60, ALLEGRO_ALIGN_CENTER, "learning pleas wait");
                al_flip_display();
                learning();
                b_learned = 1;
                printf("leaned");
            }
        }
        if ( al_is_event_queue_empty(queue) && screen_state == 2)
        {
            if (selected == 2 && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                printf("selecting file\n");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 140, ALLEGRO_ALIGN_CENTER, "openning");
                /*
                filechooser = al_create_native_file_dialog("", "Choose a file.", "*.*;*.bmp;", 1);
                al_show_native_file_dialog(disp, filechooser);
                const char * path = al_get_native_file_dialog_path(filechooser, 1);
                if (path == 0)
                {
                    printf("faild to open");
                }*/
                printf("enter yuor file name");
                gets(path);
                printf("%s",path);
                crop(path);
                detcted_saat =  detecting();
                //ALLEGRO_BITMAP *image = al_load_bitmap(path);
                //al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 140, ALLEGRO_ALIGN_CENTER, "%s",path);
            }
            al_clear_to_color(al_map_rgb(140, 140, 250));
            al_draw_filled_rectangle(140, 100, 140 + 400, 100 + 120, al_map_rgb(255, (selected == 2) * 100, (selected == 2) * 100));
            al_draw_filled_rectangle(140, 250, 140 + 400, 250 + 120, al_map_rgb(255, (selected == 0) * 100, (selected == 0) * 100));
            // al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 400 + 60, ALLEGRO_ALIGN_CENTER, "start learn");
            //al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 550 + 60, ALLEGRO_ALIGN_CENTER, "main menu");
            if (selected == 3)
            {
                selected = 0;
            }
            if (selected == 1)
            {
                selected = 2;
            }
            if (selected == -1)
            {
                selected = 2;
            }
            drawsaat(a, b, c);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 140, ALLEGRO_ALIGN_CENTER, "%d", selected);
            al_flip_display();
            a++;
            if (a == 60)
            {
                a = 0;
                b++;
            }
            if (b == 60)
            {
                b = 0;
                c++;
            }
            if (c == 24)
            {
                c = 0;
            }
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
void drawsaat(int a, int b, int c)
{
    double teta_sanie, teta_dagige, teta_saat;

    teta_sanie = 2 * ALLEGRO_PI / 60 * a;
    teta_dagige = 2 * ALLEGRO_PI / 60 * b;
    teta_saat = 2 * ALLEGRO_PI / 60 * c * 5;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    //al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 140, ALLEGRO_ALIGN_CENTER, "%d:%d:%d", c, b, a);
    //al_draw_text(font, al_map_rgb(250, 252, 252), 300, 120, ALLEGRO_ALIGN_CENTER, "12");
    //    al_draw_text(font, al_map_rgb(250, 250, 250), 300, 480, ALLEGRO_ALIGN_CENTER, "6");
    //  al_draw_text(font, al_map_rgb(250, 250, 250), 480, 300, ALLEGRO_ALIGN_CENTER, "3");
    //    al_draw_text(font, al_map_rgb(250, 250, 250), 120, 300, ALLEGRO_ALIGN_CENTER, "9");
    al_draw_line(680/2, 680/2, 680/2 - 190 * cos(teta_sanie + ALLEGRO_PI / 2), 680/2 - 190 * sin(teta_sanie + ALLEGRO_PI / 2), al_map_rgb(0, 255, 0), 3);
    al_draw_line(680/2, 680/2, 680/2 - 170 * cos(teta_dagige + ALLEGRO_PI / 2), 680/2 - 170 * sin(teta_dagige + ALLEGRO_PI / 2), al_map_rgb(0, 255, 255), 5);
    al_draw_line(680/2, 680/2, 680/2 - 150 * cos(teta_saat + ALLEGRO_PI / 2), 680/2 - 150 * sin(teta_saat + ALLEGRO_PI / 2), al_map_rgb(255, 0, 25), 10);
    al_draw_circle(680/2, 680/2, 200, al_map_rgb(255, 20, 20), 5);
    al_draw_filled_circle(680/2, 680/2, 5, al_map_rgb(250, 220, 250));

    //  al_play_sample(sample,1.0,0,1.1,ALLEGRO_PLAYMODE_ONCE,NULL);
    //   al_draw_ellipse(a, a, 150, 50, al_map_rgb(0, 255, 0), 10);

    al_flip_display();
}

/*



teta = 2 * ALLEGRO_PI / 60 * a;
            teta_dagige = 2 * ALLEGRO_PI / 60 * b;
            teta_saat = 2 * ALLEGRO_PI / 60 * c * 5;

            r = A * B / (sqrt(A * A * sin(teta + ALLEGRO_PI / 2) * sin(teta + ALLEGRO_PI / 2) + B * B * cos(teta + ALLEGRO_PI / 2) * cos(teta + ALLEGRO_PI / 2)))-10;
            r_dagige = A * B / (sqrt(A * A * sin(teta_dagige + ALLEGRO_PI / 2) * sin(teta_dagige + ALLEGRO_PI / 2) + B * B * cos(teta_dagige + ALLEGRO_PI / 2) * cos(teta_dagige + ALLEGRO_PI / 2)))-30;
            r_saat= A * B / (sqrt(A * A * sin(teta_saat + ALLEGRO_PI / 2) * sin(teta_saat + ALLEGRO_PI / 2) + B * B * cos(teta_saat + ALLEGRO_PI / 2) * cos(teta_saat + ALLEGRO_PI / 2)))-50;
            al_clear_to_color(al_map_rgb(0, 0, 0));
        //  al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 140, ALLEGRO_ALIGN_CENTER, "teta is %lf and r is %lf and sanie is:%lf", teta, r, a);
            al_draw_text(font, al_map_rgb(250, 252, 252), 680/2, 80, ALLEGRO_ALIGN_CENTER, "12");
            al_draw_text(font, al_map_rgb(250, 250, 250), 680/2, 600, ALLEGRO_ALIGN_CENTER, "6");
            al_draw_text(font, al_map_rgb(250, 250, 250), 470, 680/2, ALLEGRO_ALIGN_CENTER, "3");
            al_draw_text(font, al_map_rgb(250, 250, 250), 210, 680/2, ALLEGRO_ALIGN_CENTER, "9");
            al_draw_line(680/2, 680/2, 680/2 - r * cos(teta + ALLEGRO_PI / 2), 680/2 - r * sin(teta + ALLEGRO_PI / 2), al_map_rgb(0, 255, 0), 3);
            al_draw_line(680/2, 680/2, 680/2 - r_dagige * cos(teta_dagige + ALLEGRO_PI / 2), 680/2 - r_dagige * sin(teta_dagige + ALLEGRO_PI / 2), al_map_rgb(0, 255, 255), 5);
            al_draw_line(680/2, 680/2, 680/2 - r_saat * cos(teta_saat + ALLEGRO_PI / 2), 680/2 - r_saat * sin(teta_saat + ALLEGRO_PI / 2), al_map_rgb(255, 0, 25), 10);
            //    al_draw_circle(300, 300, 200, al_map_rgb(255, 20, 20), 5);
            al_draw_ellipse(680/2, 680/2, A, B, al_map_rgb(255, 20, 20), 5);
            al_draw_filled_circle(680/2, 680/2, 5, al_map_rgb(250, 220, 250));
            al_draw_rectangle(0, 0, 10, 10, al_map_rgb(0, 22, 255), 5);
            al_play_sample(sample, 1.0, 0, 1.1, ALLEGRO_PLAYMODE_ONCE, NULL);
            //   al_draw_ellipse(a, a, 150, 50, al_map_rgb(0, 255, 0), 10);
            a++;
            al_flip_display();


r
teta = sanie * 60;
2 * ALLEGRO_PI/60 * sanie = teta 

for a ellips 

r = A*B/(sqrt(A*A*sin(teta + ALLEGRO_PI/2)*sin(teta+ALLEGRO_PI/2)+B*B*cos(teta+ALLEGRO_PI /2)*cos(teta*ALLEGRO_PI/2)))

*/