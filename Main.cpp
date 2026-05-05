#include <iostream>
#include "Operations.h"

/*void Calculate() {
	
}*/

int main() {
	/*while (true) {
		Calculate();
		std::cout << "Go again? y/n(assumed)";
		char GoAgain;
		std::cin >> GoAgain;
		if (GoAgain == 'Y' or GoAgain == 'y') {
			continue;
		}
		break;
	}*/
	//std::cout << Sum(uint64_t(1), uint64_t(5), std::string("a"), [](std::pair<const std::string&, uint64_t> iter) -> double { return static_cast<double>(iter.second); }).value();
	constexpr double X = 2.448618111050801;
	std::string Input;
	std::getline(std::cin, Input);
	//using T = std::complex<double>;
	using T = double;
	std::expected<std::vector<Token<T>>, bool> ExpectedTokens = Tokenize(Input);
	if (ExpectedTokens.has_value()) {
		std::vector<Token<T>> Tokens = ExpectedTokens.value();
		for (auto& Tok : Tokens) {
			std::cout << Tok << ' ';
		}
		std::cout << '\n';
		std::expected<std::deque<Token<T>>, bool> ExpectedParsedTokens = Parse(Tokens);
		if (ExpectedParsedTokens.has_value()) {
			std::deque<Token<T>> ParsedTokens = ExpectedParsedTokens.value();
			for (auto& Tok : ParsedTokens) {
				std::cout << Tok << ' ';
			}
			std::cout << '\n';
		}
	}
	else {
		std::cout << "Error(s) encountered while parsing input.\n";
	}
	std::deque<Token<double>> A{Token<double>(ETokenType::OpenBracket), Token<double>(ETokenType::ClosedBracket)};
	ConsumeUntilToken<double>(A, ETokenType::ClosedBracket, EStopConsumingCondition::CorrectParenthesis);


	
	//system("pause");
}