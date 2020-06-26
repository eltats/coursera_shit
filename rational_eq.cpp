#include <iostream>
using namespace std;

int eu(int a, int b) {
    int n = a, m = b, c = 0;
    while (m != 0) {
        c = n % m;
        n = m;
        m = c;
    }
    return n;
}

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        int d = eu(numerator, denominator);
        if (denominator / d < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        p = numerator / d;
        q = denominator / d;
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int p;
    int q;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
    const int gcd = eu(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return (lhs.Numerator() * l) == (rhs.Numerator() *r);
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    const int gcd = eu(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return Rational((lhs.Numerator() * l) + (rhs.Numerator() *r), n);
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    const int gcd = eu(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return Rational((lhs.Numerator() * l) - (rhs.Numerator() *r), n);
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}