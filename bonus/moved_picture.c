/*
** EPITECH PROJECT, 2018
** open_window
** File description:
** open a window of 800x600
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

typedef struct framebuffer {
    unsigned int width;
    unsigned int height;
    unsigned char *pixel;
} framebuffer_t;

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *framebuffer;

    framebuffer = malloc(sizeof(framebuffer_t));
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->pixel = malloc(width * height * 4);
    return (framebuffer);
}

void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color)
{
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    int alpha = color.a;

    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4] = red;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 1] = green;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 2] = blue;
    framebuffer->pixel[((framebuffer->width) * (y - 1) + x - 1) * 4 + 3] = alpha;
}

void draw_square(framebuffer_t *framebuffer, int x, int y, unsigned int width, unsigned int height, sfColor color, sfColor color2)
{
    if (width == 1 && height == 1) {
        put_pixel(framebuffer, x, y, color);
        return;
    } else {
        for (int i = 0; i != width; i++)
            put_pixel(framebuffer, x, y + i, color);
        for (int i = 0; i != height; i++) {
            put_pixel(framebuffer, x + 1 + i, y, color);
            for (int j = 1; j != width - 1; j++)
                put_pixel(framebuffer, x + 1 + i, y + j, color2);
            put_pixel(framebuffer, x + 1 + i, y + width - 1, color);
        }
        for (int i = 0; i != width; i++)
            put_pixel(framebuffer, x + height, y + i, color);
        return;
    }
}

sfCircleShape *draw_circle(int radius)
{
    sfVector2f origin_ball = {radius, radius};
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setFillColor(circle, sfYellow);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOrigin(circle, origin_ball);
    return (circle);
}

sfTexture *make_brique(void)
{
    framebuffer_t *fb2 = framebuffer_create(193, 51);
    sfTexture *brique = sfTexture_create(1915, 51);
    
    draw_square(fb2, 1, 1, 50, 192, sfBlack, sfRed);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 0, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 192, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 384, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 576, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 768, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 960, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 1152, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 1342, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 1531, 0);
    sfTexture_updateFromPixels(brique, fb2->pixel, 193, 51, 1720, 0);
    return (brique);
}

int main(int n, char **arg)
{
    sfVideoMode mode = {1915, 967, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Breakout", sfDefaultStyle, NULL);
    sfEvent event;
    framebuffer_t *fb = framebuffer_create(171, 31);
    framebuffer_t *fb2 = framebuffer_create(193, 51);
    sfCircleShape *circle = draw_circle(15);
    sfCircleShape *circle2 = sfCircleShape_create();
    sfTexture *wall = sfTexture_createFromFile("bonus/brique.jpg", NULL);
    sfSprite *background = sfSprite_create();
    sfSprite *brique = sfSprite_create();
    sfTexture *texture = make_brique();
    sfTexture *t_bat = sfTexture_create(171, 31);
    sfSprite *bat = sfSprite_create();
    sfVector2f move = {400, 921};
    sfVector2f origin_ball2 = {10, 0};
    sfVector2f origin_bat = {83, 0};
    sfVector2f scale = {2.82, 2.82};
    sfVector2f position = {950, 937};
    int sens_x = 0;
    int sens_y = 1;
    int begin = 0;
    int brique1 = 0;
    int brique2 = 0;
    int brique3 = 0;
    int brique4 = 0;
    int brique5 = 0;
    int brique6 = 0;
    int brique7 = 0;
    int brique8 = 0;
    int brique9 = 0;
    int brique10 = 0;
    float x = 0.6;
    float y = 0.5;
    float mult = 1.0001;
    int compteur = 0;
    sfColor color = {200, 200, 200, 100};

    if (n != 2) {
        my_putstr("Please enter a difficulty (Easy, Hard, Lunatic)\n");
        return (84);
    }
    sfCircleShape_setRadius(circle2, 4);
    sfCircleShape_setFillColor(circle2, sfWhite);
    sfCircleShape_setOrigin(circle2, origin_ball2);
    sfSprite_setOrigin(bat, origin_bat);
    draw_square(fb, 1, 1, 30, 170, sfBlack, sfBlue);
    sfTexture_updateFromPixels(t_bat, fb->pixel, 171, 31, 0, 0);
    sfSprite_setTexture(bat, t_bat, sfTrue);
    sfSprite_setTexture(background, wall, sfFalse);
    sfSprite_setTexture(brique, texture, sfTrue);
    sfSprite_scale(background, scale);
    draw_square(fb2, 1, 1, 50, 192, sfTransparent, sfTransparent);
    if (my_strcmp(arg[1], "Easy") == 0)
        mult = 1.00001;
    else if (my_strcmp(arg[1], "Hard") == 0)
        mult = 1.0001;
    else if (my_strcmp(arg[1], "Lunatic") == 0) {
        sfCircleShape_setFillColor(circle, color);
        mult += 0.0002;
    }
    else {
        my_putstr("Please enter a difficulty (Easy, Hard, Lunatic)\n");
        return (84);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background, NULL);
        sfCircleShape_setPosition(circle, move);
        sfCircleShape_setPosition(circle2, move);
        sfSprite_setPosition(bat, position);
        sfSprite_setTexture(brique, texture, sfFalse);
        sfRenderWindow_drawSprite(window, bat, NULL);
        sfRenderWindow_drawSprite(window, brique, NULL);
        sfRenderWindow_drawCircleShape(window, circle, NULL);
        sfRenderWindow_drawCircleShape(window, circle2, NULL);
        sfRenderWindow_display(window);
        if (begin == 1) {
            (sens_x == 0) ? (move.x += x) : (move.x -= x);
            (sens_y == 0) ? (move.y += y) : (move.y -= y);
            (move.y > 967 - 14 - 30 && position.x > move.x - 85 && position.x < move.x + 85) ? (sens_y = 1, compteur++) : sens_y;
            (move.y > 967 - 14) ? (sfRenderWindow_close(window)) : move.x;
            (move.y < 14 + 50 && move.x < 192 && brique1 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 0, 0), brique1 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 192 && move.x < 384 && brique2 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 192, 0), brique2 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 384 && move.x < 576 && brique3 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 384, 0), brique3 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 576 && move.x < 768 && brique4 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 576, 0), brique4 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 768 && move.x < 960 && brique5 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 768, 0), brique5 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 960 && move.x < 1152 && brique6 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 960, 0), brique6 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 1152 && move.x < 1342 && brique7 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 1152, 0), brique7 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 1342 && move.x < 1531 && brique8 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 1342, 0), brique8 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 1531 && move.x < 1720 && brique9 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 1531, 0), brique9 = 1, sens_y = 0) : move.y;
            (move.y < 14 + 50 && move.x > 1720 && brique10 == 0) ? (sfTexture_updateFromPixels(texture, fb2->pixel, 193, 51, 1720, 0), brique10 = 1, sens_y = 0) : move.y;
            (move.y < 14) ? (sens_y = 0) : sens_y;
            (move.x < 14) ? (sens_x = 0) : sens_x;
            (move.x > 1915 - 14) ? (sens_x = 1) : sens_x;
            
            x *= mult;
            y *= mult;
        } else {
            move.x = event.mouseMove.x;
            x = 0.6;
            y = 0.5;
        }
        if (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed)
                if (event.key.code == sfKeyRight)
                    position.x += 25;
                else if (event.key.code == sfKeyLeft)
                    position.x -= 25;
                else if (event.key.code == sfKeyEscape)
                    sfSprite_setColor(bat, sfTransparent);
            if (event.type == sfEvtMouseMoved)
                if (event.mouseMove.x > 1825)
                    position.x = 1825;
                else if (event.mouseMove.x < 85)
                    position.x = 85;
                else
                    position.x = event.mouseMove.x;
            if (event.type == sfEvtMouseButtonPressed)
                begin = 1;
        }
    }
    free(fb->pixel);
    free(fb);
    sfCircleShape_destroy(circle);
    sfTexture_destroy(t_bat);
    sfSprite_destroy(bat);
    sfSprite_destroy(brique);
    sfRenderWindow_destroy(window);
    printf("Vous avez effectué %d rebonds.\n", compteur);
    return (0);
}
