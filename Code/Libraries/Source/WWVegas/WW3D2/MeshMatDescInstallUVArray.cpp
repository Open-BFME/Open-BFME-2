// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
//
// ?Install_UV_Array@MeshMatDescClass@@QAEXHHPAVVector2@@H@Z,
// retail 0x0015B960 (413 bytes).
// BFME1 meshmatdesc.cpp Install_UV_Array port (their 355B Open-BFME1 clean
// C++ row at 0x0092A560, same QAEXHH/PAVVector2/H signature).
// BFME2 adaptations (all retail-measured from the 0x15B960 body):
// - CRC_Memory takes an explicit init crc (matched 3-arg row
//   ?CRC_Memory@@YAKPBEKK@Z; this body passes 0).
// - The CRC-dedup scan runs only when the pass carries no +0xB8/+0x108 entry
//   (retail gate: either set skips straight to a fresh slot). A CRC hit
//   stores the source index and returns directly (retail has two epilogues).
// - Fresh install via plain operator new (matched ??2@YAPAXI@Z) + the
//   ShareBufferClass<Vector2> base ctor (pinned @0xD1D33) + derived vptr +
//   CRC(-1), inlined memcpy, inlined Update_CRC.
// Uses the canonical MeshMatDescClass.h layout (0x118); the +0xB8/+0x108
// pass slots are its field_B8/field_108.

#include <windows.h>

#include <string.h>

#include "../../../../../reference/shims/wwmath/Vector2.h"

unsigned long CRC_Memory(const unsigned char *data, unsigned long length, unsigned long crc);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// (sharebuf_vector2_copy_ctor.cpp precedent).
#include "../WWLib/RefCountData.h"

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h,
// with BFME's RawBuffer/Alignment pair around Zero Hour's Array and Count
// (sharebuf_vector2_copy_ctor.cpp precedent).
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	~ShareBufferClass();
	Type *Get_Array(void) { return Array; }
	int Get_Count(void) { return Count; }

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;

private:
	// not implemented!
	ShareBufferClass &operator=(const ShareBufferClass &);
};

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
extern const void *const g_007CE338[];
class __declspec(novtable) UVBufferClass : public ShareBufferClass<Vector2>
{
public:
	// Keep the inlined construction here; MatInfoUVBufferO1Inlines owns the retail body.
	__declspec(dllimport) __forceinline UVBufferClass(int count, const char *msg) : ShareBufferClass<Vector2>(count, msg)
	{
		*(const void **)this = g_007CE338;
		CRC = 0xFFFFFFFF;
	}
	virtual ~UVBufferClass();
	unsigned Get_CRC(void) { return CRC; }
	void Update_CRC(void) { CRC = CRC_Memory((const unsigned char *)Get_Array(), Get_Count() * sizeof(Vector2), 0); }

private:
	unsigned CRC;
};

#include "MeshMatDescClass.h"

inline int MeshMatDescClass::Get_UV_Array_Count(void)
{
	int count = 0;
	while ((UV[count] != NULL) && (count < MAX_UV_ARRAYS)) {
		count++;
	}
	return count;
}

inline void MeshMatDescClass::Set_UV_Source(int pass, int stage, int sourceindex)
{
	UVSource[pass][stage] = sourceindex;
}

// ?Install_UV_Array@MeshMatDescClass@@QAEXHHPAVVector2@@H@Z
void MeshMatDescClass::Install_UV_Array(int pass, int stage, Vector2 *uvs, int count)
{
	unsigned int crc = CRC_Memory((const unsigned char *)uvs, count * sizeof(Vector2), 0);

	if (field_B8[pass] == NULL && field_108[pass] == NULL) {
		for (int i = 0; i < Get_UV_Array_Count(); i++) {
			if (UV[i]->Get_CRC() == crc) {
				Set_UV_Source(pass, stage, i);
				return;
			}
		}
	}

	int new_index = 0;
	while ((UV[new_index] != NULL) && (new_index < MAX_UV_ARRAYS)) {
		new_index++;
	}

	if (new_index < MAX_UV_ARRAYS) {
		UV[new_index] = new UVBufferClass(count, "MeshMatDescClass::UV");
		memcpy(UV[new_index]->Get_Array(), uvs, count * sizeof(Vector2));
		UV[new_index]->Update_CRC();
		if (field_B8[pass] == NULL && field_108[pass] == NULL) {
			Set_UV_Source(pass, stage, new_index);
		}
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_007CE338@@3QBQBXB=??_7UVBufferClass@@6B@")
