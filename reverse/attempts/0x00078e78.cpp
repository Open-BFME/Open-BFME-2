// ?rva00078E78@Rva00078E78@@QAE_NPBV1@M@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /G7 /arch:SSE /MD
// ?rva00078E78@Rva00078E78@@QAE_NPBV1@M@Z @0x00078E78 285B
// Guarded visual-LOD equality: TheGameLODManager+0x1788 !=4 gate, +4 handle
// compare, +8/0x200 float compare, guarded Rva00078C10 LOD-index query,
// triple-entry int compare loop plus fabs(float diff) <= tol checks.
// Identity: callee row ?rva00078C10@Rva00078C10@@QAE_NPBV1@PAH1@Z,
// fabs import 0x00629210, TheGameLODManager extern in use.
#include <math.h>

class GameLODManager
{
public:
	char m_pad00[0x1788];
	int m_1788;
};

extern GameLODManager *TheGameLODManager;

struct Detail200
{
	char m_pad[0x200];
	float m_val;
};

class Rva00078C10
{
public:
	bool rva00078C10(Rva00078C10 const *other, int *outA, int *outB);
	char m_pad00[8];
	Detail200 *m_08;
	char m_pad0C[0x104];
	struct Entry
	{
		int m_00;
		float m_04;
		char m_pad08[8];
		int m_10;
		int m_14;
		char m_pad18[4];
	};
	Entry m_entries[2];
};

class Rva00078E78
{
public:
	bool rva00078E78(Rva00078E78 const *other, float tol);
private:
	Rva00078C10 *m_00;
	int m_04;
};


bool Rva00078E78::rva00078E78(Rva00078E78 const *other, float tol)
{
	if (TheGameLODManager->m_1788 == 4)
		return false;
	if (m_04 != other->m_04)
		return false;
	if (m_00->m_08->m_val != other->m_00->m_08->m_val)
		return false;
	if (m_00 != 0 && other->m_00 != 0)
	{
		int a;
		int b;
		if (m_00->rva00078C10(other->m_00, &a, &b))
		{
			if (a != b)
				return false;
		}
	}
	for (int i = 0; i <= 1; i++)
	{
		if (other->m_00->m_entries[i].m_00 != m_00->m_entries[i].m_00)
			return false;
		if (other->m_00->m_entries[i].m_00 != 0)
		{
			if (other->m_00->m_entries[i].m_14 != m_00->m_entries[i].m_14)
				return false;
			if (other->m_00->m_entries[i].m_10 != m_00->m_entries[i].m_10)
				return false;
		}
	}
	if (fabs(m_00->m_entries[0].m_04 - other->m_00->m_entries[0].m_04) > tol)
		return false;
	if (m_00->m_entries[1].m_00 == 0)
		return true;
	if (fabs(m_00->m_entries[1].m_04 - other->m_00->m_entries[1].m_04) > tol)
		return false;
	return true;
}
