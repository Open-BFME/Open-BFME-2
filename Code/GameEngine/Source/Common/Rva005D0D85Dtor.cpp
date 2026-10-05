// cl: /O1 /MD /EHsc
// ??1Rva005D0D85@@UAE@XZ 0x005D0D85 54 dtor calls clear 0x005D0ABB at +4 vtable 0x00C75590 base vtable 0x00C75278 via callers 0x0057653E 0x005D100A
class Rva005D0ABB
{
public:
	void clear();
};

class Rva005D0D85Base
{
public:
	virtual ~Rva005D0D85Base();
};

// ??1Rva005D0D85Base@@UAE@XZ present-unmatched
inline Rva005D0D85Base::~Rva005D0D85Base()
{
}

class Rva005D0D85 : public Rva005D0D85Base
{
public:
	virtual ~Rva005D0D85();
private:
	Rva005D0ABB m_holder;
};

Rva005D0D85::~Rva005D0D85()
{
	m_holder.clear();
}
