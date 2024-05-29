void Ocultar_cursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 0;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}
