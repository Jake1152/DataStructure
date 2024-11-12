'''
# 문제 정의

힙, 완전이진트리, min max heap
최상위 부모만 가장 작은 값이거나 큰 값이다.
부모는 자식보다 작거나(min) 크다(max)
일관된 룰을 따라야 한다.

## 힙 삽입 
last 1 증가 시킨다.
heap를 배열에서 top 위치에 새로운 값을 넣는다.
부모노드가 값이 더 작거나(min heap) 큰지(max heap) 확인하여
규칙에 맞지 않다면 부모 노드와 자식 노드의 위치를 바꾼다.
규칙에 맞지 않으면서 루트노드와 비교할때까지 반복한다.


## 힙 삭제
루트 노드를 삭제하며 마지막에 들어온 노드(top위치에 있는 노드)

# 문제 해결 방법 


'''
class Heap:
    # __heap
    def __init__(self):
        self.__heap = [None]
        self.__last = 0

    def top(self):
        return self.__heap[self.__last]

    def insert(self, value):
        pass

    def delete(self):
        self.__top -= 1
        pass

if '__name__' == '__main__':
    Heap()
