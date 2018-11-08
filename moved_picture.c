/*
** EPITECH PROJECT, 2018
** open_window
** File description:
** open a window of 800x600
*/

#include <SFML/Graphics.h>
#include <stdlib.h>

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

void draw_square(framebuffer_t *framebuffer, sfVector2f position, unsigned int width, unsigned int height, sfColor color)
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
    sfTexture *t_bat = sfTexture_create(1915, 967);
    sfSprite *bat = sfSprite_create();
    sfVector2f move = {event.mouseMove.x, 921};
    sfVector2f origin_ball = {15, 15};
    sfVector2f origin_bat = {120, 0};
    sfVector2f scale = {0.06, 0.06};
    sfVector2f position = {event.mouseMove.x, 469};
    int sens_x = 0;
    int sens_y = 1;
    int begin = 0;
    float x = 0.6;
    float y = 0.5;

    sfCircleShape_setRadius(circle, 15);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setFillColor(circle, sfYellow);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOrigin(circle, origin_ball);
    sfSprite_setOrigin(bat, origin_bat);
    draw_square(fb, position, 30, 150, sfBlack);
    sfTexture_updateFromPixels(t_bat, fb->pixel, 1915, 967, 0, 0);
    sfSprite_setTexture(bat, t_bat, sfFalse);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfWhite);
        sfCircleShape_setPosition(circle, move);
        sfSprite_setPosition(bat, position);
        sfRenderWindow_drawSprite(window, bat, NULL);
        sfRenderWindow_drawCircleShape(window, circle, NULL);
        sfRenderWindow_display(window);
        if (begin == 1) {
            (sens_x == 0) ? (move.x += x) : (move.x -= x);
            (sens_y == 0) ? (move.y += y) : (move.y -= y);
            (move.y > 967 - 14 - 30 && position.x > move.x - 75 && position.x < move.x + 75) ? (sens_y = 1) : sens_y;
            (move.y > 967 - 14) ? (move.x = event.mouseMove.x, move.y = 920, begin = 0, sens_y = 1) : move.x;
            (move.y < 14) ? (sens_y = 0) : sens_y;
            (move.x < 14) ? (sens_x = 0) : sens_x;
            (move.x > 1915 - 14) ? (sens_x = 1) : sens_x;
            x *= 1.00001;
            y *= 1.00001;
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
                    position.x += 15;
                else if (event.key.code == sfKeyLeft)
                    position.x -= 15;
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
    return (0);
}
