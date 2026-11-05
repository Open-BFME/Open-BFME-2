// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
//
// ??1Rva00098690@@UAE@XZ, retail 0x000986E7..0x0009873C (85 bytes, EH);
// pinned until now as the opaque ??1Rva000986E7@@UAE@XZ. The subsystem whose
// shutdown is the rowed 0x00098690 (Rva00098690Handles.cpp: two particle
// system handles at +0x4C / +0x58, derived from the subsystem base
// Rva00985E4 of SubsystemDerivedDtors.cpp): the destructor shuts it down,
// releases the two handles (an inline test-and-destroy of the folded
// smart-pointer wrapper RvaSmartPtr12, whose out-of-line copy is the
// unwinding target 0x002115C5) and runs the base. Class name address-derived.
#include "../../Include/Common/RvaSmartPtr12.h"

inline RvaSmartPtr12::~RvaSmartPtr12() throw()
{
	if (field00)
		rva0004CBC0();
}

class Rva00985E4
{
public:
	virtual ~Rva00985E4();
private:
	char m_pad04[0x4C - 4];
};

class Rva00098690 : public Rva00985E4
{
public:
	void destroyParticleSystems();
	virtual ~Rva00098690();
private:
	RvaSmartPtr12 m_first; // +0x4C
	RvaSmartPtr12 m_second; // +0x58
};

Rva00098690::~Rva00098690()
{
	destroyParticleSystems();
}
