import java.util.ArrayList;

import Vectors.Direction;
import Vectors.Vector;

public class Multithreading extends Thread {
    private Laberynth laberynth;
    private Vector position;
    private Direction direction;

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

    public Multithreading(Laberynth laberynth, Vector position, Direction direction) {
        this.laberynth = laberynth;
        this.position = position;
        this.direction = direction;
    }

    @Override
    public void run() {
        this.iterate();
    }

    private void iterate() {
        if (Multithreading.found) {
            return;
        }

        Multithreading.setVisited(this.position.x, this.position.y);

        if (this.laberynth.isEnd(this.position)) {
            this.onEnd();
        }

        ArrayList<Vector> paths = this.laberynth.getPaths(position);
        paths.removeIf(p -> p.equals(position.sub(this.direction)));
        paths.removeIf(p -> Multithreading.isVisited(p.x, p.y));

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
        Multithreading.found = true;
    }

    private void onOneOption(Vector path) {
        this.direction = new Direction(this.position, path);
        this.position = this.position.add(this.direction);
        this.iterate();
    }

    private void onMultipleOptions(ArrayList<Vector> paths) {
        if (Multithreading.found) {
            return;
        }
        ArrayList<Multithreading> threads = new ArrayList<Multithreading>();

        for (Vector path : paths) {
            Direction direction = new Direction(this.position, path);
            Multithreading thread = new Multithreading(this.laberynth, path, direction);
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
    }
}
