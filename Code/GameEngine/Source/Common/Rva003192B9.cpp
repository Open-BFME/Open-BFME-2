// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?GetMaxCommandPoints@@YAPAXPAX@Z @0x003192B9 75B: free helper resolving a Value
// via LivingWorld find plus empty-name Owner fallback. Evidence: packet
// disasm with rowed find 0x002B51F8 via g_009FEF10 plus rowed StringBase
// isEmpty at +0x18 plus pinned rva00318C32 plus rowed rva003EFD6F, callers
// 0x003193FF 0x005CF41A 0x005E1A51 0x005E58D4 0x005E63C2 0x005F4B6E 0x005F4C2A,
// neighbour AsciiString-at-+0x18 shape from Rva00319159Get.cpp.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Rva002E2903Player;
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class Rva00318C32Ret;
class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
};

struct Value003EFD6F
{
	char m_pad[4];
};

class Rva003EFD6F
{
public:
	Value003EFD6F *rva003EFD6F(const Rva002E071E *arg);
};

struct Key003192B9
{
	char m_pad00[0x18];
	AsciiString m_str18;
	char m_pad1C[0x54 - 0x1C];
	int m_id54;
};

void *GetMaxCommandPoints(void *keyPtr)
{
	Key003192B9 *key = (Key003192B9 *)keyPtr;
	int id = key->m_id54;
	Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, (unsigned int *)0);
	if (player == 0)
		return 0;
	if (!key->m_str18.isEmpty())
	{
		void *mid = *(void **)((char *)player + 0x40);
		return *(void **)((char *)mid + 0x1C);
	}
	Rva00318C32Ret *owner = ((Rva00318C79Owner *)key)->rva00318C32();
	if (owner == 0)
		return 0;
	return ((Rva003EFD6F *)owner)->rva003EFD6F((const Rva002E071E *)player);
}
