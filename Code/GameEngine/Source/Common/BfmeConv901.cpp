// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ??0BfmeThingJC@@QAE@PAX@Z
// retail 0x002DB882, 33 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv901.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// The base-initialiser call lands on retail 0x001320D0, rowed as BfmeThingSJ's
// constructor. The constructor stores retail's table itself, last as retail does;
// the base layout at +0x30 and +0x38 is the donor's.
extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_GRva002DB8BA@@UAEPAXI@Z")();
void __identifier("?Delete@AssetFactoryBase@@UAEXXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?PreLoad@MapPreviewTextureAssetFactory@@UAEXXZ")();
void __identifier("?Rva000EF29AGet@@YAHXZ")();
void __identifier("?UnloadNow@BfmeE1024@@QAEXXZ")();
void __identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ")();
void __identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ")();
void __identifier("?invoke@Rva0044F320VirtualChain@@QAEXXZ")();
void __identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ")();
void __identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ")();
void __identifier("?rva00131CEA@Rva00131CEAForwarder@@QAEXH@Z")();
void __identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ")();
void __identifier("?rva00133380@Rva00131BE5@@QAEXXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
}

// Retail table at VA 0x00C03E48, each slot the ledger row at the native address.
extern "C" const void *const g_bfmeThingJCTable[18] = {
	(const void *)&__identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ"), // slot 0, RVA 0x00131C40
	(const void *)&__identifier("?PreLoad@MapPreviewTextureAssetFactory@@UAEXXZ"), // slot 1, RVA 0x002DB8BF
	(const void *)&__identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ"), // slot 2, RVA 0x00131CD3
	(const void *)&__identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ"), // slot 3, RVA 0x00132129
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 4, RVA 0x0047A69C
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 5, RVA 0x000B3FD0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 6, RVA 0x000B3FD0
	(const void *)&__identifier("?rva00133380@Rva00131BE5@@QAEXXZ"), // slot 7, RVA 0x00133380
	(const void *)&__identifier("?Delete@AssetFactoryBase@@UAEXXZ"), // slot 8, RVA 0x0061EDA0
	(const void *)&__identifier("??_GRva002DB8BA@@UAEPAXI@Z"), // slot 9, RVA 0x000EF981
	(const void *)&__identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ"), // slot 10, RVA 0x00131CF2
	(const void *)&__identifier("?invoke@Rva0044F320VirtualChain@@QAEXXZ"), // slot 11, RVA 0x002DB8A3
	(const void *)&__identifier("?UnloadNow@BfmeE1024@@QAEXXZ"), // slot 12, RVA 0x0061EE50
	(const void *)&__identifier("?Rva000EF29AGet@@YAHXZ"), // slot 13, RVA 0x000EF29A
	(const void *)&__identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ"), // slot 14, RVA 0x00131CDB
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 15, RVA 0x005CB9FF
	(const void *)&__identifier("?rva00131CEA@Rva00131CEAForwarder@@QAEXH@Z"), // slot 16, RVA 0x00131CEA
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 17, RVA 0x0047A699
};

class BfmeThingSJ
{
public:
	BfmeThingSJ(int a);
	char m_bfmePad[0x30];
	int m_bfme30;
	char m_bfmePad2[4];
	int m_bfme38;
};

class BfmeThingJC : public BfmeThingSJ
{
public:
	BfmeThingJC(void *a);
};

BfmeThingJC::BfmeThingJC(void *a) : BfmeThingSJ((int)a)
{
	m_bfme30 = 1;
	m_bfme38 = 1;
	*(const void *const **)this = g_bfmeThingJCTable;
}