// ??0AptSaveLoad@@QAE@PAX@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Target evidence: vptr pair 0x00C3CDC8/0x00C3CDC4 at this/+0x218, AptSaveLoad
// strings and neighboring callbacks, pending kind at +0x28, and the fields
// read through +0x2AC. The opaque address-derived type keeps the owner name
// unclaimed. The two-base/string prefix follows the independently matched
// BFME2 _bfme_AptGameWindow destructor; BFME1 AptSaveLoad dtor is a semantic
// and control-flow donor, with target-specific pending and replay branches.
#include <list>
#include "../reference/shims/bfme2_ascii/ascii_string.h"
#include "../reference/shims/bfme2_ascii/unicode_string.h"

class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
private:
	unsigned char m_opaque[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char m_opaque[0x58 - 4];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename270;
};

struct BfmeSubobject0022CE19
{
	virtual ~BfmeSubobject0022CE19();
	unsigned char m_pad004[0x20];
	int m_kind;
	unsigned char m_opaque028[0xDE4 - 0x24];
	BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};

struct TreeHintOpaque0043671B
{
	UnicodeString m_text;
	BfmeSubobject0022CE19 m_subobject;
	unsigned int m_wordDEC;
	unsigned int m_wordDF0;
	TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
	~TreeHintOpaque0043671B();
};

class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *name);
};

class Rva00222A8BTarget
{
public:
	void rva00222F55(bool showBackground);
	void rva002233A6(int);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
};

class GameLogic
{
public:
	unsigned char isGamePaused();
	void rva0023CD9E(bool paused, int mode, bool affectInput);
	void rva00376E92(bool showScore, bool unknown);
};

class GameState
{
public:
	int rva002DE3C1(TreeHintOpaque0043671B info);
};

class RecorderClass
{
public:
	bool playbackFile(UnicodeString name);
};

class Shell
{
public:
	void hide(bool doHide);
	bool rva0035BD5D();
	void rva0035C7CF(bool runInit);
};

class GameEngineView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
};

class GameWindowManagerView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
};

class AudioManagerView
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void slot8C(int a, int b, int c);
};

class RvaLogicHolder
{
public:
	void rva002B2E77(int value);
};

void Rva0051AF0BEnable(int value);
void Rva005210ECEnable(bool value);
void _bfme_closeAptScreen(const AsciiString &name);


// Complete native436259..4366FF and named WB12AB350/2908 establish this
// save/load screen constructor. Existing base, list and callback binder
// providers guide the C++ representation; no new address pin is asserted.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding {
    FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
    FunctorTarget *m_target; unsigned int m_pad; FunctorMethod m_method;
};
__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target) {
    FunctorBinding binding(method,target); return binding;
}
struct FunctorWrapperHead { void *m_vtbl; int m_refCount; };
class Rva0057BC63FunctorHolder {
public:
    Rva0057BC63FunctorHolder(const FunctorBinding &);
    Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr) {
        if(m_ptr) ++m_ptr->m_refCount;
    }
    FunctorWrapperHead *m_ptr;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template<class T> class AptRef : public Rva0057BC63FunctorHolder {
public:
    AptRef(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
    ~AptRef();
};
class AptCommandMap; class AptExternHandler; class AptScreenInitGadgets;
class AptCommandMapAdder { public: void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>); };
class AptPlayer {
public:
    void AddExternHandler(const AsciiString &, int, AptRef<AptExternHandler>);
    void rva002233A6(bool);
    unsigned char unknown00[0x31c];
    int background31c;
};
extern AptPlayer *TheAptPlayer;
extern GameLogic *TheGameLogic;
extern int g_Va00E032E0;
extern const char *const saveLoadExternNames[3];
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);
class Gen_0056E190 {
public: bool bfmeDiffers(const Gen_0056E190 &) const;
    Gen_0056E190() {}
    Gen_0056E190(unsigned int initial) : value04(initial) {}
    unsigned int unknown00, value04;
};
class Rva00435CFE { public: void rva00435CFE(unsigned short); };
class Rva00435B82 { public: Rva00435B82 *rva0043611F(Rva00435B82 *); };
int Rva0043549AHook(int,int);

class __multiple_inheritance AptSaveLoad : public _bfme_AptGameWindow {
public:
    AptSaveLoad(void *);
    virtual ~AptSaveLoad();
    void rva00433DF1(const char *);
    void OnClosed(const char *);
    void Load(const char *);
    void rva0043566A(const char *);
    void Delete(const char *);
    void Cancel(const char *);
    void ConfirmationOk(const char *);
    void Externs(int,char *,bool);
    void InitGadgets(const char *,void *,GameWindow *);
private:
    unsigned char pad274[8];
    int state27c;
    TreeHintOpaque0043671B *pending280;
    unsigned char paused284;
    unsigned char pad285[3];
    void *gameList288, *autoSaveList28c, *fileName290;
    int word294,word298;
    bool flag29c,flag29d;
    int mode2a0;
    bool background2a4;
    unsigned char pad2a5[3];
    int word2a8;
    _STL::list<TreeHintOpaque0043671B> entries2ac;
};

AptSaveLoad::AptSaveLoad(void *context)
 : _bfme_AptGameWindow(context),state27c(0),pending280(0),paused284(TheGameLogic->isGamePaused()),
   gameList288(0),autoSaveList28c(0),fileName290(0),word294(0),word298(0),flag29c(false),flag29d(true),
   mode2a0(0),background2a4(false),word2a8(0)
{
    if(!g_Va00E032E0) {
        g_Va00E032E0=(int)this;
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433DF1);
            AsciiString name("AptSaveLoad::OnInitialized");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::OnClosed);
            AsciiString name("AptSaveLoad::OnClosed");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::Load);
            AsciiString name("AptSaveLoad::Load");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva0043566A);
            AsciiString name("AptSaveLoad::Save");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::Delete);
            AsciiString name("AptSaveLoad::Delete");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::Cancel);
            AsciiString name("AptSaveLoad::Cancel");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::ConfirmationOk);
            AsciiString name("AptSaveLoad::ConfirmationOk");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::rva00433DF1);
            AsciiString name("AptSaveLoad::ConfirmationCancel");
            reinterpret_cast<AptCommandMapAdder *>(reinterpret_cast<char *>(this)+0x21c)->AddCommandMap(
                name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        Gen_0056E190 index;
        reinterpret_cast<Rva00435CFE *>(&index)->rva00435CFE(0);
        Gen_0056E190 end(0x3a76d6c6);
        for(;;) {
            if(!index.bfmeDiffers(end)) break;
            {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::Externs);
            AsciiString name(saveLoadExternNames[(short)Rva0043549AHook(index.value04,index.value04)]);
            TheAptPlayer->AddExternHandler(name,(short)Rva0043549AHook(index.value04,index.value04),
                AptRef<AptExternHandler>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
            }
            Gen_0056E190 old;
            reinterpret_cast<Rva00435B82 *>(&index)->rva0043611F(reinterpret_cast<Rva00435B82 *>(&old));
        }
        {
            FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptSaveLoad::InitGadgets);
            AsciiString name("AptSaveLoad::InitGadgets");
            _bfme_setAptScreenRef(name,AptRef<AptScreenInitGadgets>(FunctorBinding(method,reinterpret_cast<FunctorTarget *>(this))));
        }
        TheGameLogic->rva0023CD9E(true,2,true);
        background2a4=TheAptPlayer->background31c==0;
        if(background2a4) reinterpret_cast<Rva00222A8BTarget *>(TheAptPlayer)->rva002233A6(1);
    }
}

template<class T> AptRef<T>::~AptRef() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
