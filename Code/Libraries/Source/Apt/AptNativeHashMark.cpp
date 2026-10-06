// cl: /MD
// ?rva0070B220@AptNativeHash@@QAEXPAX@Z @0x0070B220 145B. AptNativeHash GC-mark helper.
// Evidence: layout matches AptNativeHash (mnTotalSize+0 mpData+4 mp__proto__+8 mpPrototype+0xC
// Entry 8B value+4) from Code/Libraries/Source/Apt/AptNativeHashBFME2.cpp; forwarder
// 0x006DCC00 (slot 0x34 of Rva006D6360) does add ecx,8 then calls here; callers 0x006CD330
// (push 0) and 0x006E11B0 (push esi parent) pass one dword that this body ignores (ret 4);
// triple mark pattern (get/setGCMark(true)/virtual 0x34) matches Rva006E39A0 precedent.
class Rva006DBB40ShrAndField {
public:
    bool get() const;
};
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    void setGCMark(bool value);
};
class AptNativeHash {
    int mnTotalSize;
    struct Entry { void *key; AptValue *value; } *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
public:
    void rva0070B220(void *arg);
};
void AptNativeHash::rva0070B220(void *arg)
{
    (void)arg;
    if (mp__proto__) {
        if (!((const Rva006DBB40ShrAndField *)mp__proto__)->get()) {
            mp__proto__->setGCMark(true);
            mp__proto__->unused13();
        }
    }
    if (mpPrototype) {
        if (!((const Rva006DBB40ShrAndField *)mpPrototype)->get()) {
            mpPrototype->setGCMark(true);
            mpPrototype->unused13();
        }
    }
    if (mpData) {
        for (int i = 0; i < mnTotalSize; ++i) {
            if (mpData[i].value) {
                if (!((const Rva006DBB40ShrAndField *)mpData[i].value)->get()) {
                    mpData[i].value->setGCMark(true);
                    mpData[i].value->unused13();
                }
            }
        }
    }
}
