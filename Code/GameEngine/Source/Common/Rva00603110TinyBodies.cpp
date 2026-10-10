// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva003F92BB@Rva003F92DA@@QAEXPAXPBVAsciiString@@@Z
// retail 0x003F92BB, 31 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva00603110TinyBodies.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor body is
// byte-identical to retail once relocations are masked (unique hit on unclaimed
// .text). Only the placed body is defined here; the donor's other 23 accessor
// definitions are omitted.
//
// Native 3F92DA sets ECX to the same receiver before four calls to3F92BB.
// The helper never reads that receiver; rename the existing owner to its
// target-proven member ABI rather than adding a second name/pin. The donor
// established the lookup body; the receiver contract comes from target calls.
//
// A lookup through the living-world manager: find the item by name, and store
// its value through the out pointer only when the name resolved. The global is
// EA's `LivingWorldManager *TheLivingWorldManager`, defined once elsewhere;
// this TU sees it only through its own local view, and the pointee is cast at
// the use because the view types differ.

#include "ascii_string.h"
class LivingWorldManager;

struct Rva00612430Item
{
	char m_padding[4];
	void *m_value;
};

class Rva00612430Owner
{
public:
	Rva00612430Item *find(const AsciiString &name);
};

extern LivingWorldManager *TheLivingWorldManager;

class Rva003F92DA {public:
 __declspec(noinline) void rva003F92BB(void*,const AsciiString*);
 void rva003F92DA();
 int unknown00;AsciiString names[4];void *slots[4];char params[24];};
void Rva003F92DA::rva003F92BB(void *out,const AsciiString *name)
{
	Rva00612430Item *item = reinterpret_cast<Rva00612430Owner *>(TheLivingWorldManager)->find(*name);
	if (item != 0)
		*(void **)out = item->m_value;
}

// ?rva003F934B@Rva003F934B@@QAEXXZ, RVA 0x003F934B, 15 bytes.
// Called on a pointer loaded from caller offset 0x2c4; the four zeroed slots
// are inferred from the retail stores at this object's offsets 0x14 through 0x20.
class Rva003F934B
{
public:
	char m_padding[0x14];
	unsigned int m_slot14;
	unsigned int m_slot18;
	unsigned int m_slot1C;
	unsigned int m_slot20;
	void rva003F934B();
};

void Rva003F934B::rva003F934B()
{
	m_slot14 = 0;
	m_slot18 = 0;
	m_slot1C = 0;
	m_slot20 = 0;
}

struct Vec3{float x,y,z;};
class Rva003F936EHost{public:void rva003FB793(Vec3*);};
class Rva003FB7C7{public:void rva003FB7C7();};
// ?rva003F92DA@Rva003F92DA@@QAEXXZ
// Native113B resolves four4B names to four handles, snapshots coordinates
// through handles0/2 into30/24 and updates handles2/3. Owner identity unknown.
void Rva003F92DA::rva003F92DA(){
 rva003F92BB(&slots[0],&names[0]);rva003F92BB(&slots[1],&names[1]);rva003F92BB(&slots[2],&names[2]);rva003F92BB(&slots[3],&names[3]);
 if(slots[0])((Rva003F936EHost*)slots[0])->rva003FB793((Vec3*)(params+12));
 if(slots[2])((Rva003F936EHost*)slots[2])->rva003FB793((Vec3*)params);
 ((Rva003FB7C7*)slots[2])->rva003FB7C7();((Rva003FB7C7*)slots[3])->rva003FB7C7();
}
