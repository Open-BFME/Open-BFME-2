// cl: /O1 /DNDEBUG /MD /EHsc
// The two concrete slots of the FXNugget-family base vftable 0x00BDC940
// (tools/vftable_map.py: ~dtor, purecall, 0x001DFF1F, purecall, 0x001DFF5D),
// inherited unchanged by the nugget vftables (EvaEvent 0x00BDD754, Sound
// 0x00BDD768, ...), so no derived table can be defined until both have names.
//
// ?doFXObj@Rva001DFEAABase@@UBEXPBVObject@@0@Z @0x001DFF1F 62B: ZH
// FXNugget::doFXObj's shape - forwards to slot 1 (doFXPos) with the
// primary's position (+0x38) and transform (+0x08), speed 0 and the
// secondary's position; BFME2's doFXPos has no overrideRadius.
// ?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z @0x001DFF5D 157B: the
// nugget's fire gate. Primary: filter +0x08 (0x00362437), model-condition
// masks +0x10/+0x5C against Object+0x10C (0x001DFE56), no drawable in state
// 5; secondary: filter +0x0C and masks +0xA8/+0xF4; then +0x140 (2 = any)
// against TheWritableGlobalData+0x138. Identity of the gate unproven, so it
// keeps the address name; the base class keeps its do-not-name token.
struct Coord3D { float x, y, z; };
class Matrix3D { public: float m[12]; };
class Drawable;
class Player;

class Rva001DFE56
{
public:
	bool rva001DFE56(const void *required, const void *exempt) const;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	virtual ~Object();
	Drawable *getDrawable() const;
	int m_04;
	Matrix3D m_transform;		// +0x08
	Coord3D m_cachedPos;		// +0x38
	unsigned char m_pad44[0x10C - 0x44];
	Rva001DFE56 m_modelConditions;	// +0x10C
};

class Drawable
{
public:
	unsigned char m_pad[0x164];
	int m_164;
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
	int m_index;
};

class GlobalData
{
public:
	unsigned char m_pad[0x138];
	int m_138;
};
extern GlobalData *TheWritableGlobalData;

struct Mask76 { unsigned char m_bytes[0x4C]; };

class Rva001DFEAABase
{
public:
	virtual ~Rva001DFEAABase();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;
	virtual void slot3() const = 0;
	virtual bool rva001DFF5D(Object *primary, Object *secondary);

	int m_field04;
	Rva2225E0Filter m_filter08;
	Rva2225E0Filter m_filter0C;
	Mask76 m_mask10;
	Mask76 m_mask5C;
	Mask76 m_maskA8;
	Mask76 m_maskF4;
	int m_140;
	bool m_144;
};

void Rva001DFEAABase::doFXObj(const Object *primary, const Object *secondary) const
{
	const Coord3D *primaryPos = primary ? primary->getPosition() : 0;
	const Matrix3D *primaryMtx = primary ? primary->getTransformMatrix() : 0;
	const Coord3D *secondaryPos = secondary ? secondary->getPosition() : 0;
	doFXPos(primaryPos, primaryMtx, 0.0f, secondaryPos);
}

bool Rva001DFEAABase::rva001DFF5D(Object *primary, Object *secondary)
{
	if (primary)
	{
		if (!m_filter08.accepts(primary, 0))
			return false;
		if (!primary->m_modelConditions.rva001DFE56(&m_mask10, &m_mask5C))
			return false;
		Drawable *draw = primary->getDrawable();
		if (draw && draw->m_164 == 5)
			return false;
	}
	if (secondary)
	{
		if (!m_filter0C.accepts(secondary, 0))
			return false;
		if (!secondary->m_modelConditions.rva001DFE56(&m_maskA8, &m_maskF4))
			return false;
	}
	if (m_140 != 2 && TheWritableGlobalData->m_138 != m_140)
		return false;
	return true;
}
