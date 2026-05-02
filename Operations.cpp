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

#pragma region TrigFunction Implementations
std::expected<double, MathError<double>>
TrigFunction(double A, ETrigFunc Function) {
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
}

inline bool IsNormal(const std::complex<double>& x) {
	return isnormal(x.real()) && isnormal(x.imag());
}

std::expected<std::complex<double>, MathError<std::complex<double>>>
TrigFunction(const std::complex<double>& A, ETrigFunc Function) {
	switch (std::complex<double> Value; Function) {
	case ETrigFunc::sin:
		return std::sin(A);
	case ETrigFunc::cos:
		return std::cos(A);
	case ETrigFunc::tan:
		Value = std::tan(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"tan is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::cot:
		Value = cot(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"cot is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::sinh:
		return std::sinh(A);
	case ETrigFunc::cosh:
		return std::cosh(A);
	case ETrigFunc::tanh:
		Value = std::tanh(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"tanh is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::coth:
		Value = coth(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"coth is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::asin:
		return std::asin(A);
	case ETrigFunc::acos:
		return std::acos(A);
	case ETrigFunc::atan:
		Value = std::atan(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"atan is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::acot:
		Value = acot(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"acot is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::asinh:
		return std::asinh(A);
	case ETrigFunc::acosh:
		return std::acosh(A);
	case ETrigFunc::atanh:
		Value = std::atanh(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"atanh is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	case ETrigFunc::acoth:
		Value = acoth(A);
		if (IsNormal(Value) || Value == std::complex<double>(0.0, 0.0)) {
			return Value;
		}
		else {
			return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
				"acoth is not defined for " + ToString(A), std::vector<std::complex<double>>{A}));
		}
	}
	return std::unexpected(MathError<std::complex<double>>(EOperation::Trig,
		"No such function: " + TrigToFunctionNames.at(Function), std::vector<std::complex<double>>{A}));
}
#pragma endregion

#pragma region Iterator Implementations

#pragma region Range-based Sum
std::expected<double, MathError<double>> Sum(uint64_t BoundMin, uint64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, uint64_t>)) {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return 0.0;
	}
	double Value{ 0.0 };
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value += Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	uint64_t BoundMin, uint64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, uint64_t>)) {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return std::complex<double>(0.0, 0.0);
	}
	std::complex<double> Value{ 0.0, 0.0 };
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value += Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}
#pragma endregion

#pragma region Set-based Sum

std::expected<double, MathError<double>> Sum(
	std::vector<double> IteratedSet, std::string IteratorVariableName, 
	double(*Expression)(std::pair<const std::string&, double>)) {
	if (IteratedSet.size() == 0) {
		return 0.0;
	}
	double Value{ 0.0 };
	for (auto& i : IteratedSet) {
		Value += Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>)) {
	if (IteratedSet.size() == 0) {
		return std::complex<double>(0.0, 0.0);
	}
	std::complex<double> Value{ 0.0, 0.0 };
	for (auto& i : IteratedSet) {
		Value += Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

#pragma endregion

#pragma region Range-based Product
std::expected<double, MathError<double>> Product(uint64_t BoundMin, uint64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, uint64_t>)) {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return 1.0;
	}
	double Value{ 1.0 };
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value *= Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	uint64_t BoundMin, uint64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, uint64_t>)) {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return std::complex<double>(1.0, 0.0);
	}
	std::complex<double> Value{ 1.0, 0.0 };
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value *= Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}
#pragma endregion

#pragma region Set-based Product

std::expected<double, MathError<double>> Product(
	std::vector<double> IteratedSet, std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, double>)) {
	if (IteratedSet.size() == 0) {
		return 1.0;
	}
	double Value{ 1.0 };
	for (auto& i : IteratedSet) {
		Value *= Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>)) {
	if (IteratedSet.size() == 0) {
		return std::complex<double>(1.0, 0.0);
	}
	std::complex<double> Value{ 1.0, 0.0 };
	for (auto& i : IteratedSet) {
		Value *= Expression(std::make_pair(IteratorVariableName, i));
	}
	return Value;
}

#pragma endregion

#pragma endregion

#pragma region Factorial Implementations

#pragma region Complex tgamma

std::complex<double> tgamma(const std::complex<double>& z)
{
	constexpr static const int g = 7;
	constexpr static const double p[g + 2] = { 0.99999999999980993, 676.5203681218851,
		-1259.1392167224028, 771.32342877765313, -176.61502916214059,
		12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6,
		1.5056327351493116e-7 };
	std::complex<double> z1 = z;
	if (std::real(z1) < 0.5) {
		return pi / (sin(pi * z1) * tgamma(1.0 - z1));
	}
	z1 -= 1.0;
	std::complex<double> x = p[0];
	for (int i = 1; i < g + 2; i++) {
		x += p[i] / (z1 + std::complex<double>(i, 0));
	}
	const std::complex<double> t = z1 + (g + 0.5);
	return std::sqrt(2 * pi) * std::pow(t, z1 + 0.5) * std::exp(-t) * x;
}

#pragma endregion

#pragma region Factorial

std::expected<double, MathError<double>> Factorial(double A) {
	if (A <= 0 && fmod(A, 1) == 0) {
		return std::unexpected(MathError<double>(
			EOperation::Factorial,
			"The factorial does not exist for negative integers.",
			std::vector<double>{A}));
	}
	return std::tgamma(A + 1);
}

std::expected<std::complex<double>, MathError<std::complex<double>>> Factorial(
	std::complex<double> A) {
	return tgamma(A + std::complex<double>(1.0, 0.0));
}

#pragma endregion

#pragma region nCr

std::expected<double, MathError<double>> nCr(double N, double R) {
	if (R < 0.0 || R > N) {
		return 0.0;
	}
	std::expected<double, MathError<double>>
		a = Factorial(N),
		b = Factorial(N - R),
		c = Factorial(R);
	return a.value() / (b.value() * c.value());
}

std::expected<std::complex<double>, MathError<
	std::complex<double>>> nCr(std::complex<double> N, std::complex<double> R) {
	std::expected<std::complex<double>, MathError<std::complex<double>>>
		a = Factorial(N),
		b = Factorial(N - R),
		c = Factorial(R);
	return a.value() / (b.value() * c.value());
}

#pragma endregion

#pragma region nPr

std::expected<double, MathError<double>> nPr(double N, double R) {
	if (R < 0.0 || R > N) {
		return 0.0;
	}
	std::expected<double, MathError<double>>
		a = Factorial(N),
		b = Factorial(N - R);
	return a.value() / b.value();
}

std::expected<std::complex<double>, MathError<
	std::complex<double>>> nPr(std::complex<double> N, std::complex<double> R) {
	std::expected<std::complex<double>, MathError<std::complex<double>>>
		a = Factorial(N),
		b = Factorial(N - R);
	return a.value() / b.value();
}

#pragma endregion

#pragma endregion