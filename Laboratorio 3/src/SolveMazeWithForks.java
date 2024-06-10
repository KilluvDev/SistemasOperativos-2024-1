import java.util.ArrayList;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

import Vectors.Direction;
import Vectors.Vector;

public class SolveMazeWithForks extends RecursiveTask<Integer> {
    Laberynth laberynth;
    Vector position;
    Direction direction;

    static Boolean found = false;
    static ArrayList<ArrayList<Boolean>> visited = new ArrayList<ArrayList<Boolean>>();

    public static void setVisited(int x, int y) {
        while (visited.size() <= y) {
            visited.add(new ArrayList<Boolean>());
        }

        while (visited.get(y).size() <= x) {
            visited.get(y).add(false);
        }

        visited.get(y).set(x, true);
    }

    public static Boolean isVisited(int x, int y) {
        if (y < 0 || y >= visited.size() || x < 0 || x >= visited.get(y).size()) {
            return false;
        }

        return visited.get(y).get(x);
    }

    public SolveMazeWithForks(Laberynth laberynth, Vector position, Direction direction) {
        this.laberynth = laberynth;
        this.position = position;
        this.direction = direction;
    }

    @Override
    protected Integer compute() {
        this.iterate();
        return 0;
    }

    private void iterate() {
        if (SolveMazeWithForks.found) {
            return;
        }

        SolveMazeWithForks.setVisited(this.position.x, this.position.y);

        if (this.laberynth.isEnd(this.position)) {
            this.onEnd();
        }

        ArrayList<Vector> paths = this.laberynth.getPaths(position);
        paths.removeIf(p -> p.equals(position.sub(this.direction)));
        paths.removeIf(p -> SolveMazeWithForks.isVisited(p.x, p.y));

        if (paths.size() == 0) {
            this.onDeadEnd();
        } else if (paths.size() == 1) {
            this.onOneOption(paths.get(0));
        } else {
            this.onMultipleOptions(paths);
        }
    }

    private void onDeadEnd() {
        this.position.show("Dead end");
    }

    private void onEnd() {
        this.position.show("End");
        SolveMazeWithForks.found = true;
    }

    private void onOneOption(Vector path) {
        this.direction = new Direction(this.position, path);
        this.position = this.position.add(this.direction);
        this.iterate();
    }

    private void onMultipleOptions(ArrayList<Vector> paths) {
        if (SolveMazeWithForks.found) {
            return;
        }
        ArrayList<SolveMazeWithForks> forks = new ArrayList<SolveMazeWithForks>();
        ForkJoinPool pool = new ForkJoinPool();


        for (Vector path : paths) {
            Direction direction = new Direction(this.position, path);
            SolveMazeWithForks fork = new SolveMazeWithForks(this.laberynth, path, direction);
            forks.add(fork);
            pool.execute(fork);
        }

        for (SolveMazeWithForks fork : forks) {
            fork.join();
        }
    }
}
