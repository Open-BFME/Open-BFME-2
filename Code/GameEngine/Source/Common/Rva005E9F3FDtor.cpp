// cl: /MD
// ??1Rva005E9F3F@@UAE@XZ retail 0x005E9F3F 14B
// Virtual dtor stores derived vtable then tail-jmps to member clear at +4.
// Layout from caller 0x005E948B deleting wrapper vtable 0x00C780A8#0 and rowed clear 0x005E9E27.
// Evidence: mov [ecx] C780A8 plus add ecx 4 plus jmp clear; twin 0x005E888A 8B plus vptr.

class Rva005E9E27
{
public:
	void clear();
};

class Rva005E9F3F
{
public:
	virtual ~Rva005E9F3F();
private:
	Rva005E9E27 m_04;
};

Rva005E9F3F::~Rva005E9F3F()
{
	m_04.clear();
}
