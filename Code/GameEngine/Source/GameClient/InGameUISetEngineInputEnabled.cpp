// cl: /O1 /DNDEBUG /MD
//
// InGameUI::setEngineInputEnabled, retail 0x0029AB22, 19 bytes.
// Dedicated TU so GameEngineClientSubsystems.cpp cannot see this body.
// Forwards the flag to virtual slot 0x148 with this+0x15 as the extra arg.

class InGameUI
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81)
#undef V
	virtual void setInputLockState(bool enabled, char *extra) = 0;
	virtual void unusedSlot14C() = 0;
	void setEngineInputEnabled(bool enabled);
	void setInputEnabled(bool enabled);
};

void InGameUI::setEngineInputEnabled(bool enabled)
{
	setInputLockState(enabled, (char *)this + 0x15);
}

// InGameUI::setInputEnabled, retail 0x0029AB35 (19 bytes), directly after the
// method above; the same forward with this+0x16. ZH's
// ScriptActions::doEnableInput pairs it with Mouse::setVisibility, and
// ScriptEngine::reset makes that same pair of calls with TRUE.
void InGameUI::setInputEnabled(bool enabled)
{
	setInputLockState(enabled, (char *)this + 0x16);
}

// BFME1 semantic guide ba7ddda7: W3DInGameUIDraw.cpp, native6FBFF0.
// Target8F0CA..8F179 adds a fourth per-view call and changes the measured
// slots/fields. Original receiver and new slot names remain unproved.
class View;
#define DRAW_SLOT(N) virtual void unused##N() = 0;
class Display
{
public:
    DRAW_SLOT(0)
    DRAW_SLOT(1)
    DRAW_SLOT(2)
    DRAW_SLOT(3)
    DRAW_SLOT(4)
    DRAW_SLOT(5)
    DRAW_SLOT(6)
    DRAW_SLOT(7)
    DRAW_SLOT(8)
    DRAW_SLOT(9)
    DRAW_SLOT(10)
    DRAW_SLOT(11)
    DRAW_SLOT(12)
    DRAW_SLOT(13)
    DRAW_SLOT(14)
    DRAW_SLOT(15)
    DRAW_SLOT(16)
    DRAW_SLOT(17)
    DRAW_SLOT(18)
    DRAW_SLOT(19)
    DRAW_SLOT(20)
    DRAW_SLOT(21)
    DRAW_SLOT(22)
    DRAW_SLOT(23)
    DRAW_SLOT(24)
    DRAW_SLOT(25)
    DRAW_SLOT(26)
    DRAW_SLOT(27)
    DRAW_SLOT(28)
    DRAW_SLOT(29)
    DRAW_SLOT(30)
    DRAW_SLOT(31)
    DRAW_SLOT(32)
    DRAW_SLOT(33)
    DRAW_SLOT(34)
    DRAW_SLOT(35)
    virtual View *getFirstView(); // native +0x90
    virtual View *getNextView(View *);
};
class GameWindowManager
{
public:
    DRAW_SLOT(0)
    DRAW_SLOT(1)
    DRAW_SLOT(2)
    DRAW_SLOT(3)
    DRAW_SLOT(4)
    DRAW_SLOT(5)
    DRAW_SLOT(6)
    DRAW_SLOT(7)
    DRAW_SLOT(8)
    DRAW_SLOT(9)
    DRAW_SLOT(10)
    DRAW_SLOT(11)
    DRAW_SLOT(12)
    DRAW_SLOT(13)
    DRAW_SLOT(14)
    DRAW_SLOT(15)
    DRAW_SLOT(16)
    DRAW_SLOT(17)
    DRAW_SLOT(18)
    DRAW_SLOT(19)
    DRAW_SLOT(20)
    DRAW_SLOT(21)
    DRAW_SLOT(22)
    DRAW_SLOT(23)
    DRAW_SLOT(24)
    DRAW_SLOT(25)
    DRAW_SLOT(26)
    DRAW_SLOT(27)
    DRAW_SLOT(28)
    DRAW_SLOT(29)
    DRAW_SLOT(30)
    DRAW_SLOT(31)
    DRAW_SLOT(32)
    DRAW_SLOT(33)
    DRAW_SLOT(34)
    DRAW_SLOT(35)
    DRAW_SLOT(36)
    DRAW_SLOT(37)
    DRAW_SLOT(38)
    DRAW_SLOT(39)
    DRAW_SLOT(40)
    virtual void winRepaintWindows(); // native +0xA4
private:
    char unknown04[0x38];
public:
    int drawState; // native +0x3C
};
extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;
// Reuse the existing partial UI slot prefix as an ABI view. The donor
// supplies an inheritance lead; slot arithmetic alone proves no class name.
class Rva0008F0CA : public InGameUI
{
public:
    virtual void slot150();
    virtual void slot154();
    DRAW_SLOT(86)
    DRAW_SLOT(87)
    DRAW_SLOT(88)
    DRAW_SLOT(89)
    DRAW_SLOT(90)
    DRAW_SLOT(91)
    DRAW_SLOT(92)
    DRAW_SLOT(93)
    DRAW_SLOT(94)
    DRAW_SLOT(95)
    DRAW_SLOT(96)
    DRAW_SLOT(97)
    DRAW_SLOT(98)
    DRAW_SLOT(99)
    DRAW_SLOT(100)
    DRAW_SLOT(101)
    DRAW_SLOT(102)
    DRAW_SLOT(103)
    DRAW_SLOT(104)
    DRAW_SLOT(105)
    DRAW_SLOT(106)
    DRAW_SLOT(107)
    DRAW_SLOT(108)
    DRAW_SLOT(109)
    DRAW_SLOT(110)
    DRAW_SLOT(111)
    DRAW_SLOT(112)
    DRAW_SLOT(113)
    DRAW_SLOT(114)
    DRAW_SLOT(115)
    DRAW_SLOT(116)
    DRAW_SLOT(117)
    DRAW_SLOT(118)
    DRAW_SLOT(119)
    virtual void slot1E0();
    virtual void slot1E4(View *);
    virtual void slot1E8(View *);
    virtual void slot1EC(View *);
    virtual void slot1F0(View *);
    void rva0008F0CA();
private:
    char unknown04[0x24];
    bool dragSelecting;
};
#undef DRAW_SLOT
void Rva0008F0CA::rva0008F0CA()
{
    int state=TheWindowManager->drawState;
    switch (state) {
    case -1:
    case 1: break;
    case 0: TheWindowManager->winRepaintWindows(); return;
    default: return;
    }
    slot150();
    if (dragSelecting) slot1E0();
    if (TheDisplay) {
        for (View *view=TheDisplay->getFirstView(); view; view=TheDisplay->getNextView(view)) {
            slot1E4(view);
            slot1E8(view);
            slot1EC(view);
            slot1F0(view);
        }
    }
    slot154();
    TheWindowManager->winRepaintWindows();
}
