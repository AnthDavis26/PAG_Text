#include "Thesaurus.h"


std::unordered_set<std::string> Thesaurus::eatSynonyms = {
	"eat", "devour", "ingest", "partake", "consume", "indulge", "inhale", "swallow",
	"chew", "absorb"
};

std::unordered_set<std::string> Thesaurus::trashSynonyms = {
	"trash", "garbage", "filth", "rubbish", "waste", "litter", "junk",
	"detritus"
};

bool Thesaurus::IsEatSynonym(std::string& str) {
    return eatSynonyms.find(str) != eatSynonyms.end();
}

bool Thesaurus::IsTrashSynonym(std::string& str) {
    return trashSynonyms.find(str) != trashSynonyms.end();
}
