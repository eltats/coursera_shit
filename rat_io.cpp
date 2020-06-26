#include <iostream>
#include <sstream>
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

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

ostream& operator << (ostream& out, const Rational& rational) {
    out << rational.Numerator() << '/'  << rational.Denominator();
    return out;
}

istream& operator >> (istream& stream, Rational& r) {
    int p, q;
    if (stream >> p && stream.ignore(1) && stream >> q) {
        r = { p, q };
    }
    return stream;
}


int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }
    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}