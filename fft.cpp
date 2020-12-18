/* source code from
https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=221633584963&proxyReferer=https:%2F%2Fwww.google.com%2F
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
#include <complex> // 복소수 사용을 위해

using namespace std;

const double PI = acos(-1); // set PI
typedef complex<double> cpx;

// n-1차 다항식 f를 n개의 복소수로 DFT함. 이때 w = x
void FFT(vector<cpx> &f, cpx w)
{
    int n = f.size();
    if(n == 1) return; // f(x) = c

    // 홀수차수와 짝수차수로 다항식 분리
    vector<cpx> even(n / 2), odd(n / 2);

    for(int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            even[i / 2] = f[i];
        }
        else {
            odd[i / 2] = f[i];
        }
    }

    // divide: 각각의 다항식을 재귀적으로 DFT함
    FFT(even, w * w);
    FFT(odd, w * w);

    // conquer: 재귀적으로 알아온 DFT 값들로 이번 함수의 결과를 계산
    cpx wp(1, 0);
    for(int i = 0; i < n / 2; ++i) {
        // f(x) = f_even(x^2) + x * f_odd(x^2)
        f[i] = even[i] + wp * odd[i];
        // f(-x) = f_even(x^2) - x * f_odd(x^2)
        f[i + n / 2] = even[i] - wp * odd[i];
        wp *= w;
    }
}

// 두 다항식 a, b를 곱한 c를 계산해 돌려주는 함수. i번째 원소는 x^i의 계수
vector<cpx> multiply(vector<cpx> a, vector<cpx> b)
{
    // 다항식의 길이보다 큰 최소의 2의 거듭제곱수를 찾아 n으로 둔다
    int n = 1;
    while(n < a.size()+1 || n < b.size()+1) n *= 2;
    n *= 2;
    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    cpx w(cos(2*PI/n), sin(2*PI/n));

    // FFT를 통해 두 다항식을 DFT해 둔다.
    FFT(a, w);
    FFT(b, w);

    // DFT한 값들끼리 곱하면 결과 다항식의 DFT값이 된다.
    for(int i = 0; i < n; ++i)
        c[i] = a[i]*b[i];

    // 역변환: c의 DFT 값으로부터 c의 다항식 형태를 복원한다.
    FFT(c, cpx(1, 0)/w);
    for(int i = 0; i < n; ++i){
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}

int main()
{
    vector<cpx> a(10), b(8);
    vector<cpx> c;

    for (size_t i = 0; i < a.size(); i++) {
        a[i] = i + 1;
    }

    for (size_t i = 0; i < b.size(); i++) {
        b[i] = i + 1;
    }

    c = multiply(a, b);

    for (auto data : a) {
        cout << data << ' ';
    }
    cout << '\n';

    for (auto data : b) {
        cout << data << ' ';
    }
    cout << '\n';

    for (auto data : c) {
        cout << data << ' ';
    }
    cout << '\n';

    return 0;
}
