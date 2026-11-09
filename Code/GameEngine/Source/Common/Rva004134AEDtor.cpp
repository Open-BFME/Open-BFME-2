// cl: /MD /EHs
//
// ??1Rva004134AE@@UAE@XZ, retail 0x004134AE, 53 bytes.
// Virtual dtor over SubsystemInterface with tree member at +0xC; novtable
// omits any intermediate vptr store (matching retail's SEH body).
// Evidence: vtable 0x008399B8 slot 0 (0x00413492 ??_GRva004134AE@@UAEPAXI@Z)
// calls this; retail calls rowed ??1Rva0041331E at 0x00413396 via lea [esi+0xC]
// then rowed ??1SubsystemInterface@@UAE@XZ at 0x001B4E74 with ecx=esi (base at +0);
// EH prolog with and [ebp-4],0 / or [ebp-4],-1 needs /EHs; neighbour 0x004134E3 is
// a method of a class with a map at +0xC in the same directory.

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva0041331E
{
public:
	~Rva0041331E();
};

class __declspec(novtable) Rva004134AE : public SubsystemInterface
{
public:
	virtual ~Rva004134AE();
private:
	Rva0041331E m_tree0C;
};

Rva004134AE::~Rva004134AE()
{
}
