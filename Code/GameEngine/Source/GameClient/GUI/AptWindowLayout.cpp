// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG
class GameWindow { public: int winSetSize(int,int); int winHide(bool); int winEnable(bool); };
class AptLayoutWindowCallbacks {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
#undef SLOT
 virtual bool ready();
 virtual void initialized();
};
struct AptLayoutScale { float x,y; };
class AptLayoutPlayerScaleView {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8)
 SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
 virtual const AptLayoutScale *scale();
};
class AptLayoutManagerFocusView {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8)
 SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16)
 SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
 SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
 SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40)
 SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
#undef SLOT
 virtual void focus(GameWindow *);
};
class AptPlayer { public: bool ShowLevel(int); };
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class ModuleData;
class Rva00223CBD { public: void rva00223CBD(const ModuleData *); };
void Rva006CD6F0Get(void **,void **);
// Native221-byte slot0; WB109D190 proves callback order and dimensions;
// the original method name is unknown. Constructor/WB109CD40 proves the
// AptWindowLayout owner and its window+24 and initialized-byte+28.
class AptWindowLayout {
public:
 virtual void rva0040FB9C(void *);
 virtual void slot1(); virtual void slot2(void *); virtual void slot3(void *);
 virtual void hide(bool); virtual void bringForward(); virtual void addWindow(GameWindow *);
private:
 unsigned char pad04[0x20];
 GameWindow *m_gameWindow;
 bool m_initialized;
};
void AptWindowLayout::rva0040FB9C(void *)
{
 if(!m_gameWindow || m_initialized || !reinterpret_cast<AptLayoutWindowCallbacks *>(m_gameWindow)->ready()) return;
 hide(false);
 int width,height;
 Rva006CD6F0Get(reinterpret_cast<void **>(&width),reinterpret_cast<void **>(&height));
 const AptLayoutScale *scale=reinterpret_cast<AptLayoutPlayerScaleView *>(g_bfmeAptWindowManager)->scale();
 width=static_cast<int>(static_cast<float>(width)*scale->x);
 height=static_cast<int>(static_cast<float>(height)*scale->y);
 m_gameWindow->winSetSize(width,height);
 m_gameWindow->winHide(false);
 m_gameWindow->winEnable(true);
 bringForward();
 reinterpret_cast<AptLayoutManagerFocusView *>(TheWindowManager)->focus(m_gameWindow);
 reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->ShowLevel(*reinterpret_cast<int *>(reinterpret_cast<char *>(m_gameWindow)+0x274));
 reinterpret_cast<Rva00223CBD *>(g_bfmeAptWindowManager)->rva00223CBD(*reinterpret_cast<const ModuleData **>(reinterpret_cast<char *>(m_gameWindow)+0x274));
 reinterpret_cast<AptLayoutWindowCallbacks *>(m_gameWindow)->initialized();
 m_initialized=true;
}
