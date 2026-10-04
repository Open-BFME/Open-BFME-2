// ?rva00100568@?$SimpleDynVecClass@VVector3@@@@QAEXXZ
// partial score=0.93 date=2026-10-04
// ?rva00100568@?$SimpleDynVecClass@VVector3@@@@QAEXXZ
// partial score=0.93 date=2026-10-02
// cl: /O1 /G7 /arch:SSE /MD
//
// ?rva00100568@?$SimpleDynVecClass@VVector3@@@@QAEXXZ, retail 0x00100568, 400 bytes.
// Remove near-duplicate Vector3s within 0.01 (g_Va00BCF628) via fabs and Delete.
// Evidence: this+4/this+12 Vector/ActiveCount; idiv modulo indexing; fabs via
// 0x7fffffff mask in esi and comiss vs epsilon; three pairwise per-component
// compares; Delete((i+1)%count,1) row 0x00100306; caller 0x0010078B;
// prev simpledynvec_vector3_add_single /O1/G7.

extern float g_Va00BCF628;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	bool Delete(int index, bool allow_shrink);
	void rva00100568();

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

// ?rva00100568@?$SimpleDynVecClass@VVector3@@@@QAEXXZ present-unmatched
void SimpleDynVecClass<Vector3>::rva00100568()
{
	int count = ActiveCount;
	if (count == 0)
		return;
	float eps = g_Va00BCF628;
	if (count < 3)
		return;
	int mask = 0x7fffffff;
	int outer = 0;
	int inner = 2;
	while (true) {
		int prevIdx = (inner - 1) % count;
		int curIdx = inner % count;
		Vector3 *base = Vector;
		Vector3 *outerV = &base[outer];
		Vector3 *prevV = &base[prevIdx];
		Vector3 *curV = &base[curIdx];
		float dx1 = outerV->X - prevV->X;
		*(int *)&dx1 &= mask;
		if (eps <= dx1)
			goto check_cur;
		float dy1 = outerV->Y - prevV->Y;
		*(int *)&dy1 &= mask;
		if (eps <= dy1)
			goto check_cur;
		float dz1 = outerV->Z - prevV->Z;
		*(int *)&dz1 &= mask;
		if (eps > dz1)
			goto found;
	check_cur: {
			float dx2 = outerV->X - curV->X;
			*(int *)&dx2 &= mask;
			if (eps <= dx2)
				goto check_prev_cur;
			float dy2 = outerV->Y - curV->Y;
			*(int *)&dy2 &= mask;
			if (eps <= dy2)
				goto check_prev_cur;
			float dz2 = outerV->Z - curV->Z;
			*(int *)&dz2 &= mask;
			if (eps > dz2)
				goto found;
		}
	check_prev_cur: {
			float dx3 = prevV->X - curV->X;
			*(int *)&dx3 &= mask;
			if (eps <= dx3)
				goto next;
			float dy3 = prevV->Y - curV->Y;
			*(int *)&dy3 &= mask;
			if (eps <= dy3)
				goto next;
			float dz3 = prevV->Z - curV->Z;
			*(int *)&dz3 &= mask;
			if (eps > dz3)
				goto found;
		}
	next:
		outer++;
		inner++;
		if (outer >= ActiveCount)
			return;
		count = ActiveCount;
		continue;
	found: {
			int del = (outer + 1) % ActiveCount;
			Delete(del, true);
			outer = 0;
			eps = g_Va00BCF628;
			continue;
		}
	}
}
