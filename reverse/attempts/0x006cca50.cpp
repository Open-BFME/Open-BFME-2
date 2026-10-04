// ?rva006CCA50@@YAXHPBD@Z
// partial score=0.72 date=2026-10-04
// cl: /O2 /MD /EHs-c- /DNDEBUG
// ?rva006CCA50@@YAXHH@Z @ 0x006CCA50 (145B).
//
// Address-derived Apt string worker sitting between the rowed
// ?Rva006CC9A0@@YAXHHH@Z (0x006CC9A0) and the unrowed 0x006CC530 it calls.
//
// Retail, in order:
//   AptString::Create()          0x006D7210  -> pAptString
//   pAptString->vtable[0]()      add-input forwarder (the rowed
//                                Rva006E34D0 three-int packer reached
//                                through the AptString's AptValue base)
//   pAptString->SetString(a2)    0x006CBF70  (AptValue::SetString, rowed)
//   local EAStringC(arg2)        0x006D4C80  (EAStringC(char const*))
//   rva006CC530(0,0,&local,1,1,pAptString)  <- the single unknown callee,
//                                `ret 4`, so its last push is the one
//                                `add esp, 4` discards
//   g_aptDateInterpreter.ecx=0x00E182E0; rva006FED00(ret) 0x006FED00
//   pAptString->vtable[1]()      Release / second AptString member
//   local EAStringC dtor         0x006D3010
//
// Frame: the SEH scope-table/-1 tricycle is 12 bytes (push -1, push
// 0x00BA80E8 scope pointer, push fs:[0]) and the EAStringC temporary sits at
// entry ESP-12, NOT -8; the dtor stores 0xFFFFFFFF at that slot from the
// handler-cleanup path (`lea ecx,[esp+4]; mov [esp+0x10],-1`), which pins the
// temporary as 4-byte aligned and 8 bytes wide. So the temporary must be a
// by-value object destroyed inside the __try scope.
//
// Identity of the class and of 0x006CC530/0x006FED00 is NOT proven; they are
// address-derived on the target addresses. The AptString vtable slots are
// reproduced as an opaque member-call pair because the AptValue base offset of
// AptString is not independently established here.

#include <excpt.h>

class EAStringC
{
    void *data;
public:
    EAStringC(const char *text);
    ~EAStringC();
};

class AptValue
{
public:
    void SetString(const char *text);
};

class AptString : public AptValue
{
public:
    static AptString *Create();
    void rva006CCA50V0();
    void rva006CCA50V4();
};

class Rva006E182E0
{
public:
    void rva006FED00(void *arg);
};

// g_aptDateInterpreter: the interpreter global constructed at VA 0x00E182E0
// (matched Rva006D74E0Cluster.cpp references already place the AptBasePtrStack
// sub-object at offset 0). The retail body loads the VA straight into ecx.
extern Rva006E182E0 g_aptDateInterpreter;

void *rva006CC530(int a, int b, EAStringC *str, int c, int d, AptString *apt);

void rva006CCA50(int arg1, const char *arg2)
{
    AptString *p = AptString::Create();
    p->rva006CCA50V0();
    p->SetString(arg2);
    __try
    {
        EAStringC local(arg2);
        void *ret = rva006CC530(0, 0, &local, 1, 1, p);
        g_aptDateInterpreter.rva006FED00(ret);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    p->rva006CCA50V4();
}