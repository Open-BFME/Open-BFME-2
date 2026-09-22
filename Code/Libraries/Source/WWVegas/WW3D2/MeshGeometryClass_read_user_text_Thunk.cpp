// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Donor: BFME1 MeshGeometryClass_read_user_text_Thunk.cpp at 0x009252C0.
// Target: read_chunks at 0x0016D340 dispatches chunk 0x0C to this 187B body.
// The reference W3D format names chunk 0x0C MESH_USER_TEXT.
// /G7 reproduces the retail body; the donor class/member labels are retained.

#include "chunkio.h"
#include "sharebuf.h"

// Donor layout labels are retained; target accesses establish the +0x14 slot.
class MeshGeometryClass
{
protected:
	bool read_user_text(ChunkLoadClass & cload);

private:
	char pad_00[0x14];
	ShareBufferClass<char> *NameSlot;			// target +0x14; NameSlot is the donor label
};

// ?read_user_text@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_user_text(ChunkLoadClass & cload)
{
	unsigned int textlen = cload.Cur_Chunk_Length();

	if (NameSlot != NULL) {
		return true;
	}

	NameSlot = NEW_REF(ShareBufferClass<char>,(textlen, "MeshGeometryClass::UserText"));

	if (cload.Read(NameSlot->Get_Array(),textlen) != textlen) {
		return false;
	}
	return true;
}
