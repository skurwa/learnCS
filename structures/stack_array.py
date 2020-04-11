class Stack:
    def __init__(self):
        self.array = []
        self.idx = 0

    def push(self, data):
        self.array.append(data)
        
    def pop(self):
        if len(self.array) == 0:
            return None
        return self.array.pop()

    def peek(self): 
        return self.array[len(self.array) - 1]

if __name__ == "__main__":
    myStack = Stack()
    myStack.push(1)
    print(myStack.peek())
    myStack.push(2)
    print(myStack.peek())
    myStack.push(3)
    print(myStack.peek())
    print(myStack.pop())
    print(myStack.pop())
    print(myStack.pop())
    print(myStack.pop())