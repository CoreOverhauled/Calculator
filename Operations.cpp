#include "Operations.h"

#pragma region Parsing Helper Implementations | Error Type

std::string ToString(const std::vector<double>& X) {
	std::string Result = "";
	for (const auto& x : X) {
		Result += std::to_string(x);
		Result += ", ";
	}
	Result.pop_back();
	Result.pop_back();
	return Result;
}

std::string ToString(const std::vector<std::complex<double>>& X) {
	std::string Result = "";
	for (const auto& x : X) {
		Result += '(' + std::to_string(x.real()) + ", " + std::to_string(x.imag()) + ')';
		Result += ", ";
	}
	Result.pop_back();
	Result.pop_back();
	return Result;
}

std::string ToString(const std::complex<double>& x) {
	return '(' + std::to_string(x.real()) + ", " + std::to_string(x.imag()) + ')';
}

#pragma endregion

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

#pragma region Parser Implementation

#pragma region Tokenizer

static bool IsNumeric(std::string String) {
	std::set<char> Numeric = {
		'0', '1','2','3','4','5','6','7','8','9','0','.'
	};
	for (auto& x : String) {
		if (!Numeric.contains(x))return false;
	}
	return true;
}

static bool IsOneOf(Token<double> Tok, std::set<ETokenType> PassingTypes) {
	return PassingTypes.contains(Tok.Type);
}
static bool IsOneOf(Token<std::complex<double>> Tok, std::set<ETokenType> PassingTypes) {
	return PassingTypes.contains(Tok.Type);
}

std::expected<std::vector<Token<double>>, bool> Tokenize(std::string_view Input) {
	std::vector<Token<double>> TokenVec{ Token<double>(ETokenType::StartToken) };
	std::string CurrentSubString{};
#pragma region Lambdas
	//Add a multiplication operation if the previous token was of a numeric type,
	//and the next one will be of such type too.(or parenthesis)
	auto AddMultIfNumeric = [&TokenVec]() -> void {
		if (IsNumericType(TokenVec.back()) ||
			IsOneOf(TokenVec.back(), {ETokenType::ClosedParenthesis})) {
			TokenVec.push_back(Token<double>(ETokenType::Multiply));
		}
		};
	auto ClearSubStr = [&TokenVec, &CurrentSubString, &AddMultIfNumeric]() -> void {
		if (!CurrentSubString.empty()) {
			if (IsNumeric(CurrentSubString)) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(std::stod(CurrentSubString)));
				CurrentSubString.clear();
			}
			else {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(CurrentSubString));
				CurrentSubString.clear();
			}
		}
		};
#pragma endregion
	while (!Input.empty()) {
		switch (Input.at(0)) {
#pragma region Special Characters
		case ' ':
			ClearSubStr();
			break;
		case '(':
			ClearSubStr();
			AddMultIfNumeric();
			TokenVec.push_back(Token<double>(ETokenType::OpenParenthesis));
			break;
		case ')':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::ClosedParenthesis));
			break;
		case '{':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::OpenCurlyBrace));
			break;
		case '}':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::ClosedCurlyBrace));
			break;
		case '[':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::OpenBracket));
			break;
		case ']':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::ClosedBracket));
			break;
		case ',':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Comma));
			break;
		case ';':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Semicolon));
			break;
		case ':':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Colon));
			break;
#pragma endregion
#pragma region Digits
		case'.':
			[[fallthrough]];
		case '1':
			[[fallthrough]];
		case '2':
			[[fallthrough]];
		case '3':
			[[fallthrough]];
		case '4':
			[[fallthrough]];
		case '5':
			[[fallthrough]];
		case '6':
			[[fallthrough]];
		case '7':
			[[fallthrough]];
		case '8':
			[[fallthrough]];
		case '9':
			[[fallthrough]];
		case '0':
			if (IsNumeric(CurrentSubString) || CurrentSubString.empty()) {
				CurrentSubString.append(1, Input.at(0));
				break;
			}
			else {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(CurrentSubString));
				CurrentSubString.clear();
			}
			break;
#pragma endregion
#pragma region Operators
		case '+':
			ClearSubStr();
			if (IsOneOf(TokenVec.back(), { ETokenType::OpenParenthesis, ETokenType::Comma,
				ETokenType::Semicolon })) {
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Add, ETokenType::Substract,
				ETokenType::Negate, ETokenType::Retain })) {
				break;
			}
			TokenVec.push_back(Token<double>(ETokenType::Add));
			break;
		case '-':
			ClearSubStr();
			if (IsOneOf(TokenVec.back(), { ETokenType::OpenParenthesis, ETokenType::Comma,
				ETokenType::Semicolon })
				) {
				TokenVec.push_back(Token<double>(ETokenType::Negate));
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Add })) {
				TokenVec.back() = Token<double>(ETokenType::Substract);
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Substract })) {
				TokenVec.back() = Token<double>(ETokenType::Add);
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Negate })) {
				TokenVec.pop_back();
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Retain })) {
				TokenVec.back() = Token<double>(ETokenType::Negate);
			}
			TokenVec.push_back(Token<double>(ETokenType::Substract));
			break;
		case '*':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Multiply));
			break;
		case '/':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Divide));
			break;
		case '^':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Power));
			break;
		case '!':
			ClearSubStr();
			TokenVec.push_back(Token<double>(ETokenType::Factorial));
			break;
#pragma endregion
#pragma region Functions (and such)
		case 'e':
			if (CurrentSubString.empty() || IsNumeric(CurrentSubString)) {
				ClearSubStr();
				AddMultIfNumeric();
				if (Input.at(1) == '^') {
					TokenVec.push_back(Token<double>(ETokenType::Exponential));
					Input = std::string_view(Input.begin() + 1, Input.end());
					break;
				}
				TokenVec.push_back(Token<double>(ETokenType::e));
				break;
			}
			else {
				CurrentSubString.append(1, 'e');
				if (InputOperationNames.contains(CurrentSubString)) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<double>(
						OperationNameToTokenType.at(
							InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<double>(
						InputTrigFunctionNames.at(CurrentSubString)));
					CurrentSubString.clear();
					break;
				}
				break;
			}
		default:
			if (IsNumeric(CurrentSubString)) {
				ClearSubStr();
			}
			CurrentSubString.append(1, Input.at(0));
			if (CurrentSubString == std::string("pi")) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(ETokenType::pi));
				CurrentSubString.clear();
				break;
			}
			if (InputOperationNames.contains(CurrentSubString)) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(
					OperationNameToTokenType.at(
						InputOperationNames.at(CurrentSubString))));
				CurrentSubString.clear();
				break;
			}
			else if (InputTrigFunctionNames.contains(CurrentSubString) &&
				!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<double>(
					InputTrigFunctionNames.at(CurrentSubString)));
				CurrentSubString.clear();
				break;
			}
#pragma endregion
		}
		Input = std::string_view(Input.begin() + 1, Input.end());
	}
	ClearSubStr();
	TokenVec.push_back(Token<double>(ETokenType::EndToken));
	return TokenVec;
};

std::expected<std::vector<Token<std::complex<double>>>, bool> TokenizeComplex(
	std::string_view Input) {
	std::vector<Token<std::complex<double>>> TokenVec{
		Token<std::complex<double>>(ETokenType::StartToken) };
	std::string CurrentSubString{};
#pragma region Lambdas
	//Add a multiplication operation if the previous token was of a numeric type,
	//and the next one will be of such type too.
	auto AddMultIfNumeric = [&TokenVec]() -> void {
		if (IsNumericType(TokenVec.back()) ||
			IsOneOf(TokenVec.back(), { ETokenType::ClosedParenthesis })) {
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
		}
		};
	auto ClearSubStr = [&TokenVec, &CurrentSubString, &AddMultIfNumeric]() -> void {
		if (!CurrentSubString.empty()) {
			if (IsNumeric(CurrentSubString)) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(std::stod(CurrentSubString)));
				CurrentSubString.clear();
			}
			else {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(CurrentSubString));
				CurrentSubString.clear();
			}
		}
		};
#pragma endregion
	while (!Input.empty()) {
		switch (Input.at(0)) {
#pragma region Special Characters
		case ' ':
			ClearSubStr();
			break;
		case '(':
			ClearSubStr();
			AddMultIfNumeric();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenParenthesis));
			break;
		case ')':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedParenthesis));
			break;
		case '{':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenCurlyBrace));
			break;
		case '}':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedCurlyBrace));
			break;
		case '[':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenBracket));
			break;
		case ']':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedBracket));
			break;
		case ',':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Comma));
			break;
		case ';':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Semicolon));
			break;
		case ':':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Colon));
			break;
#pragma endregion
#pragma region Digits
		case'.':
			[[fallthrough]];
		case '1':
			[[fallthrough]];
		case '2':
			[[fallthrough]];
		case '3':
			[[fallthrough]];
		case '4':
			[[fallthrough]];
		case '5':
			[[fallthrough]];
		case '6':
			[[fallthrough]];
		case '7':
			[[fallthrough]];
		case '8':
			[[fallthrough]];
		case '9':
			[[fallthrough]];
		case '0':
			if (IsNumeric(CurrentSubString) || CurrentSubString.empty()) {
				CurrentSubString.append(1, Input.at(0));
				break;
			}
			else {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(CurrentSubString));
				CurrentSubString.clear();
			}
			break;
#pragma endregion
#pragma region Operators
		case '+':
			ClearSubStr();
			if (IsOneOf(TokenVec.back(), { ETokenType::OpenParenthesis,  ETokenType::Comma,
				ETokenType::Semicolon })) {
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Add,  ETokenType::Substract,
				ETokenType::Negate,  ETokenType::Retain })) {
				break;
			}
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Add));
			break;
		case '-':
			ClearSubStr();
			if (IsOneOf(TokenVec.back(), { ETokenType::OpenParenthesis,  ETokenType::Comma,
				ETokenType::Semicolon })) {
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Negate));
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Add })) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Substract));
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Substract })) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Add));
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Negate })) {
				TokenVec.pop_back();
				break;
			}
			if (IsOneOf(TokenVec.back(), { ETokenType::Retain })) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Negate));
			}
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Substract));
			break;
		case '*':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
			break;
		case '/':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Divide));
			break;
		case '^':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Power));
			break;
		case '!':
			ClearSubStr();
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Factorial));
			break;
#pragma endregion
#pragma region Functions (and such)
		case 'i':
			if (CurrentSubString.empty() || IsNumeric(CurrentSubString)) {
				ClearSubStr();
				if (IsOneOf(TokenVec.back(), { ETokenType::Number, ETokenType::pi, ETokenType::e })) {
					TokenVec.back().Value = std::complex<double>(0, TokenVec.back().Value.real());
					break;
				}
				else {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(std::complex<double>(0, 1)));
					break;
				}
			}
			else {
				CurrentSubString.append(1, 'i');
				if (CurrentSubString == std::string("pi")) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::pi));
					CurrentSubString.clear();
					break;
				}
				else if (InputOperationNames.contains(CurrentSubString)) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(
						OperationNameToTokenType.at(
							InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(
						InputTrigFunctionNames.at(CurrentSubString)));
					CurrentSubString.clear();
					break;
				}
				break;
			};
			break;
		case 'e':
			if (CurrentSubString.empty() || IsNumeric(CurrentSubString)) {
				ClearSubStr();
				AddMultIfNumeric();
				if (Input.at(1) == '^') {
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::Exponential));
					//Ignore next
					Input = std::string_view(Input.begin() + 1, Input.end());
					break;
				}
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::e));
				break;
			}
			else {
				CurrentSubString.append(1, 'e');
				if (InputOperationNames.contains(CurrentSubString)) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(
						OperationNameToTokenType.at(
							InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
					AddMultIfNumeric();
					TokenVec.push_back(Token<std::complex<double>>(
						InputTrigFunctionNames.at(CurrentSubString)));
					CurrentSubString.clear();
					break;
				}
				break;
			}
			break;
		default:
			if (IsNumeric(CurrentSubString)) {
				ClearSubStr();
			}

			CurrentSubString.append(1, Input.at(0));
			if (CurrentSubString == std::string("pi")) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::pi));
				CurrentSubString.clear();
				break;
			}
			if (InputOperationNames.contains(CurrentSubString)) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(
					OperationNameToTokenType.at(
						InputOperationNames.at(CurrentSubString))));
				CurrentSubString.clear();
				break;
			}
			else if (InputTrigFunctionNames.contains(CurrentSubString) &&
				!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
				AddMultIfNumeric();
				TokenVec.push_back(Token<std::complex<double>>(
					InputTrigFunctionNames.at(CurrentSubString)));
				CurrentSubString.clear();
				break;
			}
#pragma endregion
		}
		Input = std::string_view(Input.begin() + 1, Input.end());
	}
	ClearSubStr();
	TokenVec.push_back(Token<std::complex<double>>(ETokenType::EndToken));
	return TokenVec;
}

#pragma endregion

#pragma region Parser

std::expected<std::deque<Token<double>>, bool> Parse(const std::vector<Token<double>>& Tokens) {
	bool bShouldReturnParsedTokens = true;
	std::deque<Token<double>> ParsedTokenStack{};
	std::stack<Token<double>> OperatorStack{};
	for (auto& Tok : Tokens) {
		if (IsNumericType<double>(Tok)) {
			ParsedTokenStack.push_back(Tok);
			continue;
		}
		if (IsOperatorType<double>(Tok)) {
			const EOperation Operation = TokenTypeToOperationName.at(Tok.Type);
			const uint8_t Precedence = OperatorPrecedence.at(Operation);
			const bool bIsRightAssociative = OperatorRightAssociativity.at(Operation);
			if (bIsRightAssociative) {
				while (TokenOperatorPrecedence.at(OperatorStack.top().Type) > Precedence) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				OperatorStack.push(Tok);
			}
			else {
				while (TokenOperatorPrecedence.at(OperatorStack.top().Type) >= Precedence) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				OperatorStack.push(Tok);
			}
			continue;
		}
		if (IsSeparatorType<double>(Tok)) {
			if (Tok.Type == ETokenType::EndToken) {
				while (!OperatorStack.empty()) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				ParsedTokenStack.pop_back();
				continue;
			}
			if (Tok.Type == ETokenType::ClosedCurlyBrace) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenCurlyBrace) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					bShouldReturnParsedTokens = false;
					std::cout << "Syntax error: expected '{'.\n";
					continue;
				}
				OperatorStack.pop();
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::ClosedParenthesis) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenParenthesis) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '('.\n";
						continue;
					}
				}
				OperatorStack.pop();
				continue;
			}
			if (Tok.Type == ETokenType::ClosedBracket) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenBracket) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '['.\n";
						continue;
					}
				}
				OperatorStack.pop();
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::Comma || Tok.Type == ETokenType::Semicolon) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenCurlyBrace) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '{'.\n";
						continue;
					}
				}
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::Colon) {
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::OpenCurlyBrace || Tok.Type == ETokenType::OpenBracket) {
				ParsedTokenStack.push_back(Tok);
				OperatorStack.push(Tok);
				continue;
			}
			OperatorStack.push(Tok);
			continue;
		}
		std::cout << "Error: unsupported token. Please contact the dev with the input you used.";
		bShouldReturnParsedTokens = false;
	}
	if (!bShouldReturnParsedTokens) {
		return std::unexpected(false);
	}
	return ParsedTokenStack;
}

std::expected<std::deque<Token<std::complex<double>>>, bool> Parse(
	const std::vector<Token<std::complex<double>>>& Tokens) {
	bool bShouldReturnParsedTokens = true;
	std::deque<Token<std::complex<double>>> ParsedTokenStack{};
	std::stack<Token<std::complex<double>>> OperatorStack{};
	for (auto& Tok : Tokens) {
		if (IsNumericType<std::complex<double>>(Tok)) {
			ParsedTokenStack.push_back(Tok);
			continue;
		}
		if (IsOperatorType<std::complex<double>>(Tok)) {
			const EOperation Operation = TokenTypeToOperationName.at(Tok.Type);
			const uint8_t Precedence = OperatorPrecedence.at(Operation);
			const bool bIsRightAssociative = OperatorRightAssociativity.at(Operation);
			if (bIsRightAssociative) {
				while (TokenOperatorPrecedence.at(OperatorStack.top().Type) > Precedence) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				OperatorStack.push(Tok);
			}
			else {
				while (TokenOperatorPrecedence.at(OperatorStack.top().Type) >= Precedence) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				OperatorStack.push(Tok);
			}
			continue;
		}
		if (IsSeparatorType<std::complex<double>>(Tok)) {
			if (Tok.Type == ETokenType::EndToken) {
				while (!OperatorStack.empty()) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				ParsedTokenStack.pop_back();
				continue;
			}
			if (Tok.Type == ETokenType::ClosedCurlyBrace) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenCurlyBrace) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					bShouldReturnParsedTokens = false;
					std::cout << "Syntax error: expected '{'.\n";
					continue;
				}
				OperatorStack.pop();
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::ClosedParenthesis) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenParenthesis) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '('.\n";
						continue;
					}
				}
				OperatorStack.pop();
				continue;
			}
			if (Tok.Type == ETokenType::ClosedBracket) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenBracket) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '['.\n";
						continue;
					}
				}
				OperatorStack.pop();
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::Comma || Tok.Type == ETokenType::Semicolon) {
				while (!OperatorStack.empty() &&
					OperatorStack.top().Type != ETokenType::OpenCurlyBrace) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				if (OperatorStack.empty()) {
					if (OperatorStack.empty()) {
						bShouldReturnParsedTokens = false;
						std::cout << "Syntax error: expected '{'.\n";
						continue;
					}
				}
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::Colon) {
				ParsedTokenStack.push_back(Tok);
				continue;
			}
			if (Tok.Type == ETokenType::OpenCurlyBrace || Tok.Type == ETokenType::OpenBracket) {
				ParsedTokenStack.push_back(Tok);
				OperatorStack.push(Tok);
				continue;
			}
			OperatorStack.push(Tok);
			continue;
		}
		std::cout << "Error: unsupported token. Please contact the dev with the input you used.";
		bShouldReturnParsedTokens = false;
	}
	if (!bShouldReturnParsedTokens) {
		return std::unexpected(false);
	}
	return ParsedTokenStack;
}

#pragma endregion

#pragma region Evaluator

#pragma region Consume Tokens

std::expected<std::deque<Token<double>>, bool> ConsumeUntilCorrectParenthesis(
	std::deque<Token<double>>& InputTokens, ETokenType StopTokenType) {
	std::deque<Token<double>> ConsumedTokens{};
	std::stack<ETokenType> ParenthesesStack{};
	while (!InputTokens.empty() && InputTokens.front().Type != StopTokenType) {
		if (InputTokens.front().Type == ETokenType::OpenParenthesis) {
			ParenthesesStack.push(ETokenType::OpenParenthesis);
		}
		else if (InputTokens.front().Type == ETokenType::OpenCurlyBrace) {
			ParenthesesStack.push(ETokenType::OpenCurlyBrace);
		}
		else if (InputTokens.front().Type == ETokenType::OpenBracket) {
			ParenthesesStack.push(ETokenType::OpenBracket);
		}
		else if (InputTokens.front().Type == ETokenType::ClosedParenthesis) {
			if (ParenthesesStack.top() == ETokenType::OpenParenthesis) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier ')'.\n";
				return std::unexpected(false);
			}
		}
		else if (InputTokens.front().Type == ETokenType::ClosedCurlyBrace) {
			if (ParenthesesStack.top() == ETokenType::OpenCurlyBrace) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier '}'.\n";
				return std::unexpected(false);
			}

		}
		else if (InputTokens.front().Type == ETokenType::ClosedBracket) {
			if (ParenthesesStack.top() == ETokenType::OpenBracket) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier ']'.\n";
				return std::unexpected(false);
			}

		}
		ConsumedTokens.push_back(InputTokens.front());
		InputTokens.pop_front();
		if (!InputTokens.empty() && InputTokens.front().Type == StopTokenType
			&& ParenthesesStack.size() > 1) {
			std::cout << "Syntax error: " << TokenTypeNames.at(CorrespondingToken.at(
				ParenthesesStack.top())) << " was never closed.\n";
			return std::unexpected(false);
		}
	}
	if (InputTokens.empty()) {
		std::cout << "Syntax error: " << TokenTypeNames.at(CorrespondingToken.at(StopTokenType))
			<< " was never closed.\n";
		return std::unexpected(false);
	}
	return ConsumedTokens;
}

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilCorrectParenthesis(
	std::deque<Token<std::complex<double>>>& InputTokens, ETokenType StopTokenType) {
	std::deque<Token<std::complex<double>>> ConsumedTokens{};
	std::stack<ETokenType> ParenthesesStack{};
	while (!InputTokens.empty() && InputTokens.front().Type != StopTokenType) {
		if (InputTokens.front().Type == ETokenType::OpenParenthesis) {
			ParenthesesStack.push(ETokenType::OpenParenthesis);
		}
		else if (InputTokens.front().Type == ETokenType::OpenCurlyBrace) {
			ParenthesesStack.push(ETokenType::OpenCurlyBrace);
		}
		else if (InputTokens.front().Type == ETokenType::OpenBracket) {
			ParenthesesStack.push(ETokenType::OpenBracket);
		}
		else if (InputTokens.front().Type == ETokenType::ClosedParenthesis) {
			if (ParenthesesStack.top() == ETokenType::OpenParenthesis) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier ')'.\n";
				return std::unexpected(false);
			}
		}
		else if (InputTokens.front().Type == ETokenType::ClosedCurlyBrace) {
			if (ParenthesesStack.top() == ETokenType::OpenCurlyBrace) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier '}'.\n";
				return std::unexpected(false);
			}

		}
		else if (InputTokens.front().Type == ETokenType::ClosedBracket) {
			if (ParenthesesStack.top() == ETokenType::OpenBracket) {
				ParenthesesStack.pop();
			}
			else {
				std::cout << "Syntax error: unexpected identifier ']'.\n";
				return std::unexpected(false);
			}

		}
		ConsumedTokens.push_back(InputTokens.front());
		InputTokens.pop_front();
		if (!InputTokens.empty() && InputTokens.front().Type == StopTokenType
			&& ParenthesesStack.size() > 1) {
			std::cout << "Syntax error: " << TokenTypeNames.at(CorrespondingToken.at(
				ParenthesesStack.top())) << " was never closed.\n";
			return std::unexpected(false);
		}
	}
	if (InputTokens.empty()) {
		std::cout << "Syntax error: " << TokenTypeNames.at(CorrespondingToken.at(StopTokenType))
			<< " was never closed.\n";
		return std::unexpected(false);
	}
	return ConsumedTokens;
}


std::expected<std::deque<Token<double>>, bool> ConsumeIteratorBody(
	std::deque<Token<double>>& InputTokens, ETokenType StopTokenType) {
	uint8_t NestedIteratorCount = 1;
	std::deque<Token<double>> ConsumedTokens{};
	while (NestedIteratorCount > 0 && !InputTokens.empty()) {
		if (InputTokens.front().Type == ETokenType::ClosedCurlyBrace) {
			NestedIteratorCount++;
		}
		else if (InputTokens.front().Type == ETokenType::Sum ||
			InputTokens.front().Type == ETokenType::Product) {
			NestedIteratorCount--;
		}
		ConsumedTokens.push_back(InputTokens.front());
		InputTokens.pop_front();
	}
	if (NestedIteratorCount > 0) {
		std::cout << "Syntax error: an iterator was never finished.";
		return std::unexpected(false);
	}
	return ConsumedTokens;
}

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeIteratorBody(
	std::deque<Token<std::complex<double>>>& InputTokens, ETokenType StopTokenType) {
	uint8_t NestedIteratorCount = 1;
	std::deque<Token<std::complex<double>>> ConsumedTokens{};
	while (NestedIteratorCount > 0 && !InputTokens.empty()) {
		if (InputTokens.front().Type == ETokenType::ClosedCurlyBrace) {
			NestedIteratorCount++;
		}
		else if (InputTokens.front().Type == ETokenType::Sum ||
			InputTokens.front().Type == ETokenType::Product) {
			NestedIteratorCount--;
		}
		ConsumedTokens.push_back(InputTokens.front());
		InputTokens.pop_front();
	}
	if (NestedIteratorCount > 0) {
		std::cout << "Syntax error: an iterator was never finished.";
		return std::unexpected(false);
	}
	return ConsumedTokens;
}


std::expected<std::deque<Token<double>>, bool> ConsumeUntilToken(
	std::deque<Token<double>>& InputTokens,
	ETokenType StopTokenType, EStopConsumingCondition Behavior) {
	std::expected<std::deque<Token<double>>, bool> Consumed{};
	switch (Behavior) {
	case EStopConsumingCondition::CorrectParenthesis:
		Consumed = ConsumeUntilCorrectParenthesis(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	case EStopConsumingCondition::IteratorBodyEnd:
		Consumed = ConsumeIteratorBody(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	}
	return std::unexpected(false);
}

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilToken(
	std::deque<Token<std::complex<double>>>& InputTokens,
	ETokenType StopTokenType, EStopConsumingCondition Behavior) {
	std::expected<std::deque<Token<std::complex<double>>>, bool> Consumed{};
	switch (Behavior) {
	case EStopConsumingCondition::CorrectParenthesis:
		Consumed = ConsumeUntilCorrectParenthesis(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	case EStopConsumingCondition::IteratorBodyEnd:
		Consumed = ConsumeIteratorBody(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	}
	return std::unexpected(false);
}

#pragma endregion

#pragma endregion

#pragma endregion