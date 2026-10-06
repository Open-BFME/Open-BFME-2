// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00421520@Rva00421520@@QAEXPAVRva004210B0@@PBV?$StringBase@D@@@Z @0x00421520 82B
// Chain from 0x004213DB: search vector<ModuleData*> at +0x0C by name at +0x10
// via rowed StringBase compare 0x000069D6 with dup guard via rowed 0x001E35DF
// then add index via rowed 0x004213DB. Evidence: chain lane calls landed
// 0x004213DB; caller at 0x002A9F2D passes holder at +0x318 plus name.
#include "ascii_string.h"

class ModuleData;
class Rva004210B0;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void __cdecl dup_001e35df();

namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class Rva004210B0
{
public:
	void rva004213DB(const ModuleData *data);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_nextOverride;
	int m_isOverride;
	int m_extra0C;
};

class ModuleData : public Overridable
{
public:
	StringBase<char> m_10;
};

class Rva00421520
{
public:
	void rva00421520(Rva004210B0 *holder, const StringBase<char> *name);
private:
	char m_pad[12];
	const ModuleData **m_begin;
	const ModuleData **m_end;
};
void Rva00421520::rva00421520(Rva004210B0 *holder, const StringBase<char> *name)
{
	for (unsigned i = 0; i < (m_end - m_begin); ++i) {
		_ReadWriteBarrier();
		const ModuleData *md = m_begin[i];
		const Overridable *target = md;
		if (md->m_nextOverride) {
			target = md->m_nextOverride->getFinalOverride();
		}
		if (((const ModuleData *)target)->m_10.compare(*name) == 0) {
			holder->rva004213DB((const ModuleData *)i);
			break;
		}
	}
}
