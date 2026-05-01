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
std::expected<double, MathError<double>>
TrigFunction(double A, ETrigFunc Function) noexcept {
	switch (double Value; Function) {
	case ETrigFunc::sin:
		return std::sin(A);
	case ETrigFunc::cos:
		return std::cos(A);
	case ETrigFunc::tan:
		Value = std::tan(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"tan is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::cot:
		Value = cot(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"cot is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::sinh:
		return std::sinh(A);
	case ETrigFunc::cosh:
		return std::cosh(A);
	case ETrigFunc::tanh:
		Value = std::tanh(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"tanh is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::coth:
		Value = coth(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"coth is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::asin:
		return std::asin(A);
	case ETrigFunc::acos:
		return std::acos(A);
	case ETrigFunc::atan:
		Value = std::atan(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"atan is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::acot:
		Value = acot(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"acot is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::asinh:
		return std::asinh(A);
	case ETrigFunc::acosh:
		return std::acosh(A);
	case ETrigFunc::atanh:
		Value = std::atanh(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"atanh is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	case ETrigFunc::acoth:
		Value = acoth(A);
		if (isnormal(Value) || Value == 0.0) {
			return Value;
		}
		else {
			return std::unexpected(MathError<double>(EOperation::Trig,
				"acoth is not defined for " + std::to_string(A), std::vector<double>{A}));
		}
	}
	return std::unexpected(MathError<double>(EOperation::Trig,
		"No such function: " + TrigToFunctionNames.at(Function), std::vector<double>{A}));
	//return ETrigFuncToFunctionMap<double, double>.at(Function)(static_cast<double>(A));
};

std::expected<std::complex<double>, MathError<const std::complex<double>&>>
TrigFunction(const std::complex<double>& A, ETrigFunc Function) noexcept {
	return ETrigFuncToFunctionMap<std::complex<double>,
		const std::complex<double>&>.at(Function)(A);
};



