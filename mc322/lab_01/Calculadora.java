package com.unicamp.mc322.lab01;

import java.util.Scanner;

public class Calculadora {
    static Scanner scanner = new Scanner(System.in);

    public static double somar(double a, double b) {
        return a + b;
    }

    public static double subtrair(double a, double b) {
        return a - b;
    }

    public static double multiplicar(double a, double b) {
        return a * b;
    }

    public static double dividir(double dividendo, double divisor) {
        if(divisor == 0) {
            throw new IllegalArgumentException("Nao divida por zero!");
        }
        return (double) dividendo /(double) divisor;
    }

    public static double fatorial(double numero) {
        if(numero < 0) {
            throw new IllegalArgumentException("Nao posso calcular o fatorial de numeros negativos!");
        }

        double resultado = 1;
        while(numero > 1) {
            resultado *= numero;
            numero--;
        }

        return resultado;
    }

    public static boolean ehPrimo(double numero) {
        if(numero < 1) {
            throw new IllegalArgumentException("Se mantenha nos naturais, por favor!");
        }
        if(numero == 2) {
            return true;
        }
        if(numero % 2 == 0 || numero == 1) {
            return false;
        }

        double divisor = (int) Math.sqrt(numero);
        if(divisor % 2 == 0) {
            divisor++;
        }

        while(divisor > 1) {
            if(numero % divisor == 0) {
                return false;
            }
            divisor -= 2;
        }

        return true;
    }

    public static boolean usuarioQuerContinuar() {
        String mensagemNovaOP = "Deseja realizar outra operacao? \n" +
                                "1) Sim\n" +
                                "2) Nao\n" +
                                "Valor: ";
        System.out.print(mensagemNovaOP);
        int op = scanner.nextInt();

        while(op != 1 && op != 2) {
            System.out.print(mensagemNovaOP);
            op = scanner.nextInt();
        }

        if(op == 1)
            return true;
        return false;
    }

    public static void mostraMenu() {
        String mensagemMenu = "1) Digite 1 para somar;\n" +
        "2) Digite 2 para subtrair;\n" +
        "3) Digite 3 para multiplicar;\n" +
        "4) Digite 4 para dividir;\n" +
        "5) Digite 5 para calcular fatorial;\n" +
        "6) Digite 6 para verificar se um numero eh primo;\n" +
        "7) Qualquer outro valor para sair do programa;\n" +
        "Valor: ";
        System.out.print(mensagemMenu);
    }

    public static void main(String[] args) {
        mostraMenu();
        int operacao = scanner.nextInt();
        scanner.nextLine();

        while(operacao >= 1 && operacao <= 6) {
            double primeiroNumero = 0, segundoNumero = 0;
            System.out.print("Digite o primeiro numero: ");
            primeiroNumero = scanner.nextInt();

            if(operacao < 5) {
                System.out.print("Digite o segundo numero: ");
                segundoNumero = scanner.nextInt();
            }

            scanner.nextLine();
            double resultado;

            switch(operacao) {
                case 1:
                    resultado = somar(primeiroNumero, segundoNumero);
                    System.out.println("A soma eh: " + resultado);
                    break;
                case 2:
                    resultado = subtrair(primeiroNumero, segundoNumero);
                    System.out.println("A diferenca eh: " + resultado);
                    break;
                case 3:
                    resultado = multiplicar(primeiroNumero, segundoNumero);
                    System.out.println("O produto eh: " + resultado);
                    break;
                case 4:
                    resultado = dividir(primeiroNumero, segundoNumero);
                    System.out.println("A divisao eh: " + resultado);
                    break;
                case 5:
                    resultado = fatorial(primeiroNumero);
                    System.out.println("O fatorial de " + primeiroNumero + " eh: " + resultado);
                    break;
                case 6:
                    if(ehPrimo(primeiroNumero)) {
                        System.out.println(primeiroNumero + " eh primo");
                    } else {
                        System.out.println(primeiroNumero + " nao eh primo");
                    }
                    break;
            }

            if(usuarioQuerContinuar()) {
                mostraMenu();
                operacao = scanner.nextInt();
                scanner.nextLine();
            } else {
                operacao = -1;
            }
        }
    }
}