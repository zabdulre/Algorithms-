from collections import deque
import functools

numberOfTestCases = int(input())
numberOfPeopleInQueue = []
maxAmountThatCanBeWithdrawn = []
theAmountEachPersonNeeds = []
solution = []
queue = deque()

def sorter(i, j):
    ki = int(i[1][0]/i[1][1])
    kj = int(j[1][0]/j[1][1])
    if ki < kj:
        return -1
    elif kj > ki:
        return 1
    elif ki == kj and i[0] <= j[0]:
        return -1
    elif ki == kj and i[0] > j[0]:
        return 1
    return 1

for i in range(numberOfTestCases):
    holder = input().split()
    numberOfPeopleInQueue.append(int(holder[0]))
    maxAmountThatCanBeWithdrawn.append(int(holder[1]))
    holder = input().split()
    
    for c in range(numberOfPeopleInQueue[i]):
        theAmountEachPersonNeeds.append({})
        theAmountEachPersonNeeds[i].update({c:(int(holder[c]), maxAmountThatCanBeWithdrawn[i])})
    
    solution.append(sorted(theAmountEachPersonNeeds[i].items(), key= functools.cmp_to_key(sorter)))
    stri = ''
    for c in range(len(solution[i])):
        stri += str(solution[i][c][0] + 1) + ' '
    print("Case #" + str(i + 1) + ": " + stri)


# for i in range(numberOfTestCases):
#     solution.append([])
#     for c in range(numberOfPeopleInQueue[i]):
#         queue.append(c)

#     while queue:
#         currentPerson = queue.popleft()
#         theAmountEachPersonNeeds[i][currentPerson] = theAmountEachPersonNeeds[i][currentPerson] - maxAmountThatCanBeWithdrawn[i]
#         if theAmountEachPersonNeeds[i][currentPerson] > 0:
#             queue.append(currentPerson)
#         else:
#             solution[i].append(currentPerson + 1)
#     stri = str(solution[i])
#     print("Case #" + str(i + 1) + ": " + stri[1:len(stri) - 1].replace(',', ' '))

