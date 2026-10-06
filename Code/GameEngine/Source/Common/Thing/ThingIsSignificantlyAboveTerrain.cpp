// cl: /DNDEBUG /MD
//
// ?rva0030AD8B@Thing@@QBE_NM@Z (0x0030AD8B, 60B) and
// ?isSignificantlyAboveTerrain@Object@@QBE_NXZ (0x0030ADDC, 12B).
// Zero Hour's Thing::isSignificantlyAboveTerrain ("more than 3 frames of
// fall": height above terrain > -(3*3) * gravity) grown in BFME 2 into a
// worker taking a height offset, which first refuses things whose template
// carries either of the two kind-of bits in byte +0x11F (mask 0x81); the
// no-argument form passes 0.0f. The caller-facing row keeps its pinned Object
// spelling; the worker's identity beyond the donor shape is address-derived.

typedef bool Bool;
typedef float Real;

class GlobalData
{
public:
	unsigned char m_pad000[0xC4];
	Real m_gravity; // +0xC4
};
extern class GlobalData *TheWritableGlobalData;

struct Rva0030AD8BTemplate
{
	unsigned char m_pad000[0x11F];
	unsigned char m_kindOfByte11F; // +0x11F
};

class Thing
{
public:
	Real getHeightAboveTerrain() const;
	Bool rva0030AD8B(Real offset) const;

protected:
	void *m_vptr;
	const Rva0030AD8BTemplate *m_template; // +0x04
};

class Object : public Thing
{
public:
	Bool isSignificantlyAboveTerrain() const;
};

Bool Thing::rva0030AD8B(Real offset) const
{
	if ((m_template->m_kindOfByte11F & 0x81) == 0)
		return getHeightAboveTerrain() + offset > -(3 * 3) * TheWritableGlobalData->m_gravity;
	return false;
}

Bool Object::isSignificantlyAboveTerrain() const
{
	return rva0030AD8B(0.0f);
}
