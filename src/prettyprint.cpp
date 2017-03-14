#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

string Matrix::pretty() const {
	ostringstream osstr, main;
	vector<string> strs;
	uint mwidth = 0;
	for (uint j = 0; j < n_; ++j) {
		for (uint i = 0; i < m_; ++i) {
			double term = (*this)(i, j);
			if (EQUAL(term,0))
				term = 0;
			osstr << term;
			string str = osstr.str();
			osstr.str(string());
			strs.push_back(str);
			uint nl = str.size();
			mwidth = nl > mwidth ? nl : mwidth;
		}
	}
	uint midwidth = (mwidth * n_) + ((n_ + 1) << 1);
	main << "\u250c\u2500" << setw(midwidth - 2) << "" << "\u2500\u2510";
	for (uint i = 0; i < m_; i++) {
		main << endl;
		main << "\u2502";
		for (uint j = 0; j < n_; j++) {
			string& str = strs[i + (j * m_)];
			int wlen = (str.size() + mwidth + 1) >> 1;
			main << "  ";
			main << setw(wlen);
			main << str;
			main << setw(mwidth - wlen) << "";
		}
		main << "  \u2502";

	}
	main << endl << "\u2514\u2500" << setw(midwidth - 2) << "" << "\u2500\u2518";
	return main.str();
}
