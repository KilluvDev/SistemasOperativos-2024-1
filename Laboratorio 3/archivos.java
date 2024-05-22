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
}
