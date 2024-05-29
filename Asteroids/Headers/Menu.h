void presenta_menu_1(int posX, int posY);
int scroll_menu_1(int posX, int posY, int cantOpc);
int mainJuego();

void muestra_instrucciones() {
    FILE *archivo;
    char caracter;

    archivo = fopen("Instrucciones.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while ((caracter = fgetc(archivo)) != EOF) {
        printf("%c", caracter);
    }

    fclose(archivo);
}

int mainMenuAst() {
    int op = 0;
    int x = 20, y = 10;
    do {
        presenta_menu_1(x, y);
        op = scroll_menu_1(x, y, 4);
        system("cls");
        switch (op) {
            case 1:
                printf("Bienvenido");
                mainJuego();
                break;
            case 2:
                printf("AYUDA\n\n");
                muestra_instrucciones();
                break;
            case 3:
                printf("CREDITOS\n");
                break;
            case 4:
                printf("SALIR\n\n\n");
                printf("Gracias por jugar hasta luego");
                break;
        }
        getch();
    } while (op != 4);
    return 0;
}

void presenta_menu_1(int posX, int posY) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoxy(posX + 30, posY += 5);
    printf("Jugar");
    gotoxy(posX + 30, ++posY);
    printf("Ayuda");
    gotoxy(posX + 30, ++posY);
    printf("Puntajes");
    gotoxy(posX + 30, ++posY);
    printf("Salir");
}

int scroll_menu_1(int posX, int posY, int cantOpc) {
    char tecla = '\0';
    int op = 1, y = posY + 5;
    posX = posX + 27;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(posX, posY + 5);
    printf(">");
    do {
        tecla = getch(); //pide una tecla y la guarda
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        gotoxy(posX, y);
        printf(">");
        if (tecla == 80 && op < (cantOpc)) {
            y++;
            op++;
        }
        if (tecla == 72 && op > 1) {
            y--;
            op--;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        gotoxy(posX, y);
        printf(">");
    } while (tecla != 27 && tecla != 13); //ESC 27 ENTER 13
    return (op);
}
