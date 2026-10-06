// cl: /DNDEBUG /MD /EHsc

// ?m@T_009f4fb0@@QAEXPAURva009F5970StateInit@@@Z @ 0x006276E0 (129B)
//
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/Common/Bfme/T_009F4FB0.cpp
// shape: cleanup, refresh the six state values, rescale from the wider of
// two spans, then visit each node off the list head. BFME2 repair: the list
// head sits at +0x114 here, not BFME1's +0xE4 (near-miss drift at +0x59 and
// +0x63: [edi+0xE4]/[edi+0xE8] vs [edi+0x114]/[edi+0x118]), the same +0x30
// shift the BfmeHostEQR lane proved at 0x00627810 (bfmeAddEQR).
// B1 0x009F4FB0 132B -> B2 0x006276E0 129B, immediate-only drift.

struct Rva009F5970StateInit
{
	float value[6];
};

struct BfmeNode912C
{
	char m_pad00[0x0c];
	BfmeNode912C *m_next;
};

class Gen_dtor_009f2600
{
public:
	void cleanup();
};

// Forward declarations only: the ledger's established identities for the
// node-visit callee (pin at 0x006274B0). BFME1's T_009F4FB0 donor spells
// this call BfmeThing912C::bfmeDo912C(BfmeNode912C *); both spellings reach
// the same address, and the BfmeHostEQR spelling is already pinned, so this
// TU reuses it instead of minting a second pin for one body.
class BfmeRecEQR;
class BfmeHostEQR
{
public:
	void bfmeLinkEQR(BfmeRecEQR *rec);
};

static float g_bfmeDefaultBU;

class T_009f4fb0
{
public:
	void m(Rva009F5970StateInit *value);

	Rva009F5970StateInit m_values;
	char m_pad18[0xfc];
	BfmeNode912C *m_head;
	float m_scale;
	int m_flags;
	void *m_tail;
};

void T_009f4fb0::m(Rva009F5970StateInit *value)
{
	T_009f4fb0 *self = this;
	((Gen_dtor_009f2600 *)self)->cleanup();

	self->m_values = *value;

	float first = self->m_values.value[3] - self->m_values.value[0];
	float second = self->m_values.value[4] - self->m_values.value[1];
	if (!(first > second))
		first = second;
	self->m_scale = g_bfmeDefaultBU / first;

	BfmeNode912C *node = self->m_head;
	while (node != 0) {
		((BfmeHostEQR *)self)->bfmeLinkEQR((BfmeRecEQR *)node);
		node = node->m_next;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva006276E0@ShroudManager@@QAEXPBURegion3D@@@Z=?m@T_009f4fb0@@QAEXPAURva009F5970StateInit@@@Z")
#pragma comment(linker, "/alternatename:?m@T_009f4fb0@@QAEXXZ=?m@T_009f4fb0@@QAEXPAURva009F5970StateInit@@@Z")
