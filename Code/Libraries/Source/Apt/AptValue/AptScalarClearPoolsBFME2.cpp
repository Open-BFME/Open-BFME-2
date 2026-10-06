// cl: /MD /EHsc
// Source guide: public-material/777b24f0e1dc0929-AptInteger.cpp and
// dfdaf615e1a3b9ce-AptFloat.cpp, ClearPool. Retail independently proves all
// three pool heads, +8 next links, slot11 GC clearing and slot14 deletion.
// Boolean retail is pooled (also established by matched Create6D88C0),
// unlike the later Boolean donor singleton implementation.
// Each extent is 55 bytes through RET, followed by INT3 padding; Ghidra's
// 52-byte entries truncate the loop branch and omit POP/RET. Partial views.
class AptValue {
public:
    virtual void vtableSlot0();
    virtual void vtableSlot1();
    virtual void vtableSlot2();
    virtual void vtableSlot3();
    virtual void vtableSlot4();
    virtual void vtableSlot5();
    virtual void vtableSlot6();
    virtual void vtableSlot7();
    virtual void vtableSlot8();
    virtual void vtableSlot9();
    virtual void vtableSlot10();
    virtual void DestroyGCPointers();
    virtual void vtableSlot12();
    virtual void vtableSlot13();
    virtual ~AptValue();
    unsigned int flags;
};
class AptInteger : public AptValue {
public:
    AptInteger *nextFree;
    static void ClearPool();
};
extern AptInteger *g_00E18020;
void AptInteger::ClearPool()
{
    while (g_00E18020 != 0) {
        AptInteger *next = g_00E18020->nextFree;
        g_00E18020->DestroyGCPointers();
        delete g_00E18020;
        g_00E18020 = next;
    }
}
class AptFloat : public AptValue {
public:
    AptFloat *nextFree;
    static void ClearPool();
};
extern AptFloat *g_00E18024;
void AptFloat::ClearPool()
{
    while (g_00E18024 != 0) {
        AptFloat *next = g_00E18024->nextFree;
        g_00E18024->DestroyGCPointers();
        delete g_00E18024;
        g_00E18024 = next;
    }
}
class AptBoolean : public AptValue {
public:
    AptBoolean *nextFree;
    static void ClearPool();
};
extern AptBoolean *g_00E18028;
void AptBoolean::ClearPool()
{
    while (g_00E18028 != 0) {
        AptBoolean *next = g_00E18028->nextFree;
        g_00E18028->DestroyGCPointers();
        delete g_00E18028;
        g_00E18028 = next;
    }
}
