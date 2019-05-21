#pragma once
#include <vector>
typedef std::vector<std::pair<std::string, std::string>> Vpss;
class Language
{
public:
	enum TypeL{russian = 0, english};
private:
	const int count_phrases = 97;
	TypeL now;
	Vpss map;
public:

	Language() {}
	Language(const Language&) = delete;
	Language&operator=(Language&) = delete;

	static Language& get() {
		static Language  instance;
		return instance;
	}
	std::string MsgAt(int i);
	TypeL Current();
	void SetLanguage(TypeL t);
	bool read_from_file(std::string ru, std::string eng);
	
};

