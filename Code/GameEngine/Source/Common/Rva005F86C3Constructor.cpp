// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE /G7
// stlport
//
// ??0Rva005F86C3@@QAE@HH@Z, retail 0x005F8671..0x005F86C3 (82 bytes, ret 8).
// Constructor of the StrategicHUD class whose vtable 0x00879CBC the deleting
// destructors name Rva005F86C3: the rowed base Rva00577936 gets the first
// argument, the second is kept at +8, two far floats (1e6) at +0xC / +0x10, a
// zero float at +0x14, two -500 words at +0x18 / +0x1C and an empty vector
// at +0x20. Class name address-derived; the vector element is a 4-byte
// stand-in. Fields are one-word structs with inline constructors (see
// Rva00074626Constructor.cpp) which keeps retail's store schedule.
#include <vector>

class Rva00577936
{
public:
	Rva00577936(int arg);
	virtual ~Rva00577936();
private:
	char m_pad04[4];
};

struct IntVal { int v; __forceinline IntVal(int x) : v(x) {} };
struct FloatVal { float v; __forceinline FloatVal(float x) : v(x) {} };

struct Rva005F86C3Base2 { IntVal m_08; __forceinline Rva005F86C3Base2(int v) : m_08(v) {} };

class Rva005F86C3 : public Rva00577936, public Rva005F86C3Base2
{
public:
	Rva005F86C3(int owner, int value);
	virtual ~Rva005F86C3();
private:
	FloatVal m_0C;
	FloatVal m_10;
	FloatVal m_14;
	IntVal m_18;
	IntVal m_1C;
	_STL::vector<int> m_20;
};

Rva005F86C3::Rva005F86C3(int owner, int value)
	: Rva00577936(owner), Rva005F86C3Base2(value), m_0C(1000000.0f), m_10(1000000.0f), m_14(0.0f), m_18(-500), m_1C(-500)
{
}
