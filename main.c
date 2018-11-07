/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main of the 101pong project
*/

#include "include/my.h"

int pong(float x0, float y0, float z0, float x1, float y1, float z1, int n);

int main(int ac, char **av)
{
    float x0 = my_getfloat(av[1]);
    float x1 = my_getfloat(av[4]);
    float y0 = my_getfloat(av[2]);
    float y1 = my_getfloat(av[5]);
    float z0 = my_getfloat(av[3]);
    float z1 = my_getfloat(av[6]);
    int n = my_getnbr(av[7]);

    printf("%f, %f, %f",x0,y0,x1);
    pong(x0, y0, z0, x1, y1, z1, n);
    return (0);
}
