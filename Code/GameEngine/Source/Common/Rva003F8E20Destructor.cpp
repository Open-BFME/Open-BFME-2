// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva003F8E20@@UAE@XZ, retail 0x003F8E20..0x003F8EA2 (130 bytes, EH);
// pinned until now as the opaque ??1Rva003F8E20@@UAE@XZ. A listener-owning
// holder (vtable 0x00C3731C, restored to 0x00C37298 last by the first base
// 0x003F7BC5): the destructor tells every listener in the list at +4 about
// it (rowed listener-list forEach 0x003F86B6 with the vcall thunk 0x001FF3A9
// as the slot), releases the file pointers at +0x14 through the rowed range
// releaser 0x0059E2DC, then the buffers go. The list and the pointer vector
// are 4-byte POD stand-ins (the list is a base at +4 that retail unwinds
// through the folded buffer destructor 0x0007FAB3). Class name
// address-derived.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

enum ObjectID { INVALID_ID = 0 };

class FileClass;

struct Rva0059E2DCBox
{
	bool flag;
};

bool __cdecl rva0059E2DC(FileClass **first, FileClass **last, Rva0059E2DCBox box);

class Gen_uwm_003f7bc5
{
public:
	virtual void slot00();
	~Gen_uwm_003f7bc5() {}
};

class Rva003F86B6Listener
{
public:
	virtual void notify(void *);
};

class Rva003F86B6List
{
public:
	void forEach(void (Rva003F86B6Listener::*notify)(void *), void *arg);
};

class Rva003F8E20 : public Gen_uwm_003f7bc5, public _STL::vector<ObjectID>
{
public:
	virtual ~Rva003F8E20();
private:
	int m_index; // +0x10
	_STL::vector<ObjectID> m_files; // +0x14
};

Rva003F8E20::~Rva003F8E20()
{
	((Rva003F86B6List *)static_cast<_STL::vector<ObjectID> *>(this))->forEach(&Rva003F86B6Listener::notify, this);
	Rva0059E2DCBox box = Rva0059E2DCBox();
	rva0059E2DC((FileClass **)&*m_files.begin(), (FileClass **)&*m_files.end(), box);
}
