#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// m(x) = x^10 + x^3 + 1
const int MinimalPoly = 1033; 

//Tìm độ dài của bit của một số
int bitLength(int x) {
    int length = 0;
    while (x > 0) {
        length++;
        x >>= 1;
    }
    return length;
}

int polyMul(int a, int b) {
    int res = 0;
    while (b > 0) {
        if (b & 1) res ^= a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

void polyDiv(int a, int b, int &q, int &r) {
    q = 0;
    int len_a = bitLength(a);
    int len_b = bitLength(b);
    while (len_a >= len_b && len_b > 0) {
        int shift = len_a - len_b;
        q ^= (1 << shift);
        a ^= (b << shift);
        len_a = bitLength(a);
    }
    r = a;
}

void euclidean() {
    int input_a;
    cout << "==> Nhap so can tim nghich dao trong GF(2^10): ";
    if (!(cin >> input_a)) return;

    // Rut gon neu input >= 1033
    if (input_a >= MinimalPoly) {
        int q_tmp, r_tmp;
        polyDiv(input_a, MinimalPoly, q_tmp, r_tmp);
        cout << "[!] Rut gon " << input_a << " ve: " << r_tmp << endl;
        input_a = r_tmp;
    }

    // Khoi tao cac gia tri
    int r_prev2 = MinimalPoly, r_prev1 = input_a;
    int x_prev2 = 1, x_prev1 = 0;
    int y_prev2 = 0, y_prev1 = 1;

    cout << "\n[BANG THUAT TOAN EUCLIDEAN MO RONG]" << endl;
    cout << "| " << setw(3) << "i" 
         << " | " << setw(6) << "r_i" 
         << " | " << setw(6) << "q_i" 
         << " | " << setw(6) << "x_i" 
         << " | " << setw(6) << "y_i" << " |" << endl;
    cout << "|-----|--------|--------|--------|--------|" << endl;
    
    // Dong i = -1 
    cout << "| " << setw(3) << "-1" << " | " << setw(6) << r_prev2 << " | " << setw(6) << "-" << " | " << setw(6) << x_prev2 << " | " << setw(6) << y_prev2 << " |" << endl;
    // Dong i = 0 
    cout << "| " << setw(3) << "0" << " | " << setw(6) << r_prev1 << " | " << setw(6) << "-" << " | " << setw(6) << x_prev1 << " | " << setw(6) << y_prev1 << " |" << endl;

    int i = 1;
    while (r_prev1 != 0) {
        int q, r_curr;
        polyDiv(r_prev2, r_prev1, q, r_curr);
        
        int x_curr = x_prev2 ^ polyMul(q, x_prev1);
        int y_curr = y_prev2 ^ polyMul(q, y_prev1);

        cout << "| " << setw(3) << i << " | " << setw(6) << r_curr << " | " << setw(6) << q << " | " << setw(6) << x_curr << " | " << setw(6) << y_curr << " |" << endl;

        // Cap nhat cac bien cho buoc tiep theo
        r_prev2 = r_prev1; r_prev1 = r_curr;
        x_prev2 = x_prev1; x_prev1 = x_curr;
        y_prev2 = y_prev1; y_prev1 = y_curr;
        i++;
    }

    cout << "-----------------------------------------------" << endl;
    if (r_prev2 == 1) {
        cout << "=> KET QUA: Nghich dao cua " << input_a << " la: " << y_prev2 << endl;
    } else {
        cout << "=> KET QUA: Khong ton tai nghich dao!" << endl;
    }
}

int main() {
    cout << "--- TIM NGHICH DAO TRONG GF(2^10) VOI m(x)=x^10+x^3+1 ---" << endl;
    char choice;
    do {
        euclidean();
        cout << "\nTiep tuc voi so khac? (y/n): ";
        cin >> choice ;
    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}
