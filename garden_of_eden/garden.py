from copy import deepcopy

class CircularList:
    def __init__(self, state):
        self.state = state

    def previousIndex(self, i):
        if (i - 1 < 0):
            return len(self.state) - 1
        return i - 1
    
    def nextIndex(self, i):
        if (i + 1 > len(self.state) - 1):
            return 0
        return i + 1

    def previous(self, i):
        return self.state[self.previousIndex(i)]

    def next(self, i):
        return self.state[self.nextIndex(i)]

    def __getitem__(self, key):
        return self.state[key]

    def __setitem__(self, key, value):
        self.state[key] = value

class Automaton:
    def __init__(self, identifier):
        self.rules = {i: [] for i in range(2)}

        for i, j in zip(self.parseIdentifier(identifier), self.generateTable()):
            self.rules[i].append(j)

    def parseIdentifier(self, identifier):
        binaryId = "{0:b}".format(identifier)
        parsed = [int(i) for i in binaryId]

        parsed.reverse()
        parsed.extend([0] * (8 - len(parsed)))
        parsed.reverse()

        return parsed

    def generateTable(self):
        table = []
        for i in range(2):
            for j in range(2):
                for k in range(2):
                    table.append((i, j, k))
        return table

    def __getitem__(self, key):
        return self.rules[key]

    def __setitem__(self, key, value):
        self.rules[key] = value

def isReachable(cells, originalCells, automaton, index = 0):
    for rule in automaton[cells[index]]:
        newCells = deepcopy(originalCells)

        if (newCells[index] == -1):
            newCells[index] = rule[1]
        elif(newCells[index] != rule[1]):
            continue

        if (newCells.previous(index) == -1):
            newCells[newCells.previousIndex(index)] = rule[0]
        elif(newCells.previous(index) != rule[0]):
            continue

        if (newCells.next(index) == -1):
            newCells[newCells.nextIndex(index)] = rule[2]
        elif(newCells.next(index) != rule[2]):
            continue

        if (index == len(cells.state) - 1):
            return True

        if (isReachable(cells, newCells, automaton, index + 1)):
            return True
        
    else:
        return False
        
if __name__ == "__main__":
    while True:
        automatonId, _, cellString = None, None, None

        try:
            automatonId, _, cellString = input().strip().split()
        except ValueError:
            print("BAD INPUT")
            continue

        if (int(automatonId) < 0 or int(automatonId) > 255 or
            int(_) < 0 or int(_) > 32 or len(cellString) != int(_)):
            print("BAD INPUT")
            continue


        cells = CircularList([int(i) for i in cellString])
        automaton = Automaton(int(automatonId))
        originalCells = CircularList([-1] * len(cells.state))

        if(isReachable(cells, originalCells, automaton)):
            print("REACHABLE")
        else:
            print("GARDEN OF EDEN")