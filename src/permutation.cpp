/*
This is based upon the Steinhaus-Johnson-Trotter algorithm
https://en.wikipedia.org/wiki/Steinhaus–Johnson–Trotter_algorithm
This is used to iterate through every permutation (p) of the set S_(n).

The algorithm is slightly modified to use zero indexing instead, so that
{0, 1, 2} \in S_3. This makes more sense as we are using the results of the
permutations as indexes for the matrix.
*/

#include "matrix.hpp"
#define SWAP(a, b) tmp=(a); (a)=(b); (b)=tmp

namespace matrix {
	inline uint Matrix::permutation_position(uint n, uint i, uint *p) {
		for (uint j = 0; j < n; j++)
			if (p[j] == i)
				return j;
		return 0;
	}

	void Matrix::permutation_init(uint n, uint *p, uint *v) {
		for (uint i = 0; i < n; i++) {
			p[i] = i;
			v[i] = 0;
		}
	}

	int Matrix::permutation_permute(uint n, uint *p, uint *v) {
		uint i = n;
		while (i) {
			--i;
			uint pi = permutation_position(n, i, p);
			// Determine if mobile
			if (pi == 0 && !v[pi])
				continue;
			if (pi == n - 1 && v[pi])
				continue;
			if (!v[pi] && p[pi - 1] > i)
				continue;
			if (v[pi] && p[pi + 1] > i)
				continue;
			// Is largest mobile int
			uint tmp;
			uint sp = v[pi] ? pi + 1 : pi - 1;
			SWAP(p[pi], p[sp]);
			SWAP(v[pi], v[sp]);

			// Flip directions of larger ints
			for (uint j = i + 1; j < n; j++) {
				pi = permutation_position(n, j, p);
				v[pi] = !v[pi];
			}
			return 1;
		}
		return 0;
	}
}
