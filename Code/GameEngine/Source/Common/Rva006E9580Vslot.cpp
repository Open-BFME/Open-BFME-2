// cl: /O2 /DNDEBUG /MD /EHsc
// ?rva006E9580@Rva006E9580@@QAE_NHPAVEAStringC@@PAVBfmeAptValue006DCD20@@@Z @ 0x006E9580, 333B.
// vslot slot 8 (offset 0x20) of vtable 0x008EC85C (class of ??1S4Dtor00587B30@@UAE@XZ).
// Evidence: two EAStringC members at +0x20/+0x24 (dtor destroys both via 0x006D3010);
// string literals "message"/"name"; rowed EAStringC helpers and Rva006CC110Log;
// Apt assert globals. First stack arg unused (virtual override shape, ret 0xc).

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	EAStringC &clear();
	bool rva006D3490(const char *text) const;
	bool rva006D3510(const char *text) const;
	EAStringC &Assign(const EAStringC &other);
	const char *rva00620090() const;
	~EAStringC();
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	void rva006DD6C0(EAStringC *pBuffer);
};

void __cdecl Rva006CC110Log(int level, const char *fmt, ...);
extern const char g_00CEC838[];
extern const char g_00BBFDDC[];
extern const char g_00CEC710[];
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006E9580
{
public:
	bool rva006E9580(int, EAStringC *pName, BfmeAptValue006DCD20 *pValue);

private:
	char m_pad[0x20];
	EAStringC m_message;
	EAStringC m_name;
};

bool Rva006E9580::rva006E9580(int, EAStringC *pName, BfmeAptValue006DCD20 *pValue)
{
	if (pName->rva006D3490("message")) {
		EAStringC tmp;
		pValue->rva006DD6C0(&tmp);
		m_message.Assign(tmp);
		return true;
	}
	if (pName->rva006D3490("name")) {
		EAStringC tmp;
		pValue->rva006DD6C0(&tmp);
		m_name.Assign(tmp);
		return true;
	}
	if (pName->rva006D3510("message") || pName->rva006D3510("name")) {
		Rva006CC110Log(3, g_00CEC838, pName->rva00620090());
		g_bfmeAptAssertAtE17734(g_00BBFDDC, g_00CEC710, 0x518);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return false;
}
