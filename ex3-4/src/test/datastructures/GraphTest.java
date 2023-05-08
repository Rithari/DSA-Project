package test.datastructures;

import datastructures.Graph;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GraphTest {

    @Test
    void testAddSelfLoop() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addArc("A", "A", 1.0f);

        assertTrue(graph.containsArc("A", "A"));
    }

    @Test
    void testRemoveNonExistentArc() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");

        assertDoesNotThrow(() -> graph.deleteArc("A", "B"));
        assertFalse(graph.containsArc("A", "B"));
    }

    @Test
    void testRemoveNonExistentNode() {
        Graph<String, Float> graph = new Graph<>(false);

        assertDoesNotThrow(() -> graph.deleteNode("A"));
        assertFalse(graph.containsNode("A"));
    }

    @Test
    void testAddDuplicateNode() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("A");

        assertEquals(1, graph.numberOfNodes());
    }

    @Test
    void testAddDuplicateArc() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addArc("A", "B", 1.0f);
        graph.addArc("A", "B", 1.0f);

        assertEquals(1, graph.numberOfArcs());
    }

    @Test
    void testUpdateArcWeight() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addArc("A", "B", 1.0f);
        graph.addArc("A", "B", 2.0f);

        assertEquals(2.0f, graph.getWeight("A", "B"));
    }

    @Test
    void testGetArcsCountDirectedUndirected() {
        Graph<String, Float> directedGraph = new Graph<>(true);
        Graph<String, Float> undirectedGraph = new Graph<>(false);

        directedGraph.addNode("A");
        directedGraph.addNode("B");
        directedGraph.addNode("C");
        directedGraph.addNode("D");
        directedGraph.addArc("A", "B", 1.0f);
        directedGraph.addArc("B", "C", 2.0f);
        directedGraph.addArc("C", "D", 3.0f);
        directedGraph.addArc("A", "D", 4.0f);

        undirectedGraph.addNode("A");
        undirectedGraph.addNode("B");
        undirectedGraph.addNode("C");
        undirectedGraph.addNode("D");
        undirectedGraph.addArc("A", "B", 1.0f);
        undirectedGraph.addArc("B", "C", 2.0f);
        undirectedGraph.addArc("C", "D", 3.0f);
        undirectedGraph.addArc("A", "D", 4.0f);

        assertEquals(4, directedGraph.getArcsCount());
        assertEquals(8, undirectedGraph.getArcsCount());
    }

}
