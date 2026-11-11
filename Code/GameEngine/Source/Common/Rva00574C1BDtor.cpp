// cl: /O1 /MD /EHsc
// ??1Rva00574C1B@@UAE@XZ retail 0x00574C1B 83B
// Two-base dtor: own vptrs C6E4A4 (+0) and C6E4C0 (+0x10); under EH state 1
// the +0x10 subobject is unregistered from the list at +4 of the owner held
// at +0x14 through the rowed ?rva002B7250@Rva002B7250 0x002B7250; the second
// base's inline dtor restores C6E360 and the pinned first-base dtor
// ??1Rva005746AF@@UAE@XZ 0x005746D2 runs. Names address-derived.

class CreateAHeroData;

#include "../../Include/Common/Rva002B7250.h"

struct Rva00574C1BOwner
{
	int m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva005746AF
{
public:
	virtual ~Rva005746AF();

private:
	unsigned char m_pad04[0x10 - 4];
};

class Rva00575125Second
{
public:
	virtual void slot0(int);
	~Rva00575125Second();
};
inline Rva00575125Second::~Rva00575125Second() {}
class Rva00574C1B : public Rva005746AF, public Rva00575125Second
{
public:
	virtual ~Rva00574C1B();
	virtual void slot0(int);
private:
	Rva00574C1BOwner *m_owner;
};

Rva00574C1B::~Rva00574C1B()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva00575125Second *>(this));
}

#include "../../Include/Common/Rva000AD6F4.h"

// Native C6E4C0 slot 0 receives the secondary-base pointer. MSVC adjusts
// this override's receiver by -0x10, producing the native [ecx-0x0C] load.
void Rva00574C1B::slot0(int)
{
	((Rva000AD6F4 *)(*(char **)((char *)this + 4) + 0x54))->~Rva000AD6F4();
}
