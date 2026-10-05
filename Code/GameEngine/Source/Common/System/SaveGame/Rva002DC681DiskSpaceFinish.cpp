// cl: /O1 /EHsc
// ?rva002DC681@Rva002DC267@@QBE_NXZ, retail 0x002DC681, 201 bytes.
//
// Save-dir disk-space check via rva002DC267 + GetDiskFreeSpaceExW. Retail
// str() falls back to UnicodeString TheNullChr at 0x00BBB5C4
// (?TheNullChr@?1??str@UnicodeString) when m_data is null; see the
// class-gate note below for why this body keeps a private view of that.
//
// The 0.99 bank reached 199 bytes and was missing the `jb` at +0x99. Retail
// splits the free-space test into a three-way unsigned branch on the high
// dword:
//
//   cmp  DWORD PTR [ebp-0x18], edi   ; high word vs a register zero
//   ja   +0x0f                        ; -> mov bl,1  (plenty of space)
//   jb   +0x09                        ; -> the low-word compare
//   cmp  DWORD PTR [ebp-0x1c], 0F00000h
//
// which is ONE predicate, not two nested tests: `ja` and `jb` are the two
// arms of a single unsigned comparison and the `jb` arm falls into the same
// low-word compare as the equal case. Spelled as the two-armed ternary the
// bank used (`if (hi > 0) ok = true; else if (lo >= F00000) ...`) MSVC folds
// the pair into a single test/ja, dropping the `jb` and the two bytes with it.
// Written as one disjunction both arms survive and the body is byte-exact:
//
//   ok = ((unsigned)(freeBytes >> 32) > 0u) || (freeBytes >= 0xF00000);
//
// Everything else in the bank was already correct: the UnicodeString temporary,
// the isEmpty guard that only calls set() when the string has data, and the
// ok-is-true-on-API-failure arm.

// class-gate: allow UnicodeString the shared header's view is not a codegen match here: its
// ctor/dtor emit a different call sequence, its TheNullChr is a different address and it
// drops the __SEH_prolog this body carries, so the 201B retail body only reproduces with
// the retail-private view of str()/releaseBuffer(). Established by compiling both.
typedef int Int;
typedef unsigned short WideChar;
#define NULL 0
template <typename T>
class StringBase
{
	friend class UnicodeString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
public:
	StringBase() : m_data(0) {}
	bool isEmpty() const throw();
	void set(const StringBase<T> &other);
protected:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};
class UnicodeString : public StringBase<WideChar>
{
public:
	UnicodeString() {}
	__forceinline UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	__forceinline UnicodeString(const WideChar *s) : StringBase<WideChar>(s) {}
	__forceinline ~UnicodeString() { releaseBuffer(); }
	const WideChar *str() const
	{
		static const WideChar TheNullChr = 0;
		return m_data ? &m_data->data[0] : &TheNullChr;
	}
};

extern const WideChar g_00C03F94[];

extern "C" __declspec(dllimport) Int __stdcall GetDiskFreeSpaceExW(
	const WideChar *dir, void *freeAvail, void *totalBytes, void *totalFree);

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
	bool rva002DC681() const;
};

bool Rva002DC267::rva002DC681() const
{
	UnicodeString path(g_00C03F94);
	bool has = !rva002DC267().isEmpty();
	if (has) {
		path.set(rva002DC267());
	}
	unsigned long long freeBytes = 0;
	bool ok;
	if (GetDiskFreeSpaceExW(path.str(), &freeBytes, 0, 0) != 0) {
		ok = ((unsigned)(freeBytes >> 32) > 0u) || (freeBytes >= 0xF00000);
	} else {
		ok = true;
	}
	return ok;
}