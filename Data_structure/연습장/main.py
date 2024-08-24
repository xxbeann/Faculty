'''
class Room:
    def __init__(self, coords, neighbors=None, traversal_mode=False):
        self.coords = coords
        if neighbors:
            self.neighbors = neighbors
        else:
            self.neighbors = []

        # Derived Attributes
        self.row, self.col = self.coords
        self.is_intersection = len(self.neighbors) > 2
        self.is_dead_end = len(self.neighbors) == 1

        # These don't come into play until the traversal stage
        self.prev = None
        self.traversal_mode = traversal_mode

    def __repr__(self):
        if self.traversal_mode and self.prev:
            return f"""{self.prev} -> {self.coords}"""
        elif self.traversal_mode and not self.prev:
            return f"""{self.coords}"""
        else:
            return f"""Neighbors={self.neighbors}, Intersection={self.is_intersection}, Dead End={self.is_dead_end}"""

def find_neighbors(coords, maze):
    row, col = coords

    visited = (
        discover_room((row - 1, col), maze),  # North
        discover_room((row + 1, col), maze),  # South
        discover_room((row, col - 1), maze),  # East
        discover_room((row, col + 1), maze),  # West
    )
    return [v for v in visited if isinstance(v, tuple)]


def discover_room(coords, maze):
    width, height = n, n
    row, col = coords

    if any((row < 0, row > height - 1, col < 0, col > width - 1)):
        return False
    elif nested_list[row][col] == PATH:
        return (row, col)
    else:
        return False


def nested_list2adjlist(nested_list):
    adjlist = OrderedDict()

    for row_idx, row in enumerate(nested_list):
        for col_idx, c in enumerate(row):
            coords = (row_idx, col_idx)
            if discover_room(coords, nested_list):
                new_room = Room(coords, find_neighbors(coords, nested_list))
                adjlist.update({coords: new_room})
    return adjlist
'''
'''
game = [[1, 1, 1, 1, 1],
        [1, 'e', 1, 1, 1],
        [1, 0, 0, 'x', 1 ],
        [1, 0, 1, 1, 1],
        [1, 1, 1, 1, 1]]

rows = len(game) #5
cols = len(game[0]) #5

graph = {}
for i in range(1, rows -1):
    for j in range(1, cols - 1):
        if (game[i][j] != 1):
            adj = []
        for ele in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:
            if game[ele[0]][ele[1]] == 0 or game[ele[0]][ele[1]] == 'B':
                adj.append((ele[0], ele[1]))
        graph[(i, j)] = adj

print(rows, cols)
pprint(graph, width=200)
'''

'''
# 그래프를 반복적으로 dfs함
def iterative_dfs_desc(graph, input_start):
    visited = [0] * len(graph)
    answer = []
    stack = [input_start]

    while stack:
        print("\nstack: ", stack)
        temp = stack.pop()
        print("pop된 노드: ", temp)
        visited[temp] = 1
        answer.append(temp)

        for i in range(len(graph[temp])):
            if graph[temp][i] == 1 and visited[i] == 0 and temp != i:
                stack.append(i)
    return answer


graph = [[1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
         [1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
         [0, 1, 1, 0, 1, 0, 0, 0, 0, 0],
         [0, 1, 0, 1, 1, 1, 0, 0, 0, 0],
         [0, 0, 1, 1, 1, 0, 0, 0, 0, 0],
         [0, 0, 0, 1, 0, 1, 1, 1, 0, 0],
         [0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
         [0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
         [0, 0, 0, 0, 0, 0, 0, 1, 1, 0],
         [0, 0, 0, 0, 0, 0, 0, 1, 0, 1]
         ]

start = 3

print(iterative_dfs_desc(graph,start))
#스택에 중복값 들어감
'''

'''
# 인접 리스트 행렬로 변환
def convert_to_matrix(graph):
    matrix = []
    for i in range(len(graph)):
        matrix.append([0]*len(graph))
        for j in graph[i]:
            matrix[i][j] = 1
    return matrix
#the lst shows in a form of each index(each inner list) as a form of vertex,
#and each element in the inner list as the vertices that each vertex connected to.
lst = [[1,2,3,5,6],[0,3,6,7],[0,3],[0,1,2,4],[3,5,8],[0,4,8],[0,1],[1],[4,5]]
print(convert_to_matrix(lst))
'''
'''
#node, edge, 간선정보를 알 때 adj 표현

adj = [[0 for _ in range(node)] for _ in range(node)]

for _ in range(edge):
    src, dest = map(int, stdin.readline().split())
    adj[src-1][dest-1] = 1
    adj[dest-1][src-1] = 1

pprint(adj, width=100)
'''

graph = {'A': set(['B', 'C']),
         'B': set(['A', 'D', 'E']),
         'C': set(['A', 'F']),
         'D': set(['B']),
         'E': set(['B', 'F']),
         'F': set(['C', 'E'])}

def bfs(graph, start):
  visited = []
  queue = [start]

  while queue:
    n = queue.pop(0)
    if n not in visited:
      visited.append(n)
      queue += graph[n] - set(visited)
  return visited

def main():
    print(bfs(graph, 'A'))

main()