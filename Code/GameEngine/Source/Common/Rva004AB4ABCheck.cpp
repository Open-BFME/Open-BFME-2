// cl: /MD
// ?rva004AB4AB@Rva004AB4AB@@QBE_NXZ @0x004AB4AB 45B: returns false when TheGameLogic findObjectByID over m_28 misses or Object plus 0x438 bit0 set else inverted isKindOf 0x45. Callees rowed 0x00049DC5 and 0x0006F039. Caller at 0x004AB517. Prev Rva0024A797Grandchildren next LargeGroupAudioUpdateRandom share flags.

typedef bool Bool;

#include "GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Module;
class Drawable;
class AIUpdateInterface;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum KindOfType
{
	KIND_45 = 0x45
};

enum ObjectStatusTypes;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class WallUpgradeUpdate;
public:
	bool isKindOf(KindOfType kind) const;
	void rva0028C2DD(Coord3D *center) const;	// 0x0028C2DD
	int rva0028B511() const;			// 0x0028B511
	void teleportTo(const Coord3D *pos, bool flag);  // rowed 0x0029660C
	__declspec(dllimport) __forceinline void rva0029660C(const Coord3D *pos, int flag) { (this->*reinterpret_cast<void (Object::*)(const Coord3D *, int)>(&Object::teleportTo))(pos, flag); }
	Drawable *getDrawable() const;			// 0x005508E2
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0xB8 - 0x78];
	float m_B8;			// +0xB8 (geometry +0xA8, its +0x10 radius)
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_flag438;	// +0x438
};


extern GameLogic *TheGameLogic;

class Rva004AB4AB
{
public:
	Bool rva004AB4AB() const;

private:
	unsigned char m_pad00[0x28];
	ObjectID m_id28;
};

Bool Rva004AB4AB::rva004AB4AB() const
{
	Object *obj = TheGameLogic->findObjectByID(m_id28);
	if (!obj || (obj->m_flag438 & 1))
		return false;
	return !obj->isKindOf(KIND_45);
}
