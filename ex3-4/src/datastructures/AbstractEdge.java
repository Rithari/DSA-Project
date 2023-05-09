package datastructures;

public interface AbstractEdge<V,L> {
    V start(); // il nodo di partenza dell'arco
    V end(); // il nodo di arrivo dell'arco
    L label(); // l'etichetta dell'arco
};
