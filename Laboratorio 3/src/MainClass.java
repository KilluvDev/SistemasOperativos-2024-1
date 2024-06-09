import Vectors.Vector;

public class MainClass {

    public static void main(String[] args) {
        Laberynth map = new Laberynth("ArchivosDePrueba/15x15/laberinto.txt");

        int nx = map.size.x;
        int ny = map.size.y;

        for (int j = -1; j <= ny; j++) {
            for (int i = -1; i <= nx; i++) {
                if (map.isWall(new Vector(i, j))) {
                    System.out.print("0 ");
                } else {
                    if (map.isEnd(new Vector(i, j))) {
                        System.out.print("S ");
                    } else if (map.init.equals(new Vector(i, j))) {
                        System.out.print("E ");
                    } else {
                        System.out.print("  ");
                    }
                }
            }
            System.out.println();
        }
    }
}
