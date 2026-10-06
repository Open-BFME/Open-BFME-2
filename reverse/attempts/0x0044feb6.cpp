// ?rva0044FEB6@SpecialAbilityUpdate@@QAEPAVObject@@XZ
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0044FEB6@SpecialAbilityUpdate@@QAEPAVObject@@XZ, retail 0x0044FEB6, 183 bytes.
// SpecialAbilityUpdate helper that spawns one special object via ThingFactory.
// Evidence: prev row 0x0044F996 xfer same TU dir; callee 0x0044F72E same class
// (list clear plus count zero); ModuleData +0x40 AsciiString lookup via rowed
// 0x002D06CA through g_009FF000; 16-byte zeroed CreateMask via memset thunk
// 0x006291AE; ThingFactory::newObject pin 0x002D0A23 (template team mask false);
// list<int> push_back row 0x0005548F at +0x64 plus count inc at +0x68;
// Thing::setPosition row 0x0030AA80 at +0x38; AIUpdateInterface
// setLastCommandSource row 0x003B23AF via +0x264 with +0x74 source.
#include "ascii_string.h"
#include <list>

#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int words[4];
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

class ThingFactory
{
public:
	class Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};

extern Rva002D06CA *g_009FF000;

enum CommandSourceType
{
	CMD_SOURCE_ZERO = 0
};

class SpecialAbilityUpdate;

class AIUpdateInterface
{
protected:
	void setLastCommandSource(CommandSourceType source);
	friend class SpecialAbilityUpdate;
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_coord38;
	char m_pad44[0x74 - 0x44];
	int m_id74;
	char m_pad78[0x264 - 0x78];
	AIUpdateInterface *m_ai264;
	char m_pad268[0x304 - 0x268];
	Team *m_team304;
};

class SpecialAbilityUpdateModuleData
{
public:
	char m_pad00[0x40];
	AsciiString m_name40;
	char m_pad44[0x80 - 0x44];
	int m_max80;
	char m_pad84[0xA9 - 0x84];
	bool m_flagA9;
};

class SpecialAbilityUpdate
{
public:
	void rva0044F72E();
	Object *rva0044FEB6();

private:
	char m_pad00[4];
	const SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x64 - 0x0C];
	_STL::list<int> m_list64;
	int m_count68;
};

// ?rva0044FEB6@SpecialAbilityUpdate@@QAEPAVObject@@XZ present-unmatched
Object *SpecialAbilityUpdate::rva0044FEB6()
{
	const SpecialAbilityUpdateModuleData *md = m_moduleData;
	Object *newObj = 0;
	if (m_count68 == md->m_max80) {
		if (md->m_flagA9)
			return 0;
		rva0044F72E();
	}
	void *tmplRaw = g_009FF000->rva002D06CA(&md->m_name40);
	if (tmplRaw == 0)
		return newObj;
	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Team *team = m_object->m_team304;
	newObj = ((ThingFactory *)g_009FF000)->newObject((const ThingTemplate *)tmplRaw, team, &mask, false);
	if (newObj == 0)
		return newObj;
	int id = newObj->m_id74;
	m_list64.push_back(id);
	++m_count68;
	((Thing *)newObj)->setPosition(&m_object->m_coord38);
	AIUpdateInterface *ai = newObj->m_ai264;
	if (ai == 0)
		return newObj;
	ai->setLastCommandSource((CommandSourceType)m_object->m_id74);
	return newObj;
}
