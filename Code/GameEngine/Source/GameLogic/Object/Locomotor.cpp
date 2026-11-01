// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/zh_outofline /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// TU Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp (retail TU of the
// Locomotor, LocomotorTemplate, LocomotorSet and LocomotorStore rows).
//
// The seed keeps its two matched rows over native views. Of the Zero Hour
// port that compiled here only Locomotor's empty destructor, crc and
// loadPostProcess stay: LocomotorCtor.cpp's Locomotor table (??_7Locomotor,
// ??_G) references them and no other object defines them. The rest, bodies
// with no row, is gone, so the donors' retail-matched bodies compose here.
#include <utility>
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

enum NameKeyType;
class LocomotorTemplate
{
public:
	char m_pad00[0x10];
	int m_surfaces;							// +0x10, the legal-surface mask
};

// Zero Hour's OVERRIDE<T>: operator-> resolves the final override
// (0x0035C95F for LocomotorTemplate).
template <class T> class OVERRIDE
{
public:
	const T *operator->() const;
private:
	T *m_node;
};

// Locomotor as 0x002BEDBE reads it (an override at +0x08); its Snapshot
// slots are LocomotorCtor.cpp's, so both units emit one table.
class Locomotor : public Snapshot
{
public:
	int getLegalSurfaces() const;
protected:
	virtual ~Locomotor();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	char m_pad04[0x08 - 0x04];
public:
	OVERRIDE<LocomotorTemplate> m_template;	// +0x08
};

// ?Locomotor::~Locomotor present-unmatched
Locomotor::~Locomotor()
{
}

// ?Locomotor::crc present-unmatched
void Locomotor::crc(Xfer *xfer)
{
}

// Locomotor::xfer is rowed in LocomotorXfer.cpp (0x00341E2D).

// ?Locomotor::loadPostProcess present-unmatched
void Locomotor::loadPostProcess()
{
}

// ?getLegalSurfaces@Locomotor@@QBEHXZ, 0x002BEDBE (12 bytes): Zero Hour's
// Locomotor.h inline m_template->m_surfaces, out of line as retail keeps it
// (ecx+8, the override resolver, then +0x10).
int Locomotor::getLegalSurfaces() const
{
	return m_template->m_surfaces;
}

// The store singleton (0x00DFDC5C, .data, zero-initialised as Zero Hour's
// `LocomotorStore *TheLocomotorStore = NULL`).
class LocomotorStore;
LocomotorStore *TheLocomotorStore = 0;

// LocomotorStore::parseLocomotorTemplateDefinition (0x001E8A94, in
// Code/GameEngine/Source/Common/Rva001E72B4Reload.cpp) inserts into its
// template map; that insertion instantiated this pair constructor here
// (0x00363B35, 22 bytes).
template _STL::pair<const NameKeyType, LocomotorTemplate *>::pair(const NameKeyType &, LocomotorTemplate *const &);
