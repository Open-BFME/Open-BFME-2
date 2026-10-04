// ??1MoveToFormationGroupOrder@@UAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// Banked destructor-only ABI view. Native identity is MoveToFormationGroupOrder:
// C6A4CC slot12(547BC5) passes cacheDD211C to StaticNameKey::key(148F5E);
// raw cache+4 points toCStringC6A504 "MoveToFormationGroupOrder". Slot2(547B64)
// passes the same key to NameKeyGenerator::keyToName(148C95).
// Target entry547B8A/59B, deleting wrapper547C9A/28B, member+30 dtor5473F7/57B,
// base dtor548948/60B. The base's original name is unknown; SpecialPowerModuleData
// is used only as the existing verified COFF provider name, not owner evidence.
// Native vtable has14slots. This destructor-only view emits a smaller table and
// MUST NOT be landed until that native vtable's complete provider is reconciled.
// Reference lead: Open-BFME-1@1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// game/GameEngine/Source/Common/INI/INIWater.cpp's WaterTransparencySetting dtor.
// That donor name is refuted here: its member/base callees are different.
#pragma comment(linker, "/alternatename:??1Rva00548948@@UAE@XZ=??1SpecialPowerModuleData@@UAE@XZ")
class Rva00548948
{
public:
    virtual ~Rva00548948();
private:
    unsigned char prefix04[0x18-4];
};
class Rva005473F7
{
public:
    ~Rva005473F7();
private:
    unsigned int opaque0;
    void *begin;
    void *finish;
    void *end;
    unsigned int count;
};
class MoveToFormationGroupOrder : public Rva00548948
{
public:
    virtual ~MoveToFormationGroupOrder();
private:
    unsigned char opaque18[0x30-0x18];
    Rva005473F7 member30;
    bool flag44;
};
MoveToFormationGroupOrder::~MoveToFormationGroupOrder()
{
}