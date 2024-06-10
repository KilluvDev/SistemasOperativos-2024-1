import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

import Vectors.Direction;
import Vectors.Vector;

public class Laberynth {
    String[][] map;
    Vector init;
    Vector end;
    Vector size;

    public Laberynth(String filepath) {
        ArrayList<String> lineas = new ArrayList<String>();
        try {
            BufferedReader bf = new BufferedReader(new FileReader(filepath));

            String bfRead;

            while ((bfRead = bf.readLine()) != null) {
                lineas.add(bfRead);
            }

            bf.close();
        } catch (Exception e) {
            System.out.println("Archivo no encontrado");
            return;
        }

        String[] size = lineas.get(0).split("x");
        this.size = new Vector(Integer.parseInt(size[0]), Integer.parseInt(size[1]));

        String[] init = lineas.get(1).replace("[", "").replace("]", "").split(",");
        this.init = new Vector(Integer.parseInt(init[0]), Integer.parseInt(init[1]));

        this.map = new String[this.size.y][this.size.x];
        for (int i = 2; i < lineas.size(); i++) {
            String[] row = lineas.get(i).split(" ");

            for (int j = 0; j < row.length; j++) {
                this.map[i - 2][j] = row[j];
                if (row[j].equals("S")) {
                    this.end = new Vector(j, i - 2);
                }
            }

        }
    }

    public Boolean isWall(Vector v) {
        if (v.x < 0 || v.x >= this.size.x || v.y < 0 || v.y >= this.size.y) {
            return true;
        }
        return this.map[v.y][v.x].equals("0");
    }

    public Boolean isEnd(Vector v) {
        return v.equals(this.end);
    }

    public ArrayList<Vector> getPaths(Vector v) {
        ArrayList<Vector> paths = new ArrayList<Vector>();

        for (Vector dir : Direction.getDirections()) {
            Vector next = v.add(dir);
            if (!this.isWall(next)) {
                paths.add(next);
            }
        }

        return paths;
    }

    public void show() {
        for (int j = -1; j <= this.size.y; j++) {
            for (int i = -1; i <= this.size.x; i++) {
                if (this.isWall(new Vector(i, j))) {
                    System.out.print("0 ");
                } else {
                    if (this.isEnd(new Vector(i, j))) {
                        System.out.print("S ");
                    } else if (this.init.equals(new Vector(i, j))) {
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
