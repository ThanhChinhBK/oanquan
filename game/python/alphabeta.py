import time

MAX_MOVES = [7,8,9,10,11]
MIN_MOVES = [1,2,3,4,5]
QUAN = [0,6]
DO_SAU = 8

def In(s):
  print "+---------------------------+"
  print "|   |%3d|%3d|%3d|%3d|%3d|   |"%(s[1],s[2],s[3],s[4],s[5])
  print "|%3d|-------------------|%3d|"%(s[0],s[6])
  print "|   |%3d|%3d|%3d|%3d|%3d|   |"%(s[11],s[10],s[9],s[8],s[7])
  print "+---------------------------+"

class Node(object):

  def __init__(self,s,player="MAX",max_scored=0,min_scored=0,path =[]):
    self.s = s
    self.player = player
    self.max_scored = max_scored
    self.min_scored = min_scored
    self.path = path
    
  def move(self,a):
    s = self.s
    chieu = 1 if a[1] == "right" else -1
    vitri = a[0]
    
    diem = 0
    soluong = s[vitri]       
    
    s[vitri] = 0
    matluot = True
        
    while (matluot):
      vitri+=chieu
      vitri%=12
      soluong-=1
      s[vitri]+=1    

      if soluong == 0:
        vitri_ke = (vitri+chieu)%12
        vitri_keke = (vitri_ke+chieu)%12

        if ((vitri_ke in QUAN) or
          (s[vitri_ke] == 0 and s[vitri_keke] == 0)):
          #In(s)
          print "***MAT LUOT (Gap O QUAN hoac 2 O TRONG)"
          
          matluot = False
          break
                       
        if (s[vitri_ke] == 0 and s[vitri_keke] > 0):                    
          diem += s[vitri_keke]
          s[vitri_keke] = 0
          vitri = vitri_keke
          print "***AN QUAN", (vitri,a[1])
          In(s)
          print "-"*30
          if s[(vitri+chieu)%12] > 0:
            #In(s)
            print "***MAT LUOT (Sau khi an, O tiep theo co quan)"
            matluot = False
            break
          #return "**MAT LUOT", s, diem                    
        elif (s[vitri_ke] > 0):
          soluong = s[vitri_ke]
          s[vitri_ke] = 0
          vitri = vitri_ke                    
          print "***BOC TIEP", (vitri,a[1])
          In(s)
          print "-"*35
    In(s)
    print "~"*50
    return "KET THUC LUOT DI", s, diem
    
def moveIter(state,a):
  s = [e for e in state.s] # Sao chep trang thai ban dau
  chieu = 1 if a[1] == "right" else -1
  vitri = a[0]
        
  diem = 0
  soluong = s[vitri]       
  
  s[vitri] = 0
  matluot = False
        
  while not(matluot):         

    if soluong > 0:
      vitri+=chieu
      vitri%=12
      soluong-=1
      s[vitri]+=1                
      
    if soluong == 0:
      vitri_ke = (vitri+chieu)%12
      vitri_keke = (vitri_ke+chieu)%12

      if ((vitri_ke in QUAN) or
          (s[vitri_ke] == 0 and s[vitri_keke] == 0)):
        matluot = True
        break
                              
      if (s[vitri_ke] == 0 and s[vitri_keke] > 0):                    
        diem += s[vitri_keke]
        s[vitri_keke] = 0
        vitri = vitri_keke
        #print "***AN QUAN", (vitri,a[1])
        #In(s)
        #print "-"*30
        if s[(vitri+chieu)%12] > 0:
        
          matluot = True
          break
          
      elif (s[vitri_ke] > 0):
        soluong = s[vitri_ke]
        s[vitri_ke] = 0
        vitri = vitri_ke                    
        #print "***BOC TIEP", (vitri,a[1])
        #(s)
        #print "-"*35
                    
            
        #In(self.s)
  #In(s)
  #print "~"*50
  return "KET THUC LUOT DI", s, diem
        
def less(x,y):
  if x == "-INF": return True
  else:
    if y == "+INF": return True
    if y == "-INF": return False
    #bo sung
    if x == "+INF": return False
  return x <= y


def Test():
  print less(3,4)
  print less(4,3)
  
  print less(3,"-INF")
  print less(3,"+INF")
  
  print less("-INF",3)
  print less("-INF","-INF")
  print less("-INF","+INF")
    
  print less("+INF","+INF")
  print less("+INF","-INF")
  print less("+INF",3)

#Test()

def Max(x,y):
  if less(x,y): return y
  return x

def Min(x,y):
  if less(x,y): return x
  return y

### (vitri, huongdi): (8,'left')..
def Actions(state):
  actions = []
  if state.player is "MAX":
    actions = [p for p in MAX_MOVES if state.s[p] > 0]
  elif state.player is "MIN":
    actions = [p for p in MIN_MOVES if state.s[p] > 0]

  final = []
  for a in actions:
    final.append( (a,"left") )
    final.append( (a,"right"))
  return final

### New Node
def Result(state,a):
  #print moveIter(state,a)
  status, s, diem = moveIter(state,a)
  player = "MIN" if state.player == "MAX" else "MAX"
  path = state.path + [a]
  if state.player == "MAX":
    return Node(s,player,state.max_scored + diem,state.min_scored,path)
  else:
    return Node(s,player,state.max_scored,state.min_scored + diem,path)
    
TRACK = {}    
def CutoffTest(state,d):
  return (state.s[0] == 0 and state.s[6] == 0) or d >= DO_SAU

def Eval(state):
  max_eval = sum(state.s[7:12])
  min_eval = sum(state.s[1:6])
  value = 0
  if state.player == "MAX":        
    value = max_eval - min_eval + state.max_scored - state.min_scored       
  else:
    value = min_eval - max_eval + state.min_scored - state.max_scored    
  # dung track la list
  #val_path = [value] + state.path
  #TRACK.append(val_path)

  # Dung track la dictionary

  if value not in TRACK.keys(): TRACK[value] = state.path
  #print TRACK
  return value

def AlphaBetaSearch(state):
  start = time.clock()
  v = MaxValue(state,"-INF","+INF",0)
  run_time = time.clock() - start
  return "(*)",v, run_time

def MaxValue(state,alpha,beta,d):
  #print "Goi: Max({0},{1},{2},{3})".format(state,alpha,beta,d)
  if CutoffTest(state,d): return Eval(state)
  v = "-INF"
  for a in Actions(state):
    #print "- Tu trang thai: ", state.s
    #In(state.s)
    #print "-> HANH DONG cua MAX:", a
    #free = raw_input()
    #print
    #print "->Max(...,Min{0})".format(a)
    v = Max(v, MinValue(Result(state,a),alpha,beta,d+1) )        
    if less(beta, v): return v        
    alpha = Max(alpha,v)
  return v

def MinValue(state,alpha,beta,d):
  #print "Goi: Min({0},{1},{2},{3})".format(state,alpha,beta,d)
  if CutoffTest(state,d): return Eval(state)
  v = "+INF"
  for a in Actions(state):
    #print "- Tu trang thai: ", state.s
    #In(state.s)
    #print "-> HANH DONG cua MIN:", a
    #free = raw_input()
    #print
    #print "->Min(...,Max{0})".format(a)
    v = Min(v,MaxValue(Result(state,a),alpha,beta,d+1))
    if less(v, alpha): return v        
    beta = Min(beta,v)
  return v
