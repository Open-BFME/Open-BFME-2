// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003C41BA@BfmeApplierBH@@QAEXPAXABVAsciiString@@0@Z @0x003C41BA 80B.
// BfmeApplierBH helper that resolves a SpecialPowerTemplate by name and applies
// it when the TerrainLogic helper is present. Evidence: calls rowed
// findSpecialPowerTemplate 0x0029B6EB via TheSpecialPowerStore and pin-only bfmeApplyBH
// 0x003C069B; TerrainLogic virtual at +0x88; StringBase copy 0x000365F0 for the
// by-value AsciiString; prev/next share // cl: /O1; caller 0x003CC74F.
#include "ascii_string.h"

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void *v34(void *arg);
};

extern TerrainLogic *TheTerrainLogic;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class BfmeSubBH
{
public:
	char m_pad[4];
};

class BfmeApplierBH
{
public:
	void rva003C41BA(void *owner, const AsciiString &name, void *arg3);
	void bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();
};

void BfmeApplierBH::rva003C41BA(void *owner, const AsciiString &name, void *arg3)
{
	void *helper = TheTerrainLogic->v34(arg3);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);
	if (helper != 0 && found != 0)
		bfmeApplyBH(owner, (void *)found, (BfmeSubBH *)((char *)helper + 0xc));
}
