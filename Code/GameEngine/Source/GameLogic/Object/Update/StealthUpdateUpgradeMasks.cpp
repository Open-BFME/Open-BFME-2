// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// ?rva003748BD@StealthUpdate@@QAEXXZ, retail 0x003748BD, 133 bytes.
// StealthUpdate upgrade-mask resolver (BFME2-new, no ZH donor).
// Evidence: callers jmp at 0x00374AFD in slot-1 loadPostProcess and at 0x00374FD0;
// ModuleData vectors at +0xB0/+0xBC (StealthUpdateModuleDataCtor row 0x0037588B);
// masks at +0x48/+0xC8 cleared as 0x80 pairs by ctor 0x00374B02;
// UpgradeCenter::findUpgrade row 0x0026F26D via global 0x009FEB60;
// UpgradeTemplate mask index at +0x38 (UpgradeMuxData precedent).
// TU-local faithful model; untouched members padded to retail offsets.
#include <vector>

#include "ascii_string.h"

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const { return m_maskIndex; }

private:
	unsigned char m_pad[0x38];
	unsigned int m_maskIndex;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const throw();
};

extern UpgradeCenter *TheUpgradeCenter;	// Upgrade.cpp's global (0x009FEB60)

struct UpgradeMaskType
{
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (unsigned long)1 << (bit & 31);
	}

	unsigned long m_words[32];
};

class StealthUpdateModuleData
{
public:
	unsigned char m_pad00[0xB0];
	_STL::vector<AsciiString> m_vecB0;
	_STL::vector<AsciiString> m_vecBC;
};

class StealthUpdate
{
public:
	void rva003748BD();

private:
	void *m_vptr;
	const StealthUpdateModuleData *m_data;
	unsigned char m_pad08[0x40];
	UpgradeMaskType m_mask48;
	UpgradeMaskType m_maskC8;
};

void StealthUpdate::rva003748BD()
{
	const StealthUpdateModuleData *data = m_data;
	if (!data)
		return;
	_STL::vector<AsciiString>::const_iterator it;
	for (it = data->m_vecB0.begin(); it != data->m_vecB0.end(); ++it)
	{
		const UpgradeTemplate *templ = TheUpgradeCenter->findUpgrade(*it);
		if (templ)
			m_mask48.set(templ->getUpgradeMask());
	}
	for (it = data->m_vecBC.begin(); it != data->m_vecBC.end(); ++it)
	{
		const UpgradeTemplate *templ = TheUpgradeCenter->findUpgrade(*it);
		if (templ)
			m_maskC8.set(templ->getUpgradeMask());
	}
}
