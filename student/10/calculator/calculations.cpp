// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double power(double left, double right) {
    double result = 1;
    for ( int i = 0; i < right; ++i ) {
        result *= left;
    }
    return result;
}

double calculate(double(*action)(double, double), double dub1, double dub2) {
    return action(dub1, dub2);
}
