from sys import stdin
from pprint import pprint

def makemaze(): #미로 입력 받기
    data1 = stdin.readline().strip().split()
    global n
    n = len(data1)
    maze = []
    maze.append(data1)
    for i in range(n - 1):
        data = stdin.readline().strip().split()
        maze.append(data)
    return maze

def Index_numbering(): #인덱스 넘버링
    count = 1
    for i in range(0, n):
        for j in range(0, n):
            if maze[i][j] == '0':
                maze[i][j] = count
                count += 1
    return maze

def insertdict(): #좌표와 인덱스 넘버 매칭
    global dict
    dict = {}
    for i in range(0, n):
        for j in range(0, n):
            if maze[i][j] != '1':
                dict[i, j] = maze[i][j]
    return dict

def make_adjlist(): #인접리스트생성
    adjlist = {}
    for i in range(0, n):
        for j in range(0, n):
            if maze[i][j] != '1':  # 순회하다가 '1'이 아닐경우 상하좌우로 탐색시작
                adj = set([])
                for search in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:  # 좌 우 상 하
                    if (search[0] < 0 or search[1] < 0 or search[0] == n or search[1] == n):
                        pass
                    elif maze[search[0]][search[1]] != '1':  # 연결된 노드가 있으면 인접리스트(딕셔너리)에 삽입
                        adj.add(dict[search[0], search[1]])
                adjlist[dict[i, j]] = adj
    return adjlist

def bfs(graph, start): #너비우선탐색
    visited = []
    queue = [start]

    while queue:
        n = queue.pop(0)
        if n not in visited:
            visited.append(n)
            queue += graph[n] - set(visited)
    return visited

def bfs_paths(graph, start, goal): #두 노드 간 경로탐색
    queue = [(start, [start])]
    result = []

    while queue:
        n, path = queue.pop(0)
        if n == goal:
            result.append(path)
        else:
            for m in graph[n] - set(path):
                queue.append((m, path + [m]))
    return result

def display(): #출력하기
    print('경로 : ',end='')
    for i in range(0, len(minimum) - 1):
        print(minimum[i], ' - ', end='')
    print(minimum[len(minimum) - 1])
    print('길이 :', len(minimum) - 1)

maze = makemaze() #입력받기
Index_maze = Index_numbering() #index 넣기
dict = insertdict() #딕셔너리에 넣어주기
adjlist = make_adjlist() #인접리스트 생성
pprint(adjlist, indent=1, width=80) #인접리스트 출력
bfs = bfs(adjlist,'e') #너비우선탐색
bfs_paths = bfs_paths(adjlist,'e','x') #두 노드 간 길찾기
minimum = bfs_paths[0] # 두 노드간 찾은 길 중 최단거리
display() #출력
