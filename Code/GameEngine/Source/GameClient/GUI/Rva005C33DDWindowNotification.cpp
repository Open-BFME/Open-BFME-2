// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 5C33DD..5C3427 RET0; matched5C3586 tail-calls this method on
// its +08 child. Original owner/method identity unresolved. Window+0C,
// rowed instance getter314046 and id getter5C4AE9, instance owner+14 and
// canonical globals establish the data/call ABI. Slot E8 forwards four words.
class GameWindow;
class WinInstanceData
{
public:
    char prefix[0x14];
    GameWindow *owner;
};
class GameWindow
{
public:
    WinInstanceData *winGetInstanceData();
    int winGetWindowId();
};
class ControlBar
{
public:
    __declspec(noinline) void rva00405D77();
};
extern ControlBar *TheControlBar;
class GameWindowManager
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58(GameWindow *owner, unsigned int message,
                        GameWindow *data1, unsigned int data2);
};
extern GameWindowManager *TheWindowManager;
class Rva005C33DD
{
public:
    void rva005C33DD();
private:
    char prefix[0x0C];
    GameWindow *window;
};
void Rva005C33DD::rva005C33DD()
{
    WinInstanceData *instance = window->winGetInstanceData();
    if (instance == 0)
        return;
    TheControlBar->rva00405D77();
    GameWindow *owner = instance->owner;
    TheWindowManager->slot58(owner, 0x4008,
                            window,
                            window->winGetWindowId());
}

// Native 5C3453..5C349D RET0; the matched 5C3596 slot tail-calls this
// method on its +08 child. The same target getters, receiver field and
// owner field as 5C33DD dispatch message 4009 instead of 4008. The existing
// address-derived callee name preserves the unresolved application identity.
class Rva005C3453
{
public:
    void rva005C3453();
private:
    char prefix[0x0C];
    GameWindow *window;
};
void Rva005C3453::rva005C3453()
{
    WinInstanceData *instance = window->winGetInstanceData();
    if (instance == 0)
        return;
    TheControlBar->rva00405D77();
    GameWindow *owner = instance->owner;
    TheWindowManager->slot58(owner, 0x4009,
                            window,
                            window->winGetWindowId());
}

// The native 405D77 wrapper tail-jumps to the already verified 34-byte
// cleanup at 405AA7 with the same receiver. Supply that provider rather
// than leaving the notification bound only through a pin.
class Rva00405AA7
{
public:
    void rva00405AA7();
};
void ControlBar::rva00405D77()
{
    reinterpret_cast<Rva00405AA7 *>(this)->rva00405AA7();
}
