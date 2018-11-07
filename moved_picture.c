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
            put_pixel(framebuffer, x + height - 1, y + i, color);
        return;
    }
}

int main(int n, char **arg)
{
    sfVideoMode mode = {1915, 967, 32};
    sfRenderWindow *window;
    sfEvent event;
    framebuffer_t *fb = framebuffer_create(1915, 967);
    sfTexture *t_ball = sfTexture_createFromFile("ball.jpg", NULL);
    sfTexture *t_bat = sfTexture_create(1915, 967);
    sfSprite *ball = sfSprite_create();
    sfSprite *bat = sfSprite_create();
    sfVector2f move;
    sfVector2f origin_ball = {275, 275};
    sfVector2f origin_bat = {250, 40};
    sfVector2f scale = {0.06, 0.06};
    sfVector2f position = {1, 469};
    int sent_x = 0;
    int sent_y = 0;
    int sens_x = 0;
    int sens_y = 0;

    move.x = 100;
    move.y = 100;
    window = sfRenderWindow_create(mode, "Breakout", sfDefaultStyle, NULL);
    sfSprite_setOrigin(ball, origin_ball);
    sfSprite_setScale(ball, scale);
    draw_square(fb, position, 30, 150, sfBlack);
    sfTexture_updateFromPixels(t_bat, fb->pixel, 1915, 967, 0, 0);
    sfSprite_setPosition(ball, move);
    sfSprite_setTexture(bat, t_bat, sfFalse);
    sfSprite_setTexture(ball, t_ball, sfTrue);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfWhite);
        sfSprite_setPosition(ball, move);
        sfSprite_setPosition(bat, position);
        sfRenderWindow_drawSprite(window, bat, NULL);
        sfRenderWindow_drawSprite(window, ball, NULL);
        sfRenderWindow_display(window);
        (sens_x == 0) ? (move.x += 0.6) : (move.x -= 0.6);
        (sens_y == 0) ? (move.y += 0.5) : (move.y -= 0.5);
        (move.y > 967 - 14 - 30) ? (sens_y = 1) : sens_y;
        (move.y < 14) ? (sens_y = 0) : sens_y;
        (move.x < 14) ? (sens_x = 0) : sens_x;
        (move.x > 1915 - 14) ? (sens_x = 1) : sens_x;
        position.x = move.x - 75;
        while (sfRenderWindow_pollEvent(window, &event))
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
    }
    free(fb->pixel);
    free(fb);
    sfTexture_destroy(t_ball);
    sfSprite_destroy(ball);
    sfTexture_destroy(t_bat);
    sfSprite_destroy(bat);
    sfRenderWindow_destroy(window);
    return (0);
}
