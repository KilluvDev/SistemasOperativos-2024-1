public class MainClass {

    public static void main(String[] args) {
        Laberynth map = new Laberynth("ArchivosDePrueba/15x15/ejemplo.txt");

        map.show();


        MazeSolver mazeSolver = new MazeSolver(map);

        // long time = mazeSolver.solveWithThreads();
        long time = mazeSolver.solveWithForks();

        System.out.println("Time: " + time);
    }
}
