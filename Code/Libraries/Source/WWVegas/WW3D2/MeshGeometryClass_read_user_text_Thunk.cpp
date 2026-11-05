// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Donor: BFME1 MeshGeometryClass_read_user_text_Thunk.cpp at 0x009252C0.
// Target: read_chunks at 0x0016D340 dispatches chunk 0x0C to this 187B body.
// The reference W3D format names chunk 0x0C MESH_USER_TEXT.
// /G7 reproduces the retail body; the donor class/member labels are retained.

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "chunkio.h"
#include "sharebuf.h"
// bfme link decl-only begin
template <> ShareBufferClass<char>::~ShareBufferClass();
// bfme link decl-only end
// Rowed explicit specialization (MeshGeometryShareBufferInstantiations.cpp, 0x00169E20):
// declared so this unit does not instantiate the generic sharebuf.h destructor.
template<> ShareBufferClass<char>::~ShareBufferClass();

// Target accesses establish the canonical UserText member at +0x14.
// Keep the reference RefCountClass inline definitions and the canonical list base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#include "../WWLib/MultiListObjectClass.h"
#define MULTILIST_H
#include "MeshGeometryClass.h"

// ?read_user_text@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_user_text(ChunkLoadClass & cload)
{
	unsigned int textlen = cload.Cur_Chunk_Length();

	if (UserText != NULL) {
		return true;
	}

	UserText = NEW_REF(ShareBufferClass<char>,(textlen, "MeshGeometryClass::UserText"));

	if (cload.Read(UserText->Get_Array(),textlen) != textlen) {
		return false;
	}
	return true;
}
