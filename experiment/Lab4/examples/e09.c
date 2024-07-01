// int gcd(int a, int b) {
//     println_int(a);
//     println_int(b);
//     if (b == 0) {
//         return a;
//     } else {
//         println_int(gcd(b, a % b));
//         return gcd(b, a % b);
//     }
// }

// int main() {
//     int num1 =7;
//     int num2 =13;
//     int result = gcd(num1, num2);
//     println_int(result);
//     return 0;
// }
#include <stdio.h>

int gcd(int a, int b) {
    printf("%d\n", a);
    printf("%d\n", b);
    if (b == 0) {
        return a;
    } else {
        printf("%d\n", gcd(b, a % b));
        int result = gcd(b, a % b); // 存储gcd的结果，避免重复计算
        return result;
    }
}

int main() {
    int num1 = 7;
    int num2 = 13;
    int result = gcd(num1, num2);
    printf("%d\n", result);
    return 0;
}