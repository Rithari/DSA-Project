package test.datastructures;

import datastructures.AbstractEdge;
import datastructures.Graph;
import org.junit.jupiter.api.Test;

import java.util.Collection;

import static org.junit.jupiter.api.Assertions.*;

class GraphTest {

    @Test
    void testIsDirected() {
        Graph<String, Float> directedGraph = new Graph<>(true, false);
        Graph<String, Float> undirectedGraph = new Graph<>(false, false);

        assertTrue(directedGraph.isDirected());
        assertFalse(undirectedGraph.isDirected());
    }

    @Test
    void testIsLabelled() {
        Graph<String, Float> labelledGraph = new Graph<>(false, true);
        Graph<String, Float> unlabelledGraph = new Graph<>(false, false);

        assertTrue(labelledGraph.isLabelled());
        assertFalse(unlabelledGraph.isLabelled());
    }

    @Test
    void testAddNode() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addNode("A");

        assertTrue(graph.containsNode("A"));
    }

    @Test
    void testAddEdge() {
        Graph<String, Float> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1.0f);

        assertTrue(graph.containsEdge("A", "B"));
        assertEquals(1.0f, graph.getLabel("A", "B"));
    }

    @Test
    void testRemoveNode() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.removeNode("B");

        assertFalse(graph.containsNode("B"));
    }

    @Test
    void testRemoveEdge() {
        Graph<String, Float> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1.0f);
        graph.removeEdge("A", "B");

        assertFalse(graph.containsEdge("A", "B"));
    }

    @Test
    void testNumNodes() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");

        assertEquals(3, graph.numNodes());
    }

    @Test
    void testNumEdges() {
        Graph<String, Float> graph = new Graph<>(true, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addEdge("A", "B", 1.0f);
        graph.addEdge("B", "C", 2.0f);

        assertEquals(2, graph.numEdges());
    }

    @Test
    void testGetNodes() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");

        Collection<String> nodes = graph.getNodes();
        assertEquals(3, nodes.size());
        assertTrue(nodes.contains("A"));
        assertTrue(nodes.contains("B"));
        assertTrue(nodes.contains("C"));
    }

    @Test
    void testGetEdges() {
        Graph<String, Float> graph = new Graph<>(true, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addEdge("A", "B", 1.0f);
        graph.addEdge("B", "C", 2.0f);

        Collection<AbstractEdge<String, Float>> edges = graph.getEdges();
        assertEquals(2, edges.size());

        int count = 0;
        for (AbstractEdge<String, Float> edge : edges) {
            if (edge.start().equals("A") && edge.end().equals("B") && edge.label().equals(1.0f)) {
                count++;
            } else if (edge.start().equals("B") && edge.end().equals("C") && edge.label().equals(2.0f)) {
                count++;
            }
        }

        assertEquals(2, count);
    }

    @Test
    void testGetNeighbours() {
        Graph<String, Float> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addEdge("A", "B", 1.0f);
        graph.addEdge("A", "C", 2.0f);

        Collection<String> neighbours = graph.getNeighbours("A");
        assertEquals(2, neighbours.size());
        assertTrue(neighbours.contains("B"));
        assertTrue(neighbours.contains("C"));
    }

    @Test
    void testGetLabel() {
        Graph<String, Float> graph = new Graph<>(false, true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1.0f);

        assertEquals(1.0f, graph.getLabel("A", "B"));
    }
}