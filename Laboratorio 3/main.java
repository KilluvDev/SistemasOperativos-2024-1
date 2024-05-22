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

        // mov.MovFork(mapa, pos);
        // mov.MovThread(mapa, pos);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(mapa[i][j]);
            }
            System.out.println();
        }
    }
}
