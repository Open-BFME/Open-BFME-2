// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme_stlport_int_dealloc_link
// stlport
//
// ??0Rva0056B7E4@@QAE@ABVAsciiString@@@Z, retail 0x0056B7E4, 166 bytes.
//
// Evidence (retail body only; names are address-derived):
//  56b7e4: mov eax, FuncInfo / call __EH_prolog; vtable 0x00C37898 at +0
//          (this class's own table; the derived ctors 0x0056B63E / 0x0056BDC8
//          / 0x0056BEFB overwrite it after this base construction).
//          AsciiString at +4 (default), _Vector_base ctor 0x00211E58 at +8,
//          AsciiString at +0x14 (default), AsciiString at +0x18 copy-
//          constructed from the single argument through 0x000365F0. Then
//          +0x1C = 0.0f, +0x20 = 1.0f (the float at VA 0xBBB8D8), +0x24 =
//          0.0f, +0x28 = 0, +0x2C = 1, +0x30..+0x40 = 0, +0x44 = +0x48 = 10,
//          +0x4C = 0.0f, and the seven bytes at +0x50..+0x56 = 0.
// The state-count clue identifies the third string: retail sets trylevel 0
// (destroy the +4 string) BEFORE the vector ctor and trylevel 2 before the
// +0x18 copy, so the +4 word is a destructible object, not a scalar. The
// class is the LivingWorldArmyIconSubObject whose rowed method
// ?rva0056B89F@LivingWorldArmyIconSubObject@@QAEEXZ lives at 0x0056B89F.
// The existing symbols.csv pin ?rva0056B7E4@Rva0056B7E4@@QAEXPAX@Z at this
// address is the scaffolding spelling the already-rowed callers call through;
// retail's own subobject-construction sequence here is a constructor's.

#include "ascii_string.h"
#include <vector>
#include "int_dealloc.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<int,allocator<int> >::~_Vector_base(); }
// bfme link decl-only begin
namespace _STL { template <> vector<int, allocator<int> >::~vector(); }
// bfme link decl-only end

class Rva003F9FE6
{
public:
	// Retail vtable 0x00837898 slot 0 holds Rva003F9FE6::rva0056B7A0.
	virtual unsigned char rva0056B7A0(int id);
};

class Rva0056B7E4 : public Rva003F9FE6
{
public:
	Rva0056B7E4(const AsciiString &name);

private:
	AsciiString m_4;         // +0x04, default-constructed
	std::vector<int> m_8;   // +0x08..+0x14
	AsciiString m_14;        // +0x14, default-constructed
	AsciiString m_18;        // +0x18, copied from the argument
	float m_1c;              // +0x1C
	float m_20;              // +0x20, 1.0f
	float m_24;              // +0x24
	int m_28;                // +0x28
	int m_2c;                // +0x2C, 1
	int m_30;                // +0x30
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;                // +0x44, 10
	int m_48;                // +0x48, 10
	float m_4c;              // +0x4C
	unsigned char m_50;      // +0x50..+0x56
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_55;
	unsigned char m_56;
};

Rva0056B7E4::Rva0056B7E4(const AsciiString &name)
	: m_18(name),
	  m_1c(0.0f),
	  m_20(1.0f),
	  m_24(0.0f),
	  m_28(0),
	  m_2c(1),
	  m_30(0),
	  m_34(0),
	  m_38(0),
	  m_3c(0),
	  m_40(0),
	  m_44(10),
	  m_48(10),
	  m_4c(0.0f),
	  m_50(0),
	  m_51(0),
	  m_52(0),
	  m_53(0),
	  m_54(0),
	  m_55(0),
	  m_56(0)
{
}
