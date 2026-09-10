// cl: /Ireference/shims/bfmerendobj /G7 /arch:SSE2 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Dedicated TU for CollisionMath::Collide(LineSeg, AABox/OBBox). colmathline.cpp
// already holds four matched LineSeg collides; adding these there would
// recompile those bodies.
#include "rendobj.h"
#include "colmath.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"

#include <assert.h>

struct BoxTestStruct
{
	Vector3 Min;
	Vector3 Max;
	Vector3 P0;
	Vector3 DP;
	float Fraction;
	bool Inside;
	int Axis;
	int Side;
};

enum BoxSideType {
	BOX_SIDE_NEGATIVE = 0,
	BOX_SIDE_POSITIVE = 1,
	BOX_SIDE_MIDDLE = 2
};

static Vector3 _box_normal[3][2] =
{
	{
		Vector3(-1,0,0),
		Vector3(1,0,0)
	},
	{
		Vector3(0,-1,0),
		Vector3(0,1,0)
	},
	{
		Vector3(0,0,-1),
		Vector3(0,0,1)
	}
};

bool Test_Aligned_Box(BoxTestStruct * test);

bool CollisionMath::Collide(const LineSegClass & line,const AABoxClass & box,CastResultStruct * res)
{
	BoxTestStruct test;
	test.Min = box.Center - box.Extent;
	test.Max = box.Center + box.Extent;
	test.P0 = line.Get_P0();
	test.DP = line.Get_DP();

	if (!Test_Aligned_Box(&test)) {
		return false;
	}

	if (test.Inside) {
		res->StartBad = true;
		return true;
	}

	if (test.Fraction < res->Fraction) {
		res->Fraction = test.Fraction;
		assert(test.Side != BOX_SIDE_MIDDLE);
		res->Normal = _box_normal[test.Axis][test.Side];
		if (res->ComputeContactPoint) {
			res->ContactPoint = line.Get_P0() + res->Fraction * line.Get_DP();
		}
		return true;
	}
	return false;
}

bool CollisionMath::Collide(const LineSegClass & line,const OBBoxClass & box,CastResultStruct * result)
{
	BoxTestStruct test;
	test.Min = box.Center - box.Extent;
	test.Max = box.Center + box.Extent;

	test.P0 = (box.Basis.Transpose() * (line.Get_P0() - box.Center)) + box.Center;
	test.DP = box.Basis.Transpose() * line.Get_DP();

	if (!Test_Aligned_Box(&test)) {
		return false;
	}

	if (test.Inside) {
		result->StartBad = true;
		return true;
	}

	if (test.Fraction < result->Fraction) {
		result->Fraction = test.Fraction;
		assert(test.Side != BOX_SIDE_MIDDLE);

		switch (test.Axis) {
			case 0:
				result->Normal.Set(box.Basis[0][0],box.Basis[1][0],box.Basis[2][0]);
				break;

			case 1:
				result->Normal.Set(box.Basis[0][1],box.Basis[1][1],box.Basis[2][1]);
				break;

			case 2:
				result->Normal.Set(box.Basis[0][2],box.Basis[1][2],box.Basis[2][2]);
				break;
		}

		if (test.Side == BOX_SIDE_NEGATIVE) {
			result->Normal = -result->Normal;
		}
		if (result->ComputeContactPoint) {
			result->ContactPoint = line.Get_P0() + result->Fraction * line.Get_DP();
		}
		return true;
	}
	return false;
}

bool Test_Aligned_Box(BoxTestStruct * test)
{
	int i;
	float candidateplane[3];
	float maxt[3];
	Vector3 coord;
	int quadrant[3];
	bool inside = true;

	for (i=0; i<3; i++) {
		if (test->P0[i] < test->Min[i]) {
			quadrant[i] = BOX_SIDE_NEGATIVE;
			candidateplane[i] = test->Min[i];
			inside = false;
		} else if (test->P0[i] > test->Max[i]) {
			quadrant[i] = BOX_SIDE_POSITIVE;
			candidateplane[i] = test->Max[i];
			inside = false;
		} else {
			quadrant[i] = BOX_SIDE_MIDDLE;
		}
	}

	if (inside) {
		test->Fraction = 0.0f;
		test->Inside = true;
		return true;
	}

	for (i=0; i<3; i++) {
		if (quadrant[i] != BOX_SIDE_MIDDLE && test->DP[i] != 0.0f) {
			maxt[i] = (candidateplane[i] - test->P0[i]) / test->DP[i];
		} else {
			maxt[i] = -1.0f;
		}
	}

	int intersection_plane = 0;

	for (i=1; i<3; i++) {
		if (maxt[i] > maxt[intersection_plane]) {
			intersection_plane = i;
		}
	}

	if (maxt[intersection_plane] < 0.0f) {
		return false;
	}

	for (i=0; i<3; i++) {

		if (intersection_plane != i) {

			coord[i] = test->P0[i] + maxt[intersection_plane] * test->DP[i];

			if ((coord[i] < test->Min[i]) || (coord[i] > test->Max[i])) {

				return false;

			}

		} else {

			coord[i] = candidateplane[i];

		}
	}

	test->Fraction = maxt[intersection_plane];
	test->Inside = false;
	test->Axis = intersection_plane;
	test->Side = quadrant[intersection_plane];
	return true;
}
