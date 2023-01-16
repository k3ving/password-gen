#include <iostream>
#include <fstream>
#include <string>
#include <random>

const std::string numberDefault = "0123456789";
const std::string smallcaseDefault = "abcdefghijklmnopqrstuvwxyz";
const std::string uppercaseDefault = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string specialDefault = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";


class List {
	private:
		std::string numberList_;
		std::string smallcaseLetterList_;
		std::string uppercaseLetterList_;
		std::string specialCharacterList_;
		std::string selectedList_;
		std::string password_;

	public:
		List(std::string numbers, std::string smallcaseLetters, std::string uppercaseLetters, std::string specialCharacters) : numberList_(numbers), smallcaseLetterList_(smallcaseLetters), uppercaseLetterList_(uppercaseLetters), specialCharacterList_(specialCharacters) {}
		
		std::string selectList() {
			
			if(numberList_ == "default") {
				numberList_ = numberDefault;
			}

			if(smallcaseLetterList_ == "default") {
				smallcaseLetterList_ = smallcaseDefault;
			}

			if(uppercaseLetterList_ == "default") {
				uppercaseLetterList_ = uppercaseDefault;
			}

			if(specialCharacterList_ == "default") {
				specialCharacterList_ = specialDefault;
			}

			selectedList_ = numberList_ + smallcaseLetterList_ + uppercaseLetterList_ + specialCharacterList_;
			return selectedList_;
		}

		std::string generatePassword(int length) {
			for(int i = 0; i < length; ++i) {
				std::random_device rd;
				std::uniform_int_distribution<unsigned long> dist(0, selectedList_.length() - 1);
				password_ += selectedList_.at(dist(rd));
			}

			return password_;
		}
};

int main(int argc, char *argv[]) {
	if(argc != 6) {
		std::cerr << "USAGE:[length] [first list] [second list] [third list] [fourth list]" << "\n";
		return 1;
	}
	if(argc == 6) { 
		List list_obj {argv[2], argv[3], argv[4], argv[5]};
		list_obj.selectList();
		std::ofstream output;
		output.open("output");
		output << list_obj.generatePassword(std::atoi(argv[1])) << "\n";
}
	return 0;
}
