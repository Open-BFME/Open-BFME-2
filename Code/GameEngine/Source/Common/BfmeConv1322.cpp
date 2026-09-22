// Open-BFME5 conversion (BfmeConv1322).
//
// An #import-style COM raise wrapper: call the raw interface method through
// the vtable, and on a failed HRESULT hand it to _com_issue_errorex with the
// interface IID. The BFME1 donor named the error helper by placeholder; retail
// calls the matched _com_issue_errorex, declared here with its real signature.
// The donor TU's other bodies have no masked retail match here and are left out.

struct IUnknown;
struct _GUID;
void __stdcall _com_issue_errorex(long hr, IUnknown *punk, const _GUID &riid);

struct BfmeGuidTSA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidTSA g_bfmeIidTSA;

class BfmeThingTSA;

struct BfmeVtTSA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	void *m_bfmeSlot7;
	long (__stdcall *m_bfmeOneTSA)(BfmeThingTSA *self);
};

class BfmeThingTSA
{
public:
	long bfmeGoOneTSA();
	BfmeVtTSA *m_bfmeVt;
};

long BfmeThingTSA::bfmeGoOneTSA()
{
	long hr = m_bfmeVt->m_bfmeOneTSA(this);
	if (hr < 0)
		_com_issue_errorex(hr, (IUnknown *)this, *(const _GUID *)&g_bfmeIidTSA);
	return hr;
}
