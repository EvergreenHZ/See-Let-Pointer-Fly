MINUS_INFINITY = -10000000000
class Heap:

    def __init__(self, A):
        self.size = A[0]
        self.heap = [x for x in A]  # copy

    def swap(self, x, y):
        t = self.heap[x]
        self.heap[x] = self.heap[y]
        self.heap[y] = t

    def left(self, i):
        return i * 2

    def right(self, i):
        return i * 2 + 1

    def parent(self, i):
        return i / 2

    def heapify(self, i):
        largest = i
        l = self.left(i)
        r = self.right(i)

        if l <= self.heap[0] and self.heap[l] > self.heap[i]:
            largest = l

        if r <= self.heap[0] and self.heap[r] > self.heap[largest]:
            largest = r

        if largest != i:
            self.swap(i, largest)
            self.heapify(largest)
        else:
            return

    def buildMaxHeap(self):
        for i in range(int(self.heap[0] / 2), 0, -1):
            print(i)
            self.heapify(i)

    # increase heap[i] to key
    def increasedKey(self, i, key):
        if key < self.heap[i]:
            print("Error: increased key is less than the original one")
            return

        # i should > 1
        while i > 1 and self.heap[i] < self.heap[i / 2]:
            self.swap(i, i /2)
            i = i / 2

    def insert(self, x):
        self.heap[0] += 1 # size increased
        self.heap.append(MINUS_INFINITY)
        self.increasedKey(self.heap[0], x)  # increase key

A = [10, 2, 4, 1, 9, 0, 3, 7, 8, 6, 5]
h = Heap(A)
h.buildMaxHeap()
print(h.heap)
