// cl: /DNDEBUG /MD
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

void __cdecl operator delete(void *) throw();

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
struct BfmeListNodeBase;

class AIGroup
{
public:
	void rva0036CE87();
	bool getCenter(Coord3D *center);
	friend class PathDeleteArgument;

private:
	char m_pad00[4];
	BfmeListNodeBase *m_list04;
	float m_speed08;
	unsigned char m_dirty0C;
	char m_pad0D[0x14 - 0x0d];
	Path *m_groundPath;
	float m_pathState18;
	float m_pathState1C;
	float m_pathState20;
	float m_pathState24;
	float m_pathState28;
	float m_pathState2C;
	void recompute();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
	unsigned char m_kind108;
};
class Object {
public:
	void *m_vtbl00;
	ThingTemplate *m_template04;
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos38;
	char m_pad44[0x1c8 - 0x44];
	unsigned char m_disabled1C8;
	char m_pad1C9[0x254 - 0x1c9];
	BodyModuleInterface *m_body254;
	Rva002627E8 *m_ai258;
};
struct BfmeListNodeBase {
	BfmeListNodeBase *m_next;
	BfmeListNodeBase *m_prev;
};
struct BfmeMemberNode : public BfmeListNodeBase {
	Object *m_value;
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
		m_owner->m_pathState18 = 0.0f;
		m_owner->m_pathState1C = 0.0f;
		m_owner->m_pathState20 = 0.0f;
	}

private:
	Path *m_path;
	AIGroup *m_owner;
};

void AIGroup::rva0036CE87()
{
	if (m_groundPath)
	{
		Path *p = m_groundPath;
		reinterpret_cast<BFMEDeletablePath *>(p)->destroy();
		operator delete(PathDeleteArgument(p, this));
		m_pathState24 = 10.0f;
		m_pathState28 = 0.0f;
		m_pathState2C = 0.0f;
	}
}

void AIGroup::recompute()
{
	float closeDist = 1.0e9f; // retail's immutable float at RVA 0x00817CFC
	Coord3D center;
	getCenter(&center);
	rva0036CE87();
	m_speed08 = 1e+10f;
	for (BfmeListNodeBase *it = m_list04->m_next; it != m_list04; it = it->m_next)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_value;
		if ((obj->m_template04->m_kind108 & 4) != 0)
			continue;
		if ((obj->m_disabled1C8 & 8) != 0)
			continue;
		Rva002627E8 *ai = obj->m_ai258;
		if (ai == 0)
			continue;
		float maxSpeed = ai->rva002627E8();
		if (m_speed08 > maxSpeed &&
			obj->m_body254->getDamageState() < TheWritableGlobalData->m_movementPenaltyDamageState)
			m_speed08 = maxSpeed;
		float dx = obj->m_pos38.x - center.x;
		float dy = obj->m_pos38.y - center.y;
		float dist = dx * dx + dy * dy;
		if (dist < closeDist)
			closeDist = dist;
	}
	m_dirty0C = 0;
}
