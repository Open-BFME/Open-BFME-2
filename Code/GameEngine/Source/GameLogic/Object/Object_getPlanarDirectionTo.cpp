// cl: /DNDEBUG /MD /EHsc
//
// ?getPlanarDirectionTo@Object@@QBEPAUCoord3D@@PAU2@PBV1@@Z,
// retail 0x002654FC (21 bytes). Dedicated TU.
//
// Object planar-delta forwarder: delegates to the 0x26382B planar-subtract
// worker (pinned ?Get2DCenterVectorTo@Object@@QBEXPAUCoord3D@@PBU2@@Z, same commit;
// shared with two other call sites) with (out, &killer->m_position) and
// returns out. m_position sits at +0x38 (retail displacement). Coord3D is a
// struct (PAU per the pin mangling), Object a class (PBV).

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *killer) const;
	void Get2DCenterVectorTo(Coord3D *out, const Coord3D *pos) const;

private:
	char m_pad[0x38];
	Coord3D m_position; // +0x38
};

// ?getPlanarDirectionTo@Object@@QBEPAUCoord3D@@PAU2@PBV1@@Z
Coord3D *Object::getPlanarDirectionTo(Coord3D *out, const Object *killer) const
{
	Get2DCenterVectorTo(out, &killer->m_position);
	return out;
}
