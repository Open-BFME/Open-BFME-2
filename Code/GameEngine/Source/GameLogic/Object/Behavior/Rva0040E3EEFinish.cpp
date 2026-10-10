// ??0ArmySummary@@QAE@XZ (was ??0Rva0040E3EE@@QAE@XZ)
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Identity (target): the last vptr store is vtable 0x00C394F0 whose slot 0
// is the rowed ??1ArmySummary@@UAE@XZ (0x0040E499) so this is ArmySummary's
// constructor. The private view keeps its manual vptr store.
#include <vector>
#include "ascii_string.h"
extern const void *const g_00C394F0[];
struct BfmeE16 { float x, y, z, w; };
class Rva00330757Member
{
public:
	Rva00330757Member();
private:
	_STL::vector<BfmeE16> m_items;
	int m_flags;
};
class Rva0040E3EEBase
{
public:
	Rva0040E3EEBase() {}
	~Rva0040E3EEBase();
};
class ArmySummary : public Rva0040E3EEBase
{
public:
	ArmySummary();
private:
	const void *m_vtable;
	Rva00330757Member m_04;
	unsigned char m_14;
	char m_pad15[3];
	AsciiString m_18;
	int m_1c;
	AsciiString m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	_STL::vector<BfmeE16> m_40;
	_STL::vector<BfmeE16> m_4c;
	float m_58;
	float m_5c;
	int m_60;
	int m_64;
};

ArmySummary::ArmySummary()
	: Rva0040E3EEBase(), m_14((m_vtable = (const void *)g_00C394F0, (char)0)), m_18(AsciiString::TheEmptyString), m_1c(0), m_20(AsciiString::TheEmptyString), m_24(0xFF000000), m_28(0xFF000000), m_2c(1), m_30(0), m_34(0), m_38(0), m_3c(1), m_40(_STL::allocator<BfmeE16>()), m_4c(_STL::allocator<BfmeE16>()), m_58(0.0f), m_5c(0.0f), m_60(0), m_64(0)
{
}
