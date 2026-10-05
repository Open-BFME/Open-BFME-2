// ?rva0031FC6A@Rva0031FC08@@QAEXV?$StringBase@D@@@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /EHsc /MD
//
// ?rva0031FC6A@Rva0031FC08@@QAEXV?$StringBase@D@@@Z retail 0x0031FC6A 163B
// Rva0031FC08 schemeste slot: finds Entry via rowed rva0031FC08 0x0031FC08
// then divides TheDisplay width/height by Entry m_4/m_8 into floats at +4/+8
// and stores Entry at +0; null clears +0. Caller 0x0031BA80 passes
// ControlBar+0x44 as this. Honest pin name.
// class-gate: allow StringBase by-value copy for 0x0031FC6A needs public copy ctor 0x000365F0; shared header keeps copy private
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
public:
	StringBase(const StringBase<T> &that);
	void toLower();
	int compareNoCase(const StringBase<T> &other) const;
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	BfmeStringData<T> *m_data;
};

template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Entry
{
	StringBase<char> m_name;
	int m_4;
	int m_8;
};

class ControlBarScheme
{
public:
	void init();
};

class Display
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
};

extern Display *TheDisplay;
extern float g_00BC26EC;

struct Node
{
	Node *m_next;
	Node *m_prev;
	Entry *m_data;
};

class Rva0031FC08
{
public:
	Entry *rva0031FC08(StringBase<char> name);
	void rva0031FC6A(StringBase<char> name);
private:
	Entry *m_entry;
	float m_f4;
	float m_f8;
	Node *m_list;
};

// ?rva0031FC6A@Rva0031FC08@@QAEXV?$StringBase@D@@@Z present-unmatched
void Rva0031FC08::rva0031FC6A(StringBase<char> name)
{
	Entry *e = rva0031FC08(name);
	if (e)
	{
		unsigned int w = TheDisplay->getWidth() / (unsigned int)e->m_4;
		m_f4 = (float)w;
		unsigned int h = TheDisplay->getHeight() / (unsigned int)e->m_8;
		m_f8 = (float)h;
		m_entry = e;
	}
	else
	{
		m_entry = 0;
	}
	if (m_entry)
		((ControlBarScheme *)m_entry)->init();
}
