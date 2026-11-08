// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /arch:SSE /G7 /EHsc /MD
//
// ?rva0050C9EF@Rva0050CBA2@@QAE_NPAVRva0013A820@@H@Z
// retail 0x0050C9EF..0x0050CBA2 (435 bytes) thiscall RET 8.
//
// The texture pass of the INIStatsRecord diagnostics (tu_map's proposed
// INIStatsRecord.cpp family; the record, constructor, dump and the 0x0050C91D
// sibling are rowed in BfmeConv1191.cpp). Target facts: it never reads its
// receiver, builds a DynamicVectorClass<StringClass> through the rowed
// constructor 0x00121FE0 and never fills it, walks it backwards comparing
// each entry against the previous name, copies the texture name to the
// record's +0x28 string, checks Render_Obj_Exists, opens
// "Art\Textures\<name>", reads the TGA width, height and depth at offset 12
// through the rowed little-endian helper 0x0050C2BF into +0x2C/+0x30/+0x34
// and accumulates the storage at +0x38, then destroys the vector inline
// (VectorClass vftable store plus the rowed VectorClass::Clear 0x001212B0).
// WorldBuilder 0x00ED8100 is the same diagnostic body (vector.h assert).
// The VectorClass/DynamicVectorClass method surface and 16/24-byte layouts
// are carried from the verified BFME1 WWLib vector.h; the record layout is
// BfmeConv1191.cpp's view. The receiver's original name is unknown.
//
// Split from BfmeConv1191.cpp so that unit keeps linking: the inline vector
// destructor makes this unit emit /O1 copies of the VectorClass<StringClass>
// destructor, scalar deleting destructor and vftable that differ from the
// /O2 WWLib bodies retail kept (retail's own unwind funclet 0x007945AF jumps
// to the WWLib copy at 0x00121E20, so retail's copy of them lost too).

#include "ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
// The diagnostic loop uses the native one-pointer conversion inline.
inline StringClass::operator const char *() const { return m_Buffer; }
#include <stdio.h>

class Rva0013A820
{
public:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	int m_24;
	AsciiString m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	AsciiString m_44;
};

#include "../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/vector.h"
// Existing providers retain the allocating and out-of-line operations.
template <> DynamicVectorClass<StringClass>::DynamicVectorClass(unsigned, const StringClass *);
template <> void VectorClass<StringClass>::Clear();
template <> void DynamicVectorClass<StringClass>::Clear();
template <> bool VectorClass<StringClass>::operator==(const VectorClass<StringClass> &) const;
template <> bool VectorClass<StringClass>::Resize(int, const StringClass *);
template <> bool DynamicVectorClass<StringClass>::Resize(int, const StringClass *);
template <> int VectorClass<StringClass>::ID(const StringClass *);
template <> int VectorClass<StringClass>::ID(const StringClass &);
template <> int DynamicVectorClass<StringClass>::ID(const StringClass *);
template <> int DynamicVectorClass<StringClass>::ID(const StringClass &);
template <> __declspec(dllimport) __forceinline VectorClass<StringClass>::~VectorClass() { VectorClass<StringClass>::Clear(); }

extern bool Render_Obj_Exists(const char *name);
extern int readLittleEndian0013A070(const unsigned char *bytes, int count);

class Rva0050CBA2
{
public:
	bool rva0050C9EF(Rva0013A820 *record, int unused);
};

bool Rva0050CBA2::rva0050C9EF(Rva0013A820 *record, int unused)
{
	DynamicVectorClass<StringClass> textures;
	int count = textures.Count();
	AsciiString previous;
	while (count) {
		StringClass &texture = textures[--count];
		if (previous.compare(texture) == 0)
			continue;
		record->m_28 = texture;
		previous = texture;
		if (!Render_Obj_Exists(record->m_28.str()))
			continue;
		AsciiString path("Art\\Textures\\");
		path += record->m_28.str();
		FILE *file = fopen(path.str(), "rb");
		if (file) {
			fseek(file, 0, 2);
			if (ftell(file)) {
				fseek(file, 12, 0);
				if (ftell(file) == 12) {
					unsigned char widthBytes[2], heightBytes[2], depth;
					fread(widthBytes, 2, 1, file);
					fread(heightBytes, 2, 1, file);
					fread(&depth, 1, 1, file);
					int width = readLittleEndian0013A070(widthBytes, 2);
					record->m_2C = width;
					int height = readLittleEndian0013A070(heightBytes, 2);
					record->m_30 = height;
					record->m_34 = depth;
					record->m_38 += (record->m_34 / 8) * height * width;
				}
			}
			fclose(file);
		}
	}
	return true;
}
