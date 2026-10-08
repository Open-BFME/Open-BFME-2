// cl: /MD
// ??1Rva005FD9FF@@UAE@XZ @0x005FD9FF 14B
// Virtual dtor storing its vtable then tail-jumping to the +4 holder's rowed
// clear 0x005FD95E (OwnedPointerResets.cpp). Called by the scalar deleting
// dtor 0x005FDA1D via vtable 0x00C7A2E8#0. Prev/next share /O1.
class Rva005FD95E
{
public:
	void clear();
};

class Rva005FD9FF
{
public:
	virtual ~Rva005FD9FF();
private:
	Rva005FD95E m_holder; // +0x04 (vptr at +0x00)
};

Rva005FD9FF::~Rva005FD9FF()
{
	m_holder.clear();
}
