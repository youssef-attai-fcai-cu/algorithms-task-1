/*
 *
 *  Author:      All code and comments are written by me, Youssef Galal Atta'i
 *  Student ID:  20200645
 *
 * */

#include <iostream>
#include <cmath>

unsigned long long max_number_length(unsigned long long &, unsigned long long &);

unsigned long long pow10(unsigned long long);

unsigned long long DivideAndConquerMultiplication(unsigned long long, unsigned long long);


int main() {
    unsigned long long x, y;

    std::cout << "-------------------------------------------------------------------------"
              << "\nLong Integer Multiplication (Using Gauss method - divide and conquer)\n"
              << "-------------------------------------------------------------------------"
              << '\n';

    std::cout << "X = ";
    std::cin >> x;

    std::cout << "Y = ";
    std::cin >> y;

    std::cout << "X * Y = "
              << DivideAndConquerMultiplication(x, y)
              << '\n';
}

unsigned long long max_number_length(unsigned long long &a, unsigned long long &b) {
//    1. Convert the numbers to strings
//    2. Get the strings lengths
//    3. Compare the lengths
//    4. Return the greater length
    return std::max(std::to_string(a).length(), std::to_string(b).length());
}

unsigned long long pow10(unsigned long long exponent) {
//    Return: 10 raised to the power of "exponent" as an "unsigned long long"
    return (unsigned long long) std::pow(10, exponent);
}

unsigned long long DivideAndConquerMultiplication(unsigned long long x, unsigned long long y) {
//    Get the greatest length between the two numbers.
    unsigned long long N = max_number_length(x, y);

//    If the greatest length is 1, then the other has to also be of length 1.
//    So, we just return the product of those two simple digits.
    if (N == 1) { return x * y; }

//    Otherwise, Split each number in to halves.
    unsigned long long xL = x / pow10(N / 2);
    unsigned long long xR = x % pow10(N / 2);
    unsigned long long yL = y / pow10(N / 2);
    unsigned long long yR = y % pow10(N / 2);

//  Basic math.
//  e.g.  X * Y = (Xl + Xr) * (Yl * Yr) = (Xl * Yl) + (Xr * Yl + Xl * Yr) + (Xr * Yr)
    unsigned long long P1 = DivideAndConquerMultiplication(xL, yL);
    unsigned long long P2 = DivideAndConquerMultiplication(xR, yR);
//       (Xl + Xr) * (Yl + Yr) = (Xr * Yl + Xl * Yr)  + (Xl * Yl) + (Xr * Yr)
//       (Xr * Yl + Xl * Yr)   = (Xl + Xr) * (Yl + Yr)  - (Xl * Yl) - (Xr * Yr)
//  So,  X * Y = (Xl + Xr) * (Yl * Yr) = (Xl * Yl) + [(Xl + Xr) * (Yl + Yr)  - (Xl * Yl) - (Xr * Yr)] + (Xr * Yr)
    unsigned long long P3 = DivideAndConquerMultiplication(xL + xR, yL + yR);

//  Typical off-by-one error when the input size is odd in a divide and conquer solution.
    if (N % 2 == 0) {
        return P1 * pow10(N) + (P3 - P1 - P2) * pow10(N / 2) + P2;
    } else {
//      The 1 is the remainder after splitting each number into two halves
//      e.g.        4 -> 2 & 2
//             but, 5 -> 2 & 2 & 1
//             This 1 is why we add -1 to the exponent when the input size is odd.
        return P1 * pow10(N - 1) + (P3 - P1 - P2) * pow10(N / 2) + P2;
    }

}
