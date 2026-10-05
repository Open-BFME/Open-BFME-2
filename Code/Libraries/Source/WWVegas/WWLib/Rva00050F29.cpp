// cl: /O1 /MD /D_CRTIMP= /DNDEBUG
// ?rva00050F29@Rva00050F29@@QAEHHH@Z, retail 0x00050F29, 24 bytes. Leaf __thiscall with ret 8 (2 stack args).
// Calls virtual slot 88 (0x160) on this with same args then returns !result via neg/sbb/inc.
// Evidence: push [esp+8] twice pattern, mov eax,[ecx] vtable load, call [eax+0x160], neg/sbb/inc/ret8. Honest Rva name, owner unknown.
class Rva00050F29
{
public:
    virtual int d0();
    virtual int d1();
    virtual int d2();
    virtual int d3();
    virtual int d4();
    virtual int d5();
    virtual int d6();
    virtual int d7();
    virtual int d8();
    virtual int d9();
    virtual int d10();
    virtual int d11();
    virtual int d12();
    virtual int d13();
    virtual int d14();
    virtual int d15();
    virtual int d16();
    virtual int d17();
    virtual int d18();
    virtual int d19();
    virtual int d20();
    virtual int d21();
    virtual int d22();
    virtual int d23();
    virtual int d24();
    virtual int d25();
    virtual int d26();
    virtual int d27();
    virtual int d28();
    virtual int d29();
    virtual int d30();
    virtual int d31();
    virtual int d32();
    virtual int d33();
    virtual int d34();
    virtual int d35();
    virtual int d36();
    virtual int d37();
    virtual int d38();
    virtual int d39();
    virtual int d40();
    virtual int d41();
    virtual int d42();
    virtual int d43();
    virtual int d44();
    virtual int d45();
    virtual int d46();
    virtual int d47();
    virtual int d48();
    virtual int d49();
    virtual int d50();
    virtual int d51();
    virtual int d52();
    virtual int d53();
    virtual int d54();
    virtual int d55();
    virtual int d56();
    virtual int d57();
    virtual int d58();
    virtual int d59();
    virtual int d60();
    virtual int d61();
    virtual int d62();
    virtual int d63();
    virtual int d64();
    virtual int d65();
    virtual int d66();
    virtual int d67();
    virtual int d68();
    virtual int d69();
    virtual int d70();
    virtual int d71();
    virtual int d72();
    virtual int d73();
    virtual int d74();
    virtual int d75();
    virtual int d76();
    virtual int d77();
    virtual int d78();
    virtual int d79();
    virtual int d80();
    virtual int d81();
    virtual int d82();
    virtual int d83();
    virtual int d84();
    virtual int d85();
    virtual int d86();
    virtual int d87();
    virtual int virt(int a1, int a2);
    int rva00050F29(int a1, int a2);
};
int Rva00050F29::rva00050F29(int a1, int a2)
{
    return !virt(a1, a2);
}
