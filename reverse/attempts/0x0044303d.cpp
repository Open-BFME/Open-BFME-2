// ?rva0044303D@MpGameSetup@@QAEXXZ
// partial score=0.99 date=2026-10-05
// ?rva0044303D@MpGameSetup@@QAEXXZ draft (inside MpGameSetupSlots.cpp, /G7): 1040B, every instruction right except the frame: retail sub esp,0x2C and the last block (MpGameSetup::InitGadgets via _bfme_setAptScreenRef) copies its FunctorBinding to [ebp-0x38] like the other ten, while cl puts the last block's inline by-value copy in a fresh slot [ebp-0x48] (sub esp,0x3C). The last block's name at [ebp-0x14] already matches retail. Same result with the cdecl call replaced by a member, a named binding local, __forceinline/out-of-class inline ctors, implicit conversion, binding factories, no braces, and with 2..11 blocks: the LAST block's copy always gets a fresh slot. The whole Apt registration family (callers of 0x0057BC63, ~45 bodies: 0x0057FFB9, 0x0057FAB0, 0x0057F0AA, 0x0057E45C, 0x00445EE3, 0x0043D686 ...) shares this shape.
// Needs in MpGameSetupSlots.cpp: the declarations below placed before class MpGameSetup; MpGameSetup's +0x00 pad split into m_pad000[4], Rva0052458E m_callbacks (+0x04), Rva005245F3 m_queries (+0x10), m_pad01c[0x58-0x1C]; members void rva0044303D() and _bfme_onInitGadget(const char *, void *, GameWindow *); view methods Rva0057E3DB::rva0057E45C, Rva0057EE5C::rva0057F0AA, Rva0057F2DE::rva0057FAB0, Rva0057FD6E::rva0057FFB9 (all void, unrowed); pins for those four plus 0x0052458E, 0x005245F3 and _bfme_setAptScreenRef 0x00411458 (signatures in the decls).
// The Apt callback functors (Rva0057BC63FunctorHolder.cpp): a binding of
// an object and an eight-byte multiple-inheritance member pointer, the
// refcounted holder 0x0057BC63 builds from it, and the functor passed by
// value that wraps the holder (its by-value constructor is out of line at
// 0x00518756 and inline here).
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

struct FunctorWrapperHead
{
	virtual void destroy(bool deleting);
	int m_refCount;
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
	~Rva0057BC63FunctorHolder()
	{
		if (m_ptr && --m_ptr->m_refCount <= 0)
			m_ptr->destroy(true);
	}

	FunctorWrapperHead *m_ptr;
};

class Rva00518756Functor : public Rva0057BC63FunctorHolder
{
public:
	Rva00518756Functor(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
};

// The panel's two callback name lists at +0x04 and +0x10 (vectors of the
// bound names): 0x0052458E binds an Apt callback, 0x005245F3 a query
// callback with its index, each through TheRva00222A8BTarget; both unrowed
// and pinned by address.
class Rva0052458E
{
public:
	void rva0052458E(const AsciiString &name, Rva00518756Functor functor);

	unsigned char m_vector[0x0C];
};

class Rva005245F3
{
public:
	void rva005245F3(const AsciiString &name, int index, Rva00518756Functor functor);

	unsigned char m_vector[0x0C];
};

// BFME1's _bfme_setAptScreenRef (AptScreenSetRef.cpp): 0x00411458 sits
// before _bfme_closeAptScreen as there and assigns the functor to the named
// slot of the screen table at 0x00E02FD0; unrowed, pinned by address.
void _bfme_setAptScreenRef(const AsciiString &name, Rva00518756Functor functor);

// The panel's member pointers are bound as eight-byte multiple-inheritance
// ones (the binding's code and delta words).
#pragma pointers_to_members(full_generality, multiple_inheritance)

// Retail 0x0044303D, 1040 bytes. Name unknown. Registers the panel's Apt
// callbacks: the sort, kick, ready and tab handlers by name, the
// 0x00442F65 query under four names with indices 0..3, and
// "MpGameSetup::InitGadgets" (the rowed _bfme_onInitGadget) as the screen
// reference; then clears the current game and lets the four members
// register theirs. Called from the LAN lobby screen 0x00444451.
void MpGameSetup::rva0044303D()
{
	m_pending = false;
	m_2c4 = false;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::OnSortIcons);
		AsciiString name("MpGameSetup::OnSortIcons");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::OnSortName);
		AsciiString name("MpGameSetup::OnSortName");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::OnSortPlayers);
		AsciiString name("MpGameSetup::OnSortPlayers");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::rva0043E4B6);
		AsciiString name("MpGameSetup::OnKickPlayer");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::OnReadyPress);
		AsciiString name("MpGameSetup::OnReadyPress");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::OnTabSelect);
		AsciiString name("MpGameSetup::OnTabSelect");
		m_callbacks.rva0052458E(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::rva00442F65);
		AsciiString name("MpGameSetup::HostMode");
		m_queries.rva005245F3(name, 0, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::rva00442F65);
		AsciiString name("MpGameSetup::IsInitialized");
		m_queries.rva005245F3(name, 1, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::rva00442F65);
		AsciiString name("AptMpGameRules::ShowClans");
		m_queries.rva005245F3(name, 2, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::rva00442F65);
		AsciiString name("AptMpGameRules::ShowChat");
		m_queries.rva005245F3(name, 3, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	Rva00446A67Set(0);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&MpGameSetup::_bfme_onInitGadget);
		AsciiString name("MpGameSetup::InitGadgets");
		_bfme_setAptScreenRef(name, Rva00518756Functor(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	m_game->m_current = 0;
	m_60.rva0057E45C();
	m_d0.rva0057F0AA();
	m_190.rva0057FAB0();
	m_244.rva0057FFB9();
}
