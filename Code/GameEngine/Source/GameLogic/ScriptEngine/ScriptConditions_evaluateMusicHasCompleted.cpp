// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateMusicHasCompleted@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E7AFC 90B. ZH donor ScriptConditions.cpp evaluateMusicHasCompleted:
// copy the track name, ask TheAudio (global 0x00DFE6E8) through vslot +0x80.
// BFME2 passes two extra arguments (0, 1) after the track index; their
// meaning is not asserted.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
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
    virtual bool hasMusicTrackCompleted(const AsciiString &trackName, int numberOfTimes, int extraA, int extraB) const; // +0x80
};
extern AudioManager *TheAudio;
class ScriptConditions
{
protected:
    bool evaluateMusicHasCompleted(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateMusicHasCompleted(Parameter *musicParm, Parameter *intParm)
{
    AsciiString str = musicParm->getString();
    int numberOfTimes = intParm->m_int;
    return TheAudio->hasMusicTrackCompleted(str, numberOfTimes, 0, 1);
}
