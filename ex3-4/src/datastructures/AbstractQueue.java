package datastructures;

public interface AbstractQueue<E> {
    boolean empty();
    boolean push(E e);
    E top();
    void pop();
}