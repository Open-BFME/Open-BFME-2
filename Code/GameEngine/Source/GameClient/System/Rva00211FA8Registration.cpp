// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 0x00211FA8..0x00212017 (111B), RET0. The existing same-receiver
// caller pin at 0x0023DA2B identifies only the singleton receiver; its
// original class and method names are unknown. Two callback addresses,
// 0x003FEBAA and 0x00210DB6, are wrapped by the matched 0x00211E75 ctor
// and passed to the verified 0x003FE7E6 registry with the existing id slot.
// GameClient::update supplies the established forwarding-constructor
// pattern and the exact by-value registry signature. The forwarding ctor
// preserves native ESP-save ordering and transfers each temporary once.
// Finally dispatch Mouse slot19, the rowed radar override setter, and the
// rowed in-game UI update. No new callee pin or literal address is added.
struct Impl00211E75;
class Rva00211E75 {
public:
    Rva00211E75(const int *arg);
    Rva00211E75(const Rva00211E75 &);
    ~Rva00211E75();
private:
    Impl00211E75 *m_impl;
};
class Rva00211E75Callback : public Rva00211E75 {
public:
    // The registry owns destruction; suppress an unused competing destructor COMDAT.
    ~Rva00211E75Callback();
    Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
};
extern int g_00E02EC4;
bool Rva003FE7E6(Rva00211E75Callback callback, int *id);
int rva00565170(int, bool);
// Native callback dispatcher611216 loads a float and forwards its bool flag.
// The rowed callback owner in Rva00211FA8Controls.cpp preserves that ABI.
int rva00210DB6(float, bool);

class Mouse;
extern Mouse *TheMouse;
struct MouseVisibilityView {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(bool);
};
class RadarWindowOverrideSource { public: void rva002D4240(bool); };
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0029B380 { public: void rva0029B34B(); };

class Rva00DFE1C8Host { public: void rva00211FA8(); };
void Rva00DFE1C8Host::rva00211FA8()
{
    {
        Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00565170)), &g_00E02EC4);
    }
    {
        Rva003FE7E6(Rva00211E75Callback(reinterpret_cast<int>(&rva00210DB6)), &g_00E02EC4);
    }
    reinterpret_cast<MouseVisibilityView *>(TheMouse)->s19(true);
    theRadarWindowOverrideSource->rva002D4240(true);
    reinterpret_cast<Rva0029B380 *>(TheInGameUI)->rva0029B34B();
}

