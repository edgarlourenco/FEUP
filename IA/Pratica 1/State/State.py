class State :
    def __init__(self, balde1, balde2, max_balde1, max_balde2, parent=None):
        self.max_balde1 = max_balde1
        self.max_balde2 = max_balde2
        self.balde1 = balde1
        self.balde2 = balde2
        self.parent = parent

    def fill(self, n):
        if n==1:
            return State(self.max_balde1, self.balde2, self.max_balde1, self.max_balde2, self)
        elif n==2:
            return State(self.balde1, self.max_balde2, self.max_balde1, self.max_balde2, self)
    
    def empty(self, n):
        if n==1:
            return State(0, self.balde2, self.max_balde1, self.max_balde2, self)
        elif n==2:
            return State(self.balde1, 0, self.max_balde1, self.max_balde2, self)
    
    def pour(self, from_balde):
        if from_balde == 1:
            if self.balde2 == self.max_balde2:
                return State(self.balde1, self.balde2, self.max_balde1, self.max_balde2, self)
            elif self.balde1 >= (self.max_balde2 - self.balde2):
                amount = self.max_balde2 - self.balde2
                return State(self.balde1 - amount, self.max_balde2, self.max_balde1, self.balde2, self)
            elif self.balde1 < (self.max_balde2 - self.balde2):
                if((self.balde2 + self.balde1) > self.max_balde2):
                    return State(0, self.max_balde2, self.max_balde1, self.max_balde2, self)
                return(0, self.balde2 + self.balde1, self.max_balde1, self.max_balde2, self)
        elif from_balde == 2:
            if self.balde1 == self.max_balde1:
                return State(self.balde1, self.balde2, self.max_balde1, self.max_balde2, self)
            elif self.balde2 >= (self.max_balde1 - self.balde1):
                amount = self.max_balde1 - self.balde1
                return State(self.max_balde1, self.balde2 - amount, self.max_balde1, self.max_balde2, self)
            elif self.balde2 < (self.max_balde1 - self.balde1):
                if (self.balde1 + self.balde2) > self.max_balde1:
                    return State(self.max_balde1, 0, self.max_balde1, self.max_balde2, self)
                return(self.balde1 + self.balde2, 0, self.max_balde1, self.max_balde2, self)
        return State(self.balde1, self.balde2, self.max_balde1, self.max_balde2, self)

    def depth(self):
        depth = 0
        state = self
        while state is not None:
            state = state.parent
            depth += 1

        return depth

    def __eq__(self, other):
        return self.balde1 == other.balde1 and self.max_balde1 == other.max_balde1 and self.balde2 == other.balde2 and self.max_balde2 == other.max_balde2
        
            