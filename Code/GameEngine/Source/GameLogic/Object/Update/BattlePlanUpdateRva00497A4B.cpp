// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva00497A4B@BattlePlanUpdate@@QAEXXZ @0x00497A4B 157B.
// BattlePlanUpdate lazy vision-object creation: if m_visionObjectID (+0x88)
// is already set do nothing; otherwise find the template named at
// payload+0xa4 via ThingFactory lookup 0x002D06CA, build an empty 0x10-byte
// CreateMask with ji_006291ae, fetch the local player's team
// (ThePlayerList+0x18 -> +0x2ec) and call ThingFactory::newObject
// 0x002D0A23. On success cache [newObj+0x74] as the vision id, place the
// new object at creator+0x38 (Thing::setPosition 0x0030AA80) and copy the
// creator's shroud range +0xbc (Object::setShroudClearingRange 0x0028BB65).
// Layout follows BattlePlanUpdateRva0049797F.cpp (payload at +0x04,
// object at +0x08) and BattlePlanUpdateXfer.cpp (vision id at +0x88).

#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object
{
public:
	void setShroudClearingRange(float range);

	char m_pad00[0x38];
	Coord3D m_coord38; // +0x38
	char m_pad44[0x74 - 0x44];
	int m_id74; // +0x74
	char m_pad78[0xbc - 0x78];
	float m_shroudBC; // +0xbc
};

class ThingTemplate;
class Team;

struct CreateMask
{
	char m_data[0x10];
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

extern class ThingFactory *TheThingFactory; // ?g_009FF000@@3PAVRva002D06CA@@A

class Player
{
public:
	char m_pad00[0x2ec];
	Team *m_team; // +0x2ec
};

class PlayerList
{
public:
	char m_pad00[0x18];
	Player *m_player; // +0x18
};

extern PlayerList *ThePlayerList; // ?ThePlayerList@@3PAVPlayerList@@A

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct Payload00497A4B
{
	char m_pad00[0xa4];
	AsciiString m_templateName; // +0xa4
};

class BattlePlanUpdate
{
public:
	void rva00497A4B();

private:
	void *m_vtable; // +0x00
	Payload00497A4B *m_payload; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x88 - 0x0c];
	int m_visionID; // +0x88
};

void BattlePlanUpdate::rva00497A4B()
{
	if (m_visionID != 0)
		return;
	Payload00497A4B *payload = m_payload;
	Object *obj = m_object;
	void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&payload->m_templateName);
	if (tmpl == 0)
		return;
	Player *player = ThePlayerList->m_player;
	if (player == 0)
		return;
	CreateMask mask;
	ji_006291ae(&mask, 0, 0x10);
	Team *team = player->m_team;
	Object *newObj = ((ThingFactory *)TheThingFactory)->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	if (newObj == 0)
		return;
	m_visionID = newObj->m_id74;
	((Thing *)newObj)->setPosition(&obj->m_coord38);
	newObj->setShroudClearingRange(obj->m_shroudBC);
}
