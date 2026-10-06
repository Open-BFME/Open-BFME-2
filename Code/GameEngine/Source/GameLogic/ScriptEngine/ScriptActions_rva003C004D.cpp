// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x003C004D, 68 bytes.
// ?rva003C004D@ScriptActions@@IAEXABVAsciiString@@M@Z
// Honest address name: ScriptActions area method dispatched from FUN_007ca4be
// (caller at 0x003CE453). Sibling of rva003C0091 (same audio null guard,
// same trigger pin, neighbouring audio vtable slot): this one feeds audio
// slot +0x174 with the trigger plus a float argument (x87 push idiom).
// Evidence: TheAudio at 0x00DFE6E8, getQualifiedTriggerAreaByName pin
// 0x0035768D, TheScriptEngine at 0x00DFE16C. Prev doTeamExitAll shares flags.
extern class AudioManager *TheAudio;

#include "ascii_string.h"

class PolygonTrigger
{
};

class ScriptEngine
{
public:
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

class BfmeAudio
{
public:
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
    virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
    virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
    virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
    virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
    virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
    virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
    virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
    virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
    virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
    virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63();
    virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67();
    virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71();
    virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75();
    virtual void a76(); virtual void a77(); virtual void a78(); virtual void a79();
    virtual void a80(); virtual void a81(); virtual void a82(); virtual void a83();
    virtual void a84(); virtual void a85(); virtual void a86(); virtual void a87();
    virtual void a88(); virtual void a89(); virtual void a90(); virtual void a91();
    virtual void a92();
    virtual void audioSlot174(PolygonTrigger *trig, float value);
};

class ScriptActions
{
protected:
    void rva003C004D(const AsciiString &, float);
};

void ScriptActions::rva003C004D(const AsciiString &areaName, float value)
{
    if (*(BfmeAudio **)&TheAudio == 0)
        return;
    PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName((AsciiString &)areaName);
    if (!trig)
        return;
    (*(BfmeAudio **)&TheAudio)->audioSlot174(trig, value);
}
