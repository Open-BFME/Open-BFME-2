// ?rva0044F6D0@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.968 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva0044F6D0@SpecialAbilityUpdate@@QAEXXZ, retail 0x0044F6D0, 94 bytes.
// Sibling of ?rva0044F633@Rva0044F633@@QAEPAXXZ (rowed 0x0044F633): same
// holder at this+4 with the Overridable at +0x38, same ObjectID at +0x40
// resolved via TheGameLogic->findObjectByID (rowed 0x00049DC5), same final
// override kind check (rowed friend_getFinalOverride 0x00288609, kind 0x27)
// and target status bytes at +0x108/+0x114. This one refreshes the cached
// slot at +0x3C from the holder's fallback at +0x78, ticking the frame
// countdown at +0x60 down toward zero first. Members match the rowed
// SpecialAbilityUpdate xfer layout (m_3C/m_40/m_60); the method name is an
// honest address-derived placeholder, the class is the proven one.
class Object
{
public:
	char m_pad0[4];
	unsigned char *m_base4;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
};

class Rva0044F6D0Inner
{
public:
	char m_pad0[0x38];
	Overridable *m_override38;
	char m_pad1[0x78 - 0x38 - 4];
	void *m_fallback78;
};

class SpecialAbilityUpdate
{
public:
	void rva0044F6D0();

private:
	char m_pad0[4];
	Rva0044F6D0Inner *m_inner4;
	char m_pad1[0x3C - 8];
	void *m_cached3C;
	ObjectID m_target40;
	char m_pad2[0x60 - 0x44];
	int m_count60;
};

// ?rva0044F6D0@SpecialAbilityUpdate@@QAEXXZ present-unmatched
void SpecialAbilityUpdate::rva0044F6D0()
{
	Rva0044F6D0Inner *inner = m_inner4;
	Overridable *ovr = inner->m_override38;
	Object *obj = TheGameLogic->findObjectByID(m_target40);
	if (m_count60 > 0)
		--m_count60;
	const Overridable *ov = ovr->friend_getFinalOverride();
	// Retail reuses the obj register for the base pointer (mov ebp,[ebp+4]);
	// spelling the reuse keeps the byte shape.
	if (ov->m_val1C != 0x27 || (obj != 0 &&
		((obj = (Object *)obj->m_base4, ((unsigned char *)obj)[0x108] & 0x40) ||
		(((unsigned char *)obj)[0x114] & 8))))
		m_cached3C = inner->m_fallback78;
	else
		m_cached3C = 0;
}
