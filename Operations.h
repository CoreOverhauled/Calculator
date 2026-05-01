#pragma once
/*
Add functions:
*/
#pragma region Includes
#include <cmath>
#include <complex>
#include <map>
#include <set>
#include <functional>
#include <concepts>
#include <expected>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#pragma endregion

#pragma region Concepts
template<typename T>
concept ComplexNumber = std::is_same_v<std::remove_cvref_t<T>, std::complex<double>>;
template<typename T>
concept RealNumber = std::is_arithmetic_v<std::remove_cvref_t<T>>;
template<typename T>
concept Number = RealNumber<T> || ComplexNumber<T>;
template<typename T>
concept UnsignedNumber = std::is_unsigned_v<std::remove_cvref_t<T>>;
template<typename T>
struct NumberType {
	using type = void;
};
template<typename T> requires Number<T> || UnsignedNumber<T>
struct NumberType<T> {
	using type = T;
};
#pragma endregion

#pragma region Constants
constexpr static const double pi =
3.1415926535897932384626433832795028841972;
constexpr static const double e =
2.7182818284590452353602874713526624977572;
#pragma endregion

#pragma region Parsing Helpers
//syntax be like:[a:12+5^0.5]sum{d:0,50a}(prod{f:d;d+1;15;(3pi)!}(atanh(f)))
#pragma region Operation Names
enum class EOperation : uint8_t {
	None = 0,
	Add,
	Substract,
	Multiply,
	Divide,
	Power,
	Exponential,
	Logarithm,
	Ln,
	Trig,
	Sum,
	Product,
	Factorial,
	nCr,
	nPr,
	Negate,
	Retain
};

enum class ETrigFunc : uint8_t {
	sin,
	cos,
	tan,
	cot,
	sinh,
	cosh,
	tanh,
	coth,
	asin,
	acos,
	atan,
	acot,
	asinh,
	acosh,
	atanh,
	acoth
};

enum class ETokenType :uint8_t {
	StartToken = 0,
	EndToken,
	Name,//variable/function
	Number,//N
	pi,//pi
	e,//e
	OpenParenthesis,//(
	ClosedParenthesis,//)
	OpenCurlyBrace,//{
	ClosedCurlyBrace,//}
	OpenBracket,//[
	ClosedBracket,//]
	Comma,//,
	Semicolon,//;
	Colon,//:
	Add,//Add
	Retain,//+
	Substract,//Sub
	Negate, //-
	Multiply,//Mult
	Divide,//Div
	Power,//Pow
	Exponential,//Exp
	Logarithm,//Log     log(base, input)
	Ln,//Ln
	Trig,//Trig
	Sum,//Sum      {V, V}-> from V to V,  {V;V;V}-> iterate on set
	Product,//Prod
	Factorial,//Fact
	nCr,//nCr
	nPr,//nPr
};

enum class EOperationType : uint8_t {
	Unary = 0,
	Binary,
	Iterative
};

static const std::unordered_map<EOperation, std::string> OperationNames
{
	{EOperation::None, std::string("Something went wrong.")},
	{EOperation::Add, std::string("Add")},
	{EOperation::Substract, std::string("Substract")},
	{EOperation::Multiply, std::string("Multiply")},
	{EOperation::Divide, std::string("Divide")},
	{EOperation::Power, std::string("Power")},
	{EOperation::Exponential, std::string("Exponential")},
	{EOperation::Logarithm, std::string("Logarithm")},
	{EOperation::Ln, std::string("Natural logarithm")},
	{EOperation::Trig, std::string("Trigonometric function")},
	{EOperation::Sum, std::string("Sum")},
	{EOperation::Product, std::string("Product")},
	{EOperation::Factorial, std::string("Factorial")},
	{EOperation::nCr, std::string("nCr")},
	{EOperation::nPr, std::string("nPr")},
	{EOperation::Negate, std::string("Negate")},
	{EOperation::Retain, std::string("Plus")}
};


static const std::unordered_map<std::string, EOperation> InputOperationNames
{
	{std::string("None"), EOperation::None},
	{std::string("add"), EOperation::Add},
	{std::string("sub"), EOperation::Substract},
	{std::string("mult"), EOperation::Multiply},
	{std::string("div"), EOperation::Divide},
	{std::string("pow"), EOperation::Power},
	{std::string("exp"), EOperation::Exponential},
	{std::string("log"), EOperation::Logarithm},
	{std::string("ln"), EOperation::Ln},
	{std::string("trig"), EOperation::Trig},
	{std::string("sum"), EOperation::Sum},
	{std::string("prod"), EOperation::Product},
	{std::string("fact"), EOperation::Factorial},
	{std::string("nCr"), EOperation::nCr},
	{std::string("nPr"), EOperation::nPr},
	{std::string("minus"), EOperation::Negate},
	{std::string("plus"), EOperation::Retain}
};

static const std::unordered_map<std::string, ETrigFunc> InputTrigFunctionNames
{
	{std::string("sin"), ETrigFunc::sin},
	{std::string("cos"), ETrigFunc::cos},
	{std::string("tan"), ETrigFunc::tan},
	{std::string("cot"), ETrigFunc::cot},
	{std::string("sinh"), ETrigFunc::sinh},
	{std::string("cosh"), ETrigFunc::cosh},
	{std::string("tanh"), ETrigFunc::tanh},
	{std::string("coth"), ETrigFunc::coth},
	{std::string("asin"), ETrigFunc::asin},
	{std::string("acos"), ETrigFunc::acos},
	{std::string("atan"), ETrigFunc::atan},
	{std::string("acot"), ETrigFunc::acot},
	{std::string("asinh"), ETrigFunc::asinh},
	{std::string("acosh"), ETrigFunc::acosh},
	{std::string("atanh"), ETrigFunc::atanh},
	{std::string("acoth"), ETrigFunc::acoth}
};

static const std::unordered_map<ETrigFunc, std::string> TrigToFunctionNames
{
	{ETrigFunc::sin, std::string("sin")},
	{ETrigFunc::cos, std::string("cos")},
	{ETrigFunc::tan, std::string("tan")},
	{ETrigFunc::cot, std::string("cot")},
	{ETrigFunc::sinh, std::string("sinh")},
	{ETrigFunc::cosh, std::string("cosh")},
	{ETrigFunc::tanh, std::string("tanh")},
	{ETrigFunc::coth, std::string("coth")},
	{ETrigFunc::asin, std::string("asin")},
	{ETrigFunc::acos, std::string("acos")},
	{ETrigFunc::atan, std::string("atan")},
	{ETrigFunc::acot, std::string("acot")},
	{ETrigFunc::asinh, std::string("asinh")},
	{ETrigFunc::acosh, std::string("acosh")},
	{ETrigFunc::atanh, std::string("atanh")},
	{ETrigFunc::acoth, std::string("acoth")}
};

static const std::unordered_map<EOperation, ETokenType> OperationNameToTokenType
{
	{EOperation::None, ETokenType::Number},
	{EOperation::Add, ETokenType::Add},
	{EOperation::Substract, ETokenType::Substract},
	{EOperation::Multiply, ETokenType::Multiply},
	{EOperation::Divide, ETokenType::Divide},
	{EOperation::Power, ETokenType::Power},
	{EOperation::Exponential, ETokenType::Exponential},
	{EOperation::Logarithm, ETokenType::Logarithm},
	{EOperation::Ln, ETokenType::Ln},
	{EOperation::Trig, ETokenType::Trig},
	{EOperation::Sum, ETokenType::Sum},
	{EOperation::Product, ETokenType::Product},
	{EOperation::Factorial, ETokenType::Factorial},
	{EOperation::nCr, ETokenType::nCr},
	{EOperation::nPr, ETokenType::nPr},
	{EOperation::Negate, ETokenType::Negate},
	{EOperation::Retain, ETokenType::Retain}
};

static const std::unordered_map<ETokenType, EOperation> TokenTypeToOperationName
{
	{ETokenType::Number, EOperation::None},
	{ETokenType::Add, EOperation::Add},
	{ETokenType::Substract, EOperation::Substract},
	{ETokenType::Multiply, EOperation::Multiply},
	{ETokenType::Divide, EOperation::Divide},
	{ETokenType::Power, EOperation::Power},
	{ETokenType::Exponential, EOperation::Exponential},
	{ETokenType::Logarithm, EOperation::Logarithm},
	{ETokenType::Ln, EOperation::Ln},
	{ETokenType::Trig, EOperation::Trig},
	{ETokenType::Sum, EOperation::Sum},
	{ETokenType::Product, EOperation::Product},
	{ETokenType::Factorial, EOperation::Factorial},
	{ETokenType::nCr, EOperation::nCr},
	{ETokenType::nPr, EOperation::nPr},
	{ETokenType::Negate, EOperation::Negate},
	{ETokenType::Retain, EOperation::Retain}
};

static const std::unordered_map<ETokenType, std::string> TokenTypeNames
{
	{ETokenType::StartToken, std::string("Start")},
	{ETokenType::EndToken, std::string("End")},
	{ETokenType::Number, std::string("Number")},
	{ETokenType::pi, std::string("pi")},
	{ETokenType::e, std::string("e")},
	{ETokenType::OpenParenthesis, std::string("(")},
	{ETokenType::ClosedParenthesis, std::string(")")},
	{ETokenType::OpenCurlyBrace, std::string("{")},
	{ETokenType::ClosedCurlyBrace, std::string("}")},
	{ETokenType::OpenBracket, std::string("[")},
	{ETokenType::ClosedBracket, std::string("]")},
	{ETokenType::Comma, std::string(",")},
	{ETokenType::Semicolon, std::string(";")},
	{ETokenType::Colon, std::string(":")},
	{ETokenType::Add, std::string("+")},
	{ETokenType::Substract, std::string("-")},
	{ETokenType::Multiply, std::string("*")},
	{ETokenType::Divide, std::string("/")},
	{ETokenType::Power, std::string("^")},
	{ETokenType::Exponential, std::string("e^")},
	{ETokenType::Logarithm, std::string("log")},
	{ETokenType::Ln, std::string("ln")},
	{ETokenType::Trig, std::string("trig")},
	{ETokenType::Sum, std::string("sum")},
	{ETokenType::Product, std::string("prod")},
	{ETokenType::Factorial, std::string("!")},
	{ETokenType::nCr, std::string("nCr")},
	{ETokenType::nPr, std::string("nPr")},
	{ETokenType::Negate, std::string("u-")},
	{ETokenType::Retain, std::string("u+")}
};

#pragma endregion

#pragma region Tokens


static const std::unordered_map<EOperation, uint8_t> OperatorPrecedence{
	{EOperation::None, 0},
	{EOperation::Add, 1},
	{EOperation::Substract, 1},
	{EOperation::Multiply, 2},
	{EOperation::Divide, 2},
	{EOperation::Power, 3},
	{EOperation::Exponential, 3},
	{EOperation::Logarithm, 5},
	{EOperation::Ln, 5},
	{EOperation::Trig, 5},
	{EOperation::Sum, 5},
	{EOperation::Product, 5},
	{EOperation::Factorial, 5},
	{EOperation::nCr, 5},
	{EOperation::nPr, 5},
	{EOperation::Negate, 5},
	{EOperation::Retain, 5}
};

static const std::unordered_map<ETokenType, uint8_t> TokenOperatorPrecedence{
	{ETokenType::StartToken, 0},
	{ETokenType::EndToken, 0},
	{ETokenType::OpenParenthesis, 0},
	{ETokenType::ClosedParenthesis, 0},
	{ETokenType::OpenCurlyBrace, 0},
	{ETokenType::ClosedCurlyBrace, 0},
	{ETokenType::OpenBracket, 0},
	{ETokenType::ClosedBracket, 0},
	{ETokenType::Comma, 0},
	{ETokenType::Semicolon, 0},
	{ETokenType::Colon, 0},
	{ETokenType::Add, 1},
	{ETokenType::Substract, 1},
	{ETokenType::Multiply, 2},
	{ETokenType::Divide, 2},
	{ETokenType::Power, 3},
	{ETokenType::Exponential, 3},
	{ETokenType::Logarithm, 5},
	{ETokenType::Ln, 5},
	{ETokenType::Trig, 5},
	{ETokenType::Sum, 5},
	{ETokenType::Product, 5},
	{ETokenType::Factorial, 5},
	{ETokenType::nCr, 5},
	{ETokenType::nPr, 5},
	{ETokenType::Negate, 5},
	{ETokenType::Retain, 5}
};

static const std::unordered_map<EOperation, bool> OperatorRightAssociativity{
	{EOperation::None, false},
	{EOperation::Add, false},
	{EOperation::Substract, false},
	{EOperation::Multiply, false},
	{EOperation::Divide, false},
	{EOperation::Power, true},
	{EOperation::Exponential, true},
	{EOperation::Logarithm, false},
	{EOperation::Ln, false},
	{EOperation::Trig, false},
	{EOperation::Sum, false},
	{EOperation::Product, false},
	{EOperation::Factorial, false},
	{EOperation::nCr, false},
	{EOperation::nPr, false},
	{EOperation::Negate, false},
	{EOperation::Retain, false}
};

static const std::unordered_map<EOperation, EOperationType> OperatorType{
	{EOperation::None, EOperationType::Unary},
	{EOperation::Add, EOperationType::Binary},
	{EOperation::Substract, EOperationType::Binary},
	{EOperation::Multiply, EOperationType::Binary},
	{EOperation::Divide, EOperationType::Binary},
	{EOperation::Power, EOperationType::Binary},
	{EOperation::Exponential, EOperationType::Unary},
	{EOperation::Logarithm, EOperationType::Binary},
	{EOperation::Ln, EOperationType::Unary},
	{EOperation::Trig, EOperationType::Unary},
	{EOperation::Sum, EOperationType::Iterative},
	{EOperation::Product, EOperationType::Iterative},
	{EOperation::Factorial, EOperationType::Unary},
	{EOperation::nCr, EOperationType::Binary},
	{EOperation::nPr, EOperationType::Binary},
	{EOperation::Negate, EOperationType::Unary},
	{EOperation::Retain, EOperationType::Unary}
};


template<Number T>
struct Token {

	Token(const T& InValue) noexcept : Value(InValue) {};
	Token(ETokenType InType) noexcept : bIsNumber(false), Type(InType) {};
	Token(ETrigFunc InFunction) noexcept : bIsNumber(false), Type(ETokenType::Trig), Function(InFunction) {};
	Token(std::string InName) noexcept : bIsNumber(false), Type(ETokenType::Name), Name(InName) {};


public:

	friend std::ostream& operator<<(std::ostream& Out, Token<T> Tok) {
		if (Tok.Type == ETokenType::e) {
			return Out << e;
		}
		if (Tok.Type == ETokenType::pi) {
			return Out << pi;
		}
		if (Tok.Type == ETokenType::Number) {
			return Out << Tok.Value;
		}
		if (Tok.Type == ETokenType::Trig) {
			return Out << TrigToFunctionNames.at(Tok.Function);
		}
		if (Tok.Type == ETokenType::Name) {
			return Out << Tok.Name;
		}
		return Out << TokenTypeNames.at(Tok.Type);

	};

public:
	bool bIsNumber = true;

	ETokenType Type = ETokenType::Number;

	std::string Name = "";
	ETrigFunc Function = ETrigFunc::sin;
	T Value = T();
};

template<Number T>
constexpr bool IsNumericType(Token<T> Tok) {
	return Tok.Type == ETokenType::Number || Tok.Type == ETokenType::e ||
		Tok.Type == ETokenType::pi || Tok.Type == ETokenType::Name;
}
template<Number T>
constexpr bool IsOperatorType(Token<T> Tok) {
	using enum ETokenType;
	static std::set<ETokenType> OperatorTokens = {
		Add, Retain, Substract, Negate, Multiply, Divide, Power, Exponential, Logarithm, Ln,
		Trig, Sum, Product, Factorial, nCr, nPr
	};
	return OperatorTokens.contains(Tok.Type);
}
template<Number T>
constexpr bool IsSeparatorType(Token<T> Tok) {
	using enum ETokenType;
	static std::set<ETokenType> OperatorTokens = {
		StartToken, EndToken, OpenParenthesis, ClosedParenthesis, OpenCurlyBrace,
		ClosedCurlyBrace, OpenBracket, ClosedBracket, Comma, Semicolon, Colon
	};
	return OperatorTokens.contains(Tok.Type);
}

template<Number T>
static std::unordered_map<std::string, T> Variables{};
template<Number T>
static std::unordered_map<std::string, Token<T>> Functions{};//for later

#pragma endregion

#pragma region Error Type

static std::string ToString(const std::vector<double>& X) {
	std::string Result = "";
	for (const auto& x : X) {
		Result += std::to_string(x);
		Result += ", ";
	}
	Result.pop_back();
	Result.pop_back();
	return Result;
}
static std::string ToString(const std::vector<std::complex<double>>& X) {
	std::string Result = "";
	for (const auto& x : X) {
		Result += '(' + std::to_string(x.real()) + ", " + std::to_string(x.imag()) + ')';
		Result += ", ";
	}
	Result.pop_back();
	Result.pop_back();
	return Result;
}
inline static std::string ToString(const std::complex<double>& x) {
	return '(' + std::to_string(x.real()) + ", " + std::to_string(x.imag()) + ')';
}

template<typename FuncArgType>
class MathError {

public:
	MathError(EOperation InFunction, std::string InErrorMessage, std::vector<FuncArgType> InPassedArguments)
		: Function(InFunction), ErrorMessage("Error in operation: " + OperationNames.at(Function)
			+ ": " + InErrorMessage + " (Operands were:" + ToString(InPassedArguments) + ')') {
	}

	friend std::ostream& operator<<(std::ostream& Out, const MathError& Error) {
		return Out << Error.GetErrorMessage();
	}
	std::string GetErrorMessage() const {
		return ErrorMessage;
	}
private:
	EOperation Function = EOperation::None;
	std::string ErrorMessage = "";
};
#pragma endregion

#pragma endregion

//Move this whole region inside eval
#pragma region Basic Operations
template<Number T>
std::expected<T, MathError<T>> Add(T A, T B) noexcept {
	return A + B;
};


template<Number T>
std::expected<T, MathError<T>> Substract(T A, T B) noexcept {
	return A - B;
};

template<Number T>
std::expected<T, MathError<T>> Multiply(T A, T B) noexcept {
	return A * B;
};

template<Number T>
std::expected<T, MathError<T>> Divide(T A, T B) noexcept {
	if (B == T(0)) {
		return std::unexpected(MathError(
			EOperation::Divide,
			"Division by zero is not allowed",
			std::vector<T>{A, B}));
	}
	return A / B;
};

template<Number T>
std::expected<T, MathError<T>> Retain(T A) noexcept {
	return A;
};

template<Number T>
std::expected<T, MathError<T>> Negate(T A) noexcept {
	return -A;
};

#pragma endregion

//Same as above
#pragma region Power Related Operations

#pragma region Exponents
template<RealNumber T>
std::expected<T, MathError<T>> Power(T Base, T Exp) noexcept {
	if (Base < 0 && std::fmod(Exp, 1) != 0) {
		return std::unexpected(MathError(
			EOperation::Power,
			"Raising negative numbers to non-whole exponents is only supported for complex numbers",
			std::vector<T>{Base, Exp}));
	}
	return std::pow(Base, Exp);
};

static std::expected<std::complex<double>, MathError<std::complex<double>>>
Power(std::complex<double> Base, std::complex<double> Exp) noexcept {
	return std::pow(Base, Exp);
};

template<Number T>
std::expected<T, MathError<T>> Exponential(T Exp) noexcept {
	return std::exp(Exp);
};

#pragma endregion

#pragma region Logarithms

template<RealNumber T>
std::expected<T, MathError<T>> Logarithm(T Base, T Num) noexcept {
	if (Base <= 0) {
		return std::unexpected(MathError(
			EOperation::Logarithm,
			"The base of a logarithm must be positive",
			std::vector<T>{Base, Num}));
	}
	if (Num <= 0) {
		return std::unexpected(MathError(
			EOperation::Logarithm,
			"You can only take the logarithm of positive numbers",
			std::vector<T>{Base, Num}));
	}
	return std::log(Num) / std::log(Base);
};

static std::expected<std::complex<double>, MathError<std::complex<double>>>
Logarithm(std::complex<double> Base,
		std::complex<double> Num) noexcept {
	return std::log(Num) / std::log(Base);
};

template<RealNumber T>
std::expected<T, MathError<T>> Ln(T Num) noexcept {
	if (Num <= 0) {
		return std::unexpected(MathError(
			EOperation::Ln,
			"You can only take the logarithm of positive numbers",
			std::vector<T>{Num}));
	}
	return std::log(Num);
};

static std::expected<std::complex<double>, MathError<std::complex<double>>> Ln(
	std::complex<double> Num) noexcept {
	return std::log(Num);
};


#pragma endregion

#pragma endregion

//rewrite for no templates, change function map to constexpr function?, add checking for infinity
//where relevant
#pragma region Trig Functions

double cot(double x) noexcept;
double coth(double x) noexcept;
double acot(double x) noexcept;
double acoth(double x) noexcept;
std::complex<double> cot(const std::complex<double>& x) noexcept;
std::complex<double> coth(const std::complex<double>& x) noexcept;
std::complex<double> acot(const std::complex<double>& x) noexcept;
std::complex<double> acoth(const std::complex<double>& x) noexcept;

template<typename Ret, typename Arg>
	requires ((std::same_as<Ret, double> && std::same_as<Arg, double>) || 
		(std::same_as<Ret, std::complex<double>> && std::same_as<Arg, const std::complex<double>&>))
static const std::map<ETrigFunc, std::function<Ret(Arg)>> ETrigFuncToFunctionMap
{
	{ETrigFunc::sin, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::sin))},
	{ETrigFunc::cos, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::cos))},
	{ETrigFunc::tan, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::tan))},
	{ETrigFunc::cot, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&cot)) },
	{ETrigFunc::sinh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::sinh))},
	{ETrigFunc::cosh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::cosh))},
	{ETrigFunc::tanh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::tanh))},
	{ETrigFunc::coth, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&coth)) },
	{ETrigFunc::asin, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::asin))},
	{ETrigFunc::acos, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::acos))},
	{ETrigFunc::atan, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::atan))},
	{ETrigFunc::acot, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&acot)) },
	{ETrigFunc::asinh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::asinh))},
	{ETrigFunc::acosh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::acosh))},
	{ETrigFunc::atanh, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&std::atanh))},
	{ETrigFunc::acoth, std::function<Ret(Arg)>(static_cast<Ret(*)(Arg)>(&acoth)) }
};


std::expected<double, MathError<double>>
TrigFunction(double A, ETrigFunc Function) noexcept;

std::expected<std::complex<double>, MathError<const std::complex<double>&>>
TrigFunction( const std::complex<double>& A, ETrigFunc Function) noexcept;
#pragma endregion

//rewrite for no templates + switch to const string &
#pragma region Iterating Operations

template<typename T, typename ExprType = typename T(typename std::tuple<const std::string, T>)>
	requires Number<T>
std::expected<T, MathError<T>> Sum(T BoundMin, T BoundMax,
	const std::string IteratorVariableName, ExprType Expression) noexcept {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return T(0);
	}
	T Value(0);
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value += Expression(std::make_tuple(IteratorVariableName, i));
	}
	return Value;

};

template<typename T, typename ExprType = typename T(typename std::tuple<const std::string, T>)>
	requires Number<T>
std::expected<T, MathError<T>> Sum(
	std::vector<T> IteratedSet, 
	const std::string IteratorVariableName, ExprType Expression) noexcept {
	if (IteratedSet.size() == 0) {
		return T(0);
	}
	T Value(0);
	for (auto& i : IteratedSet) {
		Value += Expression(std::make_tuple(IteratorVariableName, i));
	}
	return Value;

};

template<typename T, typename ExprType = typename T(typename std::tuple<const std::string, T>)>
	requires Number<T>
std::expected<T, MathError<T>> Product(T BoundMin, T BoundMax,
	const std::string IteratorVariableName, ExprType Expression) noexcept {
	if (static_cast<uint64_t>(BoundMax) < static_cast<uint64_t>(BoundMin)) {
		return T(1);
	}
	T Value(1);
	for (uint64_t i = static_cast<uint64_t>(BoundMin); i <= static_cast<uint64_t>(BoundMax); i++) {
		Value *= Expression(std::make_tuple(IteratorVariableName, i));
	}
	return Value;

};

template<typename T, typename ExprType = typename T(typename std::tuple<const std::string, T>)>
	requires Number<T>
std::expected<T, MathError<T>> Product(
	std::vector<T> IteratedSet,
	const std::string IteratorVariableName, ExprType Expression) noexcept {
	if (IteratedSet.size() == 0) {
		return T(1);
	}
	T Value(1);
	for (auto& i : IteratedSet) {
		Value *= Expression(std::make_tuple(IteratorVariableName, i));
	}
	return Value;

};

#pragma endregion

//inside
#pragma region Factorial Related Operations

//Make variables local to cpp or propably function?
#pragma region Complex Gamma Implementation

constexpr static const int g = 7;

constexpr static const double p[g + 2] = { 0.99999999999980993, 676.5203681218851,
-1259.1392167224028, 771.32342877765313, -176.61502916214059,
12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6,
1.5056327351493116e-7 };

static std::complex<double> tgamma(const std::complex<double>& z) noexcept
{
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

//get rid of templates
#pragma region Factorial

template<RealNumber EvalTo, RealNumber T>
std::expected<EvalTo, MathError<T>> Factorial(T A) noexcept {
	if (A <= 0 && fmod(A, 1) == 0) {
		return std::unexpected(MathError<T>(
			EOperation::Factorial,
			"The factorial does not exist for negative integers.",
			std::vector<T>{A}));
	}
	return static_cast<EvalTo>(std::tgamma(A+1));
};


static std::expected<std::complex<double>, MathError<std::complex<double>>> Factorial(
	std::complex<double> A) noexcept {
	return tgamma(A+std::complex<double>(1.0, 0.0));
};

#pragma endregion

//get rid of templates and unnecessary validity checks
#pragma region nCr

template<RealNumber EvalTo, RealNumber T>
std::expected<EvalTo, MathError<T>> nCr(T N, T R) {
	if (R < T(0) || R > N) {
		return 0;
	}
	std::expected<T, MathError<T>> a = Factorial<T, T>(N),
		b = Factorial<T, T>(N - R),
		c = Factorial<T, T>(R);
	[[unlikely]] if (!a.has_value()) {
		return std::unexpected(MathError<T>(
			EOperation::nCr,
			a.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					std::to_string(N).append(std::string(")]")))),
			std::vector<T>{N, R}));
	}
	[[unlikely]] if (!b.has_value()) {
		return std::unexpected(MathError<T>(
			EOperation::nCr,
			b.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					std::to_string(N - R).append(std::string(")]")))),
			std::vector<T>{N, R}));
	}
	[[unlikely]] if (!c.has_value()) {
		return std::unexpected(MathError<T>(
			EOperation::nCr,
			c.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					std::to_string(R).append(std::string(")]")))),
			std::vector<T>{N, R}));
	}
	return static_cast<EvalTo>(a.value() / (b.value() * c.value()));
}



static std::expected<std::complex<double>, MathError<
	std::complex<double>>> nCr(std::complex<double> N, std::complex<double> R) {
	std::expected<std::complex<double>, MathError<std::complex<double>>> 
		a = Factorial(N),
		b = Factorial(N - R),
		c = Factorial(R);
	if (!a.has_value()) {
		return std::unexpected(MathError<std::complex<double>>(
			EOperation::nCr,
			a.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					ToString(N).append(std::string(")]")))),
			std::vector<std::complex<double>>{N, R}));
	}
	if (!b.has_value()) {
		return std::unexpected(MathError<std::complex<double>>(
			EOperation::nCr,
			b.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					ToString(N - R).append(std::string(")]")))),
			std::vector<std::complex<double>>{N, R}));
	}
	if (!c.has_value()) {
		return std::unexpected(MathError<std::complex<double>>(
			EOperation::nCr,
			c.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					ToString(R).append(std::string(")]")))),
			std::vector<std::complex<double>>{N, R}));
	}
	return a.value() / (b.value() * c.value());
}

#pragma endregion

//get rid of templates and unnecessary validity checks
#pragma region nPr

template<RealNumber EvalTo, RealNumber T>
std::expected<EvalTo, MathError<T>> nPr(T N, T R) {
	if (R < T(0) || R > N) {
		return 0;
	}
	std::expected<T, MathError<T>> a = Factorial<T, T>(N),
		b = Factorial<T, T>(N - R);
	[[unlikely]] if (!a.has_value()) {
		return std::unexpected(MathError<T>(
			EOperation::nPr,
			a.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					std::to_string(N).append(std::string(")]")))),
			std::vector<T>{N, R}));
	}
	[[unlikely]] if (!b.has_value()) {
		return std::unexpected(MathError<T>(
			EOperation::nPr,
			b.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					std::to_string(N - R).append(std::string(")]")))),
			std::vector<T>{N, R}));
	}
	return static_cast<EvalTo>(a.value() / b.value());
}



static std::expected<std::complex<double>, MathError<
	std::complex<double>>> nPr(std::complex<double> N, std::complex<double> R) {
	std::expected<std::complex<double>, MathError<std::complex<double>>>
		a = Factorial(N),
		b = Factorial(N - R);
	if (!a.has_value()) {
		return std::unexpected(MathError<std::complex<double>>(
			EOperation::nPr,
			a.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					ToString(N).append(std::string(")]")))),
			std::vector<std::complex<double>>{N, R}));
	}
	if (!b.has_value()) {
		return std::unexpected(MathError<std::complex<double>>(
			EOperation::nPr,
			b.error().GetErrorMessage().append(
				std::string(" [Encountered when evaluating Factorial(").append(
					ToString(N - R).append(std::string(")]")))),
			std::vector<std::complex<double>>{N, R}));
	}
	return a.value() / b.value();
}

#pragma endregion

#pragma endregion

//a lot of stuff
#pragma region Parsing

#pragma region Operation Name Maps

template<RealNumber T>
const std::unordered_map<EOperation, std::function<std::expected<T, MathError<T>>(T, T)>>
OperationNameToBinaryOperationMap
{
	{EOperation::Add, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Add<T>))},
	{EOperation::Substract, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Substract<T>))},
	{EOperation::Multiply, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Multiply<T>))},
	{EOperation::Divide, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Divide<T>))},
	{EOperation::Power, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Power<T>))},
	{EOperation::Logarithm, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&Logarithm<T>))},
	{EOperation::nCr, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&nCr<T>))},
	{EOperation::nPr, std::function<std::expected<T, MathError<T>>(T, T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T, T)>(&nPr<T>))}
};

template<RealNumber T>
const std::unordered_map<EOperation, std::function<std::expected<T, MathError<T>>(T)>>
OperationNameToUnaryOperationMap
{
	{EOperation::Exponential, std::function<std::expected<T, MathError<T>>(T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T)>(&Exponential<T>))},
	{EOperation::Ln, std::function<std::expected<T, MathError<T>>(T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T)>(&Ln<T>))},
	{EOperation::Factorial, std::function<std::expected<T, MathError<T>>(T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T)>(&Factorial<T>))},
	{EOperation::Negate, std::function<std::expected<T, MathError<T>>(T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T)>(&Negate<T>))},
	{EOperation::Retain, std::function<std::expected<T, MathError<T>>(T)>(
		static_cast<std::expected<T, MathError<T>>(*)(T)>(&Retain<T>))}
};

using ComplexReturn = std::expected<std::complex<double>, MathError<std::complex<double>>>;

static const std::unordered_map<EOperation, std::function<ComplexReturn
(std::complex<double>, std::complex<double>)>>
OperationNameToComplexBinaryOperationMap
{
	{EOperation::Add, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Add<std::complex<double>>))},
	{EOperation::Substract, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Substract<std::complex<double>>))},
	{EOperation::Multiply, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Multiply<std::complex<double>>))},
	{EOperation::Divide, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Divide<std::complex<double>>))},
	{EOperation::Power, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Power))},
	{EOperation::Logarithm, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&Logarithm))},
	{EOperation::nCr, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&nCr))},
	{EOperation::nPr, std::function<ComplexReturn
		(std::complex<double>, std::complex<double>)>(static_cast<ComplexReturn
		(*)(std::complex<double>, std::complex<double>)>(&nPr))}
};

static const std::unordered_map<EOperation, std::function<ComplexReturn(std::complex<double>)>>
	OperationNameToComplexUnaryOperationMap
{
	{EOperation::Exponential, std::function<ComplexReturn(std::complex<double>)>(
		static_cast<ComplexReturn(*)(std::complex<double>)>(&Exponential<std::complex<double>>))},
	{EOperation::Ln, std::function<ComplexReturn(std::complex<double>)>(
		static_cast<ComplexReturn(*)(std::complex<double>)>(&Ln))},
	{EOperation::Factorial, std::function<ComplexReturn(std::complex<double>)>(
		static_cast<ComplexReturn(*)(std::complex<double>)>(&Factorial))},
	{EOperation::Negate, std::function<ComplexReturn(std::complex<double>)>(
		static_cast<ComplexReturn(*)(std::complex<double>)>(&Negate<std::complex<double>>))},
	{EOperation::Retain, std::function<ComplexReturn(std::complex<double>)>(
		static_cast<ComplexReturn(*)(std::complex<double>)>(&Retain<std::complex<double>>))}
};

#pragma endregion

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

#define ClearSubStr if(!CurrentSubString.empty()){\
	if(IsNumeric(CurrentSubString)){\
		if (IsNumericType(TokenVec.back())) {\
			TokenVec.push_back(Token<T>(ETokenType::Multiply));\
		}\
		TokenVec.push_back(Token<T>(static_cast<T>(std::stod(CurrentSubString))));\
		CurrentSubString.clear();\
	} else {\
		if (IsNumericType(TokenVec.back())) {\
			TokenVec.push_back(Token<T>(ETokenType::Multiply));\
		}\
		TokenVec.push_back(Token<T>(CurrentSubString));\
		CurrentSubString.clear();\
	}\
}

template<RealNumber T>
std::expected<std::vector<Token<T>>, bool> Tokenize(std::string_view Input) {
	std::vector<Token<T>> TokenVec{Token<T>(ETokenType::StartToken)};
	//uint64_t CharIndex = 0;
	std::string CurrentSubString{};
	bool bShouldReturnValue = true;
	while (!Input.empty()) {
		switch (Input.at(0)) {
#pragma region Special Characters
		case ' ':
			ClearSubStr;
			break;
		case '(':
			ClearSubStr;
			if (IsNumericType(TokenVec.back())) {
				TokenVec.push_back(Token<T>(ETokenType::Multiply));
			}
			TokenVec.push_back(Token<T>(ETokenType::OpenParenthesis));
			break;
		case ')':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::ClosedParenthesis));
			break;
		case '{':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::OpenCurlyBrace));
			break;
		case '}':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::ClosedCurlyBrace));
			break;
		case '[':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::OpenBracket));
			break;
		case ']':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::ClosedBracket));
			break;
		case ',':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Comma));
			break;
		case ';':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Semicolon));
			break;
		case ':':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Colon));
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
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<T>(ETokenType::Multiply));
				}
				TokenVec.push_back(Token<T>(CurrentSubString));
				CurrentSubString.clear();
			}
			break;
#pragma endregion
#pragma region Operators
		case '+':
			ClearSubStr;
			if (TokenVec.back().Type == ETokenType::OpenParenthesis ||
				TokenVec.back().Type == ETokenType::Comma ||
				TokenVec.back().Type == ETokenType::Semicolon
				) {
				break;
			}
			if (TokenVec.back().Type == ETokenType::Add ||
				TokenVec.back().Type == ETokenType::Substract ||
				TokenVec.back().Type == ETokenType::Negate ||
				TokenVec.back().Type == ETokenType::Retain) {
				break;
			}
			TokenVec.push_back(Token<T>(ETokenType::Add));
			break;
		case '-':
			ClearSubStr;
			if (TokenVec.back().Type == ETokenType::OpenParenthesis ||
				TokenVec.back().Type == ETokenType::Comma ||
				TokenVec.back().Type == ETokenType::Semicolon
				) {
				TokenVec.push_back(Token<T>(ETokenType::Negate));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Add) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<T>(ETokenType::Substract));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Substract) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<T>(ETokenType::Add));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Negate) {
				TokenVec.pop_back();
				break;
			}
			if (TokenVec.back().Type == ETokenType::Retain) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<T>(ETokenType::Negate));
			}
			TokenVec.push_back(Token<T>(ETokenType::Substract));
			break;
		case '*':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Multiply));
			break;
		case '/':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Divide));
			break;
		case '^':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Power));
			break;
		case '!':
			ClearSubStr;
			TokenVec.push_back(Token<T>(ETokenType::Factorial));
			break;
#pragma endregion
#pragma region Functions (and such)
		case 'e':
			if (CurrentSubString.empty() || IsNumeric(CurrentSubString)) {
				ClearSubStr;
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<T>(ETokenType::Multiply));
				}
				if (Input.at(1) == '^') {
					TokenVec.push_back(Token<T>(ETokenType::Exponential));
					Input = std::string_view(Input.begin() + 1, Input.end());
					break;
				}
				TokenVec.push_back(Token<T>(ETokenType::e));
				break;
			} else {
				CurrentSubString.append(1, 'e');
				if (InputOperationNames.contains(CurrentSubString)) {
					TokenVec.push_back(Token<T>(
						OperationNameToTokenType.at(
						InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
					TokenVec.push_back(Token<T>(
						InputTrigFunctionNames.at(CurrentSubString)));
					CurrentSubString.clear();
					break;
				}
				break;
			}
		default:
			if (IsNumeric(CurrentSubString)) {
				ClearSubStr;
			}
			CurrentSubString.append(1, Input.at(0));
			if (CurrentSubString == std::string("pi")) {
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<T>(ETokenType::Multiply));
				}
				TokenVec.push_back(Token<T>(ETokenType::pi));
				CurrentSubString.clear();
				break;
			}
			if (InputOperationNames.contains(CurrentSubString)) {
				TokenVec.push_back(Token<T>(
					OperationNameToTokenType.at(
						InputOperationNames.at(CurrentSubString))));
				CurrentSubString.clear();
				break;
			}
			else if (InputTrigFunctionNames.contains(CurrentSubString) &&
				!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
				TokenVec.push_back(Token<T>(
					InputTrigFunctionNames.at(CurrentSubString)));
				CurrentSubString.clear();
				break;
			}
#pragma endregion
		}
		Input = std::string_view(Input.begin() + 1, Input.end());
	}
	ClearSubStr;
	if (!bShouldReturnValue) {
		return std::unexpected(false);
	}
	TokenVec.push_back(Token<T>(ETokenType::EndToken));
	return TokenVec;
};

#undef ClearSubStr
//25 sum{5sin(2^e), pi*3}(acoth(21!+(-5*8)))
#define ClearSubStr if(!CurrentSubString.empty()){\
	if(IsNumeric(CurrentSubString)){\
		if (IsNumericType(TokenVec.back())) {\
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));\
		}\
		TokenVec.push_back(Token<std::complex<double>>(std::complex<double>(std::stod(CurrentSubString), 0)));\
		CurrentSubString.clear();\
	} else {\
		if (IsNumericType(TokenVec.back())) {\
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));\
		}\
		TokenVec.push_back(Token<std::complex<double>>(CurrentSubString));\
		CurrentSubString.clear();\
	}\
}

static std::expected<std::vector<Token<std::complex<double>>>, bool> Tokenize(
	std::string_view Input) {
	std::vector<Token<std::complex<double>>> TokenVec{Token<std::complex<double>>(ETokenType::StartToken)};
	//uint64_t CharIndex = 0;
	std::string CurrentSubString{};
	bool bShouldReturnValue = true;
	while (!Input.empty()) {
		switch (Input.at(0)) {
#pragma region Special Characters
		case ' ':
			ClearSubStr;
			break;
		case '(':
			ClearSubStr;
			if (IsNumericType(TokenVec.back())) {
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
			}
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenParenthesis));
			break;
		case ')':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedParenthesis));
			break;
		case '{':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenCurlyBrace));
			break;
		case '}':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedCurlyBrace));
			break;
		case '[':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::OpenBracket));
			break;
		case ']':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::ClosedBracket));
			break;
		case ',':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Comma));
			break;
		case ';':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Semicolon));
			break;
		case ':':
			ClearSubStr;
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
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
				}
				TokenVec.push_back(Token<std::complex<double>>(CurrentSubString));
				CurrentSubString.clear();
			}
			break;
#pragma endregion
#pragma region Operators
		case '+':
			ClearSubStr;
			if (TokenVec.back().Type == ETokenType::OpenParenthesis ||
				TokenVec.back().Type == ETokenType::Comma ||
				TokenVec.back().Type == ETokenType::Semicolon
				) {
				break;
			}
			if (TokenVec.back().Type == ETokenType::Add ||
				TokenVec.back().Type == ETokenType::Substract ||
				TokenVec.back().Type == ETokenType::Negate ||
				TokenVec.back().Type == ETokenType::Retain) {
				break;
			}
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Add));
			break;
		case '-':
			ClearSubStr;
			if (TokenVec.back().Type == ETokenType::OpenParenthesis ||
				TokenVec.back().Type == ETokenType::Comma ||
				TokenVec.back().Type == ETokenType::Semicolon
				) {
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Negate));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Add) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Substract));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Substract) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Add));
				break;
			}
			if (TokenVec.back().Type == ETokenType::Negate) {
				TokenVec.pop_back();
				break;
			}
			if (TokenVec.back().Type == ETokenType::Retain) {
				TokenVec.pop_back();
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::Negate));
			}
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Substract));
			break;
		case '*':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
			break;
		case '/':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Divide));
			break;
		case '^':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Power));
			break;
		case '!':
			ClearSubStr;
			TokenVec.push_back(Token<std::complex<double>>(ETokenType::Factorial));
			break;
#pragma endregion
#pragma region Functions (and such)
		case 'i':
			if (CurrentSubString.empty() || IsNumeric(CurrentSubString)) {
				ClearSubStr;
				if (TokenVec.back().Type == ETokenType::Number ||
					TokenVec.back().Type == ETokenType::pi ||
					TokenVec.back().Type == ETokenType::e) {
					TokenVec.back().Value = std::complex<double>(0, TokenVec.back().Value.real());
					break;
				}
				else {
					if (IsNumericType(TokenVec.back())) {
						TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
					}
					TokenVec.push_back(Token<std::complex<double>>(std::complex<double>(0, 1)));
					break;
				}
			}
			else {
				CurrentSubString.append(1, 'i');
				if (CurrentSubString == std::string("pi")) {
					if (IsNumericType(TokenVec.back())) {
						TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
					}
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::pi));
					CurrentSubString.clear();
					break;
				}
				else if (InputOperationNames.contains(CurrentSubString)) {
					TokenVec.push_back(Token<std::complex<double>>(
						OperationNameToTokenType.at(
							InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString+Input.at(1))) {
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
				ClearSubStr;
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
				}
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
					TokenVec.push_back(Token<std::complex<double>>(
						OperationNameToTokenType.at(
							InputOperationNames.at(CurrentSubString))));
					CurrentSubString.clear();
					break;
				}
				else if (InputTrigFunctionNames.contains(CurrentSubString) &&
					!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
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
				ClearSubStr;
			}

			CurrentSubString.append(1, Input.at(0));
			if (CurrentSubString == std::string("pi")) {
				if (IsNumericType(TokenVec.back())) {
					TokenVec.push_back(Token<std::complex<double>>(ETokenType::Multiply));
				}
				TokenVec.push_back(Token<std::complex<double>>(ETokenType::pi));
				CurrentSubString.clear();
				break;
			}
			if (InputOperationNames.contains(CurrentSubString)) {
				TokenVec.push_back(Token<std::complex<double>>(
					OperationNameToTokenType.at(
						InputOperationNames.at(CurrentSubString))));
				CurrentSubString.clear();
				break;
			}
			else if (InputTrigFunctionNames.contains(CurrentSubString) &&
				!InputTrigFunctionNames.contains(CurrentSubString + Input.at(1))) {
				TokenVec.push_back(Token<std::complex<double>>(
					InputTrigFunctionNames.at(CurrentSubString)));
				CurrentSubString.clear();
				break;
			}
#pragma endregion
		}
		Input = std::string_view(Input.begin() + 1, Input.end());
	}
	ClearSubStr;
	if (!bShouldReturnValue) {
		return std::unexpected(false);
	}
	TokenVec.push_back(Token<std::complex<double>>(ETokenType::EndToken));
	return TokenVec;
};

#undef ClearSubStr
#pragma endregion

#pragma region Parser

template<Number T>
std::expected<std::deque<Token<T>>, bool> Parse(const std::vector<Token<T>>& Tokens) {
	bool bShouldReturnParsedTokens = true;
	std::deque<Token<T>> ParsedTokenStack{};
	std::stack<Token<T>> OperatorStack{};
	for (auto& Tok : Tokens) {
		if (IsNumericType<T>(Tok)) {
			ParsedTokenStack.push_back(Tok);
			continue;
		}
		if (IsOperatorType<T>(Tok)) {
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
		if (IsSeparatorType<T>(Tok)) {
			if (Tok.Type == ETokenType::EndToken) {
				while (!OperatorStack.empty()) {
					ParsedTokenStack.push_back(OperatorStack.top());
					OperatorStack.pop();
				}
				//ParsedTokenStack.push_back(Tok);
				//for now, later
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
			else {
				OperatorStack.push(Tok);
				continue;
			}
		}
	}
	if (!bShouldReturnParsedTokens) {
		return std::unexpected(false);
	}
	return ParsedTokenStack;
}

#pragma endregion

#pragma region Evaluator

enum class EStopConsumingCondition : uint8_t {
	CorrectParenthesis,
	IteratorBodyEnd
};

static const std::unordered_map<ETokenType, ETokenType> CorrespondingToken{
	{ETokenType::OpenParenthesis, ETokenType::ClosedParenthesis},
	{ETokenType::OpenCurlyBrace, ETokenType::ClosedCurlyBrace},
	{ETokenType::ClosedParenthesis, ETokenType::OpenParenthesis},
	{ETokenType::ClosedCurlyBrace, ETokenType::OpenCurlyBrace},
	{ETokenType::OpenBracket, ETokenType::ClosedBracket},
	{ETokenType::ClosedBracket, ETokenType::OpenBracket}
};

template<Number T>
std::expected<std::deque<Token<T>>, bool> ConsumeUntilCorrectParenthesis(
	std::deque<Token<T>>& InputTokens, ETokenType StopTokenType) {
	std::deque<Token<T>> ConsumedTokens{};
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

template<Number T>
std::expected<std::deque<Token<T>>, bool> ConsumeIteratorBody(
	std::deque<Token<T>>& InputTokens, ETokenType StopTokenType) {
	uint8_t NestedIteratorCount = 1;
	std::deque<Token<T>> ConsumedTokens{};
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

template<Number T>
std::expected<std::deque<Token<T>>, bool> ConsumeUntilToken(std::deque<Token<T>>& InputTokens,
	ETokenType StopTokenType, EStopConsumingCondition Behavior) {
	std::expected<std::deque<Token<T>>, bool> Consumed{};
	switch (Behavior) {
	case EStopConsumingCondition::CorrectParenthesis:
		Consumed = ConsumeUntilCorrectParenthesis<T>(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	case EStopConsumingCondition::IteratorBodyEnd:
		Consumed = ConsumeIteratorBody<T>(InputTokens, StopTokenType);
		if (Consumed.has_value()) {
			return Consumed.value();
		}
		else {
			return std::unexpected(false);
		}
		break;
	}
	return std::unexpected(false);
};

template<Number T>
std::expected<T, bool> Eval(std::deque<Token<T>> Tokens) {
	std::vector<Token<T>> CurrentTokens{};
	bool bIsRangeIterator = false;
	bool bShouldReturnResult = true;
	Token<T> CurrentToken{T(0)};
	while (!Tokens.empty()) {
		CurrentToken = Tokens.front();
		Tokens.pop_front();
		switch (CurrentToken.Type) {
		case ETokenType::Comma:
			bIsRangeIterator = true;
			CurrentTokens.push_back(CurrentToken);
			break;
		case ETokenType::Semicolon:
			bIsRangeIterator = false;
			CurrentTokens.push_back(CurrentToken);
			break;
		case ETokenType::Name:
			if (Variables<T>.contains(CurrentToken.Name)) {
				CurrentTokens.push_back(Token<T>(Variables<T>.at(CurrentToken.Name)));
				break;
			}
			CurrentTokens.push_back(CurrentToken);
			break;
		case ETokenType::Number:
			CurrentTokens.push_back(CurrentToken);
			break;
		case ETokenType::pi:
			CurrentTokens.push_back(Token<T>(static_cast<T>(pi)));
			break;
		case ETokenType::e:
			CurrentTokens.push_back(Token<T>(static_cast<T>(e)));
			break;
		case ETokenType::OpenCurlyBrace:
			//unfinished
			break;
		}
	}
};

#pragma endregion

#pragma endregion

