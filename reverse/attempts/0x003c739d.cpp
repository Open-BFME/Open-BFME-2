// ?rva003C739D@ScriptActions@@QAEXABVAsciiString@@PAVParameter@@111@Z
// partial score=0.98 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptActions::rva003C739D, retail 0x003C739D, 549 bytes (called from the
// action dispatcher 0x003CA4BE at 0x003CE6F3). A BFME2 castle script action:
// around the object the named castle's CastleBehavior picks for the area
// name (0x00397429), the first alive structure within 1000 (BFME2's
// partition filter chain, the view AIStructureCreepTactic.cpp documents)
// that the upgrade can affect (0x002940B9) and does not have yet
// (0x00290D2B), and whose template is equivalent to the given template or
// to one of the given ObjectTypes list's, gets the upgrade (0x00293077)
// and, when given, the script name.
#include "ascii_string.h"

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

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit) throw();	// 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

struct Coord3D
{
	float x;
	float y;
	float z;
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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tt) const;	// 0x0033BB04
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	// 0x0026F26D
};
extern UpgradeCenter *TheUpgradeCenter;

class Module
{
public:
	virtual void moduleSlot();
};

class Object;

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();	// 0x003955DA
	Object *rva00397429(const AsciiString &name);	// 0x00397429
};

class Object
{
	friend class ScriptActions;
public:
	bool rva002940B9(const UpgradeTemplate *upgrade);	// 0x002940B9
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;	// 0x00290D2B
	void rva00293077(const void *upgrade);	// 0x00293077
	const Coord3D *getPosition() const { return &m_pos; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

class ObjectTypes
{
public:
	unsigned int getListSize() const { return m_end - m_begin; }
	AsciiString getNthInList(unsigned int index) const;	// 0x002041AC
private:
	char m_pad00[8];
	AsciiString *m_begin;	// +0x08
	AsciiString *m_end;	// +0x0C
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;		// +0x0C
	AsciiString m_string;	// +0x10
};

class ScriptEngine
{
public:
	Object *getUnitNamed(const AsciiString &name);			// 0x003588E7
	ObjectTypes *getObjectTypes(const AsciiString &name);		// 0x00357651
	void rva00208968(const AsciiString &name, Object *obj);		// 0x00208968
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C739D(const AsciiString &castleName, Parameter *upgradeParm, Parameter *typeParm,
		Parameter *areaParm, Parameter *nameParm);
};

void ScriptActions::rva003C739D(const AsciiString &castleName, Parameter *upgradeParm, Parameter *typeParm,
	Parameter *areaParm, Parameter *nameParm)
{
	Object *castle = TheScriptEngine->getUnitNamed(castleName);
	if (!castle)
		return;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return;
	Object *center = behavior->rva00397429(areaParm->getString());
	if (!center)
		return;
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeParm->getString());
	if (!upgrade)
		return;
	const ThingTemplate *templ = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeParm->getString());
	if (!types) {
		templ = TheThingFactory->findTemplate(typeParm->getString());
		if (!templ)
			return;
	}
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(center->getPosition(), 1000.0f, 0,
		Rva0004584D(BfmeFixedStorage0004543D(0, 7), *(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
			.link(&Rva0026119DFilter()), 1);
	Object *obj;
	while ((obj = hits.next()) != 0) {
		if (!obj->rva002940B9(upgrade))
			continue;
		if (obj->rva00290D2B(upgrade))
			continue;
		const ThingTemplate *objTemplate = obj->getTemplate();
		if (templ) {
			if (!templ->isEquivalentTo(objTemplate))
				continue;
		} else if (types) {
			bool matched = false;
			for (unsigned int i = 0; i < types->getListSize(); ++i) {
				const ThingTemplate *candidate = TheThingFactory->findTemplate(types->getNthInList(i));
				if (candidate && candidate->isEquivalentTo(objTemplate)) {
					matched = true;
					break;
				}
			}
			if (!matched)
				continue;
		}
		obj->rva00293077(upgrade);
		AsciiString name = nameParm->getString();
		if (!name.isEmpty())
			TheScriptEngine->rva00208968(name, obj);
		break;
	}
}
