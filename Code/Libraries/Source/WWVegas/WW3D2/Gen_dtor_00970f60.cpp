// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	~StringClass() { Free_String(); }
	char *m_buffer;
private:
	void Free_String();
};

class Rva009EB810TailBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void Load();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual ~Rva009EB810TailBase();

private:
	char m_pad[0x10];
};

class Gen_dtor_00970f60Held
{
public:
	virtual void destroy();
	int m_refs;
};

class Gen_dtor_00970f60 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00970f60();
	virtual void Load();

private:
	Gen_dtor_00970f60Held *m_ptr;
	StringClass m_name;
	int m_unk1C;
	int m_unk20;
};

extern "C" char *__cdecl _mbscpy(char *, const char *);
extern "C" char *__cdecl _mbscat(char *, const char *);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);
void *__cdecl operator new(unsigned int);

// Same chunk reader view as the verified sibling factory at 0x001808B0.
#include "../../../../GameEngine/Include/Common/File.h"
class FileClass;
File *__cdecl GetGameFilePart(const char *, int, int);
#include "../WWLib/ChunkLoadClass.h"

// Reduced primary-interface view. The verified MeshClass constructor and
// Clone establish size 0x324; RefCountClass occupies the primary vptr and +4.
// Construction and loading use their existing out-of-line definitions.
class MeshClass
{
public:
	virtual void Delete_This();
	int m_refs;
	MeshClass();
	bool Load_W3D(ChunkLoadClass &);
private:
	unsigned char m_rest[0x324 - 8];
};

// WorldBuilder MeshAsset::Factory::Load (meshasset.cpp), primary vtable
// 0x007D4F90 slot 2. Retail proves name +18, opener flags +1C/+20,
// MeshClass size 0x324, chunk id zero and the failure release at +14.
void Gen_dtor_00970f60::Load()
{
	char buf[0x104];
	_mbscpy(buf, m_name.m_buffer);
	char *dot = strchr(buf, '.');
	if (dot)
		_mbscpy(dot, ".w3d");
	else
		_mbscat(buf, ".w3d");
	File *file = GetGameFilePart(buf, m_unk1C, m_unk20);
	if (file) {
		// The chunk reader retains its legacy slot-compatible stream view.
		ChunkLoadClass chunk((BFMEChunkInput *)file);
		if (chunk.Open_Chunk() && chunk.Cur_Chunk_ID() == 0) {
			MeshClass *mesh = new MeshClass;
			m_ptr = reinterpret_cast<Gen_dtor_00970f60Held *>(mesh);
			if (!mesh->Load_W3D(chunk)) {
				Gen_dtor_00970f60Held *ptr = m_ptr;
				if (--ptr->m_refs == 0)
					ptr->destroy();
				m_ptr = 0;
			}
		}
		file->close();
	}
}

Gen_dtor_00970f60::~Gen_dtor_00970f60()
{
	Gen_dtor_00970f60Held *ptr = m_ptr;
	if (ptr && --ptr->m_refs == 0)
		ptr->destroy();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot00@Rva009EB810TailBase@@UAEXXZ=?get@Rva002A79A1DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?slot04@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot0C@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot14@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot1C@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot10@Rva009EB810TailBase@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot18@Rva009EB810TailBase@@UAEXXZ=?Rva0014CDCB_ReleaseTree@Rva0014CD63_Prototype@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot20@Rva009EB810TailBase@@UAEXXZ=?Delete@AssetFactoryBase@@UAEXXZ")
