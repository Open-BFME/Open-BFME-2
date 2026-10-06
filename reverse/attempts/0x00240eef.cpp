// ?rva00240EEF@Rva00240EEF@@QAEPAVObject@@VAsciiString@@PBUCoord3D@@@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs
// stlport
// ?rva00240EEF@Rva00240EEF@@QAEPAVObject@@VAsciiString@@PBUCoord3D@@@Z, retail 0x00240EEF (347B).
// Lookup via g_009FF000 Rva002D06CA 0x002D06CA, GlobalData guard +0x1110,
// set<AsciiString> ctor 0x000D3A71 + notify 0x0033CF34 + merge 0x0061F010,
// CreateMask via ji_006291ae, ThingFactory::newObject 0x002D0A23,
// Thing::setOrientation 0x0030AB9D + setPosition 0x0030AA80, pathfind + adjust.
// Evidence: callers at 0x002411BF 0x00241DA1 0x00242195, prev 0x00240DF1 next 0x002418E2.
#include "ascii_string.h"
#include <set>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ThingTemplate;
class Team;
class Object;
class Thing;
class LocomotorSet;
class Pathfinder;
class BFMEPathfinderMapShim;
class GlobalData;
class AI;
struct CreateMask;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern Rva002D06CA *g_009FF000;

class GlobalData
{
public:
	char m_pad[0x1110];
	unsigned char m_1110;
};

extern GlobalData *TheWritableGlobalData;

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

void __cdecl bfmeMergeReceiverKeys(int value);

void *__cdecl ji_006291ae(void *dst, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct CreateMask
{
	char m_data[0x10];
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};

class Thing
{
public:
	void setOrientation(float v);
	void setPosition(const Coord3D *pos);
};

class ThingTemplate
{
public:
	char m_pad[0x108];
	unsigned char m_flags108;
	char m_pad2[0x4D0 - 0x109];
	float m_orient4D0;
};

class Team
{
public:
	char m_pad[0x5D];
	unsigned char m_5d;
	unsigned char m_5e;
};

class LocomotorSet
{
public:
	char m_data[4];
};

class AIUpdateInterface
{
public:
	char m_pad[0x1CC];
	LocomotorSet m_loco;
};

class Object
{
public:
	void rva0028ACEE(int a, int b);
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *obj);
};

class Pathfinder
{
public:
	bool adjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dst, const Coord3D *group);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pf;
};

extern AI *g_Va009FF0F8;

class Rva00240EEF
{
public:
	char m_pad[0x2EC];
	Team *m_team;
	Object *rva00240EEF(AsciiString name, const Coord3D *pos);
};

// ?rva00240EEF@Rva00240EEF@@QAEPAVObject@@VAsciiString@@PBUCoord3D@@@Z present-unmatched
Object *Rva00240EEF::rva00240EEF(AsciiString name, const Coord3D *pos)
{
	void *tmplRaw = g_009FF000->rva002D06CA(&name);
	if (tmplRaw == 0)
		return 0;
	ThingTemplate *tmpl = (ThingTemplate *)tmplRaw;
	if (TheWritableGlobalData->m_1110 == 0) {
		bool flag = false;
		_STL::set<AsciiString> receivers;
		volatile int keep0 = 0;
		volatile bool keep1 = true;
		((Rva0020AA00Target *)tmpl)->notify((int)&receivers, (int)&flag);
		bfmeMergeReceiverKeys((int)&receivers);
	}
	CreateMask mask;
	ji_006291ae(&mask, 0, 0x10);
	Team *team = m_team;
	Object *obj = ((ThingFactory *)g_009FF000)->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	if (obj == 0)
		return 0;
	ThingTemplate *t2 = *(ThingTemplate **)((char *)obj + 4);
	((Thing *)obj)->setOrientation(t2->m_orient4D0);
	((Thing *)obj)->setPosition(pos);
	Team *t = m_team;
	((Rva0028CBFD *)obj)->rva0028CBFD();
	if (t != 0) {
		if (t->m_5d == 0) {
			t->m_5e = 1;
			t->m_5d = 1;
		}
	}
	((BFMEPathfinderMapShim *)g_Va009FF0F8->m_pf)->addObjectToPathfindMap(obj);
	AIUpdateInterface *aiu = *(AIUpdateInterface **)((char *)obj + 0x258);
	if (aiu == 0)
		return obj;
	ThingTemplate *t3 = *(ThingTemplate **)((char *)obj + 4);
	if (t3->m_flags108 & 4)
		return obj;
	LocomotorSet *loco = (LocomotorSet *)((char *)aiu + 0x1CC);
	Pathfinder *pf = g_Va009FF0F8->m_pf;
	if (!pf->adjustDestination(obj, *loco, (Coord3D *)pos, (const Coord3D *)0))
		return obj;
	((Object *)obj)->rva0028ACEE((int)pos, 1);
	((Thing *)obj)->setPosition(pos);
	return obj;
}
