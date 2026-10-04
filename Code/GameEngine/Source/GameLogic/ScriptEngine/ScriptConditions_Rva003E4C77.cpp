// cl: /O1
// ?Rva003E4C77Get@@YAHXZ
// retail 0x003E4C77 22B leaf free cdecl int of 0 params ret from 0x003EC0A7. Evidence:
// TheAudio global plus vslot 0x9c slot 39 taking 0 returning int then logical not
// via neg sbb inc like retail; sibling TheAudio forwarders Rva003BC4D1Do slot 0xb4.
class AudioManager
{
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
    virtual int s39(int);
};
extern AudioManager *TheAudio;

int __cdecl Rva003E4C77Get()
{
    return !TheAudio->s39(0);
}
