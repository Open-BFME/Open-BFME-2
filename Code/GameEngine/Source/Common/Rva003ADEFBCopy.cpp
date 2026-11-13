// cl: /EHs-c-
// ??0Rva003ADEFB@@QAE@ABV0@@Z @0x003ADEFB 38B derived copy via rowed base 0x003ADF21 with three derived vptrs. Evidence: callee rowed; caller 0x003ADEF0; chain from 0x003ADF21 same shape as 0x003ADE32.
class V3Vt01111D90
{
public:
	virtual ~V3Vt01111D90() {}
	int m04;
};
class V3Second08
{
public:
	virtual ~V3Second08() {}
};
class Rva003ADFDB : public V3Vt01111D90, public V3Second08
{
public:
	Rva003ADFDB(const Rva003ADFDB &other);
public:
	virtual ~Rva003ADFDB();	// rowed elsewhere; declared so this unit binds to it
};
// Inline empty destructor, as in V3PolyCopyCtors.cpp: the deleting dtor
// 0x004A10FD in its vtable 0x00C1D264 calls 0x0049B47C, which only restores
// the Snapshot vtable 0x00BBB554.
#include "../../Include/Common/Rva003ADF61.h"
class Rva003ADF21 : public Rva003ADFDB, public Rva003ADF61
{
public:
	Rva003ADF21(const Rva003ADF21 &other);
};
class Rva003ADEFB : public Rva003ADF21
{
public:
	Rva003ADEFB(const Rva003ADEFB &other);
	Rva003ADEFB *rva003ADEDE() const;
};
Rva003ADEFB::Rva003ADEFB(const Rva003ADEFB &other)
	: Rva003ADF21(other)
{
}

// ?rva003ADEDE@Rva003ADEFB@@QBEPAV1@XZ @0x003ADEDE 29B: vtable slot before
// ?rva0055F805 (xfer); allocates 0x38 bytes and copy-constructs this object.
Rva003ADEFB *Rva003ADEFB::rva003ADEDE() const
{
	return new Rva003ADEFB(*this);
}
