// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00281BF7@Rva00281BF7@@QAEHXZ, RVA 0x00281BF7, 28 bytes.
// BuildListInfo-adjacent ID lookup: push ObjectID at +0x60, call rowed
// GameLogic::findObjectByID 0x00049DC5 via TheGameLogic 0x00DFE78C, return 0
// when null, else tail-jmp to rowed BuildListInfo::getDesiredGatherers
// 0x005508E2 which reads +0x84. Callers at 0x0010CF5F 0x0010CF6A and
// 0x00281F0B; unblocks 0x00281ECA. Same je-then-xor shape as donor-verbatim
// AIPlayer supply paths; if (obj) return get else return 0 places the true
// path inline per the shape guide.
enum ObjectID
{
	INVALID_ID = 0
};
class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class BuildListInfo
{
public:
	int getDesiredGatherers();
};
struct Rva00281BF7
{
	char m_pad[0x60];
	ObjectID m_id;
	int rva00281BF7();
};
int Rva00281BF7::rva00281BF7()
{
	Object *obj = TheGameLogic->findObjectByID(m_id);
	if (obj)
		return ((BuildListInfo *)obj)->getDesiredGatherers();
	return 0;
}
