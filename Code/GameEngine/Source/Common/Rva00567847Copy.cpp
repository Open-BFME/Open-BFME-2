// cl: /MD
//
// ??0Rva00567847@@QAE@ABV0@@Z @0x00567CA6 39B: copy constructor of the
// two-field class whose constructor is the rowed ??0Rva00567847 (0x00567847,
// vtable 0x00C6CED8; see Rva0059B7CBCtor.cpp). It runs the rowed vtable-only
// base copy Rva00567860 (0x00567860), installs vtable 0x00C6CED8 and copies the
// fields at +4/+8. Caller 0x00567FDD (new then copy). Names are address-derived.

#include "../../Include/Common/Rva00567860.h"

class Rva00567847 : public Rva00567860
{
public:
	Rva00567847(const Rva00567847 &other);
	// As Rva0059B7CBCtor.cpp's view, so both units emit one vtable copy.
	virtual void slot00() {}

private:
	unsigned int m_04;
	unsigned int m_08;
};

Rva00567847::Rva00567847(const Rva00567847 &other) :
	Rva00567860(other),
	m_04(other.m_04),
	m_08(other.m_08)
{
}
