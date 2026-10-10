// cl: /O1 /DNDEBUG /MD
// PreorderCreate secondary onBuildComplete entry at 0x004B9301, 68 B.
// Reference semantic lead: pinned BFME1 575ba2b04 inputs/reference/
// CnC_Generals_Zero_Hour/GeneralsMD/.../Create/PreorderCreate.cpp:
// didPlayerPreorder selects set/clear of MODELCONDITION_PREORDER.
// Target facts: ctor 0x004B9257 installs Create interface table 0x00859664
// at primary+0x0C; slot1 enters here without a thunk, so Object+0x04 is
// reached at entry-this-8. Native Player byte+0x33B and Object mask word
// +0x118/bit30, notifier 0x0028AE6D, and controlling-player 0x0028AFA9
// independently establish these accesses. Full original layouts unasserted.
// The neutral entry view preserves that secondary ABI. Mask bit126 lives
// at +0x118 in the established +0x10C condition-word view. Reloading the
// owner inside each branch preserves native ESI lifetime and tail epilogues.
class Player
{
public:
	unsigned char m_pad[0x33B];
	unsigned char m_33B;
};

struct Rva004B9301Mask { unsigned int bits[19]; unsigned int test(unsigned int bit)const { return bits[bit>>5] & (1U<<(bit&31)); } void set(unsigned int bit) {bits[bit>>5]|=1U<<(bit&31);} void reset(unsigned int bit){bits[bit>>5]&=~(1U<<(bit&31));}};
class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	unsigned char m_pad00[0x10C];
	Rva004B9301Mask m_mask;
};

class Rva004B9301
{
public:
	void rva004B9301();
};

void Rva004B9301::rva004B9301()
{
	Object *o = *(Object **)((char *)this - 8);
	Player *p = o->getControllingPlayer();
	if (p->m_33B != 0)
	{
		o = *(Object **)((char *)this - 8);
		if (o->m_mask.test(126))
			return;
		o->m_mask.set(126);
	}
	else
	{
		o = *(Object **)((char *)this - 8);
		if (o->m_mask.test(126) == 0)
			return;
		o->m_mask.reset(126);
	}
	o->rva0028AE6D();
}
