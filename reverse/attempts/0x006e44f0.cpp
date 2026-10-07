// ?rva006E44F0@Rva006E3FF0Owner@@QAEXPAVAptCIH@@@Z
// partial score=0.95 date=2026-10-07
// cl: /O2 /Ob1 /arch:SSE /MD /DNDEBUG /EHs-c-
// Native6E44F0..6E4604 complete276 RET4. Same pool/timer layout as newly
// recovered cleanup6E3FF0; target independently proves all fields used here.
// References only existing rowed callees. Function/receiver names are neutral.
// Body size is exact; remaining mismatch is register encoding from+0x91.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptValue { public: virtual void AddRef(); virtual void Release(); };
class Rva006E0DE0 {
public:
    unsigned short count;
    unsigned short capacity;
    AptValue** entries;
    int rva006E0DE0(AptValue*);
};
struct AptIntervalTimer {
    void* owner;
    AptValue* value;
    char pad08[12];
    int count;
    int unused;
    AptValue** values;
    void cleanParams();
};
struct AptDisplayList {
    void* value;
    AptIntervalTimer* buckets;
    int count;
    void rva006F8190();
};
struct Rva006E3FF0VectorEntry { AptValue* value; char pad04[24]; };
class Rva006E34D0;
extern Rva006E34D0* g_bfmeAptPtrAtE176D0;
class AptCIH;
struct Rva006E3FF0Owner {
    char pad00[8];
    Rva006E0DE0 set;
    int vectorCount;
    Rva006E3FF0VectorEntry* vector;
    unsigned short valueCount;
    unsigned short valueCapacity;
    AptValue** values;
    unsigned short moreCount;
    unsigned short moreCapacity;
    AptValue** moreValues;
    char pad28[8];
    AptDisplayList display;
    void cleanup();
    void rva006E44F0(AptCIH*);
};
class BfmeAptValue006DCD20 {
public:
    int isCharacterInst() const;
    int isScriptFunction() const;
    BfmeAptValue006DCD20* rva006DCEE0();
};
class AptCIH {
public:
    char prefix[0x4C];
    void* inst;
    void* rva006E1170() const;
    void* rawInst() const { return inst; }
};
struct Rva006E44F0Function { char prefix[0x20]; AptCIH* owner; };
struct Rva006E44F0Instance { char prefix[0x0C]; void* grouping; };
void Rva006E3FF0Owner::rva006E44F0(AptCIH* current)
{
    int remaining=display.count;
    if(remaining==0) return;
    for(int i=0; i<reinterpret_cast<int*>(g_bfmeAptPtrAtE176D0)[0xA8/4]; ++i) {
        int offset=i*0x20;
        AptIntervalTimer* timer=reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset);
        if(timer->owner) {
            if(!static_cast<unsigned char>(reinterpret_cast<BfmeAptValue006DCD20*>(current)->isCharacterInst())) {
                g_bfmeAptAssertAtE17734("isCharacterInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xA5);
                if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm { int 3 } }
            }
            if(current->inst && static_cast<unsigned char>(reinterpret_cast<BfmeAptValue006DCD20*>(reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->value)->isScriptFunction())) {
                if(!reinterpret_cast<Rva006E44F0Function*>(reinterpret_cast<BfmeAptValue006DCD20*>(reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->value)->rva006DCEE0())->owner->rawInst() || reinterpret_cast<Rva006E44F0Instance*>(reinterpret_cast<Rva006E44F0Function*>(reinterpret_cast<BfmeAptValue006DCD20*>(reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->value)->rva006DCEE0())->owner->rva006E1170())->grouping==reinterpret_cast<Rva006E44F0Instance*>(current->rva006E1170())->grouping) {
                    reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->value->Release();
                    reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->cleanParams();
                    reinterpret_cast<AptIntervalTimer*>(reinterpret_cast<char*>(display.buckets)+offset)->owner=0;
                    --display.count;
                }
            }
            --remaining;
            if(remaining==0) break;
        }
    }
}
