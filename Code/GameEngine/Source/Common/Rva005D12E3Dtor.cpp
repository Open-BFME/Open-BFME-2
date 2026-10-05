// cl: /O1 /MD /EHsc
// ??1Rva005D12E3@@UAE@XZ 0x005D12E3 54 dtor calls clear 0x005D127C at +4 vtable 0x00C755B4 base vtable 0x00C75278 via callers 0x005765BF 0x005D131C
class Rva005D127C
{
public:
	void clear();
};

class Rva005D12E3Base
{
public:
	virtual ~Rva005D12E3Base();
};

// ??1Rva005D12E3Base@@UAE@XZ present-unmatched
inline Rva005D12E3Base::~Rva005D12E3Base()
{
}

class Rva005D12E3 : public Rva005D12E3Base
{
public:
	virtual ~Rva005D12E3();
private:
	Rva005D127C m_holder;
};

Rva005D12E3::~Rva005D12E3()
{
	m_holder.clear();
}
