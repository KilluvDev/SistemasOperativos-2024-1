final class main {

    public static void main(String[] args) {
        archivo map = new archivo();
        movimiento mov = new movimiento();
        int n;
        int[] pos;
        n = map.size("ArchivosDePrueba/15x15/laberinto.txt");
        pos = map.posicion("ArchivosDePrueba/15x15/laberinto.txt");
        String[][] mapa;
        mapa = map.Map("ArchivosDePrueba/15x15/laberinto.txt");
        System.out.println(n);
        System.out.println(pos[0] + " " + pos[1]);

        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < n + 1; j++) {
                System.out.print(mapa[i][j]);
            }
            System.out.println();
        }
    }
}
