void Ocultar_cursor();

void Ocultar_cursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1; // Debe ser 1 para el tamaño del cursor
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void pintar_limites() {
    for (int i = 2; i < 130; i++) {
        gotoxy(i, 3); printf("%c", 205);
        gotoxy(i, 35); printf("%c", 205);
    }

    for (int i = 4; i < 35; i++) {
        gotoxy(2, i); printf("%c", 186);
        gotoxy(130, i); printf("%c", 186);
    }

    gotoxy(2, 3); printf("%c", 201);
    gotoxy(2, 35); printf("%c", 200);
    gotoxy(130, 3); printf("%c", 187);
    gotoxy(130, 35); printf("%c", 188);
}

class NAVE {
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones, int _vidas);
    int X() { return x; }
    int Y() { return y; }
    int VIDAS() { return vidas; }
    void COR() { corazones--; }
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void morir();
};

NAVE::NAVE(int _x, int _y, int _corazones, int _vidas)
    : x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}

void NAVE::pintar() {
    gotoxy(x, y); printf(" %c%c%c", 201, 205, 187);
    gotoxy(x, y + 1); printf("%c%c %c%c", 201, 188, 200, 187);
    gotoxy(x, y + 2); printf("%c%c%c%c%c", 200, 205, 205, 205, 188);
    gotoxy(x, y + 3); printf("     ");
}

void NAVE::borrar() {
    gotoxy(x, y); printf("        ");
    gotoxy(x, y + 1); printf("        ");
    gotoxy(x, y + 2); printf("        ");
}

void NAVE::mover() {
    if (_kbhit()) {
        char tecla = _getch();
        borrar();
        if (tecla == 'a' && x > 3) x--;
        if (tecla == 'd' && x + 5 < 130) x++;
        if (tecla == 'w' && y > 4) y--;
        if (tecla == 's' && y + 3 < 35) y++;
        if (tecla == 'e') corazones--;
        pintar();
        pintar_corazones();
    }
}

void NAVE::pintar_corazones() {
    gotoxy(70, 2); printf("Vidas %d", vidas);
    gotoxy(90, 2); printf("HP");
    gotoxy(95, 2); printf("       ");

    for (int i = 0; i < corazones; i++) {
        gotoxy(95 + i, 2); printf("%c", 254);
    }
}

void NAVE::morir() {
    if (corazones == 0) {
        borrar();
        gotoxy(x, y); printf("     ");
        gotoxy(x, y + 1); printf(" *** ");
        gotoxy(x, y + 2); printf(" *** ");
        Sleep(300);

        borrar();
        gotoxy(x, y); printf(" *** ");
        gotoxy(x, y + 1); printf("*   *");
        gotoxy(x, y + 2); printf("*   *");
        gotoxy(x, y + 3); printf(" *** ");
        Sleep(300);
        borrar();
        vidas--;
        corazones = 3;
        pintar_corazones();
        pintar();
    }
}

void fullscreen() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

class asteroid {
    int x, y;
public:
    asteroid(int _x, int _y) : x(_x), y(_y) {}
    void pintarast();
    void moverast();
    void choque(NAVE& N);
    int X() { return x; }
    int Y() { return y; }
};

void asteroid::pintarast() {
    gotoxy(x, y); printf("%c", 178);
}

void asteroid::moverast() {
    gotoxy(x, y); printf("  ");
    y++;
    if (y > 34) {
        x = rand() % 126 + 4;
        y = 4;
    }
    pintarast();
}

void asteroid::choque(NAVE& N) {
    if (x >= N.X() && x < N.X() + 6 && y >= N.Y() && y <= N.Y() + 2) {
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand() % 126 + 4;
        y = 4;
    }
}

class bala {
    int x;
    int y;
public:
    bala(int _x, int _y) : x(_x), y(_y) {}
    int X() { return x; }
    int Y() { return y; }
    void mover();
    bool fuera();
};

void bala::mover() {
    gotoxy(x, y); printf(" ");
    y--;
    gotoxy(x, y); printf("*");
}

bool bala::fuera() {
    return y == 4;
}

void juego();

int mainJuego() {
    fullscreen();
    Ocultar_cursor();
    pintar_limites();

    NAVE n(37, 30, 3, 3);
    n.pintar();
    n.pintar_corazones();

    std::list<asteroid*> O;
    std::list<asteroid*>::iterator itO;

    for (int i = 0; i < 7; i++) {
        O.push_back(new asteroid(rand() % 75 + 3, rand() % 5 + 4));
    }

    std::list<bala*> B;
    std::list<bala*>::iterator it;

    bool game_over = false;
    
    int puntos = 0;
    while (!game_over) {
        gotoxy(4, 2); printf("Puntos %d", puntos);
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 's') {
                B.push_back(new bala(n.X() + 2, n.Y() - 1));
            }
        }

        for (it = B.begin(); it != B.end(); ++it) {
            (*it)->mover();
            if ((*it)->fuera()) {
                gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                delete (*it);
                it = B.erase(it);
                if (it == B.end()) break;
            }
        }

        for (itO = O.begin(); itO != O.end(); ++itO) {
            (*itO)->moverast();
            (*itO)->choque(n);
        }
        
        for (itO = O.begin(); itO != O.end(); ++itO) {
            for (it = B.begin(); it != B.end(); ++it) {
                if ((*itO)->X() == (*it)->X() && ((*itO)->Y() + 1 == (*it)->Y() || (*itO)->Y() == (*it)->Y())) {
                    gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = B.erase(it);
                    if (it == B.end()) break;

                    O.push_back(new asteroid(rand() % 75 + 3, 4));
                    gotoxy((*itO)->X(), (*itO)->Y()); printf(" ");
                    delete(*itO);
                    itO = O.erase(itO);
                    if (itO == O.end()) break;

                    puntos += 1;
                }
            }
        }
        
        if (n.VIDAS() == 0) {
            char respuesta;
            game_over = true;
            system("cls");
            gotoxy(63, 17); printf("Volver a jugar? s/n\n");
            gotoxy(63, 18); scanf(" %c", &respuesta);
            if (respuesta == 's' || respuesta == 'S') {
                juego();
            } else if (respuesta == 'n' || respuesta == 'N') {
                break;
            }
        }

        n.morir();
        n.mover();
        Sleep(30);
    }

    return 0;
}

void juego() {
    mainJuego();
}

#endif // JUEGO_H
