// cl: /MD
// ??0Rva00572C6E@@QAE@XZ @0x00572C5A 20B evidence: vtable 0x0086E088 store plus base ctor 0x005CB22A with null held; caller 0x0041E682; next-door Rva005CB23CDerived hosts the sibling dtors.
#include "../../Include/Common/Rva005CB22A.h"

class Rva00572C6E : public Rva005CB22A
{
public:
	Rva00572C6E();
	virtual ~Rva00572C6E();
};

Rva00572C6E::Rva00572C6E()
	: Rva005CB22A(0)
{
}
