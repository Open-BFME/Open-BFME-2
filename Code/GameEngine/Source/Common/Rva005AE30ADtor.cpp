// cl: /DNDEBUG /MD
// ??1Rva005AE30A@@UAE@XZ @0x005AE30A 21B evidence: vtable 0x008726A0 store at [this] plus second vtable 0x0087269C store at +0x218 plus tail-jmp to pinned base dtor ??1AptMessenger@@UAE@XZ @0x005125ED; caller scalar deleting dtor @0x005AE38A; ghidra 21B vs 128B trust ret plus int3 gate
class AptMessengerPrimary
{
public:
	virtual ~AptMessengerPrimary();
	unsigned char m_pad[0x214];
};

#include "../../Include/GameClient/Rva005248D0.h"

class AptMessenger : public AptMessengerPrimary, public Rva005248D0
{
public:
	virtual ~AptMessenger();
};

class Rva005AE30A : public AptMessenger
{
public:
	virtual ~Rva005AE30A();
};

Rva005AE30A::~Rva005AE30A()
{
}
