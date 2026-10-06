// cl: /DNDEBUG /MD
// ?rva002791E7@Drawable@@QAEXABVModelConditionFlags@@II@Z @0x002791E7 296B.
// BFME 1 donor naming: Drawable::replaceModelConditionState in
// reference/open-bfme-1/game/GameEngine/Source/GameClient/DrawableVisualState.cpp.
// Target identity is address-derived; layout and branches below follow BFME2
// retail at 0x002791E7 and its caller 0x0028AE6D.

class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	unsigned int m_bits[19];
};

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
	unsigned int m_bits[19];
};

class Rva00271C8A
{
public:
	void rva00271C8A(const int *clear, const int *set);
};

class Rva00263546
{
	int m_bits[19];
};

bool __cdecl Rva00275D9FGet(const Rva00263546 *flags);
bool __cdecl Rva00045473Equal(const void *left, const void *right);

class Rva002714CA
{
public:
	void rva002714CA();
};

class ObjectDrawInterface
{
public:
	virtual void replaceModelConditionState(const ModelConditionFlags &state,
		bool immediate, unsigned int effect) = 0;
};

class Drawable
{
public:
	void rva002791E7(const ModelConditionFlags &flags, unsigned int forceReplace,
		unsigned int effect);
	void rva002784EB();
	void rva002784AF();

private:
	char m_pad000[0x158];
	ObjectDrawInterface **m_drawInterfaceBegin;
	ObjectDrawInterface **m_drawInterfaceEnd;
	char m_pad160[0x258 - 0x160];
	ModelConditionFlags m_conditionState;
	ModelConditionFlags m_clearMask;
	ModelConditionFlags m_setMask;
	char m_pad33C[0x443 - 0x33C];
	bool m_isModelDirty;
	char m_pad444[3];
	unsigned char m_flag447;
	unsigned char m_flag448;
};

void Drawable::rva002791E7(const ModelConditionFlags &flags,
	unsigned int forceReplace, unsigned int effect)
{
	WeaponTemplateSetHead copiedFlags((const WeaponTemplateSetHead &)flags);
	ModelConditionFlags &newFlags = *(ModelConditionFlags *)&copiedFlags;
	if (m_setMask.rva000B3EB3() || m_clearMask.rva000B3EB3())
		((Rva00271C8A *)&newFlags)->rva00271C8A(
			(const int *)&m_clearMask, (const int *)&m_setMask);

	if ((unsigned char)forceReplace == 0 &&
		Rva00045473Equal(&m_conditionState, &newFlags))
		return;

	register unsigned int newWord = newFlags.m_bits[4];
	unsigned char newBit = (unsigned char)((newWord >> 29) & 1);
	if (newBit != 0) {
		unsigned char oldBit = (unsigned char)((m_conditionState.m_bits[4] >> 29) & 1);
		if (oldBit == 0 &&
			m_flag448 != 0 && m_flag447 != 0)
			rva002784EB();
	} else if (((unsigned char)(m_conditionState.m_bits[4] >> 29) & 1) != 0) {
		((Rva002714CA *)this)->rva002714CA();
	}

	bool changed = Rva00275D9FGet((const Rva00263546 *)&m_conditionState) !=
		Rva00275D9FGet((const Rva00263546 *)&newFlags);
	m_conditionState = newFlags;

	if ((unsigned char)forceReplace == 1) {
		ObjectDrawInterface **end = m_drawInterfaceEnd;
		for (ObjectDrawInterface **p = m_drawInterfaceBegin; p != end; ++p)
			(*p)->replaceModelConditionState(m_conditionState, true, effect);
		m_isModelDirty = false;
	} else {
		m_isModelDirty = true;
	}

	if (changed)
		rva002784AF();
}
