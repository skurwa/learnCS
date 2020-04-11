class Node:
    def __init__(self, data = None, next = None):
        self.data = data
        self.next = next

class Queue:
    def __init__(self, into = None, out = None):
        self.into = into
        self.out = out

    def enqueue(self, data):
        tmp = Node(data = data)

        if self.into != None:
            self.into.next = tmp
        
        self.into = tmp

        if self.out == None:
            self.out = self.into
        

    def dequeue(self):
        if self.out == None:
            return None
        if self.into == self.out:
            self.into = None
        outData = self.out.data
        self.out = self.out.next
        return outData

    def peek(self):
        if self.out == None:
            return None
        return self.out.data

if __name__ == "__main__":
    
    q = Queue()
    q.enqueue(4)
    print(q.peek())
    q.enqueue(5)
    q.enqueue(6)
    print(q.dequeue())
    print(q.peek())
    print(q.dequeue())
    print(q.dequeue())
    print(q.peek())
    print(q.dequeue())
    q.enqueue(7)
    print(q.peek())
    print(q.dequeue())
    print(q.peek())
    print(q.dequeue())