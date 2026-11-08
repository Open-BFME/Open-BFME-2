// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?Load_HLOD@Rva00970880Proto@@UAEXXZ
// retail 0x0018012A, 242 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/Libraries/Source/WWVegas/WW3D2/Rva00970880Proto_Load_HLOD.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// BFME HLOD catalog prototype loader — retail 0x00970AA0, 288 bytes.
//
// The constructor at 0x00970880 establishes the common BFME prototype
// layout: the base subobject ends at +0x14, the owned prototype at +0x14,
// StringClass name at +0x18, and the two file-open arguments at +0x1c/+0x20.
// The vtable containing this slot is the HLOD catalog entry: it carries the
// HLOD type and the adjacent name/delete slots, while the body below opens
// the named file and constructs an HLodDefClass for chunk 0x700.

#include "../WWLib/StringClassData.h"
inline StringClass::~StringClass() { Free_String(); }
inline StringClass::operator const char *() const { return m_Buffer; }

class BFMEChunkInput
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

class ChunkLoadClass
{
public:
	ChunkLoadClass(BFMEChunkInput *input);
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();

private:
	char m_opaque[0xc18];
};

class HLodDefClass
{
public:
	HLodDefClass();
	~HLodDefClass();
	bool Load_W3D(ChunkLoadClass &cload);

private:
	char m_opaque[0x24];
};

#include "../WWLib/GenBase009EB7D0.h"

class Rva00970880Proto : public GenBase009EB7D0
{
public:
	virtual void Load_HLOD();

private:
	HLodDefClass *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

class File;
File *__cdecl GetGameFilePart(const char *filename, int a, int b);

void Rva00970880Proto::Load_HLOD()
{
	StringClass filename(m_name, false);
	filename += ".w3d";	// the compiler literal at VA 0xBC6860

	BFMEChunkInput *file = (BFMEChunkInput *)GetGameFilePart(
		filename, m_first, m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x700) {
			m_ptr = new HLodDefClass;
			if (!m_ptr->Load_W3D(cload)) {
				delete m_ptr;
				m_ptr = 0;
			}
		}
		file->slot2();
	}
}
