// cl: /O1 /MD
//
// ?Rva00547070@Rva00546F61@@UAEPAUCoord3D@@H@Z, retail 0x00547070 41B.
// Virtual slot 8 (offset 0x20) of vtable 0x0086A420 (class of
// ??1Rva00546F61@@UAE@XZ in Rva00548948Derived.cpp). No donor (opaque Rva).
// Evidence: push [ebx+0x18] ObjectID plus TheGameLogic findObjectByID row
// 0x00049DC5 plus copy of found Object position +0x38 into this Coord3D +0x20
// via lea plus 3x movsd plus lea eax return. No callers. Ignores int dummy
// param (ret 4) and uses this only.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object
{
public:
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
};
class GameLogic
{
public:
	Object* findObjectByID(ObjectID id);
};
extern GameLogic* TheGameLogic;
class Rva00546F61
{
public:
	virtual ~Rva00546F61();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D* Rva00547070(int dummy);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	char m_pad1C[0x20 - 0x18 - 4];
	Coord3D m_pos; // +0x20
};
Coord3D* Rva00546F61::Rva00547070(int dummy)
{
	Object* found = TheGameLogic->findObjectByID(m_targetID);
	if (found != 0) {
		Coord3D* dst = &m_pos;
		const Coord3D* src = &found->m_position;
		*dst = *src;
	}
	return &m_pos;
}
