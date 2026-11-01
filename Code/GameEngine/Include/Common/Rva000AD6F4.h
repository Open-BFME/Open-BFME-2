// Target facts: RVA 0x000AD6F4 (29 bytes), shared by clear and the nonvirtual destructor, loads and clears the held pointer at +0, calls the pointee's slot 0 with flag 0 and frees its result. The holder has no virtual functions or base; the indirect call belongs to the pointee, not the holder.
// RVA 0x0057621A constructs adjacent holders at +0x28/+0x2C with zero pointer stores; destructor 0x00575F38 calls 0x000AD6F4 on each, proving four-byte storage. RVA 0x002E40DB constructs a pointer owner without a vptr store. RVA 0x002E3E2A (39 bytes) transfers its +0 pointer into a four-byte return object and clears the source.
// RVA 0x00405AC9 (65 bytes) is the ledger's assignment from _STL::auto_ptr<BfmeThingGX> by value: it releases the argument into +0, destroys the old pointee and returns this. The destructor, clear, transfer and assignment stay out of line. m_ptr is a neutral pointer label; no original class or field name is established.
#pragma once

#ifndef BFME2_COMMON_RVA000AD6F4_H
#define BFME2_COMMON_RVA000AD6F4_H

class BfmeThingGX;
class Rva002E3E2AOut;
namespace _STL { template<class T> struct auto_ptr; }

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	explicit Rva000AD6F4(void *object) : m_ptr(object) {}
	~Rva000AD6F4();
	void clear();
	Rva002E3E2AOut rva002E3E2A();
	Rva000AD6F4 &operator=(_STL::auto_ptr<BfmeThingGX> object);

	void *m_ptr;
};

#endif
