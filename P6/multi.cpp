

/**
 * @file multi.cpp
 * @brief This program implements operations in the finite field GF(2^16), including binary multiplication, binary exponentiation, and the search for the multiplicative inverse. Additionally, it allows generating a list of multiplicative inverses for each non-zero element in GF(2^16).
 * @version 1.0
 * @date 2023-10-01
 * 
 * Program developed by Alan Cervantes as part of the practice 6 of the course "Selected Topics in Cryptography" at the Superior School of Computing of the National Polytechnic Institute.
 */
/**
 * @file multi.cpp
 * @brief Este programa implementa operaciones en el campo finito GF(2^16), incluyendo multiplicación binaria, exponenciación binaria y la búsqueda del inverso multiplicativo. Además, permite generar una lista de inversos multiplicativos para cada elemento no nulo en GF(2^16).
 * @version 1.0
 * @date 2023-10-01
 * 
 * Programa desarrollado por Alan Cervantes como parte de la práctica 6 de la materia "Temas selectos de criptografía" de la Escuela Superior de Cómputo del Instituto Politécnico Nacional.
 */
#include <iostream>
#include <inttypes.h>
#include <fstream>

using namespace std;

// Function to perform binary multiplication in GF(2^16)
uint32_t gmul(uint32_t a, uint32_t b) {
    uint32_t p = 0;
    while (a != 0 && b != 0) {
        // If the least significant bit of b is 1, add a to p
        if (b & 1)
            p ^= a;
        // If the most significant bit of a is 1, shift a left and reduce by the irreducible polynomial x16 + x5 + x3 + x + 1
        if (a & 0x8000)
            a = (a << 1) ^ 0x2b;
        else
            a <<= 1; // Otherwise, just shift a left
        b >>= 1; // Shift b right

        // Print binary representation of a, b, and p
        // cout << "a: " << bitset<17>(a) << "\n";
        // cout << "b: " << bitset<17>(b) << "\n";
        // cout << "p: " << bitset<17>(p) << "\n";
    }
    return p & 0xFFFF;
}

// Function to perform binary exponentiation in GF(2^16)
uint16_t gpow(uint16_t a, uint16_t b) {
    uint16_t result = 1;
    while (b > 0) {
        // If the least significant bit of b is 1, multiply result by a
        if (b & 1)
            result = gmul(result, a);
        a = gmul(a, a); // Square a
        b >>= 1; // Shift b right
    }
    return result;
}

// Function to find the multiplicative inverse of a in GF(2^16)
uint16_t find_multiplicative_inverse(uint16_t a) {
    // Return a^(2^16 - 2) as the multiplicative inverse of a
    return gpow(a, 0x10000 - 2);
}

// Function to generate a list of multiplicative inverses
void generate_inverse_list() {
    ofstream myfile;
    myfile.open ("multiplicative_inverses.txt");

    // For each non-zero element in GF(2^16)
    for (uint32_t a = 1; a < 0x10000+1; ++a) {
        // Find its multiplicative inverse
        uint32_t b = find_multiplicative_inverse(a);
        // If the multiplicative inverse exists, write it to the file
        if (b != 0)
            myfile << a << " " << b << "\n";
        else
            myfile << a << " " << "N/A\n"; // Otherwise, write "N/A"
    }

    myfile.close();
    cout << "List of multiplicative inverses generated in 'multiplicative_inverses.txt'\n";
}

// Main function
int main() {
    int choice;
    uint32_t f, g, p;

    do {
        cout << "Menu:\n";
        cout << "1. Multiply two numbers in GF(2^16)\n";
        cout << "2. Generate list of multiplicative inverses\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter two numbers to multiply: ";
                cin >> f >> g;
                cout << "✅ The product is: " << gmul(f, g) << " bin: " <<  bitset<16>(p) << "\n";
                break;
            case 2:
                generate_inverse_list();
                cout << "Cool 🧑🏻‍💻 \n";
                break;
            case 3:
                cout << "👋🏻 Exiting the program.\n";
                break;
            default:
                cout << "❌ Invalid choice. Please enter 1, 2, or 3.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}