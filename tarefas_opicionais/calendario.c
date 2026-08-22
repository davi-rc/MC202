#include <stdio.h>

int arrumar_horarios(int *hora, int *min, int *sec) {
    //ajusta as horas para o sistema usual de 60min, 60 sec

    while (*sec < 0) {
        *sec += 60;
        *min -= 1;
    }
    while (*min < 0) {
        *min += 60;
        *hora -= 1;
    }
    while (*sec >= 60) {
        *sec -= 60;
        *min += 1;
    }
    while (*min >= 60) {
        *min -= 60;
        *hora += 1;
    }

    return 0;
}

int somar_horas(int hora) {
    //descobre quantos dias se passaram
    return (hora - (hora % 24)) / 24;
}

int arrumar_data(int* dia, int* mes, int* ano) {
    while (dia <= 0) {

    }

}

int main(void) {
    int dia, mes, ano, i, hora, min, sec, hora_i, hora_f, min_i, min_f, sec_i, sec_f, temp1, temp2, temp3;

    //roda a primeira linha de entrada
    scanf(" %d/%d/%d", &dia, &mes, &ano);
    scanf(" %d:%d:%d", &hora_i, &min_i, &sec_i);
    scanf("  %d:%d:%d", &hora_f, &min_f, &sec_f);

    hora += (hora_f-hora_i);
    min += (min_f-min_i);
    sec += (sec_f-min_i);

    arrumar_horarios(&hora, &min, &sec);

    //roda as demais linhas de entradas
    while (1) {

        scanf(" %d/%d/%d", &temp1, &temp2, &temp3);
        scanf(" %d:%d:%d", &hora_i, &min_i, &sec_i);
        i = scanf("  %d:%d:%d", &hora_f, &min_f, &sec_f);

        if (i != 3) {
            break;
        }

        hora += (hora_f-hora_i);
        min += (min_f-min_i);
        sec += (sec_f-min_i);

        arrumar_horarios(&hora, &min, &sec);

        printf("%d %d %d\n", hora, min, sec);
    }

    dia += somar_horas(hora);

    arrumar_data(&dia, &mes, &ano);




    return 0;
}