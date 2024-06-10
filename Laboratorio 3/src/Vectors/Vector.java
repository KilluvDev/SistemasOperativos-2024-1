package Vectors;

public class Vector {
    public int x;
    public int y;

    public Vector(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Vector() {
        this.x = 0;
        this.y = 0;
    }

    public Vector add(Vector v) {
        return new Vector(this.x + v.x, this.y + v.y);
    }

    public Vector sub(Vector v) {
        return new Vector(this.x - v.x, this.y - v.y);
    }

    public Vector mul(int n) {
        return new Vector(this.x * n, this.y * n);
    }

    public Boolean equals(Vector v) {
        return this.x == v.x && this.y == v.y;
    }

    public Vector copy() {
        return new Vector(this.x, this.y);
    }

    public void show(String name) {
        System.out.println(name + ": (" + this.x + ", " + this.y + ")");
    }
    public void show() {
        System.out.println("(" + this.x + ", " + this.y + ")");
    }
}
