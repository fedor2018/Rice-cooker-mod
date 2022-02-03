
class rc_fsm():
    """ rice cooker finity state machine """
    def __init__(self):
        self.fsm_file=""
        self.state=""
        self.pan=0 # current t pan
        self.lid=0 # t lid
        self.time=0 # T
    
    def set_fsm(self):
        """ set current state """
        pass
    
    def step(self, pan=0, lid=0):
        """ """
        