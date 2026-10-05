// cl: /O2 /G7 /DNDEBUG /MD
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
// Dedicated TU: the shared header MeshMatDesc is 0xF4, retail is 0x118
// (PostProcess precedent); this TU carries the 0x118 mirror (proven offsets:
// UVSource at +0x30, Shader/ShaderArray at +0x98/+0xF8, Material/MaterialArray
// at +0xA8/+0xE8, all from the landed sibling TUs).

#include <string.h>

#ifndef NULL
#define NULL 0
#endif

class Vector2
{
public:
	float X;
	float Y;
};

unsigned long CRC_Memory(const unsigned char *data, unsigned long length, unsigned long crc);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// (sharebuf_vector2_copy_ctor.cpp precedent).
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass();

private:
	int NumRefs;
};

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
	UVBufferClass(int count, const char *msg) : ShareBufferClass<Vector2>(count, msg)
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

void *operator new(unsigned int size);

class MeshMatDescClass
{
public:
	enum
	{
		MAX_PASSES = 4,
		MAX_TEX_STAGES = 2,
		MAX_UV_ARRAYS = MAX_PASSES * MAX_TEX_STAGES
	};

	void Install_UV_Array(int pass, int stage, Vector2 *uvs, int count);

	int Get_UV_Array_Count(void)
	{
		int count = 0;
		while ((UV[count] != NULL) && (count < MAX_UV_ARRAYS)) {
			count++;
		}
		return count;
	}

	void Set_UV_Source(int pass, int stage, int sourceindex)
	{
		UVSource[pass][stage] = sourceindex;
	}

private:
	char m_pad0[0x10];
	UVBufferClass *UV[MAX_UV_ARRAYS];
	int UVSource[MAX_PASSES][MAX_TEX_STAGES];
	char m_pad1[0xB8 - 0x50];
	// Pass-indexed slots at +0xB8/+0x108 (true identity open): when either is
	// set for the pass, retail skips the CRC-dedup scan and allocates fresh.
	void *m_dedupBypassA[MAX_PASSES];
	char m_pad2[0x108 - 0xC8];
	void *m_dedupBypassB[MAX_PASSES];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

// ?Install_UV_Array@MeshMatDescClass@@QAEXHHPAVVector2@@H@Z
void MeshMatDescClass::Install_UV_Array(int pass, int stage, Vector2 *uvs, int count)
{
	unsigned int crc = CRC_Memory((const unsigned char *)uvs, count * sizeof(Vector2), 0);

	if (m_dedupBypassA[pass] == NULL && m_dedupBypassB[pass] == NULL) {
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
		if (m_dedupBypassA[pass] == NULL && m_dedupBypassB[pass] == NULL) {
			Set_UV_Source(pass, stage, new_index);
		}
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_007CE338@@3QBQBXB=??_7UVBufferClass@@6B@")
