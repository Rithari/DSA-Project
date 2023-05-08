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

    @Test
    void testContains() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);

        assertTrue(priorityQueue.contains(5));
        assertTrue(priorityQueue.contains(2));
        assertTrue(priorityQueue.contains(8));
        assertFalse(priorityQueue.contains(3));
    }

    @Test
    void testIncreasePriority() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);
        priorityQueue.push(1);
        priorityQueue.push(4);

        priorityQueue.increasePriority(4, 0);

        assertEquals(0, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(1, priorityQueue.top());
        priorityQueue.pop();
        assertEquals(2, priorityQueue.top());
    }

    @Test
    void testIncreasePriorityNoSuchElement() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);

        assertThrows(NoSuchElementException.class, () -> priorityQueue.increasePriority(10, 1));
    }

    @Test
    void testIncreasePriorityInvalidPriority() {
        priorityQueue.push(5);
        priorityQueue.push(2);
        priorityQueue.push(8);

        assertThrows(IllegalArgumentException.class, () -> priorityQueue.increasePriority(5, 6));
    }
}
