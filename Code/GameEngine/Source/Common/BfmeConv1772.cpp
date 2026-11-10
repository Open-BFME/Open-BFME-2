// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" int __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

class BfmeTargetCN
{
public:
	char bfmeStepCN(int flag);
};

class BfmeInnerCN
{
public:
	void bfmeCloseCN(void *value);

	int m_bfmeDataCN;
};

class BfmeScopeCN
{
public:
	BfmeScopeCN(void *owner, BfmeTargetCN *target, void *value);
	~BfmeScopeCN()
	{
		m_bfmeVfCN = __identifier("??_7BfmeParserBindingBaseVE@@6B@");

		m_bfmeInnerCN->bfmeCloseCN(m_bfmeArgCN);
	}

	int *m_bfmeVfCN;
	BfmeInnerCN *m_bfmeInnerCN;
	void *m_bfmeArgCN;
	int m_bfmePadCN;
};

class BfmeOwnCN
{
public:
	char bfmeGuardedCN(BfmeTargetCN *target, void *value);

	unsigned char m_bfmeHeadCN[0xc];
	void *m_bfmeCtxCN;
};

char BfmeOwnCN::bfmeGuardedCN(BfmeTargetCN *target, void *value)
{
	BfmeScopeCN scope(m_bfmeCtxCN, target, value);

	return target->bfmeStepCN(0);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00306D7B reads ?handle@Q1Forwardee0000871A@@QAEXH@Z
//   0x00307AC0 reads ?parse@DataChunkInput@@QAE_NPAX@Z
//   0x0030D849 reads ??0Rva0030D849@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z
#pragma comment(linker, "/alternatename:??0BfmeScopeCN@@QAE@PAXPAVBfmeTargetCN@@0@Z=??0Rva0030D849@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z")
