// cl: /O1 /DNDEBUG /MD
// ?rva00796023@@YAHPAVObject@@PAX@Z @0x00396023 154B evidence: LINK BONUS names it free int(Object void*) neighbour Rva003960BDSearch box with 2 Vecs flag18 callees rowed findModule CastleBehavior key plus pinned trigger tests
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Module { public: virtual ~Module(); };
struct Coord3D { float x; float y; float z; };
class PolygonTrigger { public: bool rva002E3A39(const Coord3D &p); };
class CastleBehavior { public: static NameKeyType rva0003955DA(); PolygonTrigger *rva00395E53(int i); char m_pad[0x80]; void *m_80; void *m_84; };
class Object { public: char m_pad00[4]; void *m_04; protected: Module *findModule(NameKeyType key) const; };
struct ObjectHack : public Object { Module *get(NameKeyType k) const { return findModule(k); } };
struct BoxVec { int a; int b; int c; };
struct Box { BoxVec m_00; BoxVec m_0C; unsigned char m_18; };
int __cdecl rva00796023(Object *obj, void *userData)
{
	if ((((unsigned char *)obj->m_04)[0x117] & 1) == 0)
		return 1;
	CastleBehavior *beh = (CastleBehavior *)((ObjectHack *)obj)->get(CastleBehavior::rva0003955DA());
	if (beh == 0)
		return 1;
	int i = 0;
	Box *box = (Box *)userData;
	for (; i < ((((char *)beh->m_84 - (char *)beh->m_80)) >> 2); ++i)
	{
		PolygonTrigger *trig = beh->rva00395E53(i);
		if (trig->rva002E3A39(*(const Coord3D *)&box->m_00))
			return 0;
		if (box->m_18 != 0)
			continue;
		if (!trig->rva002E3A39(*(const Coord3D *)&box->m_0C))
			continue;
		box->m_18 = 1;
	}
	return 1;
}
