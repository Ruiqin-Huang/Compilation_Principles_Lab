int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        int result = fibonacci(n - 1) + fibonacci(n - 2);
        println_int(result);
        return result;
    }
}

int main() {
    int n = 5;
    println_int(fibonacci(n));
    return 0;
}