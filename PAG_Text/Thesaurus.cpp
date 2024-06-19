#include "Thesaurus.h"

std::unordered_set<std::string> Thesaurus::eatSynonyms = {
	"eat", "devour", "ingest", "partake", "consume", "indulge", "inhale", "swallow",
	"chew", "absorb"
};

std::unordered_set<std::string> Thesaurus::trashSynonyms = {
	"trash", "garbage", "filth", "rubbish", "waste", "litter", "junk",
	"detritus"
};

bool Thesaurus::IsEatSynonym(const std::string& str) {
    return Thesaurus::eatSynonyms.find(str) != Thesaurus::eatSynonyms.end();
}

bool Thesaurus::IsTrashSynonym(const std::string& str) {
    return Thesaurus::trashSynonyms.find(str) != Thesaurus::trashSynonyms.end();
}
