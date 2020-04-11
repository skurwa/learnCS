class Node:
    def __init__(self, data = None, next = None):
        self.data = data
        self.next = next

    def __str__(self):
        return str(self.data)

    def getData(self):
        return self.data
    
    def setData(self, newData):
        self.data = newData
    
    def getNext(self):
        return self.next
    
    def setNext(self, newNext):
        self.next = newNext

class Stack:
    def __init__(self, head = None, tail = None):
        self.head = head
        self.tail = tail

    def push(self, node):
        node.setNext(self.tail)
        self.tail = node
        return

    def pop(self):
        if self.tail == None:
            return None
        tmp = self.tail
        self.tail = tmp.getNext() 
        return tmp.getData()

    def peek(self): 
        return self.tail.getData()

if __name__ == "__main__":
    myStack = Stack()
    myStack.push(Node(1))
    print(myStack.peek())
    myStack.push(Node(2))
    print(myStack.peek())
    myStack.push(Node(3))
    print(myStack.peek())
    print(myStack.pop())
    print(myStack.pop())
    print(myStack.pop())
    print(myStack.pop())