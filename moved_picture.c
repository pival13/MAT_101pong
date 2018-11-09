/*
** EPITECH PROJECT, 2018
** open_window
** File description:
** open a window of 800x600
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

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

void draw_square(framebuffer_t *framebuffer, sfVector2f position, unsigned int width, unsigned int height, sfColor color, sfColor color2)
{
    int x = position.x;
    int y = position.y;

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

int main(int n, char **arg)
{
    sfVideoMode mode = {1915, 967, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Breakout", sfDefaultStyle, NULL);
    sfEvent event;
    framebuffer_t *fb = framebuffer_create(1915, 967);
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape *circle2 = sfCircleShape_create();
    sfTexture *wall = sfTexture_createFromFile("brique.jpg", NULL);
    sfSprite *background = sfSprite_create();
    sfTexture *t_bat = sfTexture_create(1915, 967);
    sfSprite *bat = sfSprite_create();
    sfVector2f move = {event.mouseMove.x, 921};
    sfVector2f origin_ball = {15, 15};
    sfVector2f origin_ball2 = {10, 0};
    sfVector2f origin_bat = {73, 0};
    sfVector2f scale = {2.82, 2.82};
    sfVector2f position = {event.mouseMove.x, 469};
    int sens_x = 0;
    int sens_y = 1;
    int begin = 0;
    float x = 0.6;
    float y = 0.5;
    float mult = 1.0001;
    int compteur = 0;
    sfColor color = {200, 200, 200, 100};

    if (n != 2) {
        my_putstr("Please enter a difficulty (Easy, Hard, Lunatic)\n");
        return (84);
    }
    sfCircleShape_setRadius(circle, 15);
    sfCircleShape_setRadius(circle2, 4);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setFillColor(circle, sfYellow);
    sfCircleShape_setFillColor(circle2, sfWhite);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOrigin(circle, origin_ball);
    sfCircleShape_setOrigin(circle2, origin_ball2);
    sfSprite_setOrigin(bat, origin_bat);
    draw_square(fb, position, 30, 150, sfBlack, sfBlue);
    sfTexture_updateFromPixels(t_bat, fb->pixel, 1915, 967, 0, 0);
    sfSprite_setTexture(bat, t_bat, sfFalse);
    sfSprite_setTexture(background, wall, sfFalse);
    sfSprite_scale(background, scale);
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
    //sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, color);
        sfRenderWindow_drawSprite(window, background, NULL);
        sfCircleShape_setPosition(circle, move);
        sfCircleShape_setPosition(circle2, move);
        sfSprite_setPosition(bat, position);
        sfRenderWindow_drawSprite(window, bat, NULL);
        sfRenderWindow_drawCircleShape(window, circle, NULL);
        sfRenderWindow_drawCircleShape(window, circle2, NULL);
        sfRenderWindow_display(window);
        if (begin == 1) {
            (sens_x == 0) ? (move.x += x) : (move.x -= x);
            (sens_y == 0) ? (move.y += y) : (move.y -= y);
            (move.y > 967 - 14 - 30 && position.x > move.x - 75 && position.x < move.x + 75) ? (sens_y = 1, compteur++) : sens_y;
            (move.y > 967 - 14) ? (sfRenderWindow_close(window)) : move.x;
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
            if (event.type == sfEvtMouseMoved)
                if (event.mouseMove.x > 1835)
                    position.x = 1835;
                else if (event.mouseMove.x < 75)
                    position.x = 75;
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
    sfRenderWindow_destroy(window);
    printf("Vous avez effectué %d rebonds.\n", compteur);
    return (0);
}
