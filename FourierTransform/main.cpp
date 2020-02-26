#include <iostream>
#include <complex>

using namespace std;

#define PI 3.14159265359f
#define ARRAY_COUNT(arr) ((sizeof(arr)) / sizeof((arr)[0]))

struct complex_num {
	float re;
	float im;
};

inline complex_num Complex(float re, float im) {
	complex_num Result;

	Result.re = re;
	Result.im = im;

	return(Result);
}

complex_num operator*(const complex_num& Num, float Scalar) {
	complex_num Result = Num;

	Result.re *= Scalar;
	Result.im *= Scalar;

	return(Result);
}

complex_num& operator*=(complex_num& Num, float Scalar) {
	Num.re *= Scalar;
	Num.im *= Scalar;

	return(Num);
}

complex_num operator*(const complex_num& A, const complex_num& B) {
	complex_num Result;

	Result.re = A.re * B.re - A.im * B.im;
	Result.im = A.re * B.im + B.re * A.im;

	return(Result);
}

void PrintComplex(const complex_num& Value) {
	printf("re(%.2f) im(%.2f)\n", Value.re, Value.im);
}

void PrintComplexArray(char* Name, complex_num* Array, int Count) {
	printf("%s\n", Name);
	
	for (int i = 0; i < Count; i++) {
		PrintComplex(Array[i]);
	}
}

void PrintStdComplex(const std::complex<float>& Value) {
	printf("re(%.2f) im(%.2f)\n", Value.real(), Value.imag());
}

void Dft(complex_num* out, complex_num* in, int count) {
	float InvCount = 1.0f / (float)count;

	for (int n = 0; n < count; n++)
	{
		complex_num xn = {};

		for (int k = 0; k < count; k++) {
			float Angle = 2.0f * PI * (float)k * (float)n * InvCount;

			float AngleCos = cosf(Angle);
			float AngleSin = sinf(Angle);

			xn.re += in[k].re * AngleCos + in[k].im * AngleSin;
			xn.im += in[k].re * -AngleSin + in[k].im * AngleCos;
		}

		out[n] = xn;
	}
}

void DftInv(complex_num* out, complex_num* in, int count) {
	float InvCount = 1.0f / (float)count;

	for (int k = 0; k < count; k++)
	{
		complex_num xk = {};

		for (int n = 0; n < count; n++)
		{
			float Angle = 2.0f * PI * (float)k * (float)n * InvCount;

			float AngleCos = cosf(Angle);
			float AngleSin = sinf(Angle);

			xk.re += in[n].re * AngleCos + in[n].im * -AngleSin;
			xk.im += in[n].re * AngleSin + in[n].im * AngleCos;
		}

		out[k] = xk * InvCount;
	}
}

void FFT(complex_num* in, complex_num* out, int count) {

}

int main(int ArgsCount, char** Args) {

	complex_num Num0 = Complex(0.0f, 0.0f);
	complex_num Num1 = Complex(1.0f, 0.0f);

	complex_num After[8];
	complex_num Before[] = {Num1, Num1, Num1, Num1, Num0, Num0, Num0, Num0};

	Dft(After, Before, 8);

	PrintComplexArray("DFT forward", After, 8);

	DftInv(Before, After, 8);
	
	PrintComplexArray("DFT Inverse", Before, 8);

	system("pause");
	return(0);
}