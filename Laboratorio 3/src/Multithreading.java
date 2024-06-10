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

        // this.position.show("Position");

        if (this.laberynth.isEnd(this.position)) {
            this.position.show("End");
            Multithreading.found = true;
            return;
        }
        ArrayList<Vector> paths = this.laberynth.getPaths(position);
        paths.removeIf(p -> p.equals(position.sub(this.direction)));

        if (paths.size() == 0) {
            // Dead end
            this.position.show("Dead end");
            return;
        } else if (paths.size() == 1) {
            // Only one path
            Vector path = paths.get(0);
            this.direction = new Direction(this.position, path);
            this.position = this.position.add(this.direction);
            this.iterate();
        } else {
            // Multiple paths
            ArrayList<Multithreading> threads = new ArrayList<Multithreading>();
            for (Vector path : paths) {
                Direction direction = new Direction(this.position, path);
                threads.add(new Multithreading(this.laberynth, path, direction));
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
        }
    }
}
