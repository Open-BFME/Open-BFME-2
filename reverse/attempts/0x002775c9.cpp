// ?rva002775C9@Drawable@@QAEXPAUCoord3D@@@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 0x002775C9..0x00277669, RET4; Ghidra inventory agrees with
// the frame prologue, return and following function start. Drawable identity
// follows this+4 template/this+FC object accesses and the adjacent Drawable
// members. Original method and virtual interface names are unknown.
#include "Coord3D.h"

class Rva002775C9Interface
{
public:
    virtual void unknownSlot0();
    virtual void unknownSlot1();
    virtual void unknownSlot2();
    virtual void unknownSlot3();
    virtual void unknownSlot4();
    virtual void unknownSlot5();
    virtual void unknownSlot6();
    virtual void unknownSlot7();
    virtual void unknownSlot8();
    virtual void unknownSlot9();
    virtual void unknownSlot10();
    virtual void unknownSlot11();
    virtual void unknownSlot12();
    virtual void unknownSlot13();
    virtual void unknownSlot14();
    virtual void unknownSlot15();
    virtual void unknownSlot16();
    virtual void unknownSlot17();
    virtual void unknownSlot18();
    virtual void unknownSlot19();
    virtual void unknownSlot20();
    virtual void unknownSlot21();
    virtual void unknownSlot22();
    virtual void unknownSlot23();
    virtual void unknownSlot24();
    virtual void unknownSlot25();
    virtual void unknownSlot26();
    virtual void unknownSlot27();
    virtual void unknownSlot28();
    virtual void unknownSlot29();
    virtual void unknownSlot30();
    virtual void unknownSlot31();
    virtual void unknownSlot32();
    virtual void unknownSlot33();
    virtual void unknownSlot34();
    virtual void unknownSlot35();
    virtual void unknownSlot36();
    virtual void unknownSlot37();
    virtual void unknownSlot38();
    virtual void unknownSlot39();
    virtual void unknownSlot40();
    virtual void unknownSlot41();
    virtual void unknownSlot42();
    virtual void unknownSlot43();
    virtual void unknownSlot44();
    virtual void unknownSlot45();
    virtual void unknownSlot46();
    virtual void unknownSlot47();
    virtual void unknownSlot48();
    virtual void unknownSlot49();
    virtual void unknownSlot50();
    virtual void unknownSlot51();
    virtual void unknownSlot52();
    virtual void unknownSlot53();
    virtual void unknownSlot54();
    virtual void unknownSlot55();
    virtual void unknownSlot56();
    virtual void unknownSlot57();
    virtual void unknownSlot58();
    virtual void unknownSlot59();
    virtual void unknownSlot60();
    virtual void unknownSlot61();
    virtual void unknownSlot62();
    virtual void unknownSlot63();
    virtual void unknownSlot64();
    virtual void unknownSlot65();
    virtual void unknownSlot66();
    virtual void unknownSlot67();
    virtual void unknownSlot68();
    virtual void unknownSlot69();
    virtual void unknownSlot70();
    virtual void unknownSlot71();
    virtual void unknownSlot72();
    virtual void unknownSlot73();
    virtual void unknownSlot74();
    virtual void unknownSlot75();
    virtual void unknownSlot76();
    virtual void unknownSlot77();
    virtual void unknownSlot78();
    virtual void unknownSlot79();
    virtual void unknownSlot80();
    virtual void unknownSlot81();
    virtual void unknownSlot82();
    virtual void unknownSlot83();
    virtual void unknownSlot84();
    virtual void unknownSlot85();
    virtual void unknownSlot86();
    virtual void unknownSlot87();
    virtual void unknownSlot88();
    virtual void unknownSlot89();
    virtual void unknownSlot90();
    virtual void unknownSlot91();
    virtual void unknownSlot92();
    virtual void unknownSlot93();
    virtual void unknownSlot94();
    virtual void unknownSlot95();
    virtual void unknownSlot96();
    virtual void unknownSlot97();
    virtual void unknownSlot98();
    virtual void unknownSlot99();
    virtual void unknownSlot100();
    virtual void unknownSlot101();
    virtual void unknownSlot102();
    virtual void unknownSlot103();
    virtual void unknownSlot104();
    virtual void unknownSlot105();
    virtual void unknownSlot106();
    virtual void unknownSlot107();
    virtual void unknownSlot108();
    virtual void unknownSlot109();
    virtual void unknownSlot110();
    virtual void unknownSlot111();
    virtual void unknownSlot112();
    virtual void unknownSlot113();
    virtual void unknownSlot114();
    virtual void unknownSlot115();
    virtual void unknownSlot116();
    virtual void unknownSlot117();
    virtual void unknownSlot118();
    virtual void unknownSlot119();
    virtual void unknownSlot120();
    virtual void unknownSlot121();
    virtual void unknownSlot122();
    virtual void unknownSlot123();
    virtual void unknownSlot124();
    virtual void unknownSlot125();
    virtual void unknownSlot126();
    virtual void unknownSlot127();
    virtual void unknownSlot128();
    virtual void unknownSlot129();
    virtual void unknownSlot130();
    virtual void unknownSlot131();
    virtual void unknownSlot132();
    virtual void unknownSlot133();
    virtual void unknownSlot134();
    virtual void unknownSlot135();
    virtual void unknownSlot136();
    virtual void unknownSlot137();
    virtual void unknownSlot138();
    virtual bool position(Coord3D *);
};
class Rva002775C9Module
{
public:
    virtual void unknownSlot0();
    virtual void unknownSlot1();
    virtual void unknownSlot2();
    virtual void unknownSlot3();
    virtual void unknownSlot4();
    virtual void unknownSlot5();
    virtual void unknownSlot6();
    virtual void unknownSlot7();
    virtual void unknownSlot8();
    virtual void unknownSlot9();
    virtual void unknownSlot10();
    virtual void unknownSlot11();
    virtual void unknownSlot12();
    virtual void unknownSlot13();
    virtual void unknownSlot14();
    virtual void unknownSlot15();
    virtual void unknownSlot16();
    virtual void unknownSlot17();
    virtual void unknownSlot18();
    virtual void unknownSlot19();
    virtual void unknownSlot20();
    virtual void unknownSlot21();
    virtual void unknownSlot22();
    virtual void unknownSlot23();
    virtual void unknownSlot24();
    virtual void unknownSlot25();
    virtual void unknownSlot26();
    virtual void unknownSlot27();
    virtual void unknownSlot28();
    virtual void unknownSlot29();
    virtual void unknownSlot30();
    virtual Rva002775C9Interface *interfaceAt7C();
};
class GeometryInfo
{
public:
    float rva006BD830() const;
private:
    char unknown[0x34];
};
struct Rva002775C9Object
{
    char unknown00[0xA8];
    GeometryInfo geometry;
    char unknownDC[0x250 - 0xDC];
    Rva002775C9Module *module;
};
struct Rva002775C9Template
{
    char unknown00[0x115];
    unsigned char flags115;
    char unknown116[0x538 - 0x116];
    float height538;
};
class Drawable
{
public:
    void rva002775C9(Coord3D *out);
    const Coord3D *rva00276470();
private:
    char unknown00[4];
    Rva002775C9Template *type;
    char unknown08[0xFC - 8];
    Rva002775C9Object *object;
};

void Drawable::rva002775C9(Coord3D *out)
{
    Rva002775C9Object *obj = object;
    if ((type->flags115 & 0x20) != 0 && obj != 0)
    {
        Rva002775C9Module *module = obj->module;
        if (module != 0 && module->interfaceAt7C() != 0)
        {
            Rva002775C9Interface *interface = obj->module->interfaceAt7C();
            if (interface->position(out))
                return;
        }
    }
    *out = *rva00276470();
    float height = 10.0f;
    if (type != 0)
        height = type->height538;
    height += out->z;
    out->z = height;
    if (obj != 0)
        out->z += obj->geometry.rva006BD830();
}
