// ?UpdatePlayerTabButtons@AptMessengerOnline@@QAEXXZ
// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Retail 0x005AED3C..0x005AEF16, 474 bytes, thiscall RET0.
// Identity: WB 0x01515B40 names UpdatePlayerTabButtons in AptMessengerOnline.cpp;
// four identical APT labels and the selection/buddy/profile call graph agree.
// Target evidence: the menu is a vector of eight-byte label/enabled entries at
// +0x28C; the pending-friend flag is +0x2A0. Existing GetSelectedPlayers,
// MyBuddyList_ snapshot and profile-query providers establish the local ABI.
// Opaque provider names and unused interface slots remain address-derived.
// The WB early returns preserve both vector cleanup paths. String assignment
// and vector indexing produce the retail stack iterator and retained zero.
// Recovered from the October 8 bank using retail and WorldBuilder evidence.
#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
struct BfmeE8 {void *p;unsigned char flag;char pad[3];};
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const {if(p)::Rva00030830FreeAllocation(p);}
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *p, size_t n) {static_cast<const allocator<int> &>(*this).deallocate(p, n);}
}
class PlayerInfo {public: bool isIgnored();};
class GameSpyInfoInterface {public:
 virtual void _M_slot_00();
 virtual void _M_slot_04();
 virtual void _M_slot_08();
 virtual void _M_slot_0c();
 virtual void _M_slot_10();
 virtual void _M_slot_14();
 virtual void _M_slot_18();
 virtual void _M_slot_1c();
 virtual void _M_slot_20();
 virtual void _M_slot_24();
 virtual void _M_slot_28();
 virtual void _M_slot_2c();
 virtual void _M_slot_30();
 virtual void _M_slot_34();
 virtual void _M_slot_38();
 virtual void _M_slot_3c();
 virtual void _M_slot_40();
 virtual void _M_slot_44();
 virtual void _M_slot_48();
 virtual void _M_slot_4c();
 virtual void _M_slot_50();
 virtual void _M_slot_54();
 virtual void _M_slot_58();
 virtual PlayerInfo *rva00382D0A(int profile);
 virtual void _M_slot_60();
 virtual void _M_slot_64();
 virtual void _M_slot_68();
 virtual void _M_slot_6c();
 virtual void _M_slot_70();
 virtual void _M_slot_74();
 virtual void _M_slot_78();
 virtual int getLocalProfileID();

};
extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva005AEB2C
{
public:
    Rva005AEB2C();
    _STL::vector<BfmeE8> m_vec;
};
class Rva005AE7A5Class
{
public:
    int rva005AE7A5(int);
};
extern int g_Va00E046BC;
class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	FunctorWrapperHead *m_ptr;
};

struct TargetRef00217D4C;

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;

class AptExternHandler;

class AptOverButtonHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

 // the first online messenger

// The base's own fields, as AptMessengerConstructor.cpp builds them: the
// second tab's 8-byte label/enabled entries live in the +0x28C vector.
struct Rva00511E48
{
	AsciiString text;
	bool enabled;
	char pad[3];
};

class AptMessenger : public _bfme_AptGameWindow
{
public:
	AptMessenger(void *context);
	virtual ~AptMessenger();
	void OnBttn_0(const char *unused);
	void OnBttn_1(const char *unused);
	__declspec(noinline) void GetSelectedPlayers(int listIndex, int a, int b);
protected:
	int m_27C; // +0x27C
	_STL::vector<unsigned int> m_280; // +0x280
	_STL::vector<Rva00511E48> m_28C; // +0x28C
	int m_298; // +0x298
	bool m_29C; // +0x29C
	bool m_29D; // +0x29D
};

class AptMessengerOnline : public AptMessenger
{
public:
	AptMessengerOnline(void *context);
	virtual ~AptMessengerOnline();
	void UpdatePlayerTabButtons();
private:
	bool m_2A0; // +0x2A0
};
void AptMessengerOnline::UpdatePlayerTabButtons()
{
    if (!TheGameSpyInfo)
        return;
    m_28C[0].text = "APT:AddFriend";
    m_28C[1].text = "APT:Ignore";
    m_28C[0].enabled = false;
    m_28C[1].enabled = false;
    m_2A0 = false;
    _STL::vector<int> selected;
    GetSelectedPlayers(g_Va00E046BC, (int)&selected, 0);
    if (selected.size() != 1)
        return;
    int ignored, notIgnored, notBuddy, pendingBuddy;
    int *it;
    ignored = 0;
    notIgnored = 0;
    notBuddy = 0;
    pendingBuddy = 0;
    int local = TheGameSpyInfo->getLocalProfileID();
    Rva005AEB2C buddies;
    for (it = selected.begin(); it != selected.end(); ++it)
    {
        int profile = *it;
        if (profile == local)
            return;
        BfmeE8 *buddy = (BfmeE8 *)((Rva005AE7A5Class *)&buddies)->rva005AE7A5(profile);
        if (buddy)
        {
            if (!buddy->flag)
                return;
            ++pendingBuddy;
        }
        else
            ++notBuddy;
        PlayerInfo *player = TheGameSpyInfo->rva00382D0A(profile);
        if (player)
        {
            if (player->isIgnored())
                ++ignored;
            else
                ++notIgnored;
        }
    }
    if (notBuddy)
        m_28C[0].enabled = (pendingBuddy == 0);
    else if (pendingBuddy)
    {
        m_28C[0].text = "APT:AcceptFriend";
        m_28C[0].enabled = true;
        m_2A0 = true;
    }
    if (notIgnored)
        m_28C[1].enabled = (ignored == 0);
    else if (ignored)
    {
        m_28C[1].enabled = true;
        m_28C[1].text = "APT:RemoveIgnore";
    }
}
