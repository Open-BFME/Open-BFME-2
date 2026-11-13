// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ??0Rva003FE58A@@QAE@PAX0@Z @0x003FE412 342B
// Rva003FE58A constructor (LivingWorldArmyIcon), retail 0x003FE412..0x003FE566
// (342 bytes, ret 8, WB 0x01072E30 names LivingWorldArmyIcon::LivingWorldArmyIcon).
// Class and vtable (0x00C37E48) are the ones the matched destructor 0x003FE58A
// already establishes: base Rva0053947D with the -99999 sentinel, child vector
// +0x2C, owner +0x38, queue +0x3C, zeroed +0x4C/+0x50/+0x54, speed 5.0f +0x58,
// active +0x5C; the owner's +0x54 color lookup goes through TheLivingWorldLogic.
typedef int Int;
typedef unsigned int UnsignedInt;

#define BFME_SNAPSHOT_NAME_SLOT
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "Coord2D.h"
#include "RGBColor.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// push_back is called out of line and the copy the link keeps is retail's; this
// unit's own copy differed, so it is declared only.
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &); }

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class Rva0053947D
{
public:
	Rva0053947D(void *owner, const Vector3 *sentinel);
	virtual ~Rva0053947D();
	virtual void v01(); virtual void rva005391D3(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12();
	virtual int v13(); virtual void v14(); virtual void *v15(int);
	char m_unmodelled04[0x10];
};

class Rva00538E22
{
public:
	Rva00538E22(Int tag);
	~Rva00538E22();
	char m_data[0x10];
};

class LivingWorldArmyIconSubObject
{
public:
	LivingWorldArmyIconSubObject(void *element, void *owner, Int color);
	char m_data[0xC8];
};
class ModuleData;
class Rva002E2903Player;
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../../Include/Common/Rva003FDD29.h"
class Rva00539281 { public: void rva00539281(unsigned char a, Int b); };
#include "../../../Include/Common/Rva003FE05E.h"

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > SubObjectVector;

// The +0x4C holder: null on construction; its out-of-line destructor
// 0x005F8F96 is the unwind action retail registers for that member.
class Rva005F8F96
{
public:
	Rva005F8F96() : m_ptr(0) {}
	~Rva005F8F96();
	void *m_ptr;
};

class Rva003FE58A : public Rva0053947D
{
public:
	Rva003FE58A(void *elements, void *owner);
	virtual ~Rva003FE58A();
	char m_unmodelled14[0x18];
	SubObjectVector m_children;					// +0x2C
	void *m_owner;								// +0x38
	Rva00538E22 m_queue;						// +0x3C
	Rva005F8F96 m_4C;							// +0x4C
	float m_50;									// +0x50
	float m_54;									// +0x54
	float m_58;									// +0x58
	bool m_5C;									// +0x5C
};

struct Rva003FE412Elements
{
	char m_pad04[4];
	void **m_begin;			// +0x4
	void **m_end;			// +0x8
};

Rva003FE58A::Rva003FE58A(void *elements, void *owner)
	: Rva0053947D(elements, &Vector3(-99999.0f, -99999.0f, -99999.0f))
	, m_owner(owner)
	, m_queue((Int)this)
{
	m_50 = 0.0f;
	m_54 = 0.0f;
	m_58 = 5.0f;
	m_5C = false;
	bool haveColor = false;
	Int color = 0;
	Int playerIndex = *(Int *)((char *)owner + 0x54);
	Rva002E2903Player *found = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerIndex, 0);
	if (found) {
		color = ((RGBColor *)((char *)found + 0x19C))->getAsInt() | (Int)0xff000000;
		haveColor = true;
	}
	Rva003FE412Elements *elems = (Rva003FE412Elements *)elements;
	m_children.reserve((Int)(elems->m_end - elems->m_begin));
	for (void **it = elems->m_begin, **end = elems->m_end; it != end; ++it) {
		LivingWorldArmyIconSubObject *sub = new LivingWorldArmyIconSubObject(*it, this, haveColor ? (Int)&color : 0);
		m_children.push_back(reinterpret_cast<const ModuleData *>(sub));
	}
	if (m_owner) {
		m_58 = *(float *)((char *)m_owner + 0x5C);
		((Rva00539281 *)this)->rva00539281(((Rva003FDD29 *)this)->rva003FDD29(), 1);
	}
	((Rva003FE05E *)this)->rva003FE05E();
}
