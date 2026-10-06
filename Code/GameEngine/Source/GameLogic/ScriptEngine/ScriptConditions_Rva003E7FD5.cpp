// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
// ?Rva003E7FD5Get@@YG_NPAVParameter@@@Z retail 0x003E7FD5 104 bytes.
// Evidence: leaf lane free function ret 4 with 1 Parameter arg; caller 0x003EBDD7; prev/next same cl; calls getQualifiedTriggerAreaByName pin plus TacticalView slot 0x118 plus pointInTrigger row.
#include "ascii_string.h"

class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class ICoord3D
{
public:
    int x;
    int y;
    int z;
};
class ScriptEngine
{
public:
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern class ScriptEngine *TheScriptEngine;
class TacticalView
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
    virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
    virtual void getPos(float *out);
};
extern TacticalView *TheTacticalView;
class PolygonTrigger
{
public:
    bool pointInTrigger(const ICoord3D &point);
};

bool __stdcall Rva003E7FD5Get(Parameter *p)
{
    PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(p->getString());
    if (trig)
    {
        float f[3];
        TheTacticalView->getPos(f);
        ICoord3D pt;
        pt.x = (int)f[0];
        pt.y = (int)f[1];
        pt.z = (int)f[2];
        return trig->pointInTrigger(pt);
    }
    return false;
}
