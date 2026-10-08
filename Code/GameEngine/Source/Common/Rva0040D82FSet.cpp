// ?setFrom@Rva0040D82FHost@@QAIXHPAURva0040D82FArg@@@Z
// partial score=0.95 date=2026-10-05
// cl: /MD
//
// Change-detecting setter at retail 0x0040D82F (57B). Reads a candidate int
// out of the argument's +0x1C through a 3-arg cdecl helper, compares it with
// the host's +0x18 field, and when different stores it through the +0x14
// subobject's __stdcall set. Names are address-derived.
class Rva0040D82FSub
{
public:
	int m_first;
};

// The callees are the rowed STLport find<CreateAHeroData **, CreateAHeroData *>
// (0x0060E873) and vector<ObjectID>::erase(iterator) (0x0025BF5D).
class CreateAHeroData;
enum ObjectID { INVALID_ID_0040D82F = 0 };
namespace _STL
{
template <class It, class T> It find(It first, It last, const T &value);
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *position);
};
}

struct Rva0040D82FArg
{
	char m_00[0x1C];
	int m_1C;
};

class Rva0040D82FHost
{
public:
	void __fastcall setFrom(int unused, Rva0040D82FArg *arg); // retail 0x0040D82F

private:
	char m_00[0x14];
	Rva0040D82FSub m_14; // +0x14
	int m_18; // +0x18 current value
};

void __fastcall Rva0040D82FHost::setFrom(int unused, Rva0040D82FArg *arg)
{
	if (arg != 0) {
		int cur = m_18;
		int tmp = arg->m_1C;
		int r = (int)_STL::find<CreateAHeroData **, CreateAHeroData *>((CreateAHeroData **)m_14.m_first, (CreateAHeroData **)cur, *(CreateAHeroData *const *)&tmp);
		if (r != cur) {
			((_STL::vector<ObjectID> *)&m_14)->erase((ObjectID *)r);
		}
	}
}
