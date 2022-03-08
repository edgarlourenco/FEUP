from State.State import State

if __name__ == '__main__':
    state = State(0,0,4,3)
    state_potential = [state]
    state_visited = []

    while not state == State(2,0,4,3):
        state = state_potential.pop(0)

        if state in state_visited:
            continue

        if state.balde1 < state.max_balde1:
            state_potential.append(state.fill(1))
        if state.balde2 < state.max_balde2:
            state_potential.append(state.fill(2))
        if state.balde1 > 0:
            state_potential.append(state.empty(1))
        if state.balde2 > 0:
            state_potential.append(state.empty(2))
        if state.balde2 < state.max_balde2 and state.balde1 >= (state.max_balde2 - state.balde2):
            state_potential.append(state.pour(1))
        if state.balde2 < state.max_balde2 and state.balde1 < (state.max_balde2 - state.balde2):
            state_potential.append(state.pour(1))
        if state.balde1 < state.max_balde1 and state.balde2 >= (state.max_balde1 - state.balde1):
            state_potential.append(state.pour(2))
        if state.balde1 < state.max_balde1 and state.balde2 < (state.max_balde1 - state.balde1):
            state_potential.append(state.pour(2))

        state_visited.append(state)

    output = []
    while state is not None:
        output.append(state)
        state = state.parent

    while len(output) > 0:
        state = output.pop()
        print("Balde1: ", state.balde1, "Balde 2: ", state.balde2)