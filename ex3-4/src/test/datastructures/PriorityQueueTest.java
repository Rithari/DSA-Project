package test.datastructures;

import datastructures.PriorityQueue;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Comparator;

import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class PriorityQueueTest {
    private PriorityQueue<Integer> priorityQueue;

    @BeforeEach
    void setUp() {
        Comparator<Integer> comparator = Integer::compare;
        priorityQueue = new PriorityQueue<>(comparator);
    }

    @Test
    void testEmptyQueue() {
        assertTrue(priorityQueue.empty());
    }

    @Test
    void testPushAndTop() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);

        assertEquals(2, priorityQueue.top());
    }

    @Test
    void testPop() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);

        priorityQueue.pop();
        assertEquals(5, priorityQueue.top());
    }

    @Test
    void testPopEmptyQueue() {
        assertThrows(NoSuchElementException.class, () -> priorityQueue.pop());
    }

    @Test
    void testTopEmptyQueue() {
        assertThrows(NoSuchElementException.class, () -> priorityQueue.top());
    }

    @Test
    void testPushPopMultipleElements() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);
        priorityQueue.push(1);
        priorityQueue.push(4);

        assertEquals(1, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(2, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(4, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(5, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(8, priorityQueue.top());
    }
}
