#pragma once
#include <unordered_set>
#include <string>

class Thesaurus {
public:
	static bool IsEatSynonym(std::string&);
	static bool IsTrashSynonym(std::string&);
private:
	static std::unordered_set<std::string> eatSynonyms;
	static std::unordered_set<std::string> trashSynonyms;
};