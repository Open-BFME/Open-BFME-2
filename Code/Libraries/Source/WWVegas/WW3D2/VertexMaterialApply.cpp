// cl: /Ireference/shims/bfmecamera /Ireference/shims/bfmemapper /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// VertexMaterialClass::Apply at 0x0013D570, transferred from BFME 1's
// vertmaterial.cpp (its matched Apply, including the ATI texture-transform
// workaround BFME added) and rebuilt with BFME 2's /G7 /arch:SSE.
//
// dx8wrapper.h is included first so the bfmecamera shim's BFME 2
// Set_Transform is the one inlined; the reference headers would otherwise
// resolve it from their own directory.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "dx8wrapper.h"
#include "mapper.h"
#include "vertmaterial.h"
#include "meshbuild.h"
#include "ww3d.h"

#ifdef DYN_MAT8
class DynD3DMATERIAL8
{
public:
	D3DMATERIAL8 Mat;
};
#define Material				(&MaterialDyn->Mat)
#else
#define Material				(MaterialOld)
#endif

// Target evidence: BFME 2's caps object is 0x2E4 bytes (allocated in
// 0x001207B0) and this body reads its vendor at +0x2D0 and device at +0x2C4.
// That is the reference DX8Caps tail -- DeviceId, DriverBuildVersion,
// DriverVersionStatus, VendorId, then DriverDLL, Direct3D, CapsLog and
// CompactLog -- ending exactly at 0x2E4. What precedes DeviceId is larger than
// any modelled DX8Caps and is not identified, so only the tail is described.
struct DX8CapsIdentityView
{
	unsigned char Unidentified[0x2C4];
	unsigned DeviceId;					// +0x2C4
	unsigned DriverBuildVersion;		// +0x2C8
	int DriverVersionStatus;			// +0x2CC
	unsigned VendorId;					// +0x2D0
};

enum
{
	VENDOR_ID_ATI = 2,					// DX8Caps::VENDOR_ATI
	ATI_DEVICE_RADEON_8500 = 0x5144,
	ATI_DEVICE_RADEON_9000_FIRST = 0x5157,
	ATI_DEVICE_RADEON_9000_LAST = 0x515A
};

void VertexMaterialClass::Apply(void) const
{
	int i;

	DX8Wrapper::Set_DX8_Material(Material);

	if (WW3D::Is_Coloring_Enabled())
		DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING,FALSE);
	else
		DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING,UseLighting);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENTMATERIALSOURCE,AmbientColorSource);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DIFFUSEMATERIALSOURCE,DiffuseColorSource);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_EMISSIVEMATERIALSOURCE,EmissiveColorSource);

	// set to default values if no mappers
	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++) {
		if (Mapper[i]) {
			Mapper[i]->Apply(UVSource[i]);
		} else {
			DX8Wrapper::Set_DX8_Texture_Stage_State(i,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU | UVSource[i]);
			DX8Wrapper::Set_DX8_Texture_Stage_State(i,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_DISABLE);
		}
	}

	// On these ATI parts, when exactly one of the two stages is mapped, give
	// the unmapped one an identity texture transform.
	const DX8CapsIdentityView *caps =
		reinterpret_cast<const DX8CapsIdentityView *>(DX8Wrapper::Get_Current_Caps());
	if (caps && caps->VendorId == VENDOR_ID_ATI &&
		(caps->DeviceId == ATI_DEVICE_RADEON_8500 ||
		 (caps->DeviceId >= ATI_DEVICE_RADEON_9000_FIRST &&
		  caps->DeviceId <= ATI_DEVICE_RADEON_9000_LAST))) {
		if ((Mapper[0] == NULL) != (Mapper[1] == NULL)) {
			unsigned int stage = Mapper[0] != NULL;
			Matrix4x4 identity;
			identity.Make_Identity();
			DX8Wrapper::Set_Transform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + stage), identity);
			DX8Wrapper::Set_DX8_Texture_Stage_State(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		}
	}
}
