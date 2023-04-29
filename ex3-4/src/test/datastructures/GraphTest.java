package test.datastructures;

import datastructures.Graph;
import org.junit.jupiter.api.Test;

import java.util.Map;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

class GraphTest {

    @Test
    void testAddNodes() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        assertEquals(4, graph.numberOfNodes());
    }

    @Test
    void testAddArcs() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        assertEquals(4, graph.numberOfArcs());
    }

    @Test
    void testNodeAndArcPresence() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addArc("A", "B", 1.0f);

        assertTrue(graph.containsNode("A"));
        assertTrue(graph.containsArc("A", "B"));
    }

    @Test
    void testArcRemoval() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addArc("A", "B", 1.0f);

        graph.deleteArc("A", "B");
        assertFalse(graph.containsArc("A", "B"));
        assertEquals(0, graph.numberOfArcs());
    }

    @Test
    void testNodeRemoval() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.deleteNode("A");
        assertFalse(graph.containsNode("A"));
        assertEquals(3, graph.numberOfNodes());
    }

    @Test
    void testIsDirected() {
        Graph<String, Float> directedGraph = new Graph<>(true);
        Graph<String, Float> undirectedGraph = new Graph<>(false);

        assertTrue(directedGraph.isDirected());
        assertFalse(undirectedGraph.isDirected());
    }

    @Test
    void testGetAdjacentNodes() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("A", "C", 2.0f);

        Set<String> adjacentNodes = graph.getAdjacentNodes("A");
        assertTrue(adjacentNodes.contains("B"));
        assertTrue(adjacentNodes.contains("C"));
        assertFalse(adjacentNodes.contains("D"));
    }

    @Test
    void testGetWeight() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        assertEquals(1.0f, graph.getWeight("A", "B"));
        assertEquals(2.0f, graph.getWeight("B", "C"));
        assertEquals(3.0f, graph.getWeight("C", "D"));
        assertEquals(4.0f, graph.getWeight("A", "D"));
    }

    @Test
    void testGetTotalWeight() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        assertEquals(10.0, graph.getTotalWeight());
    }

    @Test
    void testGetArcsCount() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        assertEquals(8, graph.getArcsCount());
    }

    @Test
    void testGetArcs() {
        Graph<String, Float> graph = new Graph<>(false);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        Set<Map.Entry<String, Float>> arcs = graph.getArcs("A");
        boolean containsAB = false;
        boolean containsAD = false;
        for (Map.Entry<String, Float> arc : arcs) {
            if (arc.getKey().equals("B") && arc.getValue() == 1.0f) {
                containsAB = true;
            } else if (arc.getKey().equals("D") && arc.getValue() == 4.0f) {
                containsAD = true;
            }
        }

        assertTrue(containsAB);
        assertTrue(containsAD);
    }

    @Test
    void testDirectedGraphArcs() {
        Graph<String, Float> graph = new Graph<>(true);
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");

        graph.addArc("A", "B", 1.0f);
        graph.addArc("B", "C", 2.0f);
        graph.addArc("C", "D", 3.0f);
        graph.addArc("A", "D", 4.0f);

        assertTrue(graph.containsArc("A", "B"));
        assertFalse(graph.containsArc("B", "A"));
        assertEquals(4, graph.numberOfArcs());
    }

    @Test
    void testCreateEmptyGraph() {
        Graph<String, Float> graph = Graph.createEmptyGraph(false);
        assertNotNull(graph);
        assertEquals(0, graph.numberOfNodes());
        assertEquals(0, graph.numberOfArcs());
    }
}
