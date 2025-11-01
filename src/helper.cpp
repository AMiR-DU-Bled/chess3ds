
short xytocell(short x, short y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return -1; // out of bounds
    return x * 8 + y;
}

void celltoxy(short& x, short& y, short cell) {
    if (cell < 0 || cell >= 64) {
        x = y = -1; // optional: indicate invalid cell
        return;
    }
    x = cell / 8;
    y = cell % 8;
}

void cellToPos(short& x, short& y, short cell){
    x = (cell % 8) * 40;
    y =  (cell / 8) * 30;

}