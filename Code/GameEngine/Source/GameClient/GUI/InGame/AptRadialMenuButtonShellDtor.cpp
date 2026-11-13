// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// AptRadialMenu::Impl::ButtonShell::~ButtonShell, retail 0x00578189 (363 bytes,
// EH). Destructor of the shell
// AptRadialMenuButtonShellConstructor.cpp builds (vftable 0x00C6EA80, scalar
// deleting dtor 0x00578409). When TheAptPlayer exists it unbinds the
// "<movie>_OnButtonFrameUnloaded_<n>" and "..._OnButtonFrameLoaded_<n>"
// command maps (0x00224455 with the converted concat temp, passed through a
// forceinline wrapper so the temp has an address) and fires "DestroyButton"
// on the holder movie (0x0052519D) with the index; then the owner is told
// (OnButtonDestroyed 0x005778FC, declared throw() because retail keeps the
// unwind state at its entry value around that call), the +0x14 list clears
// and the inline base dtor restores vftable 0x00BC6F20.
#include "ascii_string.h"

#include "../../../../Include/Common/Rva00224455.h"
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../../Include/Common/Rva000B3F84Pair.h"
#include "../../../../Include/Common/AsciiStringRef.h"
#include "../../../../Include/GameClient/Rva002226E5TextPlusString.h"
struct AsciiStringPlusText : Rva002226E5TextPlusString
{
};
struct Rva0020F58E
{
	operator AsciiString();
	Rva002226E5TextPlusString m_left;
	AsciiStringRef m_right;
};
struct AptTextPlusStringPlusString : Rva0020F58E
{
};
AsciiStringPlusText operator+(const AsciiString &left, const char *right);
AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right);

int __cdecl Rva0052519DFire(void *player, void *movie, const char *path, const char *name, int *argument);

struct RadialButtonMovie
{
	void *getMovie() const { return m_movie; }
	char m_pad00[4];
	void *m_movie; // +0x04
	AsciiString m_path; // +0x08
};
struct RadialButtonHolder
{
	RadialButtonMovie *m_button;
};

class AptRadialMenu
{
public:
	class Impl
	{
	public:
		class ButtonShell;
		void OnButtonDestroyed() throw();
	private:
		char m_pad00[0x40];
	public:
		RadialButtonHolder *m_holder; // +0x40
	};
};

#include "../../../../Include/GameClient/Rva00577A0E.h"

class Rva00577FE2Base
{
public:
	Rva00577FE2Base() : m_references(0) {}
	virtual ~Rva00577FE2Base() {}
	int m_references;
};

// The +0x14 holder's destructor is 0x000AD6F4, the body clear shares.
#include "../../../../Include/Common/Rva000AD6F4.h"

class AptRadialMenu::Impl::ButtonShell : public Rva00577FE2Base
{
public:
	virtual ~ButtonShell();
private:
	Impl *m_impl;
	int m_slot;
	int m_index;
	Rva000AD6F4 m_14;
	void *m_18;
	void *m_1C;
	int m_20;
	int m_24;
	bool m_enabled;
};

static __forceinline void removeCommandMap(const AsciiString &name)
{
	reinterpret_cast<Rva00224455 *>(g_bfmeAptWindowManager)->RemoveCommandMap(&name);
}

AptRadialMenu::Impl::ButtonShell::~ButtonShell()
{
	if (reinterpret_cast<Rva00224455 *>(g_bfmeAptWindowManager))
	{
		AsciiString indexText;
		indexText.format("%d", m_index);
		AsciiString movie = ((const Rva00577A0E *)m_impl)->rva00577A0E();
		removeCommandMap(movie + "_OnButtonFrameUnloaded_" + indexText);
		removeCommandMap(movie + "_OnButtonFrameLoaded_" + indexText);
		RadialButtonMovie *button = m_impl->m_holder->m_button;
		Rva0052519DFire(reinterpret_cast<Rva00224455 *>(g_bfmeAptWindowManager), button->getMovie(), button->m_path.str(), "DestroyButton", &m_index);
	}
	m_impl->OnButtonDestroyed();
}
