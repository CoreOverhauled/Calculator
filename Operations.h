#pragma once
/*
Add functions:
*/
#pragma region Includes
#include <cmath>
#include<numbers>
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
constexpr static const double pi = std::numbers::pi;
constexpr static const double e = std::numbers::e;
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

std::string ToString(const std::vector<double>& X);
std::string ToString(const std::vector<std::complex<double>>& X);
std::string ToString(const std::complex<double>& x);

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

#pragma region Trig Functions

double cot(double x) noexcept;
double coth(double x) noexcept;
double acot(double x) noexcept;
double acoth(double x) noexcept;
std::complex<double> cot(const std::complex<double>& x) noexcept;
std::complex<double> coth(const std::complex<double>& x) noexcept;
std::complex<double> acot(const std::complex<double>& x) noexcept;
std::complex<double> acoth(const std::complex<double>& x) noexcept;

std::expected<double, MathError<double>>
TrigFunction(double A, ETrigFunc Function);

std::expected<std::complex<double>, MathError<std::complex<double>>>
TrigFunction( const std::complex<double>& A, ETrigFunc Function);
#pragma endregion

#pragma region Iterating Operations

std::expected<double, MathError<double>> Sum(uint64_t BoundMin, uint64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, uint64_t>));

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	uint64_t BoundMin, uint64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, uint64_t>));

std::expected<double, MathError<double>> Sum(
	std::vector<double> IteratedSet, std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, double>));

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>));

std::expected<double, MathError<double>> Product(uint64_t BoundMin, uint64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, uint64_t>));

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	uint64_t BoundMin, uint64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, uint64_t>));

std::expected<double, MathError<double>> Product(
	std::vector<double> IteratedSet, std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, double>));

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>));

#pragma endregion

#pragma region Factorial Related Operations

std::complex<double> tgamma(const std::complex<double>& z);

#pragma region Factorial

std::expected<double, MathError<double>> Factorial(double A);

static std::expected<std::complex<double>, MathError<std::complex<double>>> Factorial(
	std::complex<double> A);

#pragma endregion

#pragma region nCr

std::expected<double, MathError<double>> nCr(double N, double R);

std::expected<std::complex<double>, MathError<
	std::complex<double>>> nCr(std::complex<double> N, std::complex<double> R);

#pragma endregion

#pragma region nPr

std::expected<double, MathError<double>> nPr(double N, double R);

std::expected<std::complex<double>, MathError<
	std::complex<double>>> nPr(std::complex<double> N, std::complex<double> R);

#pragma endregion

#pragma endregion

//a lot of stuff
#pragma region Parsing

#pragma region Tokenizer

std::expected<std::vector<Token<double>>, bool> Tokenize(std::string_view Input);

std::expected<std::vector<Token<std::complex<double>>>, bool> TokenizeComplex(std::string_view Input);

#pragma endregion

#pragma region Parser

std::expected<std::deque<Token<double>>, bool> Parse(const std::vector<Token<double>>& Tokens);

std::expected<std::deque<Token<std::complex<double>>>, bool> Parse(
	const std::vector<Token<std::complex<double>>>& Tokens);

#pragma endregion

#pragma region Evaluator

#pragma region Consume Tokens

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

std::expected<std::deque<Token<double>>, bool> ConsumeUntilCorrectParenthesis(
	std::deque<Token<double>>& InputTokens, ETokenType StopTokenType);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilCorrectParenthesis(
	std::deque<Token<std::complex<double>>>& InputTokens, ETokenType StopTokenType);


std::expected<std::deque<Token<double>>, bool> ConsumeIteratorBody(
	std::deque<Token<double>>& InputTokens, ETokenType StopTokenType);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeIteratorBody(
	std::deque<Token<std::complex<double>>>& InputTokens, ETokenType StopTokenType);


std::expected<std::deque<Token<double>>, bool> ConsumeUntilToken(
	std::deque<Token<double>>& InputTokens,
	ETokenType StopTokenType, EStopConsumingCondition Behavior);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilToken(
	std::deque<Token<std::complex<double>>>& InputTokens,
	ETokenType StopTokenType, EStopConsumingCondition Behavior);

#pragma endregion

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

