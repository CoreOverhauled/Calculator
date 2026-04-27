#include "Operations.h"

#pragma region Cot Implementations
double cot(double x) noexcept {
	return 1.0 / std::tan(x);
}
double coth(double x) noexcept {
	return 1.0 / std::tanh(x);
}
double acot(double x) noexcept {
	return std::atan(1.0 / x);
}
double acoth(double x) noexcept {
	return std::atanh(1.0 / x);
}
std::complex<double> cot(const std::complex<double>& x) noexcept {
	return 1.0 / std::tan(x);
}
std::complex<double> coth(const std::complex<double>& x) noexcept {
	return 1.0 / std::tanh(x);
}
std::complex<double> acot(const std::complex<double>& x) noexcept {
	return std::atan(1.0 / x);
}
std::complex<double> acoth(const std::complex<double>& x) noexcept {
	return std::atanh(1.0 / x);
}
#pragma endregion




