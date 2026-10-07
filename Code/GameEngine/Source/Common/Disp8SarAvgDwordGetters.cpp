// cl: /O1 /arch:SSE /G7 /EHsc /MD
// Disp8 sar-avg dword getters: eight-to-ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / sub eax,[ecx+<DISP2>] / sar eax,<IMM8> / ret
//
// The difference of two dwords at fixed displacements from `this` is
// arithmetically shifted right. MSVC 7.1 emits the disp8 loads `8B 41 XX`
// plus `2B 41 XX`, plus `C1 F8 XX` (or `D1 F8` for shift-by-1), plus `ret`.
// Identity is not recovered: every name is derived from its address.
// The established /O1 /SSE /G7 settings are unchanged; /EHsc supports the
// independently recovered BodyState INI driver below.
#define BFME_DISP8_SAR_AVG_DWORD_GETTER(NAME, DISP1, DISP2, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) >> IMM; \
	}

BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0004582DSarAvgField, 0x18, 0x14, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007E1A6SarAvgField, 0x04, 0x00, 1)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007E6DASarAvgField, 0x0C, 0x08, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007EB32SarAvgField, 0x18, 0x14, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva000B3F52SarAvgField, 0x04, 0x00, 6)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva000B4269SarAvgField, 0x08, 0x00, 6)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00210F8CSarAvgField, 0x44, 0x40, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00219695SarAvgField, 0x34, 0x30, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0021969FSarAvgField, 0x40, 0x3C, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0023D6F0SarAvgField, 0x5C, 0x58, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0029B1D8SarAvgField, 0x04, 0x00, 5)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva002D34F4SarAvgField, 0x08, 0x04, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00329DB4SarAvgField, 0x08, 0x00, 7)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva003B0FC6SarAvgField, 0x10, 0x0C, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0040A7CBSarAvgField, 0x14, 0x10, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00421876SarAvgField, 0x08, 0x00, 5)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva004F607ESarAvgField, 0x08, 0x00, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0052AF7ESarAvgField, 0x30, 0x2C, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0053821BSarAvgField, 0x08, 0x00, 4)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva005AE6EFSarAvgField, 0x04, 0x00, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva005BE245SarAvgField, 0x38, 0x34, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva005D1397SarAvgField, 0x0C, 0x08, 2)

// Native Ghidra [0x003B1017,0x003B1101), 234 bytes, RET 8. BodyState
// list driver: both native worker calls use complete rowed 0x003339CE;
// quoted-token reader and StringBase lifetime/tokenization ABI are the
// same as exact KindOf driver 0x00256499, used as the C++ semantic guide.
// The complete 47-byte append helper at 0x0049B6AE ignores the incoming
// receiver. Reuse its existing opaque member ABI binding without a new
// pin: native sets ECX=this before both appends. The fallback is retail's
// actual one-byte empty string. Original driver name remains unknown.
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

__forceinline const char *GetStr003B1017(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva00256499
{
public:
	void rva00256499Append(const char *s, Rva0033B84ETok *b);
};

class Rva003339CE
{
public:
	bool rva003339CE(const char *token, bool *foundNormal, bool *foundAddOrSub);

private:
	unsigned int m_words[4]; // Native worker clears/accesses the 16-byte bitset.
};

class Rva003B1017 : public Rva003339CE
{
public:
	void rva003B1017(INI *ini, void *extra);
};

void Rva003B1017::rva003B1017(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr003B1017(part);
				((Rva00256499 *)this)->rva00256499Append(s, accum);
				if (!rva003339CE(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva00256499 *)this)->rva00256499Append(token, accum);
			if (!rva003339CE(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
