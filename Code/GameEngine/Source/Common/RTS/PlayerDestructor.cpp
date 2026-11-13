// cl: /Ireference/shims/moduledata /G7 /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Player destructor: native 2B11A7..2B1418 / RET0, three vtables and
// deleting caller 2B14CF establish identity. BFME1 a7c38d3b PlayerDestructor
// supplies ownership semantics; native cleanup accesses and the matched
// PlayerCtorBFME2.cpp establish the three bases and member offsets.
// Real Snapshot member destructors are visible. novtable suppresses their
// discarded derived-vtable writes, preserving native cleanup scheduling.
// The three missing Snapshot states and the +738 wrapper are required by
// native EH graph 775E6D..775FEF; full body and graph both verify.
// The +2BC integer name map is independently established by PlayerProductionSpeed
// 2AE8CF and its Rva002AE4C5 lookup. Its real destructor replaces the old
// gen-alias at 2AE53E; the +294/+2A8 float maps keep their original owner.
// Vector element identities stay with the existing cleanup owners. Their
// destructors remain out of line, as every corresponding native call does.
// ??1Player@@UAE@XZ, retail 0x002B11A7 (625 bytes): Player destructor.
// Evidence: pin ??1Player@@UAE@XZ; caller ??_GPlayer 0x002B14CF in PlayerDeleter.cpp;
// vtable 0x00BFDF3C slot-2 name getter returns Player; BFME1 donor
// GameEngine/Source/Common/RTS/PlayerDestructor.cpp; Zero Hour Player.h layout.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <list>

#include <new>
#include <stdlib.h>

class Rva002AAC74PoolList
{
public:
	void clear();
	void destroy() throw();
	~Rva002AAC74PoolList() { destroy(); }
	void *m_head;
};

class PoolMember
{
public:
	void Rva00268902() throw();
	~PoolMember() { Rva00268902(); }
private:
	void *m_head;
};

class DelBase
{
public:
	virtual void *Delete(int flags);
	virtual ~DelBase();
};

struct TeamPrototypeRef
{
	char m_pad[8];
	void *m_owner;
};

struct PoolListNode
{
	PoolListNode *m_next;
	void *m_pad4;
	TeamPrototypeRef *m_tp;
};

#include "../../../Include/Common/Rva002E2690Element.h"

struct BfmeVectorRecord002AF478
{
	~BfmeVectorRecord002AF478();
	char bytes[36];
};

namespace _STL {
template <> vector<Rva002E2690Element>::~vector();
template <> vector<BfmeVectorRecord002AF478>::~vector();
}
// Native 2B0B8E is the +4 vector cleanup wrapper; the parent EH receiver
// is +738, although its inlined normal cleanup calls the vector at +73C.
class Rva002B0B8E
{
public:
    ~Rva002B0B8E() {}
    unsigned m_reserved;
    _STL::vector<Rva002E2690Element> m_entries;
};
class ScoreKeeper
{
public:
	virtual ~ScoreKeeper();
private:
	char m_pad[824 - 4];
};

class Rva002AC340
{
	friend class Player;
protected:
	virtual ~Rva002AC340();
private:
	char m_pad[20 - 4];
};

struct Rva001FD458
{
	void rva001FD659();
	~Rva001FD458();
	char m_pad[8];
};

struct Rva001FD42B
{
	void rva001FD630();
	~Rva001FD42B();
	char m_pad[8];
};

#include "../../../Include/GameLogic/Rva000427195.h"

// The +288/+2D0 and +294/+2A8 members are wrappers over these containers:
// each wrapper's destructor is a retail 5-byte `jmp` to the container's
// (0x001FD85E, 0x001FD863, 0x001FE065), the address the unwind funclets
// call. The implicit destructor expands on the normal path into the
// container destructor call and is emitted for the funclets as that thunk.
struct Rva001FD85E : Rva001FD42B
{
};

struct Rva001FD863 : Rva001FD458
{
};

struct Rva001FE065 : Rva000427195
{
};

struct Rva000427195BucketHandle
{
	~Rva000427195BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};
class Rva002AE4C5
{
public:
	~Rva002AE4C5();
	int &rva002AE4C5(const AsciiString *);
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned m_numElements;
};

class Rva002AE5EB
{
public:
	virtual ~Rva002AE5EB();
private:
	char m_pad[48 - 4];
};

class Xfer;
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class __declspec(novtable) S3Money : public Snapshot
{
public:
    virtual ~S3Money() {}
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    int words[2];
};
class __declspec(novtable) Rva002B0F3CEnergy : public Snapshot
{
public:
    virtual ~Rva002B0F3CEnergy() {}
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    int words[3];
};
class __declspec(novtable) Rva004F599E : public Snapshot
{
public:
    virtual ~Rva004F599E() {}
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    int words[42];
};
class Rva002B0F3CIface {
public:
 Rva002B0F3CIface() {} ~Rva002B0F3CIface() {}
 virtual void v0()=0; virtual void v1()=0; virtual void v2()=0;
};
class ExperienceScalarTable;
class Rva00380200 {
public:
 Rva00380200(); virtual ~Rva00380200() {}
 virtual bool rva0038037C(int); virtual void slot2();
 virtual void resetRank(); virtual void onRank(void*); virtual bool isReady();
private:
 AsciiString *m_ptr; ExperienceScalarTable *m_scalars;
 float m_0C,m_10; int m_14,m_18,m_1C,m_20,m_24,m_28;
};
struct FreeBlock
{
	~FreeBlock()
	{
		if (m_ptr)
			free(m_ptr);
	}
	void *m_ptr;
};

class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200
{
public:
	virtual ~Player();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool rva0038037C(int); virtual void slot2();
    virtual void resetRank(); virtual void onRank(void *); virtual bool isReady();
private:

	int m_34;
	UnicodeString m_38;
	char m_pad3c[0x4C - 0x38 - 4];
	AsciiString m_4c;
	char m_pad50[0x58 - 0x4C - 4];
	AsciiString m_58;
	char m_pad5c[0x60 - 0x58 - 4];
	Rva002AE5EB m_60;
	S3Money at90;
	char m_pad9c[0xB8 - 0x9C];
	void *m_b8;
	char m_padbc[0x1BC - 0xBC];
	Rva002B0F3CEnergy at1bc;
	Rva004F599E at1cc;
	char m_pad278[0x288 - 0x278];
	Rva001FD85E m_288;
	char m_pad290[0x294 - 0x288 - 8];
	Rva001FE065 m_294;
	Rva001FE065 m_2a8;
	Rva002AE4C5 m_2bc;
	Rva001FD863 m_2d0;
	char m_pad2d8[0x2EC - 0x2D0 - 8];
	int m_2ec;
	FreeBlock m_2f0;
	char m_pad2f4[0x2FC - 0x2F0 - 4];
	FreeBlock m_2fc;
	char m_pad300[0x308 - 0x2FC - 4];
	FreeBlock m_308;
	char m_pad30c[0x318 - 0x308 - 4];
	Rva002AC340 m_318;
	Rva002AAC74PoolList m_32c;
	DelBase *m_330;
	DelBase *m_334;
	char m_pad338[0x3B0 - 0x338];
	_STL::vector<BfmeVectorRecord002AF478> m_3b0;
	ScoreKeeper m_3bc;
	_STL::list<int> m_6f4;
	char pad6f8[8];
	_STL::list<int> m_700;
	_STL::list<int> m_704;
	DelBase *m_708[10];
	DelBase *m_730;
	char m_pad734[4];
	Rva002B0B8E m_738;
	char m_pad748[0x74C - 0x73C - 12];
	AsciiString m_74c;
	char m_pad750[0x754 - 0x74C - 4];
	PoolMember m_754;
};

typedef char PlayerDestructorSizeCheck[sizeof(Player) == 0x758 ? 1 : -1];

Player::~Player()
{
	int zero = 0;

	m_2ec = zero;
	m_34 = zero;
	for (PoolListNode *nn = ((PoolListNode*)m_32c.m_head)->m_next; nn != m_32c.m_head; nn = nn->m_next)
		nn->m_tp->m_owner = (void *)zero;
	m_32c.clear();
	::operator delete(m_334 ? m_334->Delete(zero) : 0);
	m_334 = (DelBase *)zero;
	::operator delete(m_330 ? m_330->Delete(zero) : 0);
	m_330 = (DelBase *)zero;
	DelBase **delBase = m_708;
	int count = 10;
	do {
		if (*delBase) {
			void *q = (*delBase)->Delete(zero);
			::operator delete(q);
			*delBase = (DelBase *)zero;
		}
		++delBase;
	} while (--count);
	if (m_730) {
		void *q = m_730->Delete(zero);
		::operator delete(q);
		m_730 = (DelBase *)zero;
	}
	if (m_b8) {
		::operator delete(m_b8);
		m_b8 = (void *)zero;
	}
}

// Native 2AE53E..2AE577 / RET0. Same bucket-clear worker and +4 buffer
// cleanup as the float-map destructor, with its own EH graph at775A0D.
Rva002AE4C5::~Rva002AE4C5()
{
    reinterpret_cast<Rva000427195 *>(this)->rva003A2A41();
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?GetSnapshotName@Player@@UBEPBDXZ=?Rva002B117CGet@@YAHXZ")
#pragma comment(linker, "/alternatename:?isReady@Player@@UAE_NXZ=?rva002A9F53@Rva002A9F53Forwarder@@QAEXXZ")
#pragma comment(linker, "/alternatename:?isReady@Rva00380200@@UAE_NXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@Player@@UAEXXZ=??1Region2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?onRank@Player@@UAEXPAX@Z=?rva002AD7E9@Rva002AD7E9Interface@@QAEXPBURva002AD7E9Record@@@Z")
#pragma comment(linker, "/alternatename:?onRank@Rva00380200@@UAEXPAX@Z=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?resetRank@Player@@UAEXXZ=?rva002AE318@Rva002AE318@@QAEXXZ")
#pragma comment(linker, "/alternatename:?resetRank@Rva00380200@@UAEXXZ=?rva0038028B@Rva00380200@@QAEXXZ")
#pragma comment(linker, "/alternatename:?rva0038037C@Player@@UAE_NH@Z=?rva002A9FA0@Rva002A9FA0@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?slot2@Player@@UAEXXZ=?rva002A9F5E@Rva002A9F5E@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?slot2@Rva00380200@@UAEXXZ=?rva0038027B@Rva00380200@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?v0@Player@@UAEXXZ=?rva002B118A@Rva002B118A@@QBE_NW4ScienceType@@@Z")
#pragma comment(linker, "/alternatename:?v1@Player@@UAEXXZ=?getDataLength@NetWrapperCommandMsg@@QAEIXZ")
#pragma comment(linker, "/alternatename:?v2@Player@@UAEXXZ=?rva002B1192@Rva002B1192Interface@@QAEXPAVCreateAHeroData@@PA_N@Z")
#pragma comment(linker, "/alternatename:?xfer@Player@@UAEXPAVXfer@@@Z=?DoXfer@Player@@QAEXPAVXfer@@@Z")

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?GetSnapshotName@Player@@UBEPBDXZ=?Rva002B117CGet@@YAHXZ")
#pragma comment(linker, "/alternatename:?isReady@Player@@UAE_NXZ=?rva002A9F53@Rva002A9F53Forwarder@@QAEXXZ")
#pragma comment(linker, "/alternatename:?isReady@Rva00380200@@UAE_NXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@Player@@UAEXXZ=??1Region2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?onRank@Player@@UAEXPAX@Z=?rva002AD7E9@Rva002AD7E9Interface@@QAEXPBURva002AD7E9Record@@@Z")
#pragma comment(linker, "/alternatename:?onRank@Rva00380200@@UAEXPAX@Z=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?resetRank@Player@@UAEXXZ=?rva002AE318@Rva002AE318@@QAEXXZ")
#pragma comment(linker, "/alternatename:?resetRank@Rva00380200@@UAEXXZ=?rva0038028B@Rva00380200@@QAEXXZ")
#pragma comment(linker, "/alternatename:?rva0038037C@Player@@UAE_NH@Z=?rva002A9FA0@Rva002A9FA0@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?slot2@Player@@UAEXXZ=?rva002A9F5E@Rva002A9F5E@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?slot2@Rva00380200@@UAEXXZ=?rva0038027B@Rva00380200@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?v0@Player@@UAEXXZ=?rva002B118A@Rva002B118A@@QBE_NW4ScienceType@@@Z")
#pragma comment(linker, "/alternatename:?v1@Player@@UAEXXZ=?getDataLength@NetWrapperCommandMsg@@QAEIXZ")
#pragma comment(linker, "/alternatename:?v2@Player@@UAEXXZ=?rva002B1192@Rva002B1192Interface@@QAEXPAVCreateAHeroData@@PA_N@Z")
#pragma comment(linker, "/alternatename:?xfer@Player@@UAEXPAVXfer@@@Z=?DoXfer@Player@@QAEXPAVXfer@@@Z")
