package datastructures;

import java.util.*;

public class Graph<V, L> implements AbstractGraph<V, L> {
    private final boolean directed;
    private final boolean labelled;
    private final Map<V, Map<V, L>> adjacencyMap;
    private int numEdges;

    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        adjacencyMap = new HashMap<>();
        numEdges = 0;
    }

    @Override
    public boolean isDirected() {
        return directed;
    }

    @Override
    public boolean isLabelled() {
        return labelled;
    }

    @Override
    public boolean addNode(V node) {
        if (adjacencyMap.containsKey(node)) {
            return false;
        }
        adjacencyMap.put(node, new HashMap<>());
        return true;
    }

    @Override
    public boolean addEdge(V a, V b, L label) {
        if (!containsNode(a) || !containsNode(b)) {
            return false;
        }
        if (label == null && isLabelled()) {
            return false;
        }
        adjacencyMap.get(a).put(b, label);
        if (!isDirected()) {
            adjacencyMap.get(b).put(a, label);
            numEdges += 2;
        } else {
            numEdges++;
        }
        return true;
    }

    @Override
    public boolean containsNode(V node) {
        return adjacencyMap.containsKey(node);
    }

    @Override
    public boolean containsEdge(V a, V b) {
        return adjacencyMap.get(a) != null && adjacencyMap.get(a).containsKey(b);
    }

    @Override
    public boolean removeNode(V node) {
        if (!containsNode(node)) {
            return false;
        }
        int edgesRemoved = adjacencyMap.get(node).size();
        adjacencyMap.remove(node);
        for (Map.Entry<V, Map<V, L>> entry : adjacencyMap.entrySet()) {
            entry.getValue().remove(node);
        }
        numEdges -= edgesRemoved;
        if (!isDirected()) {
            numEdges -= edgesRemoved;
        }
        return true;
    }

    @Override
    public boolean removeEdge(V a, V b) {
        if (!containsEdge(a, b)) {
            return false;
        }
        adjacencyMap.get(a).remove(b);
        if (!isDirected()) {
            adjacencyMap.get(b).remove(a);
            numEdges -= 2;
        } else {
            numEdges--;
        }
        return true;
    }

    @Override
    public int numNodes() {
        return adjacencyMap.size();
    }

    @Override
    public int numEdges() {
        return numEdges;
    }

    @Override
    public AbstractCollection<V> getNodes() {
        return new ArrayList<>(adjacencyMap.keySet());
    }

    @Override
    public AbstractCollection<AbstractEdge<V, L>> getEdges() {
        AbstractCollection<AbstractEdge<V, L>> edges = new ArrayList<>();
        for (V source : adjacencyMap.keySet()) {
            for (Map.Entry<V, L> entry : adjacencyMap.get(source).entrySet()) {
                V target = entry.getKey();
                L label = entry.getValue();
                edges.add(new Edge<>(source, target, label));
            }
        }
        return edges;
    }


    @Override
    public AbstractCollection<V> getNeighbours(V node) {
        if (!containsNode(node)) {
            return null;
        }
        return new ArrayList<>(adjacencyMap.get(node).keySet());
    }

    @Override
    public L getLabel(V a, V b) {
        if (!containsEdge(a, b)) {
            return null;
        }
        return adjacencyMap.get(a).get(b);
    }

    private record Edge<V, L>(V start, V end, L label) implements AbstractEdge<V, L> { }
}
