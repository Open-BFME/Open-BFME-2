// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Two more SpecialPowerTemplate field getters in the shape of Zero Hour's
// inline accessors (getSpecialPowerType 0x002AAE3D reads +0x14,
// getRequiredScience 0x0028F8D7 reads +0x1C): each reads one dword of the
// final override returned by the rowed Overridable::friend_getFinalOverride
// 0x00288609. Retail keeps these out-of-line copies with no direct caller.
// The fields they read are not identified, so the names are address-derived.

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	int getLightPointCost() const;
	int getEvaEventToPlayOnSuccess() const;

private:
	char m_pad00[0x30];
	int m_lightPointCost;	// +0x30
	char m_pad34[0x44 - 0x34];
	int m_evaEventToPlayOnSuccess;	// +0x44
};

// 0x004210EF (9B)
int SpecialPowerTemplate::getLightPointCost() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_lightPointCost;
}

// 0x0044EB4B (9B)
int SpecialPowerTemplate::getEvaEventToPlayOnSuccess() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_evaEventToPlayOnSuccess;
}

// 0x004D973E / 0x004D9747 (9B each): the same final-override read returning
// the ADDRESS of a member (+0x3C, +0x40) instead of its value. The owning
// Overridable subclass is not identified, so it is a separate view.
class Rva004D973EOverridable : public Overridable
{
public:
	const int *rva004D973E() const;
	const int *rva004D9747() const;

private:
	char m_pad00[0x3C];
	int m_3C;	// +0x3C
	int m_40;	// +0x40
};

const int *Rva004D973EOverridable::rva004D973E() const
{
	return &((const Rva004D973EOverridable *)friend_getFinalOverride())->m_3C;
}

const int *Rva004D973EOverridable::rva004D9747() const
{
	return &((const Rva004D973EOverridable *)friend_getFinalOverride())->m_40;
}
