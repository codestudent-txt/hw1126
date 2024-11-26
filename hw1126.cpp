#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Term 表示單項式
struct Term {
    int coefficient; 
    int exponent;    
};

// Polynomial的定義
class Polynomial {//封裝 Polynomial
private:
    vector<Term> terms; 

public:
    // 輸入 >> 時的操作
    friend istream& operator>>(istream& in, Polynomial& poly) {
        int n; 
        cout << "input the number of terms: ";
        in >> n;
        poly.terms.clear();//清空數值
        for (int i = 0; i < n; ++i) {
            Term term;
            cout << "input coefficient and exponent for term " << i + 1 << ": ";
            in >> term.coefficient >> term.exponent;
            poly.terms.push_back(term);
        }
        return in;
    }

    // 輸入 << 時的操作
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        for (size_t i = 0; i < poly.terms.size(); ++i) {
            const Term& term = poly.terms[i];
            if (i > 0 && term.coefficient > 0) out << " + ";//確定正負並輸出
            if (term.coefficient < 0) out << " - ";
            out << abs(term.coefficient);
            if (term.exponent != 0) out << "x^" << term.exponent;
        }
        return out;
    }

    // 相加的操作
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        size_t i = 0, j = 0;//定義i j來跑terms 和另一項

        while (i < terms.size() && j < other.terms.size()) {
            if (terms[i].exponent > other.terms[j].exponent) {
                result.terms.push_back(terms[i++]);
            } else if (terms[i].exponent < other.terms[j].exponent) {
                result.terms.push_back(other.terms[j++]);
            } else {
                int coeff = terms[i].coefficient + other.terms[j].coefficient;
                if (coeff != 0) {
                    result.terms.push_back({coeff, terms[i].exponent});
                }
                ++i;
                ++j;
            }
        }

        while (i < terms.size()) result.terms.push_back(terms[i++]);
        while (j < other.terms.size()) result.terms.push_back(other.terms[j++]);

        return result;
    }
};

int main() {
    Polynomial p1, p2, p3;

    cout << "Enter the first polynomial:" << endl;
    cin >> p1;

    cout << "Enter the second polynomial:" << endl;
    cin >> p2;

    p3 = p1 + p2;

    cout << "The first polynomial is: " << p1 << endl;
    cout << "The second polynomial is: " << p2 << endl;
    cout << "The sum of the two polynomials is: " << p3 << endl;

    return 0;
}
