import java.io.BufferedReader;
import java.io.FileReader;

public class archivos {
    public int[][] Map(String direccion) {
        int[][] mapa;
        try {
            BufferedReader bf = new BufferedReader(new FileReader(direccion));
            String[] size;

            String bfRead, temp = "";
            int n;
            bfRead = bf.readLine();
            size = bfRead.split("x");
            n = Integer.parseInt(size[0]);
            mapa = new int[n][n]; // creación de la matriz para el mapa
            String pos;
            pos = bf.readLine(); // pos inicial
            String[] linea;
            int i = 0;
            while ((bfRead = bf.readLine()) != null) {
                temp = bfRead;
                linea = temp.split(" ");
                for (int j = 0; j < n; j++) {
                    mapa[i][j] = Integer.parseInt(linea[j]);
                }
                i++;
            }
            return mapa;
        } catch (Exception e) {
            System.out.println("Archivo no encontrado");
        }
    }
}