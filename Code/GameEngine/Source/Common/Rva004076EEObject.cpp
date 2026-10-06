// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004076EE@Rva004076EE@@QAEPAVObject@@XZ retail 0x004076EE 23B
// Evidence: unlock lane; ObjectID at +4 plus TheGameLogic 0x00DFE78C findObjectByID 0x00049DC5 precedent BuildListInfoRva00281BF7; callers 10 incl 0x0029DCA9 0x00407705; unblocks 9.
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

class Rva004076EE
{
public:
	Object *rva004076EE();
private:
	char m_pad[4];
	ObjectID m_id;
};

Object *Rva004076EE::rva004076EE()
{
	if (m_id != INVALID_ID)
		return TheGameLogic->findObjectByID(m_id);
	return 0;
}
