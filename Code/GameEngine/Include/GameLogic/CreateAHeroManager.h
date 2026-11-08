// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x0021FE49 calls SubsystemInterface's 0x001B4E63 at 0x0021FE5C and installs 0x00BE648C at 0x0021FE7A; destructor 0x0021FFEE restores the same table at 0x00220000 and calls the parent destructor 0x001B4E74 at 0x002200F2. The parent's 0x00BD77A0 is its construction/destruction table. GameEngine::init allocates 0x1F4 at 0x0022FBED, calls this constructor at 0x0022FC05 and registers TheCreateAHeroManager (VA 0x00DFE344) at 0x0022FC2F. The base occupies +0..+0xC; its constructor clears byte +4 and string pointer +8. The global's data-ledger symbol spells PAVCreateAHeroManager (class).
// Table 0x00BE648C has fourteen entries, followed by non-code: slot 0=0x002201B9 calls the out-of-line destructor; 1=0x0021A3B7 (init); 2=0x0050B5C6 (true); 3/8/9/10/12=0x000B3FD0 (ret); 4/11=0x005CB9FF (false, ret 4); 5=0x0047A699 (false); 6=0x000D43D0 (zero); 7/13=0x0047A69C (ret 4). Slots 0, 1, 2, 9 and 10 override the parent's destructor, init, loadIniFilesFromLegend, reset and update slots; the remaining slots are inherited. Only the parent's fourteen-slot shape is observed.
// Constructor member receivers are +0xC (0x00409C3D at 0x0021FE80), +0x14C/+0x15C/+0x168 (0x00211E58 at 0x0021FE8F/0x0021FEA4/0x0021FEB3) and +0x174 (0x0040A530 at 0x0021FEC3); destruction calls 0x00409285/0x0021FDEC/0x0021DA18/0x0021DA57/0x0040A603 at 0x002200E7/0x002200DB/0x002200CC/0x002200BD/0x002200AE. Storage stays opaque where the complete member type is not established here. Constructor 0x0021FEC8..0x0021FF90 proves flags +0x184/+0x1D8, dwords +0x158/+0x194..+0x1BC/+0x1D0/+0x1D4/+0x1E0/+0x1E4/+0x1F0, float +0x1C0 and strings +0x188/+0x18C/+0x190/+0x1C4/+0x1C8/+0x1CC/+0x1DC/+0x1E8/+0x1EC (destroyed at 0x00220021..0x002200A3). Nonvirtual method names and signatures below are the matched CreateAHeroManager rows in reverse/functions.csv; lifetime and accessor bodies remain out of line. AptMyHero reads +0x1D4 at 0x005B16C0 after loading TheCreateAHeroManager at 0x005B16BB, and CreateAHeroData 0x004074CF sets byte +0x1D8 at 0x00407510 after loading it at 0x0040750B; these neutral fields are exposed for those accesses. Declared method row RVAs: BindHeroToObjectAndUpdate (0x0021B474); FindBlingByUpgradeName (0x0021D4CE); GetAvailableHeroesForFaction (0x0021D548); GetAwardCount (0x00219ED5); GetAwardNameKey (0x00219F00); GetBling (0x00219D85); GetBlingBinder (0x0021A106); GetBlingCount (0x00219239); GetBlingDescTag (0x00219DEA, 0x0021CA96); GetBlingNameTag (0x00219DAA, 0x0021CA0D); GetBlingUpgradeName (0x00219E2F); GetButtonImageName (0x0021B22E, 0x0021B670); GetClassDescTag (0x0021AFEA); GetClassImageName (0x0021B0CA); GetClassNameTag (0x0021AF7E); GetClassPowersTag (0x0021B05A); GetClassUpgradeName (0x0021A134); GetDefaultHero (0x0021A6C8); GetFactionMaskType (0x00219F8E); GetHeroForPlayer (0x0021B5D6); GetPreferedFaction (0x00219FE3); GetRequiredButton (0x0021933E); GetRequiredButtonCount (0x00219309); GetStatCount (0x00219E74); GetStatNameKey (0x00219E9F); GetSubClassAttributeDefaultValue (0x0021BFA6); GetSubClassAttributeMaxValue (0x0021BF74); GetSubClassAttributeMinValue (0x0021BF42); GetSubClassDefaultBlingId (0x0021BF11); GetSubClassDescTag (0x0021B2A2); GetSubClassImageName (0x0021B1B4); GetSubClassNameTag (0x0021B13A); GetSubClassSpendableAttributePoints (0x0021A097); GetSubClassUpgradeName (0x0021A15D); GetViewInfo (0x00219F36); LoadMyHeroList (0x0021F47E); OnDie (0x0021A5AE); UnbindHeroFromObjectAndUpdate (0x00219757); iniParseCreateAHeroSystem (0x0022044C); init (0x0021A3B7); parseCreateAHeroClassDefinition (0x002202BF); parseCreateAHeroSubClass (0x0021FB0C); parseHeroBlingUpgrades (0x0021EE37); rva002192C0 (0x002192C0); rva002196DA (0x002196DA); rva002196EC (0x002196EC); rva002197A6 (0x002197A6); rva00219D52 (0x00219D52); rva0021A016 (0x0021A016); rva0021A041 (0x0021A041); rva0021A06C (0x0021A06C); rva0021A18B (0x0021A18B); rva0021A1B6 (0x0021A1B6); rva0021A428 (0x0021A428); rva0021A4E6 (0x0021A4E6); rva0021B31C (0x0021B31C); rva0021BEE0 (0x0021BEE0); rva0021CB1F (0x0021CB1F); rva0021F5F8 (0x0021F5F8); rva0021F797 (0x0021F797); rva0022020C (0x0022020C).
#ifndef BFME2_CREATEAHEROMANAGER_H
#define BFME2_CREATEAHEROMANAGER_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include CreateAHeroManager.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}
class CommandButton;
class CreateAHeroData;
class CreateAHeroHero;
class DamageInfo;
class INI;
class Object;
class Player;
class Rva002195E6;
class Rva0040A3F9;

class CreateAHeroManager : public SubsystemInterface {
public:
    class CreateAHeroClass;
    class CreateAHeroSubClass;

    CreateAHeroManager();
    virtual ~CreateAHeroManager();
    virtual void init();
    virtual bool loadIniFilesFromLegend() { return true; }
    virtual void reset() {}
    virtual void update() {}

    int GetRequiredButtonCount();
    const CommandButton *GetRequiredButton(unsigned int);
    void BindHeroToObjectAndUpdate(Object *);
    void UnbindHeroFromObjectAndUpdate(Object *);
    void OnDie(Object *, const DamageInfo *);
    const CreateAHeroHero *GetHeroForPlayer(const Player *);
    CreateAHeroData *GetDefaultHero(int);
    bool GetAvailableHeroesForFaction(_STL::vector<unsigned int, _STL::allocator<unsigned int> > *, int);
    int GetBlingCount(int, const CreateAHeroHero *) const;
    int GetSubClassDefaultBlingId(int, unsigned int, unsigned int) const;
    bool FindBlingByUpgradeName(const AsciiString &, int *, int *);
    void *GetBling(unsigned int);
    void *GetBlingBinder(unsigned int);
    const AsciiString &GetBlingNameTag(int, const CreateAHeroHero *, unsigned int);
    const AsciiString &GetBlingDescTag(int, const CreateAHeroHero *, unsigned int);
    const AsciiString &GetBlingUpgradeName(int, const CreateAHeroHero *, unsigned int);
    const AsciiString &GetBlingNameTag(int, unsigned int, unsigned int, unsigned int);
    const AsciiString &GetBlingDescTag(int, unsigned int, unsigned int, unsigned int);
    const AsciiString &GetClassNameTag(unsigned int);
    const AsciiString &GetClassDescTag(unsigned int);
    const AsciiString &GetClassPowersTag(unsigned int);
    const AsciiString &GetClassImageName(unsigned int);
    const AsciiString &GetClassUpgradeName(unsigned int);
    const AsciiString &GetSubClassNameTag(unsigned int, unsigned int);
    const AsciiString &GetSubClassDescTag(unsigned int, unsigned int);
    const AsciiString &GetSubClassImageName(unsigned int, unsigned int);
    const AsciiString &GetSubClassUpgradeName(unsigned int, unsigned int);
    const AsciiString &GetButtonImageName(unsigned int, unsigned int);
    const AsciiString &GetButtonImageName(const CreateAHeroHero *);
    int GetSubClassSpendableAttributePoints(unsigned int, unsigned int);
    int GetStatCount(unsigned int, unsigned int);
    int GetAwardCount(unsigned int, unsigned int);
    int GetAwardNameKey(unsigned int, unsigned int, unsigned int);
    int GetStatNameKey(unsigned int, unsigned int, unsigned int);
    void *GetFactionMaskType(unsigned int, unsigned int);
    int GetPreferedFaction(unsigned int, unsigned int);
    int GetSubClassAttributeMinValue(unsigned int, unsigned int, unsigned int);
    int GetSubClassAttributeMaxValue(unsigned int, unsigned int, unsigned int);
    int GetSubClassAttributeDefaultValue(unsigned int, unsigned int, unsigned int);
    const Rva002195E6 *GetViewInfo(unsigned int, unsigned int);
    void LoadMyHeroList();
    Rva0040A3F9 *rva0021F797();
    CreateAHeroData *rva002197A6(int);
    int rva002192C0();
    int rva002196DA();
    int rva002196EC();
    int rva00219D52(unsigned int);
    int rva0021A016(unsigned int, unsigned int);
    int rva0021A041(unsigned int, unsigned int);
    int rva0021A06C(unsigned int, unsigned int);
    int rva0021A18B(unsigned int, unsigned int);
    const CreateAHeroSubClass *rva0021A1B6(unsigned int, unsigned int);
    void rva0021A428(const CreateAHeroData &);
    void rva0021A4E6();
    CreateAHeroClass *rva0021B31C(const AsciiString &);
    int rva0021BEE0(int, unsigned int, unsigned int) const;
    void rva0021CB1F();
    void rva0021F5F8();
    CreateAHeroClass *rva0022020C(CreateAHeroClass &);
    static void iniParseCreateAHeroSystem(INI *);
    static void parseCreateAHeroClassDefinition(INI *);
    static void parseCreateAHeroSubClass(INI *, void *, void *, const void *);
    static void parseHeroBlingUpgrades(INI *, void *, void *, const void *);

private:
    unsigned char field00C[0x140];
    unsigned int field14C[3];
    unsigned int field158;
    unsigned int field15C[3];
    unsigned int field168[3];
    unsigned int field174[4];
    bool field184;
    AsciiString field188;
    AsciiString field18C;
    AsciiString field190;
    unsigned int field194;
    unsigned int field198;
    unsigned int field19C;
    unsigned int field1A0;
    unsigned int field1A4;
    unsigned int field1A8;
    unsigned int field1AC;
    unsigned int field1B0;
    unsigned int field1B4;
    unsigned int field1B8;
    unsigned int field1BC;
    float field1C0;
    AsciiString field1C4;
    AsciiString field1C8;
    AsciiString field1CC;
    unsigned int field1D0;
public:
    unsigned int field1D4;
    bool field1D8;
private:
    AsciiString field1DC;
    unsigned int field1E0;
    unsigned int field1E4;
    AsciiString field1E8;
    AsciiString field1EC;
    unsigned int field1F0;
};

extern CreateAHeroManager *TheCreateAHeroManager;

#endif
