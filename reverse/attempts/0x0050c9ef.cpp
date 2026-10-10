// ?rva0050C9EF@Rva0050CBA2@@QAE_NPAVRva0013A820@@H@Z
// partial score=1.0 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP=
// Open-BFME5 conversions.
// Native dump50C69D loads the fprintf IAT at00BBA5C4; use that import
// instead of an unresolved synthetic global. The ten four-byte handles use
// BFME2's shared AsciiString: their native destructor calls all target the
// complete releaseBuffer worker36410. All home bodies retain exact bytes.
// Original diagnostic owner names remain address-derived donor views.

#include "ascii_string.h"
extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);


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

	void reset();
};

class INIStatsRecord : public Rva0013A820
{
public:
	INIStatsRecord(const char *filename);
	~INIStatsRecord();
	void bfmeDump1191(void);
	void rva0050C90D();
	char *m_bfme48;
};

INIStatsRecord::INIStatsRecord(const char *filename)
{
	reset();
	m_bfme48 = (char *)fopen(filename, "w+");
	GetLastError();
	fprintf(m_bfme48, "Thing,Class,Draw,Tag,Model,Verts,Polys,Skel,Anim,Frames,Texture,Width,Height,Depth,TexTotl,File,Line,Desc\n");
}

// ??1BfmeD1191@@QAE@XZ @0x0050C688
INIStatsRecord::~INIStatsRecord()
{
	fclose(m_bfme48);
}

void INIStatsRecord::bfmeDump1191(void)
{
	const char *s0 = m_00.str();
	int (__cdecl *fn)(void *dst, const char *fmt, ...) = fprintf;

	fn(m_bfme48, (char *)"%s,", s0);
	fn(m_bfme48, (char *)"%s,", m_04.str());
	fn(m_bfme48, (char *)"%s,", m_08.str());
	fn(m_bfme48, (char *)"%s,", m_0C.str());
	fn(m_bfme48, (char *)"%s,", m_10.str());
	fn(m_bfme48, (char *)"%d,", m_14);
	fn(m_bfme48, (char *)"%d,", m_18);
	fn(m_bfme48, (char *)"%s,", m_1C.str());
	fn(m_bfme48, (char *)"%s,", m_20.str());
	fn(m_bfme48, (char *)"%d,", m_24);
	fn(m_bfme48, (char *)"%s,", m_28.str());
	fn(m_bfme48, (char *)"%d,", m_2C);
	fn(m_bfme48, (char *)"%d,", m_30);
	fn(m_bfme48, (char *)"%d,", m_34);
	fn(m_bfme48, (char *)"%d,", m_38);
	fn(m_bfme48, (char *)"%s,", m_3C.str());
	fn(m_bfme48, (char *)"%d,", m_40);
	fn(m_bfme48, (char *)"%s\n", m_44.str());
}

// Native50C90D..50C91D16B calls diagnostic dump50C69D then tailcalls reset50C45A
// on the same receiver. Both complete callees already verify in their homes.
// This establishes dump/reset behavior and the consumed existing record view;
// the wrapper's original name is unknown. No adjacency-based type claim.
void INIStatsRecord::rva0050C90D()
{
    bfmeDump1191();
    reset();
}

// Native string copy-outs use the same shared four-byte AsciiString contract.
class ModuleInfo
{
public:
    AsciiString getNthName(int index) const;
};

class Rva0050C807
{
public:
    AsciiString rva0050C807(int index) const;
};

class Rva000B4A9F
{
public:
    const char *rva000B4A9F();
};

extern const char *const BfmeThingClassNames[];

class Rva0050CBA2
{
public:
    bool rva0050C9EF(Rva0013A820 *record, int unused);
    bool rva0050C91D(Rva0013A820 *record, ModuleInfo *modules,
                     const void *thing, Rva000B4A9F *draw, int index);
};

bool Rva0050CBA2::rva0050C91D(Rva0013A820 *record, ModuleInfo *modules,
                              const void *thing, Rva000B4A9F *draw, int index)
{
    record->m_00.setCopyInline(*(const AsciiString *)((const char *)thing + 0x64));
    record->m_04 = BfmeThingClassNames[*(const signed char *)((const char *)thing + 0x5F6)];
    record->m_08 = modules->getNthName(index);
    record->m_0C = ((const Rva0050C807 *)modules)->rva0050C807(index);
    // This existing helper's pointer names a four-byte string handle: the
    // native caller passes it to StringBase::set(copy), not set(characters).
    record->m_10.setCopyInline(*(const AsciiString *)draw->rva000B4A9F());
    record->m_1C.setCopyInline(*(const AsciiString *)((const char *)draw + 0x58));
    if (((const StringBase<char> *)&record->m_10)->isEmpty()) {
        record->reset();
        return false;
    }
    return true;
}


// Reference VectorClass/DynamicVectorClass method surface and 16/24-byte
// layouts from the verified BFME1 WWLib vector.h; existing native StringClass
// providers instantiate the constructor and virtual methods. Native50C9EF
// calls the constructor out of line and does not populate this vector.
#include "../../../Libraries/Source/WWVegas/WWLib/wwstring.h"

template<class T> class VectorClass
{
public:
    VectorClass(int size = 0, const T *array = 0);
    virtual ~VectorClass() { VectorClass<T>::Clear(); }
    virtual bool operator==(const VectorClass<T> &) const;
    virtual bool Resize(int size, const T *array = 0);
    virtual void Clear();
    virtual int ID(const T *pointer);
    virtual int ID(const T &object);
    T &operator[](int index) { return m_array[index]; }
protected:
    T *m_array;
    int m_capacity;
    bool m_valid, m_allocated, m_padding[2];
};

template<class T> class DynamicVectorClass : public VectorClass<T>
{
public:
    DynamicVectorClass(unsigned size = 0, const T *array = 0);
    virtual bool Resize(int size, const T *array = 0);
    virtual void Clear();
    virtual int ID(const T *pointer);
    virtual int ID(const T &object);
    int Count() const { return m_count; }
protected:
    int m_count, m_growth;
};

extern bool Render_Obj_Exists(const char *name);
extern int readLittleEndian0013A070(const unsigned char *bytes, int count);
extern "C" __declspec(dllimport) int __cdecl fseek(void *, long, int);
extern "C" __declspec(dllimport) long __cdecl ftell(void *);
extern "C" __declspec(dllimport) unsigned __cdecl fread(void *, unsigned, unsigned, void *);

// Target evidence: full50C9EF..50CBA2 body, RET8, no receiver read;
// WorldBuilder's corresponding diagnostic body ed8100 confirms the texture
// dimensions/file-reading purpose. The retail vector is deliberately empty.
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
        void *file = fopen(path.str(), "rb");
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
