final class main {

    public static void main(String[] args) {
        // Leer un txt
        archivos map = new archivos();
        int[][] mapa;
        mapa = map.Map("ArchivosDePrueba/15x15/laberinto.txt");

        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                System.out.print(mapa[i][j]);
            }
            System.out.println();
        }
    }
}