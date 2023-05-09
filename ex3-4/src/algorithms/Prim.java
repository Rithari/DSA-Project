package algorithms;

import datastructures.Graph;
import datastructures.AbstractGraph;
import datastructures.AbstractGraph.AbstractEdge;
import datastructures.PriorityQueue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;


public class Prim {
    public static void main(String[] args) {
        Graph<String, Double> graph = readCSV(args[0]);

        Graph<String, Double> minCoveringForest = primsAlgorithm(graph);

        System.out.println("Number of nodes: " + minCoveringForest.numNodes());
        System.out.println("Number of edges: " + minCoveringForest.numEdges() / 2);
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

    private static Graph<String, Double> primsAlgorithm(Graph<String, Double> graph) {
        Graph<String, Double> minCoveringForest = new Graph<>(false, true);

        Set<String> visited = new HashSet<>();
        PriorityQueue<AbstractEdge<String, Double>> priorityQueue = new PriorityQueue<>(Comparator.comparing(AbstractEdge::getLabel));

        for (String startNode : graph.getNodes()) {
            if (!visited.contains(startNode)) {
                visited.add(startNode);
                minCoveringForest.addNode(startNode);

                priorityQueue.addAll(getEdgesWithStartNode(graph, startNode, visited));

                while (!priorityQueue.empty()) {
                    AbstractEdge<String, Double> edge = priorityQueue.top();
                    priorityQueue.pop();

                    String endNode = edge.getEnd();
                    if (!visited.contains(endNode)) {
                        visited.add(endNode);
                        minCoveringForest.addNode(endNode);
                        minCoveringForest.addEdge(edge.getStart(), endNode, edge.getLabel());

                        priorityQueue.addAll(getEdgesWithStartNode(graph, endNode, visited));
                    }
                }
            }
        }

        return minCoveringForest;
    }

    private static Collection<AbstractEdge<String, Double>> getEdgesWithStartNode(Graph<String, Double> graph, String startNode, Set<String> visited) {
        Collection<AbstractEdge<String, Double>> edges = new ArrayList<>();
        for (String neighbour : graph.getNeighbours(startNode)) {
            if (!visited.contains(neighbour)) {
                AbstractEdge<String, Double> edge = new AbstractEdge<>() {
                    @Override
                    public String getStart() {
                        return startNode;
                    }

                    @Override
                    public String getEnd() {
                        return neighbour;
                    }

                    @Override
                    public Double getLabel() {
                        return graph.getLabel(startNode, neighbour);
                    }
                };
                edges.add(edge);
            }
        }
        return edges;
    }


    private static double calculateTotalWeight(Graph<String, Double> graph) {
        double totalWeight = 0;
        for (AbstractGraph.AbstractEdge<String, Double> edge : graph.getEdges()) {
            totalWeight += edge.getLabel();
        }
        // Since the graph is undirected, each edge is counted twice, so we need to divide by 2
        return totalWeight / 2;
    }
}