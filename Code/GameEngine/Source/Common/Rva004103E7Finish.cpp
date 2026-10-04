// ??0Rva0045EF90Object@@QAE@XZ
// cl: /O1 /arch:SSE /MD
// ??0Rva0045EF90Object@@QAE@XZ, retail 0x004103E7 58B. Default ctor of
// Rva0045EF90Object (vtable 0x00839630): inlined base ctor sets +4 to -1,
// then the derived vptr store, then the field group (non-trivial member so
// the outer vptr precedes its body).
class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_base((unsigned)-1) {}
	virtual ~Rva0045EF90Base();
protected:
	unsigned m_base;
};

struct Rva0045EF90Fields
{
	void *m_first;
	void *m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_pad25[3];
	void *m_last;
	Rva0045EF90Fields()
		: m_first(0)
		, m_second(0)
		, m_handle(0)
		, m_value24(0)
		, m_last(0)
	{
		m_value14 = -1.0f;
		m_value18 = -1.0f;
		m_value1c = -1.0f;
		m_value20 = -1.0f;
	}
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	virtual ~Rva0045EF90Object();
private:
	Rva0045EF90Fields m_fields;
};

Rva0045EF90Object::Rva0045EF90Object()
{
}
