// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva0050FC54@@QAE@HABVAsciiString@@PAVPlayer@@@Z
// retail 0x0050FC54..0x0050FDDC (392 bytes) thiscall RET 12.
//
// The remote player's tribute row (WorldBuilder AptPlayerTribute.cpp twin
// 0x01356900): constructed by Rva0050F5A6::rva0050FFEC for a non-local
// player. Calls the row base constructor 0x0050F85D (level and name; it
// binds "_level%u.%s_color"), stores vtable 0x00C655BC, keeps level +0x5C
// name +0x60 player +0x64 maximum 99999 +0x68 amount +0x6C, takes the
// player's colour (+0x280) into the base +0x58, shows the player's display
// name (UnicodeString +0x38) through 0x0050F041 and refreshes through the
// pinned 0x0050F306, then binds "_level%u.%s_InitSlider" (0x0050E889) and
// "_level%u.%s_InitTextEntry" (0x0050F3A0) as Apt screen init gadgets
// through _bfme_setAptScreenRef 0x00411458 with the eight-byte
// multiple-inheritance member pointers held by 0x0057BC63 (as in
// AptTributeRowConstructors.cpp). The destructor 0x0050FDDC closes the same
// two screens. Class spelling follows the existing constructor pin.
#include "ascii_string.h"

class UnicodeString;

// "string + text" (RegistryAsciiPath.cpp).
#include "../../../../../Include/Common/AsciiStringRef.h"
#include "../../../../../Include/Common/Rva000B3F84Pair.h"
#include "../../../../../Include/Common/AsciiStringPlusText.h"
AsciiStringPlusText operator+(const AsciiString &left, const char *right);	// 0x000B49C5

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

#include "../../../../../Include/Common/FunctorWrapperHead.h"

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);	// 0x0057BC63
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

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

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);	// 0x00411458

class GameWindow;
class Player;

// The fields of the player the row reads.
struct Rva0050FC54PlayerView
{
	unsigned char m_pad000[0x38];
	unsigned char m_displayName[4];		// +0x38, a UnicodeString
	unsigned char m_pad03C[0x280 - 0x3C];
	int m_color;				// +0x280
};

// The row's display and gadget helpers, rowed under their own views.
#include "../../../../../Include/Common/Rva0050F041.h"

class Rva0050F0AB
{
public:
	void rva0050F306();
	void InitSlider(const char *name, void *argument, GameWindow *window);	// 0x0050E889
	void InitTextEntry(const char *name, void *argument, GameWindow *window);	// 0x0050F3A0
};

// The row base: the 0x58-byte callback registry plus the colour.
class Rva0050FAEC
{
public:
	Rva0050FAEC(int level, const AsciiString &name);	// 0x0050F85D
	virtual ~Rva0050FAEC();

	void setColor(int color) { m_color = color; }

private:
	unsigned char m_pad004[0x58 - 0x04];
	int m_color;					// +0x58
};

class Rva0050FC54 : public Rva0050FAEC
{
public:
	__declspec(noinline) Rva0050FC54(int level, const AsciiString &name, Player *player);
	virtual ~Rva0050FC54();

private:
	int m_level;					// +0x5C
	AsciiString m_name;				// +0x60
	Player *m_player;				// +0x64
	unsigned int m_maximum;				// +0x68
	unsigned int m_amount;				// +0x6C
	int m_70;					// +0x70
	int m_74;					// +0x74
	GameWindow *m_slider;				// +0x78
	GameWindow *m_textEntry;			// +0x7C
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva0050FC54::Rva0050FC54(int level, const AsciiString &name, Player *player)
	: Rva0050FAEC(level, name), m_level(level), m_name(name), m_player(player), m_maximum(99999), m_amount(0), m_70(-1), m_74(0), m_slider(0), m_textEntry(0)
{
	setColor(((Rva0050FC54PlayerView *)player)->m_color);
	((Rva0050F041 *)this)->rva0050F041(0, *(const UnicodeString *)((Rva0050FC54PlayerView *)player)->m_displayName);
	((Rva0050F0AB *)this)->rva0050F306();
	AsciiString key;
	key.format("_level%u.%s", m_level, m_name.str());
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0050F0AB::InitSlider);
		_bfme_setAptScreenRef(key + "_InitSlider", AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0050F0AB::InitTextEntry);
		_bfme_setAptScreenRef(key + "_InitTextEntry", AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}

class Rva0050F5A6;
class Rva0050FF55 : public Rva0050FC54
{
public:
	Rva0050FF55(Rva0050F5A6 *owner, int level, const AsciiString &name, Player *player);
	virtual ~Rva0050FF55();

private:
	Rva0050F5A6 *m_80;
};

// ??0Rva0050FF55@@QAE@PAVRva0050F5A6@@HABVAsciiString@@PAVPlayer@@@Z @0x0050FF55 (42B)
Rva0050FF55::Rva0050FF55(Rva0050F5A6 *owner, int level, const AsciiString &name, Player *player)
	: Rva0050FC54(level, name, player), m_80(owner)
{
}
