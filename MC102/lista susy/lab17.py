#!/usr/bin/env python3

import math

# Laboratorio 15 - Banco de Dados Geografico

'''
Arquivo auxiliar de funcoes para um mapa plano

Valores de entrada:
-lista de cidades
-cidade de referencia
-raio
-cep

Valores de saida:
-lista de cidades no raio em relacao a cidade de referencia
-mediana da populacao no raio em relacao a cidade de referencia
-cidade x se cep pertence a um intervalo de cep
-populacao total  no raio em relacao a cidade de referencia
'''
class Ponto:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Cidade:
    def __init__(self, coordenadas, inicioCEP, fimCEP, numHabitantes):
        self.coordenadas = coordenadas
        self.inicioCEP = inicioCEP
        self.fimCEP = fimCEP
        self.numHabitantes = numHabitantes

#
# Funcao: distancia
#
# Parametros:
#   a, b: pontos
#
# Retorno:
#   A distancia euclidiana entre a e b.
#
def distancia(c1, c2):
    return int(100 * math.sqrt((c1.x - c2.x)**2 + (c1.y - c2.y)**2)) / 100.0

# Funcao: consulta_cidade_por_cep
#
# Parametros:
#   cidades: lista de cidades (base de dados) 
#       cep: CEP desejado 
# 
# Retorno:
#   O indice da cidade que contem o CEP desejado ou None caso não haja tal cidade.   
#
def consulta_cidade_por_cep(cidades, cep):
    #verifica se a variavel cep esta dentro do intervalo [inicioCEP, fimCep]
    for i in range(len(cidades)):
        if(cidades[i].inicioCEP<=cep and cidades[i].fimCEP>=cep):
            return i
    return None

# Funcao: consulta_cidades_por_raio
#
# Parametros:
#            cidades: lista de cidades (base de dados) 
#   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
#               raio: raio da busca
#
# Retorno:
#   Lista dos indices das cidades que estao contidas no raio de busca (incluindo
#   a cidade referencia) *ordenados pelas respectivas distancias da cidade referencia*.
#
def consulta_cidades_por_raio(cidades, cidadeReferencia, raio):
    cidade_r=[]
    #adiciona cidades dentro do raio em na lista cidade_r
    for i in range(len(cidades)):
        if(distancia(cidades[i].coordenadas, cidades[cidadeReferencia].coordenadas)<=raio):
            cidade_r.append(i)
    #coloca em ordem de distancia, se cidade i < cidade j sao trocadas as posicoes
    for i in range(len(cidade_r)):
        for j in range(len(cidade_r)):
            if(distancia(cidades[cidade_r[i]].coordenadas, cidades[cidadeReferencia].coordenadas)<distancia(cidades[cidade_r[j]].coordenadas, cidades[cidadeReferencia].coordenadas)):
                aux=cidade_r[i]
                cidade_r[i]=cidade_r[j]
                cidade_r[j]=aux
    return cidade_r

# Funcao: populacao_total
#
# Parametros:
#            cidades: lista de cidades (base de dados) 
#   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
#               raio: raio da busca
#          
# Retorno:
#   O numero de habitantes das cidades que estao contidas no raio de busca
#
def populacao_total(cidades, cidadeReferencia, raio):
    total=0
    #se a cidade i estiver dentro do raio, eh somado seu numero de habitantes ao total
    for i in range(len(cidades)):
        if(distancia(cidades[i].coordenadas, cidades[cidadeReferencia].coordenadas)<=raio):
            total+=cidades[i].numHabitantes
    return total

# Funcao: mediana_da_populacao
#
# Parametros:
#            cidades: lista de cidades (base de dados) 
#   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
#               raio: raio da busca
#
# Retorno:
#   Mediana do numero de habitantes das cidades que estao contidas no raio de busca
#
def mediana_da_populacao(cidades, cidadeReferencia, raio):
    list_med=[]
    #coloca todas as cidades dentro do raio na lista list_med
    for i in range (len(cidades)):
        if(distancia(cidades[cidadeReferencia].coordenadas, cidades[i].coordenadas)<=raio):
            list_med.append(cidades[i].numHabitantes)
    #ordena list_med
    list_med.sort()
    #verifica se numero de elementos eh impar, par ou unico e retorna como especificado.
    if(len(list_med)==1):
        return list_med[0]
    arredonda=math.ceil(len(list_med)/2)
    if(len(list_med)%2!=0):
        return list_med[arredonda-1]
    return (list_med[arredonda]+list_med[arredonda-1])/2
