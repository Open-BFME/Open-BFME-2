// cl: /EHs /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/bfmelist /ICode/GameEngine/Include/GameLogic /I. /ICode/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI /Ireference/shims/bfme2_ascii
// stlport
// ?rva0036CE87@AIGroup@@QAEXXZ @0x0036CE87 73B
// AIGroup ground-path reset: destroy the Path at +0x14 through its out-of-line
// destructor, free it, then clear the path state. The four clears run from the
// destructor of a scoped PathDeleteArgument temporary, which is what places the
// `and [esi+0x14],0` and the three float zero stores AFTER the operator-delete
// call and lets the `pop ecx` argument cleanup schedule between them; the
// banked void-return attempt stalled on exactly that `pop ecx` slot.
// Donor shape: reference/open-bfme-1 .../AIGroup/Rva00150700PathReset.cpp
// (same RAII spelling, BFME1 offsets +0x18..+0x30; this body uses BFME2's
// +0x14 ground path and +0x18/+0x1c/+0x20 float state).

#include <list>
namespace _STL {template<class T,class L,class R> static __forceinline bool operator!=(const _List_iterator<T,L>&a,const _List_iterator<T,R>&b){return a._M_node!=b._M_node;}}
#include "../../Common/Thing/thing.h"

class Object;

class Path
{
public:
	~Path(void) throw();
};

class BFMEDeletablePath : public Path
{
public:
	void destroy(void) { Path::~Path(); }
};

class PathDeleteArgument;

struct Coord3D;

class AIGroup
{
public:
	void rva0036CE87();
	bool getCenter(Coord3D *center);
	friend class PathDeleteArgument;

private:
	char m_pad00[4];
	std::list<Object *> m_memberList;
	float m_speed;
	bool m_dirty;
	char m_pad0D[0x14 - 0x0d];
	Path *m_groundPath;
	Coord3D m_position;
	Coord3D m_spacing;
	void recompute();
};

#include <new>

class Object;
class Rva002627E8 {
public:
	float rva002627E8() const;
};
class BodyModuleInterface {
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual int getDamageState();
};
class ThingTemplate {
public:
	char m_pad00[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};
class AIUpdateInterface;
class Object : public Thing {
public:
	char m_pad60[0x1c8 - 0x60];
	unsigned char m_disabledMask[0x04]; // +0x1C8
	char m_pad1CC[0x254 - 0x1cc];
	BodyModuleInterface *m_body254;
	AIUpdateInterface *m_ai;
};
class GlobalData {
public:
	char m_pad[0xb3c];
	int m_movementPenaltyDamageState;
};
extern GlobalData *TheWritableGlobalData;

class PathDeleteArgument
{
public:
	PathDeleteArgument(Path *path, AIGroup *owner) :
		m_path(path), m_owner(owner) { }
	operator void *(void) const { return m_path; }
	~PathDeleteArgument(void) throw()
	{
		m_owner->m_groundPath = 0;
		m_owner->m_position.x = 0.0f;
		m_owner->m_position.y = 0.0f;
		m_owner->m_position.z = 0.0f;
	}

private:
	Path *m_path;
	AIGroup *m_owner;
};

void AIGroup::rva0036CE87()
{
	if (m_groundPath)
	{
		Path *path = m_groundPath;
		reinterpret_cast<BFMEDeletablePath *>(path)->destroy();
		operator delete(PathDeleteArgument(path, this));
		m_spacing.x = 10.0f;
		m_spacing.y = 0.0f;
		m_spacing.z = 0.0f;
	}
}

void AIGroup::recompute()
{
	float closeDist = 1.0e9f; // retail's immutable float at RVA 0x00817CFC
	Coord3D center;
	getCenter(&center);
	rva0036CE87();
	m_speed = 1e+10f;
	for (std::list<Object *>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it)
	{
		Object *obj = *it;
		if ((obj->m_template->m_kindOf[0] & 4) != 0)
			continue;
		if ((obj->m_disabledMask[0] & 8) != 0)
			continue;
		Rva002627E8 *ai = reinterpret_cast<Rva002627E8 *>(obj->m_ai);
		if (ai == 0)
			continue;
		float maxSpeed = ai->rva002627E8();
		if (m_speed > maxSpeed &&
			obj->m_body254->getDamageState() < TheWritableGlobalData->m_movementPenaltyDamageState)
			m_speed = maxSpeed;
		float dx = obj->m_cachedPos.x - center.x;
		float dy = obj->m_cachedPos.y - center.y;
		float dist = dx * dx + dy * dy;
		if (dist < closeDist)
			closeDist = dist;
	}
	m_dirty = false;
}
