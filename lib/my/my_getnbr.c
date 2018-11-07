/*
** EPITECH PROJECT, 2018
** my_getnbr.c
** File description:
** str to int
*/

int my_getnbr(char *toconvert)
{
    int number = 0;
    int mult = 1;
    int i = 0;
    int negative = 0;

    if (toconvert[0] == '-') {
        toconvert++;
        negative = 1;
    }
    for (i = 0; toconvert[i] != 0; i++);
    for (i--; i >= 0; i--, mult *= 10)
        number += (toconvert[i] - 48) * mult;
    if (negative == 1)
        number *= (-1);
    return (number);
}
