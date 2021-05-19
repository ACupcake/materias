package com.unicamp.mc322.lab01;

public class Algorithm {
    public static void main(String[] args) {
        int quantity = 10;
        int[] vector = new int[quantity];

        //Como usamos o sinal de estritamente menor '<'
        //não precisamos subtrair -1 do tamanho do vetor
        //a menos que ter um elemento iniciado como zero
        //seja proposital
        for (int i = 0; i < vector.length; i++) {
            vector[i] = (int) (Math.random()*100);
        }

        sort(vector);

        //O i do loop for estava começando de 1, assim,
        //não mostrando o primeiro elemento
        for (int i = 0; i < vector.length; i++) {
            System.out.println(vector[i]);
        }

    }

    private static void sort(int[] vector){
        boolean switched = true;
        int aux;
        while (switched) {
            switched = false;
            //O for estava verificando elementos fora do
            //limite do vetor com vector.length + 1
            for (int i = 0; i < vector.length-1; i++) {
                if (vector[i] > vector[i + 1]) {
                    aux = vector[i];
                    vector[i] = vector[i + 1];
                    //estava trocando o elemento errado
                    //deveria ser i+1 não i-1
                    vector[i + 1] = aux;
                    //deveria alterar o switched para true
                    //para repetir o loop do insertion sort
                    switched = true;
                }
            }
        }
    }
}
