// cl: /MD
// ??1Rva005FEA50Base@FXParticleSystem@@UAE@XZ @0x003ABC0B 22B
// Leaf dtor restoring one vptr at +0x1c with null-guarded store then tail-jmp
// to rowed base ??1Rva003AEEB3 0x003A5817. Evidence: neg sbb and idiom matches
// sibling Rva003A5817Dtor plus V3InlineTemplateDtor; caller ??_G deleting dtor.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Rva003AEEB3
{
public:
	virtual ~Rva003AEEB3();
};
// FXParticleSystem::Rva005FEA50Base: its constructor 0x003A5856 installs
// the tables 0x0081B5A8 (+0) and 0x0081B598 (+0x1C) whose deleting dtor
// 0x003AEFF6 and adjustor 0x003A588E reach this body.
namespace FXParticleSystem {
class __declspec(novtable) Rva005FEA50Base : public Rva003AEEB3
{
public:
	virtual ~Rva005FEA50Base();
};
}
FXParticleSystem::Rva005FEA50Base::~Rva005FEA50Base()
{
	unsigned char *snapshot = this ? (unsigned char *)this + 0x1C : 0;
	reinterpret_cast<Snapshot *>(snapshot)->Snapshot::~Snapshot();
}

// Rva0055F9B4 (ctor 0x0055F9B4, Rva0055F9B4Ctor.cpp): its vtable 0x00C1D688 slot 0
// is the same deleting dtor 0x003AEFF6, so this 22B body is its destructor too
// (ICF alias row).
class __declspec(novtable) Rva0055F9B4 : public Rva003AEEB3
{
public:
	virtual ~Rva0055F9B4();
};
Rva0055F9B4::~Rva0055F9B4()
{
	unsigned char *snapshot = this ? (unsigned char *)this + 0x1C : 0;
	reinterpret_cast<Snapshot *>(snapshot)->Snapshot::~Snapshot();
}

// Rva0055F197 (ctor 0x0055F197, Rva003ABD20Ctor.cpp): its vtable 0x00C1D654
// slot 0 is the same deleting dtor 0x003AEFF6, so this 22B body is its
// destructor too (ICF alias row).
class __declspec(novtable) Rva0055F197 : public Rva003AEEB3
{
public:
	virtual ~Rva0055F197();
};
Rva0055F197::~Rva0055F197()
{
	unsigned char *snapshot = this ? (unsigned char *)this + 0x1C : 0;
	reinterpret_cast<Snapshot *>(snapshot)->Snapshot::~Snapshot();
}

// Rva003ABC6E's native constructor calls the Rva003AEA42 provider;
// its complete destructor shares the Snapshot-at-1C/common-head cleanup.
class __declspec(novtable) Rva003AEA42 : public Rva003AEEB3
{
public:
    virtual ~Rva003AEA42();
};
Rva003AEA42::~Rva003AEA42()
{
    unsigned char *snapshot = this ? (unsigned char *)this + 0x1C : 0;
    reinterpret_cast<Snapshot *>(snapshot)->Snapshot::~Snapshot();
}

class __declspec(novtable) Rva0055BF4B : public Rva003AEEB3 { public: virtual ~Rva0055BF4B(); };
Rva0055BF4B::~Rva0055BF4B() {
 unsigned char *snapshot = this ? (unsigned char *)this + 0x1C : 0;
 reinterpret_cast<Snapshot *>(snapshot)->Snapshot::~Snapshot();
}
