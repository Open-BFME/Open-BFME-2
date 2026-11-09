// cl: /MD
// ??_GRva004134AE@@UAEPAXI@Z @0x00413492 28B: scalar deleting dtor calling rowed ??1Rva004134AE at 0x004134AE plus rowed operator delete 0x0002FD60.
// Evidence: vtable 0x008399B8 slot 0 calls 0x004134AE (virtual dtor); SubsystemInterface overrides match Rva004134AECtor.cpp's 14-slot 0x008399B8 table.
struct EmitVtableTag;

#define BFME_SUBSYSTEM_SLOTS
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva004134AE : public SubsystemInterface
{
public:
	Rva004134AE(EmitVtableTag *);
	virtual ~Rva004134AE();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
};

// ?<Rva004134AE::Rva004134AE> absent-from-retail
Rva004134AE::Rva004134AE(EmitVtableTag *) {}
