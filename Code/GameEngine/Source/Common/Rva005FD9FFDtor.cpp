// cl: /MD /Ireference/shims/bfme2_ascii
// ??1Rva005FD9FF@@UAE@XZ @0x005FD9FF 14B
// Virtual dtor storing its vtable then tail-jumping to the +4 holder's rowed
// clear 0x005FD95E (OwnedPointerResets.cpp). Called by the scalar deleting
// dtor 0x005FDA1D via vtable 0x00C7A2E8#0. Prev/next share /O1.
#include "ascii_string.h"
class Rva005FD628;
class Rva005FD95E
{
public:
	Rva005FD95E(Rva005FD628 *value) : m_value(value) {}
	void clear();
private:
	Rva005FD628 *m_value;
};

struct Rva005FDA39Factory;
class Rva005FD9FF
{
public:
	Rva005FD9FF(unsigned level, const AsciiString &name,
		const Rva005FDA39Factory &topPanel, const Rva005FDA39Factory &bottomPanel);
	virtual ~Rva005FD9FF();
private:
	Rva005FD95E m_holder; // +0x04 (vptr at +0x00)
};

Rva005FD9FF::~Rva005FD9FF()
{
	m_holder.clear();
}

// WB identifies the implementation as ArmyUnitSwapperMovieClip::Impl.
// Keep the existing target owner names: 5FDE24 installs the same vtable
// as the rowed 5FD9FF destructor and constructs a 0x50-byte implementation
// at 5FDA39 with owner, level, AsciiString reference and two panel-factory
// references. The callee independently copies the name at +8 and reads the
// two factory references, matching the WB topPanelFactory/bottomPanelFactory
// assertions. Its rowed clear calls the 5FD628 implementation destructor.
class Rva005FD628
{
public:
	Rva005FD628(Rva005FD9FF *owner, unsigned level, const AsciiString &name,
		const Rva005FDA39Factory &topPanel, const Rva005FDA39Factory &bottomPanel);
private:
	char m_storage[0x50];
};

Rva005FD9FF::Rva005FD9FF(unsigned level, const AsciiString &name,
	const Rva005FDA39Factory &topPanel, const Rva005FDA39Factory &bottomPanel)
	: m_holder(new Rva005FD628(this, level, name, topPanel, bottomPanel))
{
}
