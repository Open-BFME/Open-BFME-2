// cl: /DNDEBUG /MD
//
// LANGameSlot::isLocalPlayer, retail 0x0044770F (100 bytes). Zero Hour's isHuman() && TheLAN &&
// local IP == slot IP, where BFME 2 compares 8-byte addresses: TheLAN vslot 64 returns the local
// BfmeNetAddress, the slot's own is at +0x38; both go through the pinned
// BfmeNetAddress::Rva00248CBF, and on a mismatch the local address is tried once more with the
// port raised by 8. Callers: LANGameInfo::getLocalSlotNum (rowed, LANGameInfoSlots.cpp) and
// LANGameInfo::amIHost.
//
// Schedule note (W7-S2 r14, measured on toys): retail copies the 8-byte local address with BOTH
// dword loads ahead of the two stores and then adds 8 to the port in memory ("add word ptr
// [ebp-4],8"). The natural aggregate copy gives load/store/load/store; copying through volatile
// dword loads and stores gives load/load/store/store, and a compiler barrier before the port
// update stops cl from forwarding the stored dword into a register add.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
#include "../../Include/GameNetwork/BfmeNetAddress.h"
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
struct LANAPISlot64View : public VSlots<64>
{
	virtual const BfmeNetAddress *GetLocalAddress(void) = 0;
};
class LANAPI;
extern LANAPI *TheLAN;
#include "../../Include/GameNetwork/GameInfo.h"
class LANGameSlot : public GameSlot
{
public:
	Bool isLocalPlayer(void) const;
};

Bool LANGameSlot::isLocalPlayer(void) const
{
	if (isHuman() && TheLAN)
	{
		// The canonical base stores the address at +0x38/+0x3C.
		const BfmeNetAddress *address = (const BfmeNetAddress *)&m_field38;
		if (((LANAPISlot64View *)TheLAN)->GetLocalAddress()->Rva00248CBF(address))
			return true;
		BfmeNetAddress alternate;
		{
			const UnsignedInt *source = (const UnsignedInt *)((LANAPISlot64View *)TheLAN)->GetLocalAddress();
			UnsignedInt first = ((volatile UnsignedInt *)source)[0];
			UnsignedInt second = ((volatile UnsignedInt *)source)[1];
			*(volatile UnsignedInt *)&((UnsignedInt *)&alternate)[0] = first;
			*(volatile UnsignedInt *)&((UnsignedInt *)&alternate)[1] = second;
		}
		_ReadWriteBarrier();
		alternate.port += 8;
		return alternate.Rva00248CBF(address);
	}
	return false;
}
