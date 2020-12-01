# Fast Fourier Transform (FFT)

## Fourier Transform vs Discrete Fourier Transform

교과서의 이론이나 실생활 상에서 대부분의 것들은 연속한 자료들이다.

그러나 컴퓨터를 통해 마주하게 되는 자료들은 대부분 불연속적인 즉, 이산적인 자료들이다.

컴퓨터를 통한 자료들은 시간 기준이나 개수의 기준으로 나뉘어 불연속적인 것들이 대다수이다.



따라서, 컴퓨터의 세상으로 푸리에 변환을 끌어들이려면 이산적인 환경에서 진행해야 한다.

## Discrete Fourier Transform -> Fast Fourier Transform

DFT는 복소수를 이용하여 곱셈 1번, 덧셈 1번의 사이클을 거치게 된다. 이 사이클을 1번의 계산이라고 하면 N 크기의 데이터에 대해 DFT를 하려고 하면 N^2번의 계산이 필요하다. 즉, O(N^2)의 시간복잡도를 가지게 된다.

그러나 Cooley-Tukey 알고리즘[2]을 활용한 FFT는 이 계산의 횟수를 NlogN으로 줄여 시간복잡도를 O(NlogN)로 만듦으로써 더 빠르게 푸리에 변환을 할 수 있게 했다.

## Fast Fourier Transform을 이용한 Polynomial 곱셈 연산 구현

### Divide and Conquer

#### Divide

다항식 f를 n개의 복소수로 DFT를 이용하여 Divide

짝수항과 홀수항을 나누어 분리 (재귀적) -> 이 단계에서 O(logN)으로 변하게 됨

#### Conquer

![Conquer](https://blogfiles.pstatic.net/MjAxOTA4MzBfNzgg/MDAxNTY3MTQzMTc3MzQ2.qcEFCMQQZXxH2i3STzYUQBN3OQ9uajanxfDqIjZFwnkg.6V-pIr3S69NG8ujzXTjOwEAyXvTRolc4_v7AxeKB2REg.PNG.kks227/4.png?type=w3)

재귀적으로 알아온 DFT 값들로 f의 결과를 계산

### Inverse FFT (IFFT)

Divide and Conquer로 알아낸 f에 대한 정보는 다항식 정보가 아닌 f의 n개에 해당하는 이산적인 점의 정보인 {(x_0, f(x_0)), (x_1, f(x_1)), ... , (x_n-1, f(x_n-1))}를 얻어낸 것이다.

이것을 이용하여 f의 다항식 정보를 얻어내기 위해서는 IFFT를 통해 알아내야 한다. (n-1차 다항식의 다항식 정보를 알아내기 위해서는 최소 n개의 점의 정보가 필요하다는 수학적 사실에 따라서..)

### Time Complexity

O(Polynomial Multiply) = O(FFT) + O(Multiply) + O(IFFT)

O(FFT) = O(Divide and Conquer)

O(Divide and Conquer) = O(Divide) X O(Conquer) = O(logN) X O(N) = O(NlogN)

O(Multiply) = O(N)

O(IDFT) = Inverse of FFT = O(FFT) = O(NlogN)

O(Polynomial Multiply) = O(FFT) + O(Multiply) + O(IFFT) = O(NlogN) + O(N) + O(NlogN) = O(NlogN)

## Reference

[1] https://helloworldpark.github.io/

[2] BENDAT, Julius S.; PIERSOL, Allan G. *Random data: analysis and measurement procedures*. John Wiley & Sons, 2011.