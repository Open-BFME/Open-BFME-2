// cl: /MD
// ?rva002B3A48@Rva002B3A48@@QAEHXZ @0x002B3A48 84B
// Sum over pointer array at +8/+C: for each element take rowed 0x00318FBE int value minus [rowed 0x00319159 result +0x618] when non-null, accumulate.
// Evidence: unlock lane; callees rowed 0x00318FBE 0x00319159; callers 0x002B3B0B 0x002B3B16 compare two objects results; ret no args returning sum; honest address name.
class Rva00318FBE
{
public:
	int rva00318FBE();
};
class Rva00319159
{
public:
	void *rva00319159();
};
class Rva002B3A48
{
public:
	int rva002B3A48();
	int rva002B3A9C();
	bool rva002B3B07(Rva002B3A48 *other);
private:
	char m_pad00[0x8];
	Rva00318FBE **m_begin;
	Rva00318FBE **m_end;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
int Rva002B3A48::rva002B3A48()
{
	int sum = 0;
	unsigned int i = 0;
	for (; i < (unsigned int)(m_end - m_begin); ++i)
	{
		_ReadWriteBarrier();
		Rva00319159 *elem = (Rva00319159 *)m_begin[i];
		int v = ((Rva00318FBE *)elem)->rva00318FBE();
		char *q = (char *)elem->rva00319159();
		if (q)
			v -= *(int *)(q + 0x618);
		sum += v;
	}
	return sum;
}

// 0x002B3B07, 95B RET4. Compare two native summary values from this
// same receiver, breaking exact ties through the rowed game-logic RNG.
// Retail's source-path literal and line 6883 corroborate the approved
// LivingWorldLogic TU map; original class and comparator names unresolved.
int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);
bool Rva002B3A48::rva002B3B07(Rva002B3A48 *other)
{
 int first = rva002B3A48();
 int second = other->rva002B3A48();
 if (first != second)
  return first > second;
 first = rva002B3A9C();
 second = other->rva002B3A9C();
 if (first != second)
  return first > second;
 return GetGameLogicRandomValue(0, 1,
  "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldLogic.cpp", 6883) == 0;
}
