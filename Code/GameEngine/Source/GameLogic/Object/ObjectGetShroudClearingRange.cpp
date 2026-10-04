// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?getShroudClearingRange@Object@@QBEMXZ retail 0x0028DE87, 193 bytes.
// Zero Hour Object::getShroudClearingRange (base range +0x1B4; under
// construction it becomes the geometry bounding radius +0xB8) with two
// BFME 2 scalings around it, both (1 + bonus) multipliers:
//  - first, the attribute-modifier pool (rowed findAttributeModifierPoolUpdate)
//    is asked through 0x00403382 for attribute 0x14 into a zeroed float;
//  - last, when the template's +0x4BC factor is positive, the height
//    (position z +0x40 minus +0x1C4) times that factor, clamped by the
//    template through 0x0028A8B5 (between its +0x4C4 and +0x4C0).
// Both helpers and the two template floats are unnamed (address-derived).

typedef float Real;
typedef bool Bool;
typedef int Int;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE,
	OBJECT_STATUS_DESTROYED,
	OBJECT_STATUS_UNDER_CONSTRUCTION
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AttributeModifierPoolUpdate
{
public:
	Bool rva00403382(Int attribute, Real *value, Int arg);
};

class ThingTemplate
{
public:
	void rva0028A8B5(Real *value) const;

	unsigned char m_pad000[0x4BC];
	Real m_heightFactor4BC;                 // +0x4BC
};

class Object
{
public:
	Real getShroudClearingRange() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	unsigned char m_pad000[4];
	const ThingTemplate *m_template;        // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;                          // +0x38
	unsigned char m_pad044[0xB8 - 0x44];
	Real m_boundingCircleRadius;            // +0xB8 (geometry info)
	unsigned char m_pad0BC[0x1B4 - 0xBC];
	Real m_shroudClearingRange;             // +0x1B4
	unsigned char m_pad1B8[0x1C4 - 0x1B8];
	Real m_height1C4;                       // +0x1C4
};

Real Object::getShroudClearingRange() const
{
	Real shroudClearingRange = m_shroudClearingRange;

	Real bonus = 0.0f;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool && pool->rva00403382(0x14, &bonus, 0))
		shroudClearingRange *= bonus + 1.0f;

	if (testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		shroudClearingRange = m_boundingCircleRadius;

	if (getTemplate()->m_heightFactor4BC > 0.0f)
	{
		Real height = (m_pos.z - m_height1C4) * getTemplate()->m_heightFactor4BC;
		getTemplate()->rva0028A8B5(&height);
		shroudClearingRange *= height + 1.0f;
	}

	return shroudClearingRange;
}
