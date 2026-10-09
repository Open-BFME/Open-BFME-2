// cl: /DNDEBUG /MD /EHsc

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
	virtual void rva00180274();
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
	virtual void rva00180274();

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
class BFMEChunkInput
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual int Read(void *, int);
	virtual void f4();
	virtual int Seek(int, int);
};
class File : public BFMEChunkInput {};
class FileClass;
File *__cdecl GetGameFilePart(const char *, int, int);
struct ChunkHeader
{
	ChunkHeader() : ChunkType(0), ChunkSize(0) {}
	unsigned int ChunkType, ChunkSize;
};
struct MicroChunkHeader
{
	MicroChunkHeader() {}
	unsigned char ChunkType, ChunkSize;
};
class ChunkLoadClass
{
public:
	ChunkLoadClass(BFMEChunkInput *);
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
private:
	FileClass *File;
	BFMEChunkInput *Input;
	int StackIndex;
	unsigned int PositionStack[256];
	ChunkHeader HeaderStack[256];
	bool InMicroChunk;
	int MicroChunkPosition;
	MicroChunkHeader MCHeader;
};

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
void Gen_dtor_00970f60::rva00180274()
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
		ChunkLoadClass chunk(file);
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
		file->f2();
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
