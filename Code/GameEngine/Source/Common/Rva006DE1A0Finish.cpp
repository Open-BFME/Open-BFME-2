// cl: /EHsc /MD
// ??0Rva006DE1A0@@QAE@XZ @ 0x006DE1A0 107B Apt ctor with hash member.
// Evidence: neighbours AptValuePtrStackTop plus Rva006DE2B0Slot7 share /O2 /MD;
// EH prolog with scopetable so plus /EHsc; rowed AptNativeHash ctor 0x0070A740
// with 8; two vptr stores at 0x00CEA228 then 0x00CEB150 to the same slot, so the
// base chain is flag-only base -> vptr class holding the hash member -> the
// constructed class; flags and 0xFFFFFFDF plus m_1C zero; unblocks 5.
class AptNativeHash
{
public:
	AptNativeHash(int n);
};
extern "C" {
extern const void *const __identifier("??_7AptValueWithHash@@6B@")[];
extern const void *const __identifier("??_7Rva006DE2B0@@6B@")[];
}

#define g_aptValueBaseTable __identifier("??_7AptValueWithHash@@6B@")
#define g_aptValueHashTable __identifier("??_7Rva006DE2B0@@6B@")

// Retail's unwind at 0x007A8DA0 jumps to the destructor rowed under this name at 0x006D6340.
class __declspec(novtable) AptValueGC
{
public:
	AptValueGC() : m_04((m_04 & 1) | 0x38000030) {}
protected:
	virtual ~AptValueGC();
protected:
	int m_04;
};
class __declspec(novtable) Rva006DE1A0Mid : public AptValueGC
{
public:
	__forceinline Rva006DE1A0Mid() : m_08((*(const void *const **)this = g_aptValueBaseTable, 8)) { m_04 &= ~0x20; }
protected:
	AptNativeHash m_08;
	char m_pad[0x1C - 0x08 - 4];
	int m_1C;
};
class __declspec(novtable) Rva006DE1A0 : public Rva006DE1A0Mid
{
public:
	Rva006DE1A0();
};
Rva006DE1A0::Rva006DE1A0() { *(const void *const **)this = g_aptValueHashTable; m_1C = 0; }
