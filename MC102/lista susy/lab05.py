t=int(input())
c=int(input())

s=[int(x) for x in input().split()]

soma=0
ts=0

for x in range(0, t):
    soma=soma+s[x]
    ts+=1
    if(soma>=c):
        break
    
if(soma>=c):
    print("sim")
    print(ts)
else:
    print("nao")
    print(t+1)
