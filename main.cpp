#include <iostream>

// Definição da função 'soma'
int soma(int a, int b) {
    return a + b; // Retorna a soma dos dois números
}

int main() {
    int resultado = soma(5, 3); // Chamada da função 'soma' com 5 e 3 como argumentos
    std::cout << "O resultado da soma é: " << resultado << std::endl;
    return 0;
}
