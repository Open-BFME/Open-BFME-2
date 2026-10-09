// cl: /DNDEBUG /MD
//
// ?rva003182CD@Rva003182CD@@QAEEXZ, retail 0x003182CD, 20 bytes.
// Bounds-checked byte getter: index at +0x10, if 0 <= index < 5 returns byte
// at [this+index*8+0x34], else 0. Callers are FUN_004953B3 at 0x00095400 and
// FUN_004982F9 at 0x0009836E plus a jmp at 0x00094AD0. Identity beyond the
// index and 5x8 table is unproven so the name stays honest address-derived.

struct Rva003182CDElem
{
	unsigned char b;
	char pad[7];
};

class Rva003182CD
{
public:
	unsigned char rva003182CD();
private:
	char m_pad00[0x10];
	int m_10;
	char m_pad14[0x34 - 0x10 - 4];
	Rva003182CDElem m_34[5];
};

// Native 94AC6 tail-calls this actual 3182CD provider.
__declspec(noinline) unsigned char Rva003182CD::rva003182CD()
{
	int idx = m_10;
	if (idx < 0 || idx >= 5)
		return 0;
	return m_34[idx].b;
}

// The global is owned by GlobalWeatherSystem.cpp at native VA E01CE4.
class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;

// BF1 f989 R2GuardedTailCalls is the structural source lead. Its guessed
// bool callee is replaced by the actual rowed raw-byte getter above; native
// 94AC6..94AD8 preserves that byte result and returns zero when the named
// weather-system pointer is null. Original wrapper name remains unknown.
unsigned char Rva00094AC6WeatherByte()
{
	if (TheGlobalWeatherSystem)
		return reinterpret_cast<Rva003182CD *>(TheGlobalWeatherSystem)->rva003182CD();
	return 0;
}
