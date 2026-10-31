// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049C67E@Rva0049C67E@@QAEXPAVObject@@@Z @0x0049C67E 99B ret 4.
// Null object returns. Otherwise clear the id via the 71B neighbour, zero
// +0x89, play FXList at [[this+4]+0xD8] from the object's +0x38, set status
// 3, then store 1 at +0x88 and 1.0 at +0x8C.

#include "GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0049C73A_2 = 2,
	OS_3 = 3,
	OS_42 = 0x42,
	OBJECT_STATUS_RVA0049C73A_66 = 0x42
};

class Player;
class UpgradeTemplate;
class ThingTemplate;
class Provider31;
class AIUpdate;
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Object *rva002931F5(bool flag);
	Player *getControllingPlayer() const; // 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const; // 0x0004E536
	const Coord3D *getPosition() const { return &m_pos; }
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04 +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38 +0x38
	char m_pad44[0x34];
	ObjectID m_78; // +0x78 +0x78
	char m_pad7C[0x1D4];
	Provider31 *m_prov250; // +0x250
	char m_pad254[0x4];
	AIUpdate *m_ai; // +0x258
	char m_pad25C[0x18];
	int m_int274; // +0x274
	char m_pad278[0xC];
	unsigned m_284[32]; // +0x284 +0x284 the upgrade mask
	char m_pad304[0x134];
	unsigned char m_b438; // +0x438
	char m_pad439[0x3];
};

struct Rva0049C67EInner
{
	char m_pad[0xD8];
	FXList *m_fx;
};

class Rva0049C592
{
public:
	void rva0049C592();
	char m_pad00[0x40];
private:
	unsigned int m_id; // +0x40
};

class Rva0049C67E
{
public:
	void rva0049C67E(Object *obj);

private:
	char m_pad0[4];
	Rva0049C67EInner *m_inner;
	char m_pad8[0x88 - 8];
	unsigned char m_88;
	unsigned char m_89;
	char m_pad8A[2];
	float m_8c;
};

void Rva0049C67E::rva0049C67E(Object *obj)
{
	if (obj == 0)
		return;
	((Rva0049C592 *)this)->rva0049C592();
	Rva0049C67EInner *inner = m_inner;
	m_89 = 0;
	FXList *fx = inner->m_fx;
	if (fx != 0)
		FXList::doFXPos(fx, &obj->m_pos, 0, 0.0f, 0);
	obj->setStatus(OS_3, true);
	m_88 = 1;
	m_8c = 1.0f;
}
