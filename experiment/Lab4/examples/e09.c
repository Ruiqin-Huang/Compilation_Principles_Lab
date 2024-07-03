int gcd(int a, int b) {
    println_int(a);
    println_int(b);
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int num1 =7;
    int num2 =13;
    int result = gcd(num1, num2);
    println_int(result);
    return 0;
}
