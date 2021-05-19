#Recebe as entradas
vi=int(input())
xi=int(input())
yi=int(input())
xf=int(input())
yf=int(input())
t=int(input())

#calcula a distancia e o preco
d=((xf-xi)+(yf-yi))
v=(vi+d*t)

#imprime o preco
print(v)
