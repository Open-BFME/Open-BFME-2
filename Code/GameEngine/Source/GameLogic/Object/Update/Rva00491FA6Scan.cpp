// cl: /O1 /MD /GX /arch:SSE
//
// ?rva00491FA6@Rva00491FA6@@QAEPAVObject@@XZ, retail 0x00491FA6, 227 bytes.
// An update-module member (+0x04 the module data, +0x08 the object; caller
// 0x00492108 in 0x004920B5, owner class not established, hence the address
// name): the nearest alive object within the module data's +0x0C range
// that passes the 0x002614EC filter (module data +0x10, the object's
// controlling player) and lacks object status 98 (the two-mask status
// filter 0x003685CF), iterated near to far.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include <string.h>

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// An ObjectStatusMaskType view: 128 bits, zeroed then set bit by bit.
struct Rva00491FA6Mask
{
	Rva00491FA6Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[4];
};

class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
};

// vftable 0x00C17968 (ctor 0x003685CF): two status masks.
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const BfmeObject872Header &a, const BfmeObject872Header &b);
	virtual bool allow(Object *obj);
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
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
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

struct Rva00491FA6ModuleData
{
	char m_pad00[0x0C];
	float m_range;		// +0x0C
	char m_10[4];		// +0x10
};

class Rva00491FA6
{
public:
	Object *rva00491FA6();
	Object *getObject() const { return m_object; }
private:
	const void *m_vtable;
	const Rva00491FA6ModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};

Object *Rva00491FA6::rva00491FA6()
{
	const Rva00491FA6ModuleData *md = m_moduleData;
	Rva00491FA6Mask mustBeSet;
	Rva00491FA6Mask mustBeClear;
	mustBeClear.set(98);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), md->m_range, 0,
		Rva0026119DFilter().link(Rva002614ECFilter(md->m_10, getObject()->getControllingPlayer(), true)
			.link(&Rva003685CF(*(BfmeObject872Header *)&mustBeSet, *(BfmeObject872Header *)&mustBeClear))), 1);
	return hits.next();
}
