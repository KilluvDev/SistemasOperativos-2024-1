public class MainClass {

    public static void main(String[] args) {
        Laberynth map = new Laberynth("ArchivosDePrueba/60x60/laberinto.txt");

        map.show();


        MazeSolver mazeSolver = new MazeSolver(map);

        long Ttime = mazeSolver.solveWithThreads();
        long Ftime = mazeSolver.solveWithForks();

        System.out.println("TTime: " + Ttime);
        System.out.println("FTime: " + Ftime);
    }
}
