#include <iostream>
#include "Operations.h"

void Calculate() {
	std::string Input;
	std::cout << "Enter expression (real): ";
	std::getline(std::cin, Input);
	if (Input.empty()) {
		std::cout << "Can't evaluate nothing.\n";
		return;
	}
	using T = double;
	std::expected<std::vector<Token<T>>, bool> ExpectedTokens = Tokenize(Input);
	if (ExpectedTokens.has_value()) {
		std::vector<Token<T>> Tokens = ExpectedTokens.value();
#ifdef ISDEBUGMODE
		for (const auto& Tok : Tokens) {
			std::cout << Tok << ' ';
		}
		std::cout << '\n';
#endif
		std::expected<std::deque<Token<T>>, bool> ExpectedParsedTokens = Parse(Tokens);
		if (ExpectedParsedTokens.has_value()) {
			std::deque<Token<T>> ParsedTokens = ExpectedParsedTokens.value();
#ifdef ISDEBUGMODE
			for (const auto& Tok : ParsedTokens) {
				std::cout << Tok << ' ';
			}
			std::cout << '\n';
#endif
			std::expected<T, bool> ExpectedResult = Eval(ParsedTokens);
			if (ExpectedResult.has_value()) {
				std::cout << ExpectedResult.value() << '\n';
			}
			else {
				std::cout << "Error(s) encountered while evaluating input.\n";
			}
		}
		else {
			std::cout << "Error(s) encountered while parsing input.\n";
		}
	}
	else {
		std::cout << "Error(s) encountered while tokenizing input.\n";
	}
}

void CalculateComplex() {
	std::string Input;
	std::cout << "Enter expression (complex): ";
	std::getline(std::cin, Input);
	if (Input.empty()) {
		std::cout << "Can't evaluate nothing.\n";
		return;
	}
	using T = std::complex<double>;
	std::expected<std::vector<Token<T>>, bool> ExpectedTokens = TokenizeComplex(Input);
	if (ExpectedTokens.has_value()) {
		std::vector<Token<T>> Tokens = ExpectedTokens.value();
#ifdef ISDEBUGMODE
		for (const auto& Tok : Tokens) {
			std::cout << Tok << ' ';
		}
		std::cout << '\n';
#endif
		std::expected<std::deque<Token<T>>, bool> ExpectedParsedTokens = Parse(Tokens);
		if (ExpectedParsedTokens.has_value()) {
			std::deque<Token<T>> ParsedTokens = ExpectedParsedTokens.value();
#ifdef ISDEBUGMODE
			for (const auto& Tok : ParsedTokens) {
				std::cout << Tok << ' ';
			}
			std::cout << '\n';
#endif
			std::expected<T, bool> ExpectedResult = Eval(ParsedTokens);
			if (ExpectedResult.has_value()) {
				std::cout << ExpectedResult.value() << '\n';
			}
			else {
				std::cout << "Error(s) encountered while evaluating input.\n";
			}
		}
		else {
			std::cout << "Error(s) encountered while parsing input.\n";
		}
	}
	else {
		std::cout << "Error(s) encountered while tokenizing input.\n";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	bool bIsComplex = false;
	{
		std::cout << "Choose number system. r - real/c - complex: ";
		char NumSystem;
		while (!std::set<char>{'c', 'C', 'r', 'R'}.contains(NumSystem)) {
			std::cin >> NumSystem;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		bIsComplex = (NumSystem == 'C' || NumSystem == 'c');
	}
	while (true) {
		if (bIsComplex) {
			CalculateComplex();
		}
		else {
			Calculate();
		}
		std::cout << "Go again? y (yes)/c (change number system and go again)/n (no)(assumed): ";
		char GoAgain;
		std::cin >> GoAgain;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (GoAgain == 'Y' || GoAgain == 'y') {
			continue;
		}
		if (GoAgain == 'C' || GoAgain == 'c') {
			std::cout << "Choose number system. r - real/c - complex: ";
			char NumSystem = ' ';
			while (!std::set<char>{'c', 'C', 'r', 'R'}.contains(NumSystem)) {
				std::cin >> NumSystem;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			bIsComplex = (NumSystem == 'C' || NumSystem == 'c');
			continue;
		}
		break;
	}
}
