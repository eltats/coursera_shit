#include <iostream>
#include <sstream>

using namespace std;


int GreatestCommonDivisor(int a, int b) {
    int n = a, m = b, c = 0;
    while (m != 0) {
        c = n % m;
        n = m;
        m = c;
    }
    return n;
    // cout << n << endl;
}

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        const int gcd = GreatestCommonDivisor(numerator, denominator);
        if (denominator / gcd < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        p = numerator / gcd;
        q = denominator / gcd;
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
    const int gcd = GreatestCommonDivisor(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return (lhs.Numerator() * l) == (rhs.Numerator() *r);
}

bool operator < (const Rational& lhs, const Rational& rhs) {
    const int gcd = GreatestCommonDivisor(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return (lhs.Numerator() * l) < (rhs.Numerator() *r);
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    const int gcd = GreatestCommonDivisor(lhs.Denominator(), rhs.Denominator());
    int n = (lhs.Denominator() * rhs.Denominator()) / gcd;
    int l = n / lhs.Denominator();
    int r = n / rhs.Denominator();
    return Rational((lhs.Numerator() * l) + (rhs.Numerator() *r), n);
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    const int gcd = GreatestCommonDivisor(lhs.Denominator(), rhs.Denominator());
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
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}