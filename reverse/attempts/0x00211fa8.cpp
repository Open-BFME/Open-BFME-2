// ?d_00211fa8@@YAXXZ
// partial score=0.96 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Retail 0x00211FA8..0x00212017 RET0 constructs two one-word callback
// handles and transfers their ownership to the cdecl registry worker.
// The callback identities and named singleton addresses come from their
// existing bodies and data ledger; the enclosing routine keeps its RVA name.
struct Impl00211E75;
class Rva00211E75 {
public:
    Rva00211E75(const int *arg);
    Rva00211E75(const Rva00211E75 &);
    ~Rva00211E75();
private:
    Impl00211E75 *m_impl;
};
extern int rva00A02EC4;
void __cdecl rva003FE7E6(Rva00211E75 callback, int *id);
int rva00565170(int, bool);
int rva00210DB6();

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

void rva00211FA8()
{
    {
        const int callback = reinterpret_cast<int>(&rva00565170);
        rva003FE7E6(Rva00211E75(&callback), &rva00A02EC4);
    }
    {
        const int callback = reinterpret_cast<int>(&rva00210DB6);
        rva003FE7E6(Rva00211E75(&callback), &rva00A02EC4);
    }
    reinterpret_cast<MouseVisibilityView *>(TheMouse)->s19(true);
    theRadarWindowOverrideSource->rva002D4240(true);
    reinterpret_cast<Rva0029B380 *>(TheInGameUI)->rva0029B34B();
}
