// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva002A8F56@Rva002A8F24@@QAEXPAVObject@@@Z, retail 0x002A8F56, 138 bytes.
// Rva002A8F24 member taking Object*: skips when Object+0x4b0 set, resolves the
// controlling Player twice via rowed Object::getControllingPlayer 0x28AFA9,
// looks up pin-only 0x2A8AB1 then rowed 0x2A8F24 dispatching to rowed 0x4E0425,
// then erases the ObjectID at Object+0x74 from the vector<ObjectID> at
// this+0x934 via rowed _STL::find CreateAHeroData 0x20E873 and rowed
// vector<ObjectID>::erase 0x25BF5D when the Kind flag at [Object+4]+0x10e has
// bit 2 set. Evidence: packet disassembly callers and LINK BONUS via 0x28BAC0,
// prev/next // cl: and offsets 0x908 map 0x914 range 0x934 vector.
// Honest address name; owner is Rva002A8F24 from shared this with 0x2A8AB1/0x2A8F24.
#include <vector>
#include <algorithm>

class Player;
class CreateAHeroData;

enum ObjectID
{
	OBJECTID_INVALID = 0
};

struct ObjectInner4
{
	char m_pad[0x10e];
	unsigned char m_flag; // +0x10e, bit 2 gates the hero-list erase
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad0[4]; // +0 (vptr)
	struct ObjectInner4 *m_p4; // +4
	char m_pad8[0x74 - 8]; // +8..+0x73
	enum ObjectID m_id; // +0x74
	char m_pad78[0x4b0 - 0x78]; // +0x78..+0x4af
	unsigned char m_4b0; // +0x4b0
};

struct Rva002A8AB1Record
{
public:
	void rva002C6A4E(Object *obj);
};

class AIStatCollector
{
public:
	void UnRegister(void *p);
};

class Rva002A8F24
{
public:
	struct Rva002A8AB1Record *rva002A8AB1(void *key);
	void *rva002A8F24(Player *player);
	void rva002A8F56(Object *obj);
private:
	char m_pad[0x934];
	_STL::vector<enum ObjectID> m_vec; // +0x934
};

void Rva002A8F24::rva002A8F56(Object *obj)
{
	if (obj->m_4b0 != 0)
		return;
	Player *p = obj->getControllingPlayer();
	struct Rva002A8AB1Record *r = rva002A8AB1(p);
	if (r != 0)
		r->rva002C6A4E(obj);
	Player *p2 = obj->getControllingPlayer();
	void *v = rva002A8F24(p2);
	if (v != 0)
		((class AIStatCollector *)v)->UnRegister(obj);
	if ((obj->m_p4->m_flag & 4) == 0)
		return;
	enum ObjectID id = obj->m_id;
	enum ObjectID *end = m_vec.end();
	CreateAHeroData **it = _STL::find((CreateAHeroData **)m_vec.begin(), (CreateAHeroData **)end, (CreateAHeroData *&)id);
	if ((enum ObjectID *)it != end)
		m_vec.erase((enum ObjectID *)it);
}
