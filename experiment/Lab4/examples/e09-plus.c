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
    int num1 = 7;
    int num2 = 13;
    int result = gcd(num1, num2);
    println_int(result);

    if (result < 5) {
        println_int(500);
    } else {
        println_int(600);
        if (result > 10) {
            println_int(700);
        } else {
            println_int(800);
        }
        if (result == 13) {
            println_int(900);
        }
    }

    return 0;
}