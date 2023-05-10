package datastructures;

public class NodeKey {
    private final String node;
    private double key;
    private String parent;

    public NodeKey(String node, double key) {
        this.node = node;
        this.key = key;
        this.parent = null;
    }

    public String getNode() {
        return node;
    }

    public double getKey() {
        return key;
    }

    public void setKey(double key) {
        this.key = key;
    }

    public String getParent() {
        return parent;
    }

    public void setParent(String parent) {
        this.parent = parent;
    }
}

