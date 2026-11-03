// Target facts (code addresses are RVAs): InGameHeroSelectInterface is the enclosing scope of the rowed Impl methods; it has no rowed constructor, destructor or virtual function. The implementation allocation at 0x00527773 is 0x1E0 bytes and calls 0x00527378 at 0x0052779B. That constructor stores VA 0x00C67F0C at +0 (0x005273A3), owner +4 (0x00527393), level +8 (0x005273A9), copies AsciiString at +0x0C (0x005273AC), stores data +0x10 (0x005273BD), and constructs members at +0x14/+0x20/+0x38 (0x005273C0/CC/D8). It constructs sixteen 0x18-byte records at +0x48 (0x005273DD..0x005273F4), clears flags +0x44/+0x45 and +0x1D8/+0x1D9/+0x1DA, and clears the final dword +0x1DC at 0x0052741B.
// The same implementation's destructor 0x0052634F first stores VA 0x00C67F0C and restores its base table VA 0x00C67E3C at 0x00526410; 0x00524F5A restores that base table alone. Both tables have five slots: base RVAs [0x0047A69C,0x0047A69C,0x000B3FD0,0x0047A69C,0x0047A69C], implementation RVAs [0x0047A69C,0x0047A69C,0x0052586B,0x00525886,0x0047A69C]. Their RET 4/RET bodies prove argument widths, not semantic names; the destructor is nonvirtual. The destructor destroys members +0x38/+0x20/+0x14/+0x0C through 0x005242D7/0x00524436/0x0052413E/0x00036410, and reads eight-byte hotkey records +0x1C8/+0x1D0 guarded by bytes +0x1D8/+0x1D9. Rva0052634F_Base::v00 is rowed at 0x0047A69C. No registered class or header identifies either table as another canonical object.
// Impl method ledger RVAs: IsBuilderOnScreen 0x00525040, OnHeroAttacked 0x0052557E, rva005255E2 0x005255E2, ShowSelectAllHeroesBttn 0x00525633, FlashHeroButton 0x00525E07, SelectAllHeroes 0x00525E55, FindReadyLocalBuilder 0x00526008, rva0052633A 0x0052633A, BuildLocalBuilderList 0x00526421, Update 0x005264F5, rva00526E8B 0x00526E8B, SelectNearestBuilder 0x00526F85, OnButtonPressed 0x00527122. 0x00525581/AB/CA prove the +0x10/+0x0C/+8 fields; 0x0052558C..A7 and 0x0052586E..82 prove the record array and its byte +0x16. Only evidenced method names are retained; unknown storage and slots use offset names. The lifetime bodies remain out of line.
#ifndef BFME2_INGAMEHEROSELECTINTERFACE_H
#define BFME2_INGAMEHEROSELECTINTERFACE_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../Common/Rva0052413E.h"

class Object;
class Rva00525119;
struct BuilderSelectionData;
struct HeroSelectData;
namespace _STL
{
    template <class T> class allocator;
    template <class T, class Allocator> class list;
}

class Rva0052634F_Base
{
public:
    ~Rva0052634F_Base();
    virtual void v00(void *);
    virtual void vslot01(int);
    virtual void vslot02();
    virtual void vslot03(int);
    virtual void vslot04(int);
};

class InGameHeroSelectInterface
{
public:
    class Impl;
};

class InGameHeroSelectInterface::Impl : public Rva0052634F_Base
{
public:
    Impl(void *owner, int level, const AsciiString &name, void *data, void *faction);
    ~Impl();

    virtual void vslot02();
    virtual void vslot03(int);

    bool IsBuilderOnScreen(const Object *builder);
    void OnHeroAttacked(void *hero);
    void rva005255E2(const AsciiString *faction);
    void ShowSelectAllHeroesBttn();
    void FlashHeroButton(const AsciiString &name, int frames);
    void SelectAllHeroes();
    BuilderSelectionData *FindReadyLocalBuilder(_STL::list<Rva00525119, _STL::allocator<Rva00525119> > *list);
    void rva0052633A(const char *argument);
    void BuildLocalBuilderList(_STL::list<Rva00525119, _STL::allocator<Rva00525119> > *list, int mode);
    void Update();
    void rva00526E8B(_STL::list<Rva00525119, _STL::allocator<Rva00525119> > *list);
    void SelectNearestBuilder(bool noCamera);
    void OnButtonPressed(const char *argument);

    struct SlotStorage
    {
        void *field00;
        void *field04;
        int field08;
        int field0C;
        int field10;
        bool field14;
        bool field15;
        bool field16;
    };

    struct HotKeyStorage
    {
        void *field00;
        bool field04;
    };

    void *field04;
    int field08;
    AsciiString field0C;
    HeroSelectData *field10;
    Rva0052413E field14;
    unsigned int field20[6];
    unsigned int field38[3];
    bool field44;
    bool field45;
    SlotStorage field48[16];
    HotKeyStorage field1C8;
    HotKeyStorage field1D0;
    bool field1D8;
    bool field1D9;
    bool field1DA;
    unsigned int field1DC;
};

#endif
