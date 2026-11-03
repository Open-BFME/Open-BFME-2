// Target facts (code addresses are RVAs; tables are VAs): AssetRegistry has no virtual functions, vtable or evidenced parent. Its shared receiver is stored at 0x00E09C0C by constructor 0x00624DB0 (ledger name AssetManagerImpl) at 0x00625007; lookup wrapper 0x0061F0D0 loads that receiver at 0x0061F0D8. Allocation 0x0061EF04 requests 0x200 bytes and calls that constructor at 0x0061EF2E. Constructor 0x00625018 stores the thread handle at +0; destructor 0x00625116 reads it for WaitForSingleObject. Neither lifetime body installs a registry table. Table 0x00C7C5C0 at 0x0061EF11 belongs to the enclosing Rva0061EEE0 object; table 0x00C7C610 at 0x00624FD2 belongs to a separate 0x2BF44-byte allocation stored at +0x1F8 by 0x00624FEE. That helper's slot 0 is 0x00621040; destructor 0x006251DC..0x006251E9 dispatches through the helper, not the registry.
// Constructor 0x00624DCE..0x00624E2B builds 0x14-byte hash storage at +0x0C/+0x4C and initializes +0x20/+0x24, +0x28/+0x2C and +0x30. Update 0x00624130 uses the +0x20/+0x24 pair as a 64-bit counter. Worker 0x00622480 stores the thread ID at +4, tests byte +8 and byte +0x1F4, and locks +0x68. Constructor 0x00624E30..0x00624E4A constructs seven 0x28-byte queues at +0x80; 0x00624E57..0x00624F6F builds four 0x14-byte groups at +0x198/+0x1AC/+0x1C0/+0x1D4; 0x00624F82..0x00624F9C initializes dwords +0x1E8/+0x1EC and bytes +0x1F4/+0x1F5/+0x1F6. Lock initialization at 0x00624FF4..0x00624FFE proves +0x34/+0x68. Iterator stores 0x00624FB4/0x00624FB7 prove +0x60/+0x64; enumeration 0x006214D0 tests the dword filter at +0x1F0. Container and lock storage remains opaque because their application types are not established.
// Out-of-line ledger methods are Render_Obj_Exists_Impl 0x00621170, Find_Asset 0x00621220, rva006213B0 0x006213B0, Get_Current_Asset 0x006214D0, Worker_Thread_00622480 0x00622480 and Queue_Keys_00622680 0x00622680. The first two call NameKeyGenerator::nameToLowercaseKey (0x00620500) through +0x1F8; this proves the existing call spelling, not the helper's identity as canonical NameKeyGenerator. Field names are neutral. No AssetRegistry constructor, destructor, copy or assignment row is established; the differently named lifetime rows remain their existing owners.

#ifndef BFME2_ASSETREGISTRY_H
#define BFME2_ASSETREGISTRY_H

class AssetReference;
class NameKeyGenerator;
struct Rva001408C0Target;

namespace _STL {
template <class T> struct less;
template <class T> class allocator;
template <class Key, class Compare, class Allocator> class set;
}

class AssetRegistry
{
public:
    bool Render_Obj_Exists_Impl(const char *name);
    AssetReference Find_Asset(const char *name);
    const char *rva006213B0(unsigned int key);
    AssetReference Get_Current_Asset();
    void Worker_Thread_00622480();
    void Queue_Keys_00622680(bool front, const _STL::set<Rva001408C0Target *,
        _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > &keys);

    unsigned int field00;
    unsigned int field04;
    bool field08;
    unsigned int field0C[5];
    __int64 field20;
    unsigned int field28[2];
    unsigned int field30;
    unsigned int field34[6];
    unsigned int field4C[5];
    void *field60[2];
    unsigned int field68[6];
    unsigned int field80[7][10];
    unsigned int field198[4][5];
    unsigned int field1E8;
    unsigned int field1EC;
    int field1F0;
    bool field1F4;
    bool field1F5;
    bool field1F6;
    NameKeyGenerator *field1F8;
};

typedef char AssetRegistrySizeCheck[sizeof(AssetRegistry) == 0x200 ? 1 : -1];

#endif
