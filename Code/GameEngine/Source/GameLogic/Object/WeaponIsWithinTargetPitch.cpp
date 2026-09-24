// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Shard for Weapon::isWithinTargetPitch: retail 0x002C9C82 is a framed
// /O1 x87-plus-SSE body. Donor is BFME1 Weapon.cpp isWithinTargetPitch with
// BFME2 repairs: positions read inline at Object+0x38 (z at +0x40, no
// getPosition calls), geometries at Object+0xA8 (not +0xAC), template ranges
// at +0x88/+0x8C (not +0x78/+0x7C), double fabs narrowed to float dz via an
// explicit cast (the cast types the 10.0f comparison as float-float and emits
// fld-dword; without it the toolchain promotes to fld-qword), comiss range
// tails. calcPitches resolves via the rowed GeometryInfo
// spelling; the +0x4c combined pitch-check flag gates everything.
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

extern "C" double fabs(double value);

class GeometryInfo
{
public:
	void calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
		const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const;
};

class Object
{
public:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0xA8 - 0x38 - sizeof(Coord3D)];
	GeometryInfo m_geometry;
};

class Weapon
{
public:
	bool isWithinTargetPitch(const Object *source, const Object *victim) const;

	const void *m_vtable;
	const void *m_template;
	unsigned char m_pad008[0x4C - 8];
	bool m_pitchCheck;
};

// ?isWithinTargetPitch@Weapon@@QBE_NPBVObject@@0@Z @0x002C9C82
bool Weapon::isWithinTargetPitch(const Object *source, const Object *victim) const
{
	if (m_pitchCheck)
	{
		const Coord3D *src = &source->m_position;
		const Coord3D *dst = &victim->m_position;

		float dz = (float)fabs(dst->z - src->z);
		if (dz < 10.0f)
			return true;

		Real minPitch, maxPitch;
		const GeometryInfo &sourceGeometry = source->m_geometry;
		const GeometryInfo &victimGeometry = victim->m_geometry;
		sourceGeometry.calcPitches(*src, victimGeometry, *dst, minPitch, maxPitch);

		const float *weaponTemplate = (const float *)m_template;

		if ((minPitch >= weaponTemplate[0x88 / 4] && minPitch <= weaponTemplate[0x8C / 4]) ||
				(maxPitch >= weaponTemplate[0x88 / 4] && maxPitch <= weaponTemplate[0x8C / 4]) ||
				(minPitch <= weaponTemplate[0x88 / 4] && maxPitch >= weaponTemplate[0x8C / 4]))
			return true;

		return false;
	}

	return true;
}
