#ifndef RATIONAL_H
#define RATIONAL_H

typedef struct {
    int num;
    unsigned int denom;
} rational_t;

/*
 * Возвращает рациональное число, получаемое как результат деления
 * n на d.
 */
rational_t rational(long n, long d);
#endif
