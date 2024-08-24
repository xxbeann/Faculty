'''
list = ["a", "b", "a"]
list.sort()
print(list)
for i in range(len(list)-2):
    if (list[i] == list[i+1]):
        print(list[i])


s = {1, 2, 3}
a = list(s)
c = set(a)
print(a)
print(c)

l = [1,2,3,4,5,5]
b = set(l)
print(b)
d = list(b)
print(d)
'''
def solution(participant, completion):
    answer = []
    # 동명이인이 없는 경우
    p = set(participant)
    c = set(completion)
    answer = list(p - c)
    # 동명이인이 있는 경우
    if len(answer) == 0:
        participant.sort()
        for i in range(len(participant) - 2):
            if (participant[i] == participant[i + 1]):
                answer.append(participant[i])
    return answer[0]
