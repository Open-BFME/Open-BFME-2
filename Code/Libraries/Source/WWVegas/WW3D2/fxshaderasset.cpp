// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?Load@Impl@FXShaderAsset@@QAEXPBD@Z @ 0x00151915 (963 bytes): the effect
// loader behind slot 3 of the asset vtable 0x00BD3A6C (wrapper 0x00151CD8
// passes slot 0's name and then sets bit 0x04000000 of the asset flags).
// Target evidence: the D3DX macro table "_WW3D_" / "_WW3D_VERSION_"="1" /
// "_W3DVIEW_", the "Shaders/Compiled/<name>o" and "Shaders/<name>" paths,
// the d3dx9_27 imports D3DXCreateEffect (IAT 0x00BBA9EC) and
// D3DXCreateEffectFromFileA (IAT 0x00BBA9F0), the effect at +4 released
// through slot 2 on failure, the 0x14-byte FXShaderParameterBinder at +8
// (rowed ctor 0x00154058), the 0x24-byte parameter records pushed into the
// vector at +0x0C (rowed push_back 0x0007D9EC, dtor 0x0007BB16), the
// validated techniques pushed into the vector at +0x18 (rowed push_back
// 0x004DFCB0) and the "_CreateShadowMap" technique stored at +0x24, all under
// the DX8 thread lock (rows 0x0011F520 / 0x00120F50). Interface slot offsets
// are the d3dx9effect.h ID3DXEffect order. The byte at 0x00DF6F0C is read
// only here and never written by code: it adds "_W3DVIEW_" and skips the
// precompiled path, so its name is a structural inference.

#define _strcmpi _stlport_hides_strcmpi
#include <vector>
#undef _strcmpi
#include "ascii_string.h"

extern "C" {
char *__cdecl strcpy(char *d, const char *s);
char *__cdecl strcat(char *d, const char *s);
__declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
}

typedef long HRESULT;
typedef const char *D3DXHANDLE;
typedef int BOOL;

struct IDirect3DDevice8;

struct D3DXMACRO
{
	const char *Name;
	const char *Definition;
};

struct D3DXEFFECT_DESC
{
	const char *Creator;
	unsigned int Parameters;
	unsigned int Techniques;
	unsigned int Functions;
};

struct D3DXPARAMETER_DESC
{
	const char *Name;
	const char *Semantic;
	int Class;
	int Type;
	unsigned int Rows;
	unsigned int Columns;
	unsigned int Elements;
	unsigned int Annotations;
	unsigned int StructMembers;
	unsigned int Flags;
	unsigned int Bytes;
};

enum
{
	D3DXPT_BOOL = 1,
	D3DXPT_INT = 2,
	D3DXPT_FLOAT = 3
};

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n()

struct ID3DXBuffer
{
	FX_SLOT(00);
	FX_SLOT(01);
	virtual unsigned long __stdcall Release();
};

struct ID3DXEffect
{
	FX_SLOT(00);
	FX_SLOT(01);
	virtual unsigned long __stdcall Release();
	virtual HRESULT __stdcall GetDesc(D3DXEFFECT_DESC *desc);
	virtual HRESULT __stdcall GetParameterDesc(D3DXHANDLE param, D3DXPARAMETER_DESC *desc);
	FX_SLOT(05);
	FX_SLOT(06);
	FX_SLOT(07);
	virtual D3DXHANDLE __stdcall GetParameter(D3DXHANDLE param, unsigned int index);
	FX_SLOT(09);
	FX_SLOT(10);
	FX_SLOT(11);
	virtual D3DXHANDLE __stdcall GetTechnique(unsigned int index);
	virtual D3DXHANDLE __stdcall GetTechniqueByName(const char *name);
	FX_SLOT(14);
	FX_SLOT(15);
	FX_SLOT(16);
	FX_SLOT(17);
	FX_SLOT(18);
	virtual D3DXHANDLE __stdcall GetAnnotationByName(D3DXHANDLE object, const char *name);
	FX_SLOT(20);
	FX_SLOT(21);
	FX_SLOT(22);
	virtual HRESULT __stdcall GetBool(D3DXHANDLE param, BOOL *b);
	FX_SLOT(24);
	FX_SLOT(25);
	FX_SLOT(26);
	virtual HRESULT __stdcall GetInt(D3DXHANDLE param, int *n);
	FX_SLOT(28);
	FX_SLOT(29);
	FX_SLOT(30);
	FX_SLOT(31);
	FX_SLOT(32);
	FX_SLOT(33);
	FX_SLOT(34);
	virtual HRESULT __stdcall GetVector(D3DXHANDLE param, float *vector);
	FX_SLOT(36);
	FX_SLOT(37);
	FX_SLOT(38);
	FX_SLOT(39);
	FX_SLOT(40);
	FX_SLOT(41);
	FX_SLOT(42);
	FX_SLOT(43);
	FX_SLOT(44);
	FX_SLOT(45);
	FX_SLOT(46);
	FX_SLOT(47);
	FX_SLOT(48);
	FX_SLOT(49);
	FX_SLOT(50);
	virtual HRESULT __stdcall GetString(D3DXHANDLE param, const char **string);
	FX_SLOT(52);
	FX_SLOT(53);
	FX_SLOT(54);
	FX_SLOT(55);
	FX_SLOT(56);
	FX_SLOT(57);
	FX_SLOT(58);
	FX_SLOT(59);
	virtual HRESULT __stdcall ValidateTechnique(D3DXHANDLE technique);
};

extern "C" HRESULT __stdcall D3DXCreateEffect(IDirect3DDevice8 *device, const void *data,
	unsigned int size, const D3DXMACRO *defines, void *include, unsigned long flags,
	void *pool, ID3DXEffect **effect, ID3DXBuffer **errors);
extern "C" HRESULT __stdcall D3DXCreateEffectFromFileA(IDirect3DDevice8 *device,
	const char *filename, const D3DXMACRO *defines, void *include, unsigned long flags,
	void *pool, ID3DXEffect **effect, ID3DXBuffer **errors);

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *D3DDevice;
};

class File
{
public:
	virtual ~File();
	virtual int open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual bool nextLine(char *buf, int bufSize);
	virtual bool scanInt(int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(AsciiString &value);
	virtual bool print(const char *format, ...);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class FXShaderParameterBinder
{
public:
	FXShaderParameterBinder(void *effect);

private:
	void *m_effect;
	int m_vec[3];
	void *m_extra;
};

struct Rva0007BB16Record
{
	Rva0007BB16Record();
	~Rva0007BB16Record();
	void SetName(const char *name);
	void SetType(unsigned int type);

	AsciiString m_name;	// +0x00
	unsigned int m_type;	// +0x04
	AsciiString m_08;	// +0x08
	float m_vector[4];	// +0x0C
	int m_int;		// +0x1C
	bool m_bool;		// +0x20
};

struct Rva004DFCB0Element
{
	D3DXHANDLE m_handle;
};

class FXShaderAsset
{
public:
	class Impl;
	static bool s_isW3DView;
};

class FXShaderAsset::Impl
{
public:
	virtual void *get(int x);
	void Load(const char *filename);

private:
	ID3DXEffect *m_effect;				// +0x04
	FXShaderParameterBinder *m_binder;		// +0x08
	_STL::vector<Rva0007BB16Record> m_params;	// +0x0C
	_STL::vector<Rva004DFCB0Element> m_techniques;	// +0x18
	D3DXHANDLE m_shadowTechnique;			// +0x24
};

void FXShaderAsset::Impl::Load(const char *filename)
{
	D3DXMACRO macros[] = {
		{ "_WW3D_", "" },
		{ "_WW3D_VERSION_", "1" },
		{ "_W3DVIEW_", "" },
		{ 0, 0 }
	};
	if (!FXShaderAsset::s_isW3DView) {
		macros[2].Name = 0;
		macros[2].Definition = 0;
	}

	m_effect = 0;
	ID3DXBuffer *errors = 0;
	BFMEDX8DeviceLock lock;

	char compiled[260];
	strcpy(compiled, "Shaders/Compiled/");
	strcat(compiled, filename);
	strcat(compiled, "o");

	HRESULT hr = -1;
	if (TheFileSystem->doesFileExist(compiled) && !FXShaderAsset::s_isW3DView) {
		File *file = TheFileSystem->openFile(compiled, 0x41, 0);
		if (file != 0) {
			int size = file->size();
			char *data = file->readEntireAndClose();
			hr = D3DXCreateEffect(DX8Wrapper::D3DDevice, data, size, macros, 0, 0, 0, &m_effect, &errors);
			delete[] data;
		}
	} else {
		char source[260];
		strcpy(source, "Shaders/");
		strcat(source, filename);
		hr = D3DXCreateEffectFromFileA(DX8Wrapper::D3DDevice, source, macros, 0, 0, 0, &m_effect, &errors);
	}

	if (hr < 0) {
		if (m_effect != 0) {
			m_effect->Release();
			m_effect = 0;
		}
	}
	if (errors != 0) {
		errors->Release();
		errors = 0;
	}

	if (m_effect == 0)
		return;

	m_binder = new FXShaderParameterBinder(m_effect);

	int num_params = 0;
	int num_techniques = 0;
	D3DXEFFECT_DESC desc;
	if (m_effect->GetDesc(&desc) >= 0) {
		num_params = desc.Parameters;
		num_techniques = desc.Techniques;
	}

	for (int i = 0; i < num_params; i++) {
		D3DXHANDLE param = m_effect->GetParameter(0, i);
		if (param == 0)
			continue;
		D3DXPARAMETER_DESC pdesc;
		if (m_effect->GetParameterDesc(param, &pdesc) < 0 || pdesc.Name == 0)
			continue;
		if (_strcmpi(pdesc.Name, "HouseColorEnable") != 0) {
			D3DXHANDLE widget = m_effect->GetAnnotationByName(param, "UIWidget");
			if (widget != 0) {
				const char *str = 0;
				if (m_effect->GetString(widget, &str) < 0)
					continue;
				if (_strcmpi(str, "None") == 0)
					continue;
			} else {
				widget = m_effect->GetAnnotationByName(param, "UIName");
				if (widget == 0)
					continue;
			}
		}

		Rva0007BB16Record record;
		record.SetName(pdesc.Name);
		if (pdesc.Type == D3DXPT_FLOAT) {
			if (pdesc.Rows > 1)
				continue;
			record.SetType(pdesc.Columns + 1);
			if (m_effect->GetVector(param, record.m_vector) < 0)
				continue;
		} else if (pdesc.Type == D3DXPT_INT) {
			record.SetType(6);
			if (m_effect->GetInt(param, &record.m_int) < 0)
				continue;
		} else if (pdesc.Type == D3DXPT_BOOL) {
			record.SetType(7);
			BOOL b;
			if (m_effect->GetBool(param, &b) < 0)
				continue;
			record.m_bool = b != 0;
		} else {
			continue;
		}
		m_params.push_back(record);
	}

	for (int t = 0; t < num_techniques; t++) {
		Rva004DFCB0Element technique;
		technique.m_handle = m_effect->GetTechnique(t);
		if (technique.m_handle != 0 && m_effect->ValidateTechnique(technique.m_handle) >= 0)
			m_techniques.push_back(technique);
	}
	m_shadowTechnique = m_effect->GetTechniqueByName("_CreateShadowMap");
}

bool FXShaderAsset::s_isW3DView;

// 0x00151CD8, slot 3 of the asset vtable: loads the effect named by slot 0
// (the +0x18 name, row 0x00151733) and marks the asset loaded.
class Rva00151632
{
public:
	virtual const char *getName() const;
	void rva00151CD8();

private:
	unsigned int m_flags;			// +0x04
	char m_pad08[0x0C];
	FXShaderAsset::Impl *m_link;		// +0x14
};

void Rva00151632::rva00151CD8()
{
	m_link->Load(getName());
	m_flags |= 0x04000000;
}

// 0x00151243: a jump to StringBase<char>::set, kept out of line.
#pragma auto_inline(off)
void Rva0007BB16Record::SetName(const char *name)
{
	m_name = name;
}
#pragma auto_inline(on)
