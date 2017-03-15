#include <cmath>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

namespace matrix::transform2d {
	Matrix rotate(double theta) {
		double cost = cos(theta);
		double sint = sin(theta);

		return Matrix{2, 2, {cost, -sint, sint, cost}};
	}
	
	Matrix stretch(double xfactor, double yfactor) {
		return Matrix{2, 2, {xfactor, 0.0, 0.0, yfactor}};
	}

	Matrix shear(double xslant, double yslant) {
		return Matrix{2, 2, {1.0, xslant, yslant, 1.0}};
	}

	Matrix reflect(double theta) {
		double cos2t = cos(2*theta);
		double sin2t = sin(2*theta);

		return Matrix{2, 2, {cos2t, sin2t, sin2t, -cos2t}};
	}
}
