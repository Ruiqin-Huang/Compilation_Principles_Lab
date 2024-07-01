int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int num1 = 48;
    int num2 = 18;
    int result = gcd(num1, num2);
    println_int(result);
    return 0;
}