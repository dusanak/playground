from sys import stdin

automatonBitsMSL = [0] * 8
state,prev_state = [-1] * 50, [-1] * 50
automatonID,n_cells,reachable = 0, 0, True

def canReach(index,reachable):
    if reachable: return

    if index == n_cells-1:
        i = ((prev_state[n_cells-2]<<2) | (prev_state[n_cells-1]<<1) | (prev_state[0]<<0))
        j = ((prev_state[n_cells-1]<<2) | (prev_state[0]<<1) | (prev_state[1]<<0))
        if int(state[index]) == automatonBitsMSL[i] and int(state[0]) == automatonBitsMSL[j]:
            reachable = True
        return

    for i in range(8):
        if (automatonBitsMSL[i] == int(state[index]) 
        and prev_state[index-1] == ((i>>2)&1) 
        and prev_state[index] == ((i>>1)&1)):
            prev_state[index+1] = (i>>0)&1
            canReach(index+1,reachable)
            if reachable: return

def main():
    while True:
        try:
            automatonID, n_cells, state = input().strip().split()
            n_cells = int(n_cells)
            prev_state = [0] * int(n_cells)
            reachable = bool(False)
    
            for i in range(8):
                automatonBitsMSL[i] = (int(automatonID)>>i)&1
        
            reachable = False
            for i in range(8):
                if automatonBitsMSL[i] == int(state[0]):
                    prev_state[0] = (i>>1)&1
                    prev_state[1] = (i>>0)&1
                    canReach(1,reachable)
                    
            if reachable:
                print("REACHABLE")
            else:
                print("GARDEN OF EDEN")
        except ValueError:
            break

if __name__ == "__main__":
    n_cells = 0
    automatonBitsMSL = [0,0,0,0,0,0,0,0]
    main()
