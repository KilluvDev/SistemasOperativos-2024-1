import java.util.ArrayList;

import Vectors.Direction;
import Vectors.Vector;

public class Multithreading extends Thread {
    private Laberynth laberynth;
    private Vector position;
    private Direction direction;

    static Boolean found = false;

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

        if (this.laberynth.isEnd(this.position)) {
            this.onEnd();
        }

        ArrayList<Vector> paths = this.laberynth.getPaths(position);
        paths.removeIf(p -> p.equals(position.sub(this.direction)));

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
