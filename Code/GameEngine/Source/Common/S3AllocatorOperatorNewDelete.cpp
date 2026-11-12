// BFME1 byte-identical donor: reference/open-bfme-1/Code/GameEngine/Source/Common/S3AllocatorOperatorNewDelete.cpp
// Trimmed to the bodies that reproduce game.dat bytes. Each carried body is a
// separate class operator new/delete through the Gen007EFFC0 allocator; the
// donor names each after its own address rather than guessing pairs.
// ICF note: 0x0065D010 folds the two operator-new twins and 0x0065D030 folds
// the two operator-delete twins, so each address carries a single pick.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(unsigned int size, int flags);
	virtual void release(void *block, int flags);
};

extern GenAlloc *Gen007EFFC0();

#include "../../Include/GameNetwork/Gen007F0130.h"

// ??2Gen007F0130@@SAPAXI@Z
void *Gen007F0130::operator new(unsigned int size)
{
	return Gen007EFFC0()->allocate(size, 0);
}

class Gen007F0170
{
public:
	static void operator delete(void *block);
};

// ??3Gen007F0170@@SAXPAX@Z
void Gen007F0170::operator delete(void *block)
{
	Gen007EFFC0()->release(block, 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??3Gen00809750@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?Gen007F0130@@YAPAXI@Z=??2Gen007F0130@@SAPAXI@Z")
#pragma comment(linker, "/alternatename:??3Gen007E9B10@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007EB140@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F1BF0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F2120@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F2E30@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F33E0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F40C0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F47E0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F4D00@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007F86D0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007FA290@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007FBAF0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen007FCF50@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen008030A0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen00803D10@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen00808FB0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??3Gen0080ACD0@@SAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDeleteVMP@@YAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeTVC@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocUNB@@YAPAXI@Z=??2Gen007F0130@@SAPAXI@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeUNA@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeTYA@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeTWA@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeSizedVF@@YAXPAXI@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeTQD@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeTWC@@YAXPAXH@Z=??3Gen007F0170@@SAXPAX@Z")
#pragma comment(linker, "/alternatename:??2Gen007F0150@@SAPAXI@Z=??2Gen007F0130@@SAPAXI@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocECMa@@YAPAXI@Z=??2Gen007F0130@@SAPAXI@Z")
