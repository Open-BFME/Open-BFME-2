// ?rva0020202B@Rva0020202B@@QAEPAXH@Z
// cl: /DNDEBUG /MD /EHsc
//
// ?rva0020202B@Rva0020202B@@QAEPAXH@Z, retail 0x0020202B, 45 bytes.
// Fixed-slot pool allocator. The sibling constructor Rva00201EACLODManager
// (Code/GameEngine/Source/Common/Rva00201DC4LODDefaults.cpp) proves the array
// composition this addresses: presets[5][32] of 32-byte stride at +0x208
// (5*32*32 = 0x1000, running 0x208..0x1208) and the pool of five 32-entry
// counters at +0x17AC. The retail body is
//   mov eax,[esp+4]; lea edx,[ecx+eax*4+0x17ac]; push esi; mov esi,[edx];
//   cmp esi,0x20; jge ret0; inc esi; shl eax,5; add eax,esi; shl eax,5;
//   mov [edx],esi; lea eax,[eax+ecx+0x208]
// so the returned slot is pool[index*32 + count+1] and the counter is
// post-incremented: the incremented value is the one stored AND the one added,
// hence `++m_counts[index]` written inline in the return expression. Hoisting
// that increment into a local makes MSVC keep a second live copy (the extra
// `push edi` / `lea edi,[esi+1]`) and swap the lea/push order, which is the
// whole diff against retail.
// Neighbours: prev 0x0020200D RetailBenchProfileAllocator, next 0x002025AC.
// Unlock lane: landing this makes 0x00202E23 ready.
class Rva0020202B
{
public:
	struct Slot
	{
		char data[32];
	};
	char m_pad0[0x208];
	Slot m_pool[160];
	char m_pad1[0x1A4];
	int m_counts[5];
	void* rva0020202B(int index);
};

void* Rva0020202B::rva0020202B(int index)
{
	if (m_counts[index] < 32)
		return (void*)&m_pool[index * 32 + (++m_counts[index])];
	return 0;
}