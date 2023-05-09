package test.algorithms;

import algorithms.Prim;
import datastructures.Graph;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class PrimTest {
    private Graph<String, Double> graph;

    private boolean containsUndirectedEdge(Graph<String, Double> graph, String node1, String node2) {
        return graph.containsEdge(node1, node2) || graph.containsEdge(node2, node1);
    }

    @BeforeEach
    void setUp() {
        graph = new Graph<>(false, true);

        // Add nodes
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addNode("E");
        graph.addNode("F");
        graph.addNode("G");

        // Add edges
        graph.addEdge("A", "B", 3.0);
        graph.addEdge("A", "D", 1.0);
        graph.addEdge("B", "C", 2.0);
        graph.addEdge("B", "E", 5.0);
        graph.addEdge("C", "E", 1.0);
        graph.addEdge("C", "F", 6.0);
        graph.addEdge("D", "E", 4.0);
        graph.addEdge("E", "F", 2.0);
        graph.addEdge("E", "G", 3.0);
        graph.addEdge("F", "G", 7.0);
    }

    @Test
    void testPrimSingleNode() {
        Graph<String, Double> singleNodeGraph = new Graph<>(false, true);
        singleNodeGraph.addNode("A");

        Graph<String, Double> mst = Prim.prim(singleNodeGraph);
        assertEquals(1, mst.numNodes());
        assertEquals(0, mst.numEdges());
    }

    @Test
    void testPrimComplexGraph() {
        Graph<String, Double> mst = Prim.prim(graph);

        assertEquals(7, mst.numNodes());
        assertEquals(6, mst.numEdges());

        assertTrue(containsUndirectedEdge(mst, "A", "D"));
        assertTrue(containsUndirectedEdge(mst, "B", "C"));
        assertTrue(containsUndirectedEdge(mst, "C", "E"));
        assertTrue(containsUndirectedEdge(mst, "E", "F"));
        assertTrue(containsUndirectedEdge(mst, "E", "G"));
    }

    @Test
    void testPrimEmptyGraph() {
        Graph<String, Double> graph = new Graph<>(false, true);

        Graph<String, Double> mst = Prim.prim(graph);

        assertEquals(0, mst.numNodes());
        assertEquals(0, mst.numEdges());
    }


    @Test
    void testPrimSingleNodeGraph() {
        Graph<String, Double> graph = new Graph<>(false, true);
        graph.addNode("A");

        Graph<String, Double> mst = Prim.prim(graph);

        assertEquals(1, mst.numNodes());
        assertEquals(0, mst.numEdges());
    }

}