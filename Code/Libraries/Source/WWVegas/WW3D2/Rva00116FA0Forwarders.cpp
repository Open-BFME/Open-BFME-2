// cl: /DNDEBUG /MD
// Four 5-byte forwarders, each its own int3-padded function in the WW3D2
// run, that tail-jump to an already rowed body with the caller's arguments:
//   0x00116FA0 -> ?Rva00120130Get@@YAHXZ (0x00120130)
//   0x001174C0 -> ?Rva0011CDB0Get@@YAHXZ (0x0011CDB0)
//   0x001174E0 -> ?Get_Box_Display_Mask@BoxRenderObjClass@@SAHXZ (0x00174F30)
//   0x0012E830 -> ?Sort@@YAXPAUTempIndexStruct@@0@Z (0x0012DCF0)
// No direct caller reaches them in retail; names stay address-derived.
int Rva00120130Get(void);
int Rva0011CDB0Get(void);
class BoxRenderObjClass
{
public:
	static int Get_Box_Display_Mask(void);
};

struct TempIndexStruct;
void Sort(TempIndexStruct *begin, TempIndexStruct *end);

void Rva0012E830Sort(TempIndexStruct *begin, TempIndexStruct *end)
{
	Sort(begin, end);
}
