#pragma once

#pragma region Includes
#include <cmath>
#include <numbers>
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

#pragma region Debug

//#define ISDEBUGMODE
constexpr inline bool IsDebugMode() {
#ifdef ISDEBUGMODE
	return true;
#else
	return false;
#endif
}

#define LOG_FUNC if constexpr (IsDebugMode()) { std::cout << __func__ << " called\n"; }

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
//syntax be like:[a:12+5^0.5]sum{d:0,50a}(prod{f:d;d+1;15;(3pi)!}(tanh(f)))
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
			+ ": " + InErrorMessage + " (Operands were:" + ToString(InPassedArguments) + ')' + '\n') {
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

#pragma region Variables

static std::unordered_map<std::string, double> Variables{};
static std::unordered_map<std::string, std::complex<double>> ComplexVariables;

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

std::expected<double, MathError<double>> Sum(int64_t BoundMin, int64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, int64_t>, std::deque<Token<double>>),
	std::deque<Token<double>> Body);

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	int64_t BoundMin, int64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, int64_t>,
		std::deque<Token<std::complex<double>>>), std::deque<Token<std::complex<double>>> Body);

std::expected<double, MathError<double>> Sum(
	std::vector<double> IteratedSet, std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, double>, std::deque<Token<double>>),
	std::deque<Token<double>> Body);

std::expected<std::complex<double>, MathError<std::complex<double>>> Sum(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>,
		std::deque<Token<std::complex<double>>>), std::deque<Token<std::complex<double>>> Body);

std::expected<double, MathError<double>> Product(int64_t BoundMin, int64_t BoundMax,
	std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, int64_t>, std::deque<Token<double>>),
	std::deque<Token<double>> Body);

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	int64_t BoundMin, int64_t BoundMax, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, int64_t>,
		std::deque<Token<std::complex<double>>>), std::deque<Token<std::complex<double>>> Body);

std::expected<double, MathError<double>> Product(
	std::vector<double> IteratedSet, std::string IteratorVariableName,
	double(*Expression)(std::pair<const std::string&, double>, std::deque<Token<double>>),
	std::deque<Token<double>> Body);

std::expected<std::complex<double>, MathError<std::complex<double>>> Product(
	std::vector<std::complex<double>> IteratedSet, std::string IteratorVariableName,
	std::complex<double>(*Expression)(std::pair<const std::string&, std::complex<double>>,
		std::deque<Token<std::complex<double>>>), std::deque<Token<std::complex<double>>> Body);

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
	IteratorBodyEnd,
	Separator
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
	std::deque<Token<double>>& InputTokens);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeIteratorBody(
	std::deque<Token<std::complex<double>>>& InputTokens);


std::expected<std::deque<Token<double>>, bool> ConsumeUntilSeparator(
	std::deque<Token<double>>& InputTokens);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilSeparator(
	std::deque<Token<std::complex<double>>>& InputTokens);


std::expected<std::deque<Token<double>>, bool> ConsumeUntilToken(
	std::deque<Token<double>>& InputTokens, EStopConsumingCondition Behavior,
	ETokenType StopTokenType = ETokenType::EndToken);

std::expected<std::deque<Token<std::complex<double>>>, bool> ConsumeUntilToken(
	std::deque<Token<std::complex<double>>>& InputTokens, EStopConsumingCondition Behavior,
	ETokenType StopTokenType = ETokenType::EndToken);

#pragma endregion

#pragma region Eval

std::expected<double, bool> Eval(std::deque<Token<double>> Tokens);

std::expected<std::complex<double>, bool> Eval(std::deque<Token<std::complex<double>>> Tokens);

#pragma endregion

#pragma endregion

#pragma endregion

