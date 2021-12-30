/*
NAME: Talike Bennett
PROJECT: Polynomial Operations
FILE: PO_polyclass.hpp
*/

#ifndef POLY_CLASS
#define POLY_CLASS

#include <iostream>
#include <cmath> // Needed for pow()
using namespace std;

template <typename T>
class Polynomial {

    // Order:       n
    // Coefficents: {c_1, c_2, c_3, ..., c_n+1}
    // Indices:      [0]  [1]  [2]  ...  [n]
    // Power:         0    1    2   ...   n
    // Coeff. Num.:  n+1   n   n-1  ...   1
    // Print:       (c_n+1)x^n + (c_n)x^(n-1) + ... + (c_2)x + c_1

    public:

        Polynomial(); // Default constructor
        Polynomial(int order, T defaultCoeff = 0); // Constructor; accepts order and initializes coefficient(s) with defaultCoeff
        Polynomial(int order, T* coefficients); // Constructor; accepts order and address to array of numbers
        Polynomial(const Polynomial<T>& rhs); // Copy constructor
        Polynomial<T>& operator=(const Polynomial<T>& rhs); // Copy assignment operator
        ~Polynomial() { delete[] coefficients; } // Destructor
        template <typename TT> friend ostream& operator<<(ostream& out, const Polynomial<TT>& rhs); // Overloaded << operator

        // Setters and getters
        void SetValues(int order, T* coefficients); // Input coefficients via external array
        int GetOrder() const { return this->order; } // Returns order of polynomial
        int* GetCoefficients() const { return this->coefficients; } // Returns pointer to coefficients array

        // Overloaded operators
        template <typename TT> friend Polynomial<TT> operator+(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs); // Polynomial addition
        template <typename TT> friend Polynomial<TT> operator-(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs); // Polynomial subtraction
        template <typename TT> friend Polynomial<TT> operator*(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs); // Polynomial multiplication
        template <typename TT> friend Polynomial<TT> operator*(const Polynomial<TT>& lhs, const TT rhs); // Scale a polynomial (P2 = P1 * scale)
        template <typename TT> friend Polynomial<TT> operator*(const TT lhs, const Polynomial<TT>& rhs); // Scale a polynomial (P2 = scale * P1)
        template <typename TT> friend bool operator==(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs); // Equality operator
        T operator[](int i) const; // Return the i-th coefficient (int value = P[i])
        T& operator[](int i); // Return the i-th coefficient (P[i] = int value)
        T operator()(T x); // Evaluate P(x) accordingly

        // NOTE: I had trouble defining operator+(), operator-(), and operator*() for Polynomials of different types.

    private:

        int order;
        T* coefficients;
        int NumCheck(T* array, int size) const;

};

template <typename T>
int Polynomial<T>::NumCheck(T* numArray, int size) const {

    for(int i = size - 1; i >= 0; i--) {
        
        if(i == 0 && numArray[i] != 0) return 2; // Only last coefficient is non-zero
        if(numArray[i] != 0) return 3; // Some or all coefficients are non-zero

    }

    return 1; // All coefficients are 0

}

template <typename T>
Polynomial<T>::Polynomial() { // Default constructor

    order = 0;
    coefficients = new T[order + 1];
    coefficients[order] = 1;

}

template <typename T>
Polynomial<T>::Polynomial(int order, T defaultCoeff) { // Constructor; accepts order and initializes coefficient(s) with defaultCoeff

    this->order = order;
    coefficients = new T[order + 1];
    for(int i = 0; i <= this->order; i++) coefficients[i] = defaultCoeff;

}

template <typename T>
Polynomial<T>::Polynomial(int order, T* coefficients) { // Constructor; accepts order and address to array of numbers

    this->order = order;
    this->coefficients = new T[order + 1];
    for(int i = 0; i <= this->order; i++) this->coefficients[i] = coefficients[i];

}

template <typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& rhs) { // Copy constructor

    this->order = rhs.order;
    this->coefficients = new T[this->order + 1];
    for(int i = 0; i <= this->order; i++) this->coefficients[i] = rhs.coefficients[i];

}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& rhs) { // Copy assignment operator

    if(this != &rhs) {

        delete[] this->coefficients;
        this->order = rhs.order;
        this->coefficients = new T[order + 1];
        for(int i = 0; i <= this->order; i++) this->coefficients[i] = rhs.coefficients[i];

    }

    return *this;

}

template <typename TT>
ostream& operator<<(ostream& out, const Polynomial<TT>& rhs) { // Overloaded << operator

    switch(rhs.NumCheck(rhs.coefficients, rhs.order + 1)) {

        case 1: // All coefficients are 0
        out << 0;
        break;

        case 2: // Only last coefficient is non-zero
        out << rhs.coefficients[0];
        break;

        case 3: // Some or all coefficients are non-zero
        for(int i = rhs.order; i >= 0; i--) { // The terms are printed out from highest power to lowest power.

            if(rhs.coefficients[i] == 0) continue; // Terms with a coefficient of 0 will not be printed.

            if(i == 0) { // The 0-power term will just print the constant.

                if(rhs.coefficients[i] > 0) out << " + ";
                else out << " - ";
                out << abs(rhs.coefficients[i]);

            } else if(i == 1) { // The 1-power term will print out the coefficient and x.

                if(rhs.coefficients[i] > 0) out << " + ";
                else out << " - ";

                if(abs(rhs.coefficients[i]) != 1) out << abs(rhs.coefficients[i]); // If the coefficient is 1 or -1, only x will be printed.
                out << "x";

            } else if(i == rhs.order) { // The term with the highest exponent will print normally.

                if(abs(rhs.coefficients[i]) != 1) out << rhs.coefficients[i]; // If the coefficient is 1 or -1, only x will be printed.
                if(rhs.coefficients[i] == -1) out << "-";
                out << "x^" << i;

            } else { // All other powers will print the coefficient, x, and the corresponding exponent. 

                if(rhs.coefficients[i] > 0) out << " + ";
                else out << " - ";
                    
                if(abs(rhs.coefficients[i]) != 1) out << abs(rhs.coefficients[i]); // If the coefficient is 1 or -1, only x will be printed.
                out << "x^" << i;

            }

        }

        break;

    }

    return out;

}

template <typename T>
void Polynomial<T>::SetValues(int order, T* coefficients) { // Input coefficients via external array

    delete[] this->coefficients;
    this->order = order;
    this->coefficients = new T[order + 1];
    for(int i = 0; i <= this->order; i++) this->coefficients[i] = coefficients[i];

}

template <typename TT>
Polynomial<TT> operator+(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs) { // Polynomial addition

    int order;
    (lhs.order >= rhs.order) ? order = lhs.order : order = rhs.order; // The greater order will be the order of the resultant polynomial

    TT* temp_coeff1 = new TT[order + 1];
    TT* temp_coeff2 = new TT[order + 1];
    TT* temp_coeff3 = new TT[order + 1];

    for(int i = 0; i <= order; i++) { temp_coeff1[i] = 0; temp_coeff2[i] = 0; } // Initializes arrays with 0 to avoid garbage values
    for(int i = 0; i <= lhs.order; i++) { temp_coeff1[i] = lhs.coefficients[i]; } // Copies coefficients of lhs to temp_coeff1
    for(int i = 0; i <= rhs.order; i++) { temp_coeff2[i] = rhs.coefficients[i]; } // Copies coefficients of rhs to temp_coeff2

    for(int i = 0; i <= order; i++) { temp_coeff3[i] = temp_coeff1[i] + temp_coeff2[i]; } // Inserts coefficient sums in temp_coeff3

    Polynomial<TT> temp(order, temp_coeff3);
    delete[] temp_coeff1;
    delete[] temp_coeff2;
    delete[] temp_coeff3;

    return temp;

}

template <typename TT>
Polynomial<TT> operator-(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs) { // Polynomial subtraction

    int order;
    (lhs.order >= rhs.order) ? order = lhs.order : order = rhs.order;

    TT* temp_coeff1 = new TT[order + 1];
    TT* temp_coeff2 = new TT[order + 1];
    TT* temp_coeff3 = new TT[order + 1];

    for(int i = 0; i <= order; i++) { temp_coeff1[i] = 0; temp_coeff2[i] = 0; }
    for(int i = 0; i <= lhs.order; i++) { temp_coeff1[i] = lhs.coefficients[i]; }
    for(int i = 0; i <= rhs.order; i++) { temp_coeff2[i] = rhs.coefficients[i]; }

    for(int i = 0; i <= order; i++) { temp_coeff3[i] = temp_coeff1[i] - temp_coeff2[i]; }

    Polynomial<TT> temp(order, temp_coeff3);
    delete[] temp_coeff1;
    delete[] temp_coeff2;
    delete[] temp_coeff3;

    return temp;

}

template <typename TT>
Polynomial<TT> operator*(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs) { // Polynomial multiplication

    // The order of the resultant polynomial will always be the sum of the orders of the
    // polynomials that are being multiplied, hence product.order = lhs.order + rhs.order

    Polynomial<TT> product(lhs.order + rhs.order); // Creates a polynomial with 0s as coefficients

    for(int i = 0; i <= lhs.order; i++) { // Multiplies every coefficient of lhs with every coefficient of rhs

        for(int j = 0; j <= rhs.order; j++) { 
            
            // The power of the resultant coefficient will always be the sum of the powers of
            // the coefficients that are being multiplied, hence:
            product.coefficients[i + j] += lhs.coefficients[i] * rhs.coefficients[j];

        }

    }
        
    return product; 

}

template <typename TT>
Polynomial<TT> operator*(const Polynomial<TT>& lhs, const TT rhs) { // Scale a polynomial (P2 = P1 * scale)

    int order = lhs.order;
    TT* temp_coeff = new TT[order + 1];
    for(int i = 0; i <= order; i++) { temp_coeff[i] = lhs.coefficients[i] * rhs; }

    Polynomial<TT> temp(order, temp_coeff);
    delete[] temp_coeff;

    return temp;

}

template <typename TT>
Polynomial<TT> operator*(const TT lhs, const Polynomial<TT>& rhs) { // Scale a polynomial (P2 = scale * P1)

    int order = rhs.order;
    TT* temp_coeff = new TT[order + 1];
    for(int i = 0; i <= order; i++) { temp_coeff[i] = rhs.coefficients[i] * lhs; }

    Polynomial<TT> temp(order, temp_coeff);
    delete[] temp_coeff;

    return temp;
  
} 

template <typename TT>
bool operator==(const Polynomial<TT>& lhs, const Polynomial<TT>& rhs) { // Equality operator

    if(lhs.order != rhs.order) return false;

    int i = 0;

    while(i <= lhs.order || i <= rhs.order) {

        if(lhs.coefficients[i] != rhs.coefficients[i]) return false;
        i++;

    }

    return true;

}

template <typename T>
T Polynomial<T>::operator[](int i) const { // Return the i-th coefficient (int value = P[i])

    if(i <= 0 || i > this->order + 1) throw i; // Handles cases where requested coefficient is out of range
    return this->coefficients[(this->order + 1) - i]; // Reads the coefficients starting at the back of the array.

}

template <typename T>
T& Polynomial<T>::operator[](int i) { // Return the i-th coefficient (P[i] = int value)

    if(i <= 0 || i > this->order + 1) throw i; // Handles cases where requested coefficient is out of range
    return this->coefficients[(this->order + 1) - i]; // Reads the coefficients starting at the back of the array.

}

template <typename T>
T Polynomial<T>::operator()(T x) { // Evaluate P(x) accordingly

    T answer = 0;
    for(int i = this->order; i >= 0; i--) answer += this->coefficients[i] * pow(x, i);

    return answer;

}

#endif 