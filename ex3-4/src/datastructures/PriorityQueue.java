package datastructures;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.NoSuchElementException;
import java.util.Comparator;

public class PriorityQueue<E> implements AbstractQueue<E> {
    private final Comparator<E> comparator;
    private final ArrayList<E> heap;
    private final HashMap<E, Integer> indexMap;

    public PriorityQueue(Comparator<E> comparator) {
        this.comparator = comparator;
        this.heap = new ArrayList<>();
        this.indexMap = new HashMap<>();
    }

    private void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (comparator.compare(heap.get(parentIndex), heap.get(index)) <= 0) {
                break;
            }
            swap(heap, parentIndex, index);
            index = parentIndex;
        }
    }
    private void heapifyDown(int index) {
        int leftChildIndex = index * 2 + 1;
        int rightChildIndex = index * 2 + 2;
        while (leftChildIndex < heap.size()) {
            int smallestChildIndex = leftChildIndex;

            if (rightChildIndex < heap.size() &&
                    comparator.compare(heap.get(rightChildIndex), heap.get(leftChildIndex)) < 0) {
                smallestChildIndex = rightChildIndex;
            }

            if (comparator.compare(heap.get(index), heap.get(smallestChildIndex)) <= 0) {
                break;
            }

            swap(heap, index, smallestChildIndex);
            index = smallestChildIndex;
            leftChildIndex = index * 2 + 1;
            rightChildIndex = index * 2 + 2;
        }
    }

    @Override
    public boolean empty() {
        return heap.isEmpty();
    }

    @Override
    public boolean push(E e) {
        heap.add(e);
        int index = heap.size() - 1;
        indexMap.put(e, index);

        heapifyUp(index);

        return true;
    }

    @Override
    public E top() {
        if (empty()) {
            throw new NoSuchElementException("PriorityQueue is empty");
        }
        return heap.get(0);
    }


    @Override
    public void pop() {
        if (empty()) {
            throw new NoSuchElementException("PriorityQueue is empty");
        }
        int lastIndex = heap.size() - 1;
        swap(heap, 0, lastIndex);
        heap.remove(lastIndex);

        heapifyDown(0);
    }

    private void swap(ArrayList<E> heap, int i, int j) {
        E temp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, temp);
        indexMap.put(temp, j);
        indexMap.put(heap.get(i), i);
    }

    public boolean contains(E e) {
        return indexMap.containsKey(e);
    }

    public boolean remove(E e) {
        Integer index = indexMap.get(e);
        if (index == null) {
            return false;
        }

        int lastIndex = heap.size() - 1;
        if (index != lastIndex) {
            swap(heap, index, lastIndex);
            heap.remove(lastIndex);
            indexMap.remove(e);

            int parentIndex = (index - 1) / 2;
            if (comparator.compare(heap.get(parentIndex), heap.get(index)) > 0) {
                while (index > 0 && comparator.compare(heap.get(parentIndex), heap.get(index)) > 0) {
                    swap(heap, parentIndex, index);
                    index = parentIndex;
                    parentIndex = (index - 1) / 2;
                }
            } else {
                heapifyDown(index);
            }
        } else {
            heap.remove(lastIndex);
            indexMap.remove(e);
        }

        return true;
    }

    public void increasePriority(E e1, E e2) {
        Integer index = indexMap.get(e1);
        if (index == null) {
            throw new NoSuchElementException("Element not found in the PriorityQueue");
        }
        if (comparator.compare(e2, e1) >= 0) {
            throw new IllegalArgumentException("New element must have a higher priority than the existing element");
        }

        heap.set(index, e2);
        indexMap.put(e2, index);
        indexMap.remove(e1);

        heapifyUp(index);
    }
}