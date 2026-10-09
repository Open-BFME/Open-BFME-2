// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva002000A4@Rva0022CA74@@UAEXXZ @0x002000A4 51B
// vtable slot 9 (offset 0x24) of 0x007E2704 = class of ??0Rva0022CA74@@QAE@XZ.
// Iterates vector at +0xC..+0x10, calls rowed deleteOverrides 0x001E35ED,
// erases via rowed vector<void*> erase 0x001FF51F when it returns 0.
// Evidence: leaf packet; prev Rva0023C6A4Check.cpp, next RankInfoCtor.cpp.
#include <vector>

class Overridable
{
public:
	Overridable *deleteOverrides();
};

class Rva0022CA74
{
public:
	virtual void rva002000A4();
private:
	char m_pad04[0xC - 4];
	_STL::vector<void *> m_vec;
};

void Rva0022CA74::rva002000A4()
{
	_STL::vector<void *>::iterator it = m_vec.begin();
	while (it != m_vec.end())
	{
		Overridable *o = (Overridable *)*it;
		if (o == 0)
			continue;
		if (o->deleteOverrides() == 0)
			it = m_vec.erase(it);
		else
			++it;
	}
}
