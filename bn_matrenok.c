#include <math.h>
#include <stdlib.h>
#include <math.h>

#define max(x, y) (((x) < (y)) ? (x) : (y))
#define N 1000000

struct bn_s {
    int *body;
    int bodysize;
    int sign;
};

typedef struct bn_s bn;



//Длинное число представляет из себя массив из шестизначных чисел
//То есть максимум каждой "цифры" 999999.

bn *bn_new() { // Создать новое BN
    bn* r = malloc(sizeof (bn));
    if (r == NULL) {
        return NULL;
    }
    r->bodysize = 1;
    r->sign = 0;
    r->body = malloc(sizeof (int) * r->bodysize);
    if (r->body == NULL) {
        free (r);
        return NULL;
    }
    r->body[0] = 0;
    return r;
} 

bn *bn_init(bn const *orig) { // Создать копию существующего BN
    bn * r = bn_new();
    r->sign = orig->sign;
    r->bodysize = orig->bodysize;
    r->body = realloc(r->body, sizeof(int) * r->bodysize);
    int i;
    for (i = 0; i < r->bodysize; i++) {
        r->body[i] = orig->body[i];
    }
    return r;
}

// Инициализировать значение BN десятичным представлением строки
int bn_init_string(bn *t, const char *init_string) {
    int sign_num = 0;
    int number_digits = strlen(init_string) - sign_num;
    t->bodysize = number_digits % 6 == 0 ? number_digits / 6 : number_digits / 6 + 1;
    t->body = realloc(t->body, sizeof(int) * t->bodysize);
    int i;
    for (i = strlen(init_string) - 1; i >= sign_num; i--){
        t->body[(strlen(init_string) - i - 1)/6] += s[i] * pow(10, (strlen(init_string) - i - 1) % 6);
    }
    return 0;
}

// Инициализировать значение BN представлением строки 
// в системе счисления radix
int bn_init_string_radix(bn *t, const char *init_string, int radix) {

}

// Инициализировать значение BN заданным целым числом
int bn_init_int(bn *t, int init_int) {
    if (init_int < 0){
        t->sign = 1;
    } else {
        t->sign = 0;
    }

    int x = abs(init_int);
    while (x > 0) {
        t->body[t->bodysize - 1] = x % N;
        t->bodysize++;
        t->body = realloc(t->body, sizeof(int) * t->bodysize);
        x /= N;
    }

    return 0;
}

// Уничтожить BN (освободить память)
int bn_delete(bn *t) {
    if (t != NULL) {
        if (t->body != NULL) {
            free (t->body);
        }
    free (t);
    }
}

// Операции, аналогичные +=, -=, *=, /=, %=
int bn_add_to(bn *t, bn const *right) {
    
}

int bn_sub_to(bn *t, bn const *right) {

}

int bn_mul_to(bn *t, bn const *right) {

}

int bn_div_to(bn *t, bn const *right) {

}

int bn_mod_to(bn *t, bn const *right) {

}

// Возвести число в степень degree
int bn_pow_to(bn *t, int degree) {
    bn* nbn = bn_init(t);
    int i;
    for (i = 0; i < degree - 1; i++) {
        bn_mul_to(t, nbn);
    }
    bn_delete(nbn);s
}

// Извлечь корень степени reciprocal из BN (бонусная функция)
int bn_root_to(bn *t, int reciprocal) {
    
}

// Аналоги операций x = l+r (l-r, l*r, l/r, l%r)
bn* bn_add(bn const *left, bn const *right) {

    bn* res = bn_new();
    
    res->sign = 0;
    res->bodysize = max (left->bodysize, right->bodysize);
    
    res->body = realloc(res->body, sizeof(int) * (res->bodysize + 1));
    int i;
    int r = 0;
    for (i = 0; i < res->bodysize | r; i++) {
        res->body[i] = left->body[i] + right->body[i] + r;
        if (res->body[i] >= N) {
            res->body[i] -= N;
            r = 1;
        } else {
            r = 0;
        }
    }
    if (res->body[res->bodysize]) {
        res->bodysize++;
    }
    return res;
}

bn* bn_sub(bn const *left, bn const *right) {

}

bn* bn_mul(bn const *left, bn const *right) {

}

bn* bn_div(bn const *left, bn const *right) {

}

bn* bn_mod(bn const *left, bn const *right) {

}

// Выдать представление BN в системе счисления radix в виде строки
//Строку после использования потребуется удалить.
const char *bn_to_string(bn const *t, int radix) {
    
}

// Если левое меньше, вернуть <0; если равны, вернуть 0; иначе >0
int bn_cmp(bn const *left, bn const *right) {

}

int bn_neg(bn *t) { // Изменить знак на противоположный
    if (t->sign) {
        t->sign = 0;
    } else {
        t->sign = 1;
    }
}

int bn_abs(bn *t) { // Взять модуль
    t->sign = 0;
}
int bn_sign(bn const *t) { //-1 если t<0; 0 если t = 0, 1 если t>0
    if ((t->bodysize == 1) && (t->body[0] == 0)) {
        return 0;
    } else {
        return ((t->sign * 2) - 1);
    }
}