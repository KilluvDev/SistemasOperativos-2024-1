import java.io.BufferedReader;
import java.io.FileReader;

public class archivo {
    public String[][] Map(String direccion) {
        String[][] mapa;
        String[] linea, sizen;
        int n;
        String texto = "", size = "", pos = "";
        try {
            BufferedReader bf = new BufferedReader(new FileReader(direccion));

            String bfRead, temp = "", tamanio, posicion;
            tamanio = bf.readLine();
            posicion = bf.readLine();
            while ((bfRead = bf.readLine()) != null) {
                temp = temp + bfRead + "\n"; // Agarra solo el mapa
            }
            texto = temp;
            size = tamanio;
            pos = posicion;
        } catch (Exception e) {
            System.out.println("Archivo no encontrado");
        }
        linea = texto.split("\n");
        sizen = size.split("x");
        n = Integer.parseInt(sizen[0]);
        mapa = new String[n][n];
        for (int i = 0; i < n; i++) {
            mapa[i] = linea[i].split(" ");
        }
        return mapa;
    }

    public int size(String direccion) {
        int n = 0;
        try {
            BufferedReader bf = new BufferedReader(new FileReader(direccion));
            String temp = "";
            String[] aux;
            temp = bf.readLine();
            aux = temp.split("x");
            n = Integer.parseInt(aux[0]);
        } catch (Exception e) {
            System.out.println("Archivo no encontrado");
        }
        return n;
    }

    public int[] posicion(String direccion) {
        int[] pos = new int[2];
        String aux = "";
        String[] posicionaux;
        try {
            BufferedReader bf = new BufferedReader(new FileReader(direccion));
            String temp = "";
            temp = bf.readLine();
            temp = bf.readLine();
            aux = temp;
        } catch (Exception e) {
            System.out.println("Archivo no encontrado");
        }
        posicionaux = aux.split(",");
        aux = posicionaux[0];
        aux = aux.replace("[", "");
        pos[0] = Integer.parseInt(aux);
        aux = posicionaux[1];
        aux = aux.replace("]", "");
        pos[1] = Integer.parseInt(aux);
        return pos;
    }
}
