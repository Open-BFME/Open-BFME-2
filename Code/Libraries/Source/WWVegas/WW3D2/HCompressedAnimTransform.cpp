// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmehcanim /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Get_Transform@HCompressedAnimClass@@UBEXAAVMatrix3D@@HM@Z @0x0018F3F0 80B
// Retail vtable 0x007D5D88 (VA 0xBD5D88) slot 10 offset 0x28 of ctor 0x0018F0E0.
// Calls slots 8/9 offsets 0x20/0x24 which are Get_Translation 0x00190610 and
// Get_Orientation 0x00190C60. Donor BFME1 hcanim.h orders Get_Translation then
// Get_Orientation then Get_Transform then Get_Visibility. Retail delegates to
// the two virtuals with identity-quaternion fallback loading 1.0f from
// 0x007BB8D8 and translation at mtx+0x10.
#include "vector3.h"
#include "quat.h"
#include "matrix3d.h"
// Eight slots precede Get_Translation in retail (vtable dump at 0x007D5D88:
// Name lea +0x10 at slot 2 and HName lea +0x30 at slot 4 and NumFrames +0x44 at
// slot 5 and FrameRate +0x50 at slot 6 and TotalTime at slot 7 plus the key
// dword +0x40 at slot 3 rowed as ?get@Rva00661FD0DwordField). The donor header
// lacks that key slot so Translation sits one slot low (0x1C vs retail 0x20).
// Declare it here with an honest address name to reproduce retail 0x20/0x24.
class HCompressedAnimClass {
public:
	virtual ~HCompressedAnimClass();
	virtual const char *Get_Name(void) const;
	virtual const char *Get_HName(void) const;
	virtual const char *Get_Key(void);
	virtual int Get_Num_Frames(void);
	virtual float Get_Frame_Rate(void);
	virtual float Get_Total_Time(void);
	virtual int Rva00661FD0(void) const;
	virtual void Get_Translation(Vector3 &translation, int pividx, float frame) const;
	virtual bool Get_Orientation(Quaternion &orientation, int pividx, float frame) const;
	virtual void Get_Transform(Matrix3D &transform, int pividx, float frame) const;
};
void HCompressedAnimClass::Get_Transform(Matrix3D& mtx, int pividx, float frame) const
{
	if (!Get_Orientation((Quaternion&)mtx, pividx, frame)) {
		((Quaternion&)mtx).Make_Identity();
	}
	Get_Translation((Vector3&)*((char*)&mtx + 16), pividx, frame);
}
