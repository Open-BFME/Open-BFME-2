// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Three small Object readers (retail 0x0028AD6C/16 + 0x0028ADE0/12 +
// 0x0028ADF7/28). /O1 selects the retail size idioms throughout: jne plus
// inc-from-known-zero for the null-or-one reader, xor-first cmp-mem-reg for
// the flag test, and hoisted xor plus inc for the bit-test's 1<<slot.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/ICoord2DBase.h"

struct Rva002EBC7FPair
{
	int x;
	int y;
};
void *__cdecl rva002EBC7F(void *out, void *owner, Rva002EBC7FPair *position, int layer);

// The object at Object+0xA4. Its float getter at 0x004DD843 is rowed under
// this address-derived class name, so the forwarders below reuse it; the
// remaining methods are pinned from the forwarders' own REL32 targets.
class PathfinderPosGoalManager
{
public:
	void rva004DE24B(int arg);
	void rva004DE4E2(int arg);
	void rva004DE511(int arg, int arg2);
	void SetGoal(int arg, float value, int arg2);
	void rva004DDD80();
	void rva004DDD6E();
	bool rva004DD80A(Coord3D *out);
	float rva004DD843();
	bool rva004DE2ED();	// returns bool, as rowed
	void rva004DDD92();
	bool rva004DD84D(Coord3D *out);
	bool rva004DD637();

	char m_pad[0x28];				// +0x000..+0x028 unknown
	int m_value;					// +0x028
};

// The object at Object+0x240: Object's constructor stores the
// FiringTracker built by ??0FiringTracker (call 0x00299898) there. Offsets
// follow the rowed FiringTracker::xfer 0x004DEBC1 (+0x24 and +0x38 ObjectIDs,
// +0x3C..+0x44 frames, +0x48 position); the address-derived class name is
// kept because rowed methods already carry it.
struct Rva0028AF76Sub
{
	char m_pad[0x24];				// +0x000..+0x024 unknown
	int m_id24;						// +0x024 ObjectID
	char m_pad28[0x38 - 0x28];		// +0x028..+0x038
	int m_id38;						// +0x038 ObjectID
	char m_pad3C[0x44 - 0x3C];		// +0x03C..+0x044
	int m_value;					// +0x044
	float m_float48;				// +0x048
	int m_int4C;					// +0x04C
	int m_int50;					// +0x050

	void *rva0028A82A(void *dst) const;
	int rva004DEA68();
};

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;


class Object;

class WeaponSet
{
public:
	void reloadAllAmmo(const Object *obj, bool now);
	bool isOutOfAmmo() const;
};

class Object
{
	char m_pad0[0x38];				// +0x000..+0x038 unknown
	int m_38;						// +0x038
	char m_pad3C[0x44 - 0x3C];		// +0x03C..+0x044 unknown
	float m_44;						// +0x044
	char m_pad48[0xA4 - 0x48];		// +0x048..+0x0A4 unknown
	PathfinderPosGoalManager *m_sub;				// +0x0A4
	char m_pad1[0x240 - 0xA4 - 4];	// +0x0A8..+0x240 unknown
	Rva0028AF76Sub *m_sub240;		// +0x240
	char m_pad2[0x358 - 0x244];		// +0x244..+0x358 unknown
	int m_flag358;					// +0x358
	int m_pad358;					// +0x35C unknown
	int m_mask360;					// +0x360
	char m_pad364[0x40C - 0x364];	// +0x364..+0x40C unknown
	int m_value40C;					// +0x40C
	char m_pad410[0x48C - 0x410];	// +0x410..+0x48C unknown
	unsigned char m_flag48C;		// +0x48C
	char m_pad48D[0x490 - 0x48D];	// +0x48D..+0x490 pad
	int m_cachedFrame;					// +0x490 cached frame

public:
	void rva0028ACCA(int worldPosition);
	void rva0028ACDC(int goalPosition);
	void rva0028ACEE(int destinationPosition, int m_goalLayer);
	void rva0028AD00(int arg, float value, int arg2);
	void rva0028AD22();
	void rva0028AD32();
	bool GetGoalPosition(Coord3D *out) const;
	float GetGoalAngle() const;
	int GetGoalLayer() const;
	void rva0028AD7C();
	void rva0028AD8C();
	bool GetPathfinderPos(Coord3D *out) const;
	bool IsAtGoalPosition() const;
	void reloadAllAmmo(bool now);
	bool hasAnyWeapon() const;
	int rva0028ADF7(int slot) const;
	int rva0028AF76() const;
	int getLastVictimID() const;
	int rva0028AF97();
	int rva0028B511() const;
	void rva0028CDB6();
	void rva0028B95F();
	bool isOutOfAmmo() const;
};

// These bodies are the methods reached by Object::GetGoalPosition and
// Object::GetPathfinderPos through Object+0xA4. Retail checks the first word
// of the relevant coordinate pair against -666666, calls rowed
// rva002EBC7F, copies its 12-byte result to the output, and returns true.
// The method names and owner layout remain address-derived; the wrappers
// support the goal/pathfinder roles and the pair offsets below.
bool PathfinderPosGoalManager::rva004DD80A(Coord3D *out)
{
	Rva002EBC7FPair *position = (Rva002EBC7FPair *)((char *)this + 0x1c);
	if (position->x == -666666)
		return false;
	Coord3D result;
	void *value = rva002EBC7F(&result, *(void **)this, position, m_value);
	*out = *(Coord3D *)value;
	return true;
}

bool PathfinderPosGoalManager::rva004DD84D(Coord3D *out)
{
	Rva002EBC7FPair *position = (Rva002EBC7FPair *)((char *)this + 4);
	if (position->x == -666666)
		return false;
	Coord3D result;
	void *value = rva002EBC7F(&result, *(void **)this, position,
		*(int *)((char *)this + 0x10));
	*out = *(Coord3D *)value;
	return true;
}

// Null-checked forwarders through the Object+0xA4 object (retail
// 0x0028ACCA..0x0028ADC1, between the rowed 0x0028ACA0 and 0x0028AD6C/
// 0x0028ADD5 Object rows). Each loads +0xA4, returns (or answers false /
// 0.0f) when it is null and otherwise tail-jumps to the method; the
// three-argument float forward at 0x0028AD00 re-pushes its arguments and
// calls instead.
void Object::rva0028ACCA(int worldPosition)
{
	if (m_sub)
		m_sub->rva004DE24B(worldPosition);
}

void Object::rva0028ACDC(int goalPosition)
{
	if (m_sub)
		m_sub->rva004DE4E2(goalPosition);
}

void Object::rva0028ACEE(int destinationPosition, int m_goalLayer)
{
	if (m_sub)
		m_sub->rva004DE511(destinationPosition, m_goalLayer);
}

void Object::rva0028AD00(int arg, float value, int arg2)
{
	if (m_sub)
		m_sub->SetGoal(arg, value, arg2);
}

void Object::rva0028AD22()
{
	if (m_sub)
		m_sub->rva004DDD80();
}

void Object::rva0028AD32()
{
	if (m_sub)
		m_sub->rva004DDD6E();
}

bool Object::GetGoalPosition(Coord3D *out) const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD80A(out);
}

float Object::GetGoalAngle() const
{
	if (!m_sub)
		return 0.0f;
	return m_sub->rva004DD843();
}

int Object::GetGoalLayer() const
{
	const PathfinderPosGoalManager *sub = m_sub;
	if (sub == 0)
		return 1;
	return sub->m_value;
}

void Object::rva0028AD7C()
{
	if (m_sub)
		m_sub->rva004DE2ED();
}

void Object::rva0028AD8C()
{
	if (m_sub)
		m_sub->rva004DDD92();
}

bool Object::GetPathfinderPos(Coord3D *out) const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD84D(out);
}

bool Object::IsAtGoalPosition() const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD637();
}

// ?rva004DD637@PathfinderPosGoalManager@@QAE_NXZ @ 0x004DD637 (33B). The exact body
// rejects -666666 at this+0x1C, then calls rowed ICoord2D::operator== at
// 0x00004CAD with this+0x1C as its receiver and this+4 as its argument.
// Object::IsAtGoalPosition above forwards here through Object+0xA4; the owner
// class and method identity remain address-derived.
bool PathfinderPosGoalManager::rva004DD637()
{
	const ICoord2D *position = (const ICoord2D *)((const char *)this + 0x1c);
	return position->x != -666666 &&
		*position == *(const ICoord2DBase *)((const char *)this + 4);
}

// ?reloadAllAmmo@Object@@QAEX_N@Z, retail 0x0028ADC2 (19B): Zero Hour's
// Object::reloadAllAmmo, immediately before isOutOfAmmo as in Object.cpp.
void Object::reloadAllAmmo(bool now)
{
	WeaponSet *ws = (WeaponSet *)((char *)this + 0x330);
	ws->reloadAllAmmo(this, now);
}

// ?hasAnyWeapon@Object@@QBE_NXZ
// ?hasAnyWeapon@Object@@QBE_NXZ
bool Object::hasAnyWeapon() const
{
	return m_flag358 != 0;
}

// ?rva0028ADF7@Object@@QBEHH@Z
// ?rva0028ADF7@Object@@QBEHH@Z
int Object::rva0028ADF7(int slot) const
{
	return (m_mask360 & (1 << slot)) != 0 ? 1 : 0;
}

int Object::rva0028AF76() const
{
	int result = 0;
	const Rva0028AF76Sub *sub = m_sub240;
	if (sub != 0)
		result = sub->m_value;
	return result;
}

// ?getLastVictimID@Object@@QBEHXZ, retail 0x0028AF86 (17B): the +0x24 ObjectID
// of the firing tracker, 0 without one. Same shape and Zero Hour position
// (after the frame getter, before getControllingPlayer 0x0028AFA9) as
// Object::getLastVictimID; no retail caller or pointer reaches it, so the
// name stays address-derived.
int Object::getLastVictimID() const
{
	const Rva0028AF76Sub *sub = m_sub240;
	return sub ? sub->m_id24 : 0;
}

// ?rva0028AF97@Object@@QAEHXZ, retail 0x0028AF97 (18B): takes the tracker's
// +0x38 ObjectID through 0x004DEA68 (FiringTrackerRva004DEA68.cpp; retail
// tail-jumps, so it is not inlined here), 0 without a tracker. The caller at
// 0x0026935C passes the result to GameLogic::findObjectByID.
int Object::rva0028AF97()
{
	Rva0028AF76Sub *sub = m_sub240;
	if (sub)
		return sub->rva004DEA68();
	return 0;
}

int Object::rva0028B511() const
{
	if (m_flag48C != 0)
		return 1;
	return m_value40C;
}

// ?rva0028CDB6@Object@@QAEXXZ, retail 0x0028CDB6, 53 bytes.
// Null-checked forwarder through Object+0xA4 (PathfinderPosGoalManager): int from
// Object::rva0028B511 plus float at +0x44 and address of +0x38 into
// 0x004DE109, then address of +0x38 into 0x004DE24B. Evidence: callees all
// rowed or pinned; callers at 0x00295C62 0x0034F681 0x00587289 0x0058808F;
// offsets +0x38 +0x44 +0xA4 from ObjectRvaSmallGetters neighbours; same-TU
// rva0028B511 keeps sub in edx with no extra push.
void Object::rva0028CDB6()
{
	PathfinderPosGoalManager *sub = m_sub;
	if (sub != 0) {
		int *p = &m_38;
		int v = rva0028B511();
		sub->SetGoal((int)p, m_44, v);
		m_sub->rva004DE24B((int)p);
	}
}

// ?rva0028B95F@Object@@QAEXXZ, retail 0x0028B95F, 22 bytes.
// Sets the +0x48C flag and caches TheGameLogic frame at +0x490. Evidence:
// flag byte proven by rva0028B511 in this TU, frame slot +0x40 proven by
// Rva002039B6Host, callers at 0x0046E268 0x0046E297 iterate and call with
// Object this.
void Object::rva0028B95F()
{
	m_flag48C = 1;
	m_cachedFrame = TheGameLogic->getFrame();
}

bool Object::isOutOfAmmo() const
{
	const WeaponSet *ws = (const WeaponSet *)((const char *)this + 0x330);
	return ws->isOutOfAmmo();
}

void *Rva0028AF76Sub::rva0028A82A(void *dst) const
{
	char *destinationBytes = (char *)dst;
	*(float *)destinationBytes = m_float48;
	*(int *)(destinationBytes + 4) = m_int4C;
	*(int *)(destinationBytes + 8) = m_int50;
	return dst;
}
