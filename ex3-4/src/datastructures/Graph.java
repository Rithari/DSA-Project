package datastructures;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;


public class Graph<E, W> {

    public record Arc<E, W>(E source, E target, W weight) {

        @Override
            public boolean equals(Object o) {
                if (this == o) return true;
                if (o == null || getClass() != o.getClass()) return false;
                Arc<?, ?> arc = (Arc<?, ?>) o;
                return source.equals(arc.source) &&
                        target.equals(arc.target) &&
                        weight.equals(arc.weight);
            }

    }

    private final boolean isDirected;
    private final Map<E, Map<E, W>> adjacencyMap;

    public Graph(boolean isDirected) {
        this.isDirected = isDirected;
        this.adjacencyMap = new HashMap<>();
    }

    // Create an empty graph - O(1)
    public static <E, W> Graph<E, W> createEmptyGraph(boolean isDirected) {
        return new Graph<>(isDirected);
    }

    // Add a node - O(1)
    public void addNode(E node) {
        adjacencyMap.putIfAbsent(node, new HashMap<>());
    }

    // Add an arc - O(1)
    public void addArc(E source, E target, W weight) {
        adjacencyMap.get(source).put(target, weight);
        if (!isDirected) {
            adjacencyMap.get(target).put(source, weight);
        }
    }

    // Check if the graph is directed - O(1)
    public boolean isDirected() {
        return isDirected;
    }

    // Verify whether the graph contains a given node - O(1)
    public boolean containsNode(E node) {
        return adjacencyMap.containsKey(node);
    }

    // Verify whether the graph contains a given arc - O(1)
    public boolean containsArc(E source, E target) {
        return adjacencyMap.containsKey(source) && adjacencyMap.get(source).containsKey(target);
    }

    // Delete a node - O(n)
    public void deleteNode(E node) {
        adjacencyMap.remove(node);
        for (Map<E, W> adjacents : adjacencyMap.values()) {
            adjacents.remove(node);
        }
    }

    // Delete an arc - O(1)
    public void deleteArc(E source, E target) {
        if (adjacencyMap.containsKey(source)) {
            adjacencyMap.get(source).remove(target);
            if (!isDirected && adjacencyMap.containsKey(target)) {
                adjacencyMap.get(target).remove(source);
            }
        }
    }

    // Determine the number of nodes - O(1)
    public int numberOfNodes() {
        return adjacencyMap.size();
    }

    // Determine the number of arcs - O(n)
    public int numberOfArcs() {
        return adjacencyMap.values().stream().mapToInt(Map::size).sum() / (isDirected ? 1 : 2);
    }

    // Retrieve the nodes of the graph - O(n)
    public Set<E> getNodes() {
        return adjacencyMap.keySet();
    }

    public int getArcsCount() {
        return adjacencyMap.values().stream().mapToInt(Map::size).sum();
    }

    // Retrieve all arcs of the graph - O(n^2)
    public Set<Arc<E, W>> getArcs() {
        Set<Arc<E, W>> arcs = new HashSet<>();
        for (E source : adjacencyMap.keySet()) {
            for (Map.Entry<E, W> entry : adjacencyMap.get(source).entrySet()) {
                E target = entry.getKey();
                W weight = entry.getValue();
                if (!isDirected) {
                    if (source.hashCode() <= target.hashCode()) {
                        arcs.add(new Arc<>(source, target, weight));
                    }
                } else {
                    arcs.add(new Arc<>(source, target, weight));
                }
            }
        }
        return arcs;
    }

    // Retrieve adjacent nodes of a given node - O(1)
    public Set<E> getAdjacentNodes(E node) {
        return adjacencyMap.get(node).keySet();
    }

    // Retrieve the weight associated with a pair of nodes - O(1)
    public W getWeight(E source, E target) {
        return adjacencyMap.get(source).get(target);
    }

    // Determine the weight of the graph - O(n)
    public double getTotalWeight() {
        if (!isWeighted()) {
            throw new UnsupportedOperationException("Graph is not weighted.");
        }
        return adjacencyMap.values().stream()
                .flatMap(adjacents -> adjacents.values().stream())
                .mapToDouble(weight -> ((Number) weight).doubleValue())
                .sum() / (isDirected ? 1 : 2);
    }

    private boolean isWeighted() {
        // Assuming the graph is weighted if the weight is of type Number
        return adjacencyMap.values().stream()
                .flatMap(adjacents -> adjacents.values().stream())
                .findFirst()
                .filter(Number.class::isInstance)
                .isPresent();
    }
}
