// cl: /DNDEBUG /MD /EHsc
//
// ?rva002AB22A@Player@@QBEPAVObject@@PBX@Z retail 0x002AB22A 54B. Player best-object
// search via rowed Rva002A996F ctor plus pinned iterateObjects 0x002AB08B with
// callback 0x002AA41A and 0x14B stack helper. Copies 12B point via struct assign
// then returns helper best pointer. Evidence: caller 0x003956C3 passes Object+0x38
// and dereferences return+0x45c plus callback 0x002AA41A writes +0xC Object and +0x10 float.
class Object;

struct Rva002AB22APoint
{
	float x;
	float y;
	float z;
};

class Rva002A996F
{
public:
	Rva002A996F();
	Rva002AB22APoint m_point;
	Object *m_best;
	float m_bestDist;
};

typedef void (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc func, void *userData) const;
	Object *rva002AB22A(const void *pos) const;
};

void __cdecl Rva002AA41A(Object *obj, void *userData);

Object *Player::rva002AB22A(const void *pos) const
{
	Rva002A996F data;
	data.m_point = *(const Rva002AB22APoint *)pos;
	iterateObjects(Rva002AA41A, &data);
	return data.m_best;
}
