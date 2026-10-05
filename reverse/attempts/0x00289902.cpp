// ?rva00289902@Rva00289902@@QAEAAV1@ABV1@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00289902@Rva00289902@@QAEAAV1@ABV1@@Z @ 0x00289902 443B
// Copy-assignment: self-check then memberwise assign of strings vectors
// decals and scalars. All callees rowed per packet. Class layout from retail
// offsets; identity address-derived (callers unclaimed).
#include "ascii_string.h"
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class RadiusDecalTemplate
{
public:
	void rva00330CDD(const RadiusDecalTemplate &other);
private:
	char m_pad[0x34];
};

struct Rva002898ACElement
{
	int a[2];
};

class CameraMarker
{
public:
	int m_a[2];
};

struct CameraMarkerVec
{
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);

	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};

class ModuleData
{
public:
	char m_pad[4];
};

struct Rva00289902Data78
{
	char m_pad[0x78];
	int m_78;
	int m_7C;
};

struct Rva00289902Block58
{
	int v[19];
};

struct Rva00289902BlockDC
{
	int v[3];
};

class Rva00289902
{
public:
	Rva00289902 &rva00289902(const Rva00289902 &other);
private:
	char m_pad00[0x10];
	AsciiString m_str10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	_STL::vector<AsciiString> m_vec24;
	_STL::vector<AsciiString> m_vec30;
	CameraMarkerVec m_vec3C;
	int m_48;
	_STL::vector<void *> m_vec4C;
	Rva00289902Block58 m_blk58;
	RadiusDecalTemplate m_radA4;
	unsigned char m_d8;
	char m_padD9[3];
	Rva00289902BlockDC m_blkDC;
	int m_e8;
	int m_ec;
	int m_f0;
	int m_f4;
	int m_f8;
	int m_fc;
	unsigned char m_100;
	unsigned char m_101;
	unsigned char m_102;
	char m_pad103;
	int m_104;
};

// ?rva00289902@Rva00289902@@QAEAAV1@ABV1@@Z present-unmatched
Rva00289902 &Rva00289902::rva00289902(const Rva00289902 &other)
{
	unsigned int i;
	if (&other == this)
		return *this;
	m_str10.set(other.m_str10);
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_vec24 = other.m_vec24;
	m_radA4.rva00330CDD(other.m_radA4);
	m_blkDC = other.m_blkDC;
	m_48 = other.m_48;
	m_blk58 = other.m_blk58;
	m_radA4.rva00330CDD(other.m_radA4);
	m_d8 = other.m_d8;
	m_e8 = other.m_e8;
	m_ec = other.m_ec;
	m_f0 = other.m_f0;
	m_f4 = other.m_f4;
	m_f8 = other.m_f8;
	m_fc = other.m_fc;
	m_100 = other.m_100;
	m_101 = other.m_101;
	m_102 = other.m_102;
	m_104 = other.m_104;
	_ReadWriteBarrier();
	m_vec30.erase(m_vec30.begin(), m_vec30.end());
	for (i = 0; i < other.m_vec30.size(); ++i)
		m_vec30.push_back(other.m_vec30[i]);
	m_vec4C.erase(m_vec4C.begin(), m_vec4C.end());
	for (i = 0; i < other.m_vec4C.size(); ++i)
		((_STL::vector<const ModuleData *> *)&m_vec4C)->push_back(*(const ModuleData * const *)&other.m_vec4C[i]);
	m_vec3C.erase(m_vec3C.m_start, m_vec3C.m_finish);
	for (i = 0; i < ((const _STL::vector<Rva002898ACElement> *)&other.m_vec3C)->size(); ++i)
		((_STL::vector<Rva002898ACElement> *)&m_vec3C)->push_back((*(const _STL::vector<Rva002898ACElement> *)&other.m_vec3C)[i]);
	return *this;
}
