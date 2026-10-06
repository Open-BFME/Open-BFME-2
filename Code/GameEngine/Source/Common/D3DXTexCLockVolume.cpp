// flags: region default (reverse/retail_inventory/flag_regions.csv)
// The archive-derived constructor identity and single zeroing store establish
// that the lock volume begins with one scalar lock state.

namespace D3DXTex {
class CLockVolume
{
public:
	CLockVolume();

private:
	int m_lockState;
};

CLockVolume::CLockVolume()
{
	m_lockState = 0;
}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0TextureClassPtr@@QAE@XZ=??0CLockVolume@D3DXTex@@QAE@XZ")
#pragma comment(linker, "/alternatename:??0MaterialPassStage@@QAE@XZ=??0CLockVolume@D3DXTex@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva00906340CellCtor@@YAXPAX@Z=??0CLockVolume@D3DXTex@@QAE@XZ")
#pragma comment(linker, "/alternatename:?b_00025e1e@@YAXXZ=??0CLockVolume@D3DXTex@@QAE@XZ")
