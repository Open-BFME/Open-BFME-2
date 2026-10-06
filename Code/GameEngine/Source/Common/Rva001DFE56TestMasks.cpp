// cl: /DNDEBUG /MD
// ?rva001DFE56@Rva001DFE56@@QBE_NPBX0@Z @0x001DFE56 66B
// 19-dword dual-mask tester: (exempt & this)==0 and (required & this)==required.
// Donor: Code/GameEngine/Source/Common/Rva0026157ETestMasks.cpp (4-dword 66B shape)
// plus Code/GameEngine/Source/Common/BitFlags116TestSetAndClear.cpp (7-dword 66B EBP-counter shape).
// Retail walks 0x13 dwords with counter in [ebp-4]; same family as Rva00263546Overlap (19-dword overlap)
// and Rva00271C8ALoop (19-dword merge). Callers pass 76-byte masks at +0x28/+0x74 (0x003EDE16),
// +0x118/+0x164 vs +0x258 (0x004CB333), +0x0C/+0x58 vs +0x258 (0x004CA328), +0x04/+0x50 array stride 0x9C (0x004CBE66).
// Landing unblocks 0x004CBE66 0x004CB333 0x003EDE16 0x004CA328.
class Rva001DFE56
{
public:
	bool rva001DFE56(const void *required, const void *exempt) const;
};

bool Rva001DFE56::rva001DFE56(const void *required, const void *exempt) const
{
	const unsigned *self = (const unsigned *)this;
	const unsigned *need = (const unsigned *)required;
	const unsigned *ban = (const unsigned *)exempt;
	for (unsigned i = 0; i < 19; i++) {
		if ((ban[i] & self[i]) != 0)
			return false;
		if ((need[i] & self[i]) != need[i])
			return false;
	}
	return true;
}
