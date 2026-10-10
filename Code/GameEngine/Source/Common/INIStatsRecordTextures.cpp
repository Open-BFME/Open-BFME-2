// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP=
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
#include "../../../Libraries/Source/WWVegas/WWLib/wwstring.h"

extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) int __cdecl fseek(void *, long, int);
extern "C" __declspec(dllimport) long __cdecl ftell(void *);
extern "C" __declspec(dllimport) unsigned __cdecl fread(void *, unsigned, unsigned, void *);

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
