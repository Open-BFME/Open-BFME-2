// cl: /MD
// ?rva0025BFF8@Rva0025BFF8@@QAEPAVObject@@H@Z, retail 0x0025BFF8, 24 bytes.
// Object getter via GameLogic::findObjectByID: loads ObjectID array at this+4,
// pushes the ID at the given index, then calls rowed findObjectByID at 0x00049DC5
// with TheGameLogic at 0x00DFE78C (same absolute-address idiom as
// Rva00203693Host.cpp). Callers (12 incl 0x004ACDD) pass an index; unblocks 9.
// Prev is VectorObjectIDFillInsert, next is FreeMemberDeleters; same /O1 /MD.
enum ObjectID
{
	OBJECTID_INVALID = -1
};
class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
private:
	char m_pad[4];
	ObjectID *m_ids;
};
Object *Rva0025BFF8::rva0025BFF8(int index)
{
	return TheGameLogic->findObjectByID(m_ids[index]);
}
