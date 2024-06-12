import java.util.ArrayList;
import java.util.concurrent.ForkJoinPool;

import Vectors.Direction;
import Vectors.Vector;

public class MazeSolver {
    Laberynth laberynth;

    public MazeSolver(Laberynth laberynth) {
        this.laberynth = laberynth;
    }

    public long solveWithThreads() {
        long startTime = System.currentTimeMillis();

        Vector position = this.laberynth.init.copy();
        ArrayList<Vector> options = this.laberynth.getPaths(position);
        ArrayList<Multithreading> threads = new ArrayList<Multithreading>();

        for (Vector option : options) {
            Direction direction = new Direction(position, option);
            Multithreading thread = new Multithreading(this.laberynth, option, direction);
            threads.add(thread);
            thread.start();
        }

        for (Multithreading thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Multithreading.visited.clear();
        Multithreading.found = false;

        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    public long solveWithForks() {
        long startTime = System.currentTimeMillis();

        Vector position = this.laberynth.init.copy();
        ArrayList<Vector> options = this.laberynth.getPaths(position);
        ArrayList<SolveMazeWithForks> tasks = new ArrayList<SolveMazeWithForks>();
        ForkJoinPool pool = new ForkJoinPool();

        for (Vector option : options) {
            SolveMazeWithForks task = new SolveMazeWithForks(this.laberynth, option, new Direction(position, option));
            tasks.add(task);
            pool.execute(task);
        }

        for (SolveMazeWithForks task : tasks) {
            task.join();
        }

        SolveMazeWithForks.visited.clear();
        SolveMazeWithForks.found = false;

        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }
}
