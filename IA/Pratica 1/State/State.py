from configparser import NoOptionError


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
                amount = self.max_balde2 - self.balde1
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
                if(self.balde1 + self.balde2) > self.max_balde1
            