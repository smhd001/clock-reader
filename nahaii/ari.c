#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double delta = .025;
double Position[1000000][4];
int Index = 0;
int i;

void drawline(double x1, double y1, double x2, double y2, int n) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_filled_circle(400, 200, 15, al_map_rgb(100, 100, 100));
  al_draw_line(400, 200, (x1 * 100) + 400, (y1 * 100) + 200,
               al_map_rgb(1000, 1000, 1000), 5);
  al_draw_line((x1 * 100) + 400, (y1 * 100) + 200, (x2 * 100) + 400,
               (y2 * 100) + 200, al_map_rgb(1000, 1000, 1000), 5);
  al_draw_filled_circle((x1 * 100) + 400, (y1 * 100) + 200, 10,
                        al_map_rgb(1000, 1000, 1000));
  al_draw_filled_circle((x2 * 100) + 400, (y2 * 100) + 200, 10,
                        al_map_rgb(1000, 1000, 1000));

  Position[Index][1] = x1;
  Position[Index][2] = y1;
  Position[Index][3] = x2;
  Position[Index][4] = y2;

  for (i = 0; i < Index; i++) {
    al_draw_filled_circle((Position[i][1] * 100) + 400,
                          (Position[i][2] * 100) + 200, 1,
                          al_map_rgb(200, 100, 100));
    al_draw_filled_circle((Position[i][3] * 100) + 400,
                          (Position[i][4] * 100) + 200, 1,
                          al_map_rgb(100, 200, 100));
  }
  al_flip_display();
  al_rest(.05);
  Index++;
}

void drawline_f(double x1, double y1, double x2, double y2, int n) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_filled_circle(400, 200, 15, al_map_rgb(100, 100, 100));
  al_draw_line(400, 200, (x1 * 100) + 400, (y1 * 100) + 200,
               al_map_rgb(1000, 1000, 1000), 5);
  al_draw_line((x1 * 100) + 400, (y1 * 100) + 200, (x2 * 100) + 400,
               (y2 * 100) + 200, al_map_rgb(1000, 1000, 1000), 5);
  al_draw_filled_circle((x1 * 100) + 400, (y1 * 100) + 200, 10,
                        al_map_rgb(1000, 1000, 1000));
  al_draw_filled_circle((x2 * 100) + 400, (y2 * 100) + 200, 10,
                        al_map_rgb(1000, 1000, 1000));

  Position[Index][1] = x1;
  Position[Index][2] = y1;
  Position[Index][3] = x2;
  Position[Index][4] = y2;

  for (i = 0; i < Index; i++) {
    al_draw_filled_circle((Position[i][1] * 100) + 400,
                          (Position[i][2] * 100) + 200, 1,
                          al_map_rgb(200, 100, 100));
    al_draw_filled_circle((Position[i][3] * 100) + 400,
                          (Position[i][4] * 100) + 200, 1,
                          al_map_rgb(100, 200, 100));
  }
  al_flip_display();
  al_rest(3);
  Index++;
}

/*void drawdot(double x1_b,double y1_b,double x2_b,double y2_b)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_circle(400,200,15,al_map_rgb(100,100,100));
    al_draw_line(400,200,(x1_b*100)+400,(y1_b*100)+200,al_map_rgb(0,0,0),5);
    al_draw_line((x1_b*100)+400,(y1_b*100)+200,(x2_b*100)+400,(y2_b*100)+200,al_map_rgb(0,0,0),5);
    al_draw_filled_circle((x1_b*100)+400,(y1_b*100)+200,10,al_map_rgb(0,0,0));
    al_draw_filled_circle((x2_b*100)+400,(y2_b*100)+200,10,al_map_rgb(0,0,0));
    al_draw_filled_circle((x1_b*100)+400,(y1_b*100)+200,5,al_map_rgb(1000,1000,1000));
    al_draw_filled_circle((x2_b*100)+400,(y2_b*100)+200,5,al_map_rgb(1000,1000,1000));
    al_flip_display();
    al_rest(.0000000000000001);
}*/

int main() {
  int i;
  double m1, m2, L1, L2, theta1, theta2, x1, x2, y1, y2, x1_f, x2_f, y1_f, y2_f,
      T, v1 = 0, v2 = 0, a1, a2, g = 9.78, x1_b, x2_b, y1_b, y2_b;

  // PLANET
  printf("Choose the planet you want the experiment to take place "
         "in:"
         "\nmercury\t\tvenus\t\tearth\t\tmoon\nmars\t\tjupiter\t\tsaturn\nuranu"
         "s\t\tneptune\t\tcustom\n");
  char arr[40];
  gets(arr);

  int value = strcmp(arr, "mercury");
  if (!value) {
    g = 0.38 * 9.78;
  }

  value = strcmp(arr, "venus");
  if (!value) {
    g = 0.9 * 9.78;
  }

  value = strcmp(arr, "earth");
  if (!value) {
    g = 9.78;
  }
  value = strcmp(arr, "moon");
  if (!value) {
    g = 0.17 * 9.78;
  }

  value = strcmp(arr, "mars");
  if (!value) {
    g = 0.38 * 9.78;
  }

  value = strcmp(arr, "jupiter");
  if (!value) {
    g = 2.53 * 9.78;
  }
  value = strcmp(arr, "saturn");
  if (!value) {
    g = 1.07 * 9.78;
  }
  value = strcmp(arr, "uranus");
  if (!value) {
    g = 0.89 * 9.78;
  }
  value = strcmp(arr, "neptune");
  if (!value) {
    g = 1.14 * 9.78;
  }
  value = strcmp(arr, "custom");
  if (!value) {
    printf("Enter desired value:");
    scanf("%lf", &g);
  }
  printf("mass1 : ");
  scanf("%lf", &m1);

  printf("mass2 : ");
  scanf("%lf", &m2);

  printf("Length of the first pole : ");
  scanf("%lf", &L1);

  printf("Length of the second pole : ");
  scanf("%lf", &L2);

  printf("initial first angle(radiant) : ");
  scanf("%lf", &theta1);

  printf("initial second angle(radiant) : ");
  scanf("%lf", &theta2);

  printf("time : ");
  scanf("%lf", &T);

  int n = (int)(T / delta);

  ALLEGRO_DISPLAY *display = NULL;
  if (!al_init()) {
    fprintf(stderr, "Couldn't initialize allegro!\n");
    return -1;
  }
  if (!al_init_primitives_addon()) {
    fprintf(stderr, "Couldn't initialize primitives addon!\n");
    return -1;
  }
  display = al_create_display(800, 700);
  if (!display) {
    fprintf(stderr, "Couldn't create allegro display!\n");
    return -1;
  }

  for (i = 0; i < n; i++) {
    double n1 = -g * (2 * m1 + m2) * sin(theta1);
    double n2 = -m2 * g * sin(theta1 - 2 * theta2);
    double n3 = -2 * sin(theta1 - theta2) * m2;
    double n4 = v2 * v2 * L2 + v1 * v1 * L1 * cos(theta1 - theta2);
    double n5 = L1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2));
    a1 = (n1 + n2 + n3 * n4) / n5;

    double f1 = 2 * sin(theta1 - theta2);
    double f2 = v1 * v1 * L1 * (m1 + m2);
    double f3 = g * (m1 + m2) * cos(theta1);
    double f4 = v2 * v2 * L2 * m2 * cos(theta1 - theta2);
    a2 = (f1 * (f2 + f3 + f4)) / n5;

    theta1 += v1 * delta;
    theta2 += v2 * delta;
    v1 += a1 * delta;
    v2 += a2 * delta;

    x1_b = x1;
    y1_b = y1;
    x2_b = x2;
    y2_b = y2;

    x1 = L1 * sin(theta1);
    y1 = L1 * cos(theta1);
    x2 = L2 * sin(theta2) + x1;
    y2 = L2 * cos(theta2) + y1;
    drawline(x1, y1, x2, y2, n);
  // drawdot(x1_b,x2_b,y1_b,y2_b);
  ALLEGRO_EVENT_DISPLAY_CLOSE:
    break;
  }

  drawline_f(x1, y1, x2, y2, n);
  al_destroy_display(display);
  printf("X1 = %0lf / Y1 = -%lf / X2 = %lf / Y2 = -%lf / Theta1 = %lf / Theta2 "
         "= %lf\n\n",
         x1, y1, x2, y2, theta1, theta2);

  return 0;
}
