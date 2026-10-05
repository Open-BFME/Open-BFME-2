// cl: /O1 /DNDEBUG /MD /EHsc
// ZH InGameUI::showIdleWorkerLayout, also recovered in BFME 1 donor
// 847fc2a5406da49baed14adf987ff6830204b9d0, InGameUI.cpp.
// Target 0x0029AFA6-0x0029AFFC has independently identified InGameUI table
// entries at RVA 0x007C7C50 and 0x007FD5D8. Its literal, lookup,
// enable call and count update establish the identity independently of bytes.
// Retail establishes idleWorkerWin +0x978 and currentIdleWorkerDisplay +0x97C.
// The count query is an opaque virtual call at +0x1C0; its semantic purpose
// comes from ZH, while that slot and ABI come from the target instructions.

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator {
public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow {
public:
    int winEnable(bool);
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva0029AFA6WindowManagerView {
public:
#define SLOT(N) virtual void slot##N() = 0;
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
    SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
    SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
    SLOT(56) SLOT(57) SLOT(58) SLOT(59)
#undef SLOT
    virtual GameWindow *lookup(void *, NameKeyType) = 0;
};

class Rva0029AFA6CountView {
public:
#define SLOT(N) virtual void slot##N() = 0;
    SLOT(000) SLOT(001) SLOT(002) SLOT(003) SLOT(004) SLOT(005) SLOT(006) SLOT(007)
    SLOT(008) SLOT(009) SLOT(010) SLOT(011) SLOT(012) SLOT(013) SLOT(014) SLOT(015)
    SLOT(016) SLOT(017) SLOT(018) SLOT(019) SLOT(020) SLOT(021) SLOT(022) SLOT(023)
    SLOT(024) SLOT(025) SLOT(026) SLOT(027) SLOT(028) SLOT(029) SLOT(030) SLOT(031)
    SLOT(032) SLOT(033) SLOT(034) SLOT(035) SLOT(036) SLOT(037) SLOT(038) SLOT(039)
    SLOT(040) SLOT(041) SLOT(042) SLOT(043) SLOT(044) SLOT(045) SLOT(046) SLOT(047)
    SLOT(048) SLOT(049) SLOT(050) SLOT(051) SLOT(052) SLOT(053) SLOT(054) SLOT(055)
    SLOT(056) SLOT(057) SLOT(058) SLOT(059) SLOT(060) SLOT(061) SLOT(062) SLOT(063)
    SLOT(064) SLOT(065) SLOT(066) SLOT(067) SLOT(068) SLOT(069) SLOT(070) SLOT(071)
    SLOT(072) SLOT(073) SLOT(074) SLOT(075) SLOT(076) SLOT(077) SLOT(078) SLOT(079)
    SLOT(080) SLOT(081) SLOT(082) SLOT(083) SLOT(084) SLOT(085) SLOT(086) SLOT(087)
    SLOT(088) SLOT(089) SLOT(090) SLOT(091) SLOT(092) SLOT(093) SLOT(094) SLOT(095)
    SLOT(096) SLOT(097) SLOT(098) SLOT(099) SLOT(100) SLOT(101) SLOT(102) SLOT(103)
    SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111)
#undef SLOT
    virtual int query() = 0;
    virtual void slot113() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

class InGameUI {
    unsigned char opaque04[0x15 - 4];
    bool engineInputEnabled;
    bool inputEnabled;
    unsigned char opaque17[0x978 - 0x17];
    GameWindow *idleWorkerWin;
    int currentIdleWorkerDisplay;
public:
    virtual void showIdleWorkerLayout();
    virtual void updateIdleWorker();
};

void InGameUI::showIdleWorkerLayout()
{
    if (!idleWorkerWin) {
        idleWorkerWin = reinterpret_cast<Rva0029AFA6WindowManagerView *>(TheWindowManager)->lookup(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker"));
        return;
    }
    idleWorkerWin->winEnable(true);
    currentIdleWorkerDisplay = reinterpret_cast<Rva0029AFA6CountView *>(this)->query();
}

// ZH updateIdleWorker; native 0x0029AFFC-0x0029B04D ends immediately before
// the already-matched max setter. Retail supplies input flags +0x15/+0x16
// and the virtual show/hide calls at +0x1C8/+0x1CC.
void InGameUI::updateIdleWorker()
{
    int idleCount = reinterpret_cast<Rva0029AFA6CountView *>(this)->query();
    if (idleCount > 0 && currentIdleWorkerDisplay != idleCount &&
        engineInputEnabled && inputEnabled)
        reinterpret_cast<Rva0029AFA6CountView *>(this)->show();
    if ((idleCount <= 0 && idleWorkerWin) || !(engineInputEnabled && inputEnabled))
        reinterpret_cast<Rva0029AFA6CountView *>(this)->hide();
}
