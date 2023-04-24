package datastructures;

import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Comparator;

public class PriorityQueue<E> implements AbstractQueue<E> {
    private final Comparator<E> comparator;
    private final ArrayList<E> heap;

    public PriorityQueue(Comparator<E> comparator) {
        this.comparator = comparator;
        this.heap = new ArrayList<>();
    }

    @Override
    public boolean empty() {
        return heap.isEmpty();
    }

    @Override
    public boolean push(E e) {
        heap.add(e);
        int index = heap.size() - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (comparator.compare(heap.get(parentIndex), heap.get(index)) <= 0) {
                break;
            }
            swap(heap, parentIndex, index);
            index = parentIndex;
        }
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

        int index = 0;
        while (true) {
            int leftChildIndex = index * 2 + 1;
            int rightChildIndex = index * 2 + 2;
            int smallestChildIndex = leftChildIndex;

            if (leftChildIndex >= heap.size()) {
                break;
            }

            if (rightChildIndex < heap.size() &&
                    comparator.compare(heap.get(rightChildIndex), heap.get(leftChildIndex)) < 0) {
                smallestChildIndex = rightChildIndex;
            }

            if (comparator.compare(heap.get(index), heap.get(smallestChildIndex)) <= 0) {
                break;
            }

            swap(heap, index, smallestChildIndex);
            index = smallestChildIndex;
        }
    }

    private void swap(ArrayList<E> heap, int i, int j) {
        E temp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, temp);
    }
}