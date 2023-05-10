package algorithms;

import datastructures.Graph;
import datastructures.AbstractGraph;
import datastructures.NodeKey;
import datastructures.PriorityQueue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;


public class Prim {
    public static void main(String[] args) {
        Graph<String, Double> graph = readCSV(args[0]);

        // Get the first node as the root
        String root = graph.getNodes().iterator().next();

        long startTime = System.nanoTime();
        Graph<String, Double> minCoveringForest = primMST(graph, root);
        long endTime = System.nanoTime();

        System.out.println("Time taken: " + ((endTime - startTime) / 10E5) + " ms");

        System.out.println("Number of nodes: " + minCoveringForest.numNodes());
        System.out.println("Number of edges: " + minCoveringForest.numEdges());
        System.out.printf("Total km: %.3f\n", calculateTotalWeight(minCoveringForest) / 1000);
    }


    private static Graph<String, Double> readCSV(String path) {
        Graph<String, Double> graph = new Graph<>(false, true);
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                String place1 = data[0];
                String place2 = data[1];
                Double distance = Double.parseDouble(data[2]);

                graph.addNode(place1);
                graph.addNode(place2);
                graph.addEdge(place1, place2, distance);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return graph;
    }
    public static Graph<String, Double> primMST(Graph<String, Double> graph, String root) {
        if (graph == null || graph.numNodes() == 0) {
            throw new IllegalArgumentException("The input graph is empty.");
        }

        Graph<String, Double> mst = new Graph<>(false, true);
        Set<String> visited = new HashSet<>();
        Map<String, NodeKey> nodeKeys = new HashMap<>();

        for (String node : graph.getNodes()) {
            nodeKeys.put(node, new NodeKey(node, Double.POSITIVE_INFINITY));
        }

        Comparator<NodeKey> nodeKeyComparator = Comparator.comparingDouble(NodeKey::getKey);
        PriorityQueue<NodeKey> priorityQueue = new PriorityQueue<>(nodeKeyComparator);
        nodeKeys.get(root).setKey(0);
        priorityQueue.addAll(nodeKeys.values());

        while (!priorityQueue.empty()) {
            NodeKey currentNodeKey = priorityQueue.top();
            priorityQueue.pop();

            String currentNode = currentNodeKey.getNode();
            visited.add(currentNode);

            mst.addNode(currentNode);

            if (currentNodeKey.getParent() != null) {
                mst.addNode(currentNodeKey.getParent());
                double edgeWeight = graph.getLabel(currentNode, currentNodeKey.getParent());
                mst.addEdge(currentNode, currentNodeKey.getParent(), edgeWeight);
            }

            for (String neighbor : graph.getNeighbours(currentNode)) {
                if (!visited.contains(neighbor)) {
                    double newKey = graph.getLabel(currentNode, neighbor);

                    if (newKey < nodeKeys.get(neighbor).getKey()) {
                        NodeKey newNeighborKey = new NodeKey(neighbor, newKey);
                        newNeighborKey.setParent(currentNode);
                        priorityQueue.increasePriority(nodeKeys.get(neighbor), newNeighborKey);
                        nodeKeys.put(neighbor, newNeighborKey);
                    }
                }
            }
        }

        return mst;
    }

    private static double calculateTotalWeight(Graph<String, Double> graph) {
        double totalWeight = 0;
        for (AbstractGraph.AbstractEdge<String, Double> edge : graph.getEdges()) {
            totalWeight += edge.getLabel();
        }
        return totalWeight / 2;
    }
}