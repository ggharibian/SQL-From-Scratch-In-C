#ifndef WORD_H
#define WORD_H
#include <string>
using namespace std;

struct Word {
	string _word;	//Word to be stored
	int _frequency;	//Frequency of the word

	Word(string word = "", int freq = 1) : _word(word), _frequency(freq) {	}

			//Note: All functions for the structure are based off the word
			//, not it's frequency

	bool friend operator ==(const Word& w1, const Word& w2) {
		return w1._word == w2._word;
	}
	bool friend operator >=(const Word& w1, const Word& w2) {
		return !(w1 < w2);
	}

	bool friend operator <=(const Word& w1, const Word& w2) {
		return !(w1 > w2);
	}

	bool friend operator >(const Word& w1, const Word& w2) {
		return w1._word > w2._word;
	}
	bool friend operator <(const Word& w1, const Word& w2) {
		return w1._word < w2._word;
	}
};

#endif // !WORD_H
