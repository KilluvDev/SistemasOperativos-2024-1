package Vectors;

public class Direction extends Vector {
    public static enum Directions {
        UP, RIGHT, DOWN, LEFT
    }

    public Direction(Direction.Directions direction) {
        switch (direction) {
            case UP:
                this.y = -1;
                break;
            case RIGHT:
                this.x = 1;
                break;
            case DOWN:
                this.y = 1;
                break;
            case LEFT:
                this.x = -1;
                break;
        }
    }

    public Direction(Vector origin, Vector destination) {
        int deltaX = destination.x - origin.x;
        int deltaY = destination.y - origin.y;

        if (deltaX != 0) {
            deltaX = deltaX / Math.abs(deltaX);
        }

        if (deltaY != 0) {
            deltaY = deltaY / Math.abs(deltaY);
        }

        this.x = deltaX;
        this.y = deltaY;
    }

    public static Direction[] getDirections() {
        return new Direction[] {
            new Direction(Direction.Directions.UP),
            new Direction(Direction.Directions.RIGHT),
            new Direction(Direction.Directions.DOWN),
            new Direction(Direction.Directions.LEFT)
        };
    }
}
