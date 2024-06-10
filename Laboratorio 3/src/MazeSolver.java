import java.util.ArrayList;

import Vectors.Direction;
import Vectors.Vector;

public class MazeSolver {
    Laberynth laberynth;

    public MazeSolver(Laberynth laberynth) {
        this.laberynth = laberynth;
    }

    public long solveWithThreads() {
        long startTime = (int) System.currentTimeMillis();
        Vector direction = this.laberynth.init.copy();
        ArrayList<Vector> options = this.laberynth.getPaths(direction);
        ArrayList<Multithreading> threads = new ArrayList<Multithreading>();

        for (Vector option : options) {
            threads.add(new Multithreading(this.laberynth, option, new Direction(direction, option)));
        }

        for (Multithreading thread : threads) {
            thread.start();
        }

        for (Multithreading thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        long endTime = (int) System.currentTimeMillis();
        return endTime - startTime;
    }

    public int solveWithForks() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
