'''
Entrada: Lista, Numero
Saida: True, False, Lista
O programa eh um arquivo auxiliar que recebe um par de conjuntos ou
um conjunto e um valor para realizar operacoes entre conjuntos. O arquivo
principal chama uma funcao do arquivo auxiliar que realiza operacao x, e
retorna o valor da respectiva operacao.
'''
#!/usr/bin/env python3

# Funcao: pertence
#
# Parametros:
#   conj: vetor contendo o conjunto de entrada
#    num: elemento a ser verificado pertinencia
#
# Retorno:
#   True se num pertence a conj e False caso contrario
#
def pertence(conj, num):
    if(num not in conj):
        return False
    return True
# Funcao: contido
#
# Parametros:
#   conj1: vetor contendo um conjunto de entrada
#   conj2: vetor contendo um conjunto de entrada
#
# Retorno:
#   True se conj1 esta contido em conj2 e False caso contrario
#
def contido(conj1, conj2):
    for i in conj1:
        if(i not in conj2):
            return False
    return True

# Funcoes: adicao e subtracao
#
# Parametros:
#   conj: vetor contendo o conjunto que tera incluso ou removido o elemento
#    num: elemento a ser adicionado ou removido
#
def adicao(conj, num):
    if(num not in conj):
        conj.append(num)
    return conj

def subtracao(conj, num):
    if(num in conj):
        conj.remove(num)
    return conj

# Funcoes: uniao, intersecao e diferenca
#
# Parametros:
#     conj1: vetor contendo o conjunto de entrada do primeiro operando
#     conj2: vetor contendo o conjunto de entrada do segundo operando
#
# Retorno:
#   Vetor contendo o conjunto de saida/resultado da operacao
#
def uniao(conj1, conj2):
    temp=conj1.copy()
    for i in conj2:
        if(i not in temp):
            temp.append(i)
    return temp

def intersecao(conj1, conj2):
    temp=[]
    for i in conj1:
        if(i in conj2):
            temp.append(i)
    return temp

def diferenca(conj1, conj2):
    temp=[]
    for i in conj1:
        if(i not in conj2):
            temp.append(i)
    return temp

def uniao_disjunta(conj1, conj2):
    temp=[]
    for i in conj1:
        if(i not in conj2):
            temp.append(i)
    for i in conj2:
        if(i not in conj1):
            temp.append(i)
    return temp
