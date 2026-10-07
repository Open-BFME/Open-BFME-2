// cl: /MD /DNDEBUG
// ?rva004C7F5C@Rva004C7F5C@@QAEXPAVObject@@@Z 222B @0x004C7F5C: heal guard via Thing KindOf plus relationship plus float range plus body mult plus attemptHealing plus doFXObj.
// Evidence: retail push ebp frame plus Thing 0x11B test plus isAnyKindOf via BitFlags at this plus4 plus0x88 plus getRelationship pin 0x28D156 plus float range via BfmeZeroRange and g_00BCEA18 plus body at plus0x254 slot 0x18 mult plus attemptHealing row 0x28FE55 plus doFXObj row 0x0B2235. Caller at 0x004C8128.
template<int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

struct Tmpl
{
	char m_pad00[0x108];
	unsigned char m_108;
	char m_pad109[0x11B - 0x109];
	unsigned char m_11B;
};

enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};

class Object;
class Mult
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual float getMult();
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
	void attemptHealing(float amount, const Object *source);

	char m_pad00[4];
	Tmpl *m_4;
	char m_pad08[0x74 - 8];
	int m_74;
	char m_pad78[0x254 - 0x78];
	Mult *m_254;
	char m_pad258[0x280 - 0x258];
	float m_280;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

extern const float BfmeZeroRange;

struct Inner
{
	char m_pad00[0x7C];
	float m_7c;
	unsigned char m_80;
	char m_pad81[0xA4 - 0x81];
	FXList *m_a4;
};

class Rva004C7F5C
{
public:
	void rva004C7F5C(Object *obj);
private:
	char m_pad00[4];
	Inner *m_4;
	Object *m_8;
};

void Rva004C7F5C::rva004C7F5C(Object *obj)
{
	Inner *inner = m_4;
	if ((obj->m_4->m_11B & 8) != 0)
		return;
	if (((Thing *)obj)->isAnyKindOf(*(const BitFlags<69> *)((char *)inner + 0x88)) == 0)
		return;
	if (obj->m_74 != m_8->m_74)
	{
		if (obj->getRelationship(m_8) != REL_2)
			return;
	}
	if ((obj->m_4->m_108 & 0x80) != 0)
	{
		float *p280 = &obj->m_280;
		if (*p280 >= BfmeZeroRange)
		{
			if (99.0f > *p280) // retail's immutable float at RVA 0x007CEA18
				return;
		}
	}
	Mult *mult = obj->m_254;
	int zero = 0;
	if (mult == (Mult *)zero)
		return;
	float amount = inner->m_7c;
	if (inner->m_80 != (unsigned char)zero)
		amount *= mult->getMult();
	if (!(amount > BfmeZeroRange))
		return;
	obj->attemptHealing(amount, (const Object *)zero);
	FXList *fx = inner->m_a4;
	if (fx == (FXList *)zero)
		return;
	FXList::doFXObj(fx, obj, (const Object *)zero);
}
