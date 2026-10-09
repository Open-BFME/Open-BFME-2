// ?rva000B83A7@Rva000B8F5A@@QAEHXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
template<> bool StringBase<char>::isEmpty() const;
class ProbeHandleB83A7 {
public:
    virtual void Delete_This();
    virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual int probe();
    int refs;
    void Release_Ref() { if(--refs==0) Delete_This(); }
};
class ProbeProviderB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual ProbeHandleB83A7 *find(const char *, bool);
};
class ProbeOuterB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual ProbeProviderB83A7 *get();
};
struct ProbeStateB83A7 {
    char unknown[0x10C];
    AsciiString name10C,name110;
};
class Rva000B8F5A {
public:
    int rva000B82F9();
    int rva000B83A7();
private:
    char unknown[0x254];
    AsciiString name254;
};
int Rva000B8F5A::rva000B83A7()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        name=(*reinterpret_cast<ProbeStateB83A7 **>((char *)this-8))->name110;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}
int Rva000B8F5A::rva000B82F9()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        if(!reinterpret_cast<const StringBase<char> *>(&name254)->isEmpty()) name=name254;
        else name=(*reinterpret_cast<ProbeStateB83A7 **>((char *)this-8))->name10C;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}
