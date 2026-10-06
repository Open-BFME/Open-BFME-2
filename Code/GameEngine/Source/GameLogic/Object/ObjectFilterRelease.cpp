// cl: /DNDEBUG /MD
// ?Rva00360CB0Release@@YAXPAH@Z @0x00360CB0 61B
// Pool release for the 0x94-byte validity-table record shared with
// ?isValid@ObjectFilter@@QBE_NXZ at 0x00360CED. Index at [arg+0] is -1 when
// empty; otherwise bounds-checked against (end-begin)/0x94 via signed idiv
// from the .data globals at 0x00A01E68/0x00A01E6C, then the dword at
// table+index*0x94+0x8C is decremented and the index reset to -1 via or.
// Evidence: 5 callers in the 0x360xxx science cluster including the
// ??1Rva00360D26Member forwarder at 0x00360D26 (40+ callers incl rowed
// TransportContainModuleData dtor); unblocks 0x00362192 for GarrisonContain
// and TunnelContain ModuleData ctors; same globals/size/flags as sibling.
struct ValidityRecord148
{
    char m_pad00[0x8C];
    int m_refCount;
    char m_pad90[0x94 - 0x90];
};

extern unsigned char *g_validityBegin;
// g_validityBegin: matched references place it at VA 0xe01e68 (zero-filled .bss).
unsigned char * g_validityBegin;
extern unsigned char *g_validityEnd;
// g_validityEnd: matched references place it at VA 0xe01e6c (zero-filled .bss).
unsigned char * g_validityEnd;

void Rva00360CB0Release(int *indexHolder)
{
    int index = *indexHolder;
    if (index == -1)
        return;
    int count = (g_validityEnd - g_validityBegin) / (int)sizeof(ValidityRecord148);
    if ((unsigned int)index > (unsigned int)count)
        return;
    ValidityRecord148 *table = (ValidityRecord148 *)g_validityBegin;
    table[index].m_refCount--;
    *indexHolder = -1;
}

// ??1Rva00360D26Member@@QAE@XZ @0x00360D26 8B
// Pool-aware member dtor forwarding this to the release above. Identity is
// triple-proven: the pin at 0x00360D26, 40+ callers including the rowed
// TransportContainModuleData dtor (two calls for +0x08/+0x0C), and the
// FamilyDeletingDtors2 ??_G at 0x00421728 calling here. Same TU and flags
// as the release (/O1 for pop-ecx cleanup).
class Rva00360D26Member
{
public:
    ~Rva00360D26Member();

private:
    unsigned m_unknown;
};

Rva00360D26Member::~Rva00360D26Member()
{
    Rva00360CB0Release((int *)this);
}

// Units that construct the record through its 0x003623E5 ctor name the class
// after it, as Rva003623E5Member (31 units) or Rva003623E5Filter (21 units);
// their teardown calls bind to this body.
#pragma comment(linker, "/alternatename:??1Rva003623E5Member@@QAE@XZ=??1Rva00360D26Member@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003623E5Filter@@QAE@XZ=??1Rva00360D26Member@@QAE@XZ")
