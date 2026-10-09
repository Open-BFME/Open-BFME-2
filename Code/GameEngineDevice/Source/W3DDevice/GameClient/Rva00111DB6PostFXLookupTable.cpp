// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva00111DB6@Rva00111DB6@@QAEXXZ
// Retail 0x00111DB6..0x00111F02 (332 bytes).
// Rebuilds the post-FX lookup-table shader held at +8: under the DX8 device
// lock it walks the 0x1C-byte entries of the list at +4 of the singleton
// returned by Rva00102215Get (rowed 0x00102215 / lea getter 0x005C4AD1);
// an entry named "BlendFactor" adds a type-2 parameter carrying the entry's
// Real (+8) and one named "LookupTexture" adds a type-1 parameter carrying the
// entry's string (+0x18); then the "PostFX_LookupTable.fx" / "Default"
// setup is created from that list (technique index 4) into the holder.
// Evidence: WorldBuilder 0x007767F0 has the same literals calls and order
// (DXWrapper::_ThreadAcquireDirectX lock; strlen+compare string equality).
// Shapes and providers follow W3DWaterDepthShaderGetter.cpp (DX8 lock and
// RefCountPtr holder assignment 0x00072A94 with inline release) and
// W3DUtility.cpp / simplestreakrender.cpp (36-byte parameter record: rowed
// ctor 0x001512F1 / string setter 0x00151288 / dtor 0x0007BB16 / list
// push_back 0x00082EB8 / list dtor 0x0007C5D5 / factory 0x00152C47).
// The owner class and method name are address-derived.
#include <vector>
#include "ascii_string.h"

class RefCountClass
{
public:
	virtual void Delete_This();
	void Release_Ref() { --NumRefs; if (!NumRefs) Delete_This(); }
private:
	int NumRefs;
};
class FXShaderSetup : public RefCountClass {};
template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};
class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &);
};

struct BfmeAssignRecord36
{
	BfmeAssignRecord36(const char *name, int type);
	unsigned char m_prefix[12];
	float m_value; // +0x0C
	unsigned char m_rest[20];
};

struct Rva0007BB16Record
{
	Rva0007BB16Record(const char *name, int type) : m_record(name, type) {}
	~Rva0007BB16Record();
	BfmeAssignRecord36 m_record;
};

namespace _STL {
template <> vector<Rva0007BB16Record>::~vector();
}

struct Rva00082EB8Rec;
class Rva00082EB8 : public _STL::vector<Rva0007BB16Record>
{
public:
	void rva00082EB8(const Rva00082EB8Rec &record);
};

class Rva00151288
{
public:
	void rva00151288(const char *text);
};

RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *file, const char *technique,
	const _STL::vector<Rva0007BB16Record> *parameters, int index);

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct Rva00111DB6Entry
{
	AsciiString m_name;    // +0x00
	int m_04;
	float m_real;          // +0x08
	unsigned char m_pad0C[0x0C];
	AsciiString m_text;    // +0x18
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Rva001021F7;
Rva001021F7 *Rva00102215Get();

class Rva00111DB6
{
public:
	void rva00111DB6();
private:
	void *m_00;
	void *m_04;
	RefCountPtr<FXShaderSetup> m_lookupShader; // +0x08
};

void Rva00111DB6::rva00111DB6()
{
	BFMEDX8DeviceLock lock;
	Rva00082EB8 parameters;
	_STL::vector<Rva00111DB6Entry> *entries = (_STL::vector<Rva00111DB6Entry> *)
		((Rva005C4AD1LeaField *)Rva00102215Get())->get();
	for (Rva00111DB6Entry *entry = entries->begin(); entry != entries->end(); ++entry)
	{
		if (entry->m_name.compare("BlendFactor") == 0)
		{
			Rva0007BB16Record parameter("BlendFactor", 2);
			parameter.m_record.m_value = entry->m_real;
			parameters.rva00082EB8(*(const Rva00082EB8Rec *)&parameter);
		}
		else if (entry->m_name.compare("LookupTexture") == 0)
		{
			Rva0007BB16Record parameter("LookupTexture", 1);
			((Rva00151288 *)&parameter)->rva00151288(entry->m_text.str());
			parameters.rva00082EB8(*(const Rva00082EB8Rec *)&parameter);
		}
	}
	*(Rva00072A94 *)&m_lookupShader = (const Rva00072A94 &)
		Rva00152C47_CreateFXShaderSetup("PostFX_LookupTable.fx", "Default", &parameters, 4);
}
