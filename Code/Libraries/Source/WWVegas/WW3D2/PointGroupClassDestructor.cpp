// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// PointGroupClass destructor, retail 0x00178ED0 (194 bytes). BFME1 port of
// PointGroupClassDestructor.cpp (their 0x009125E0, 193 bytes): six share-buffer
// releases plus the texture release. Layout matches the matched ctor
// (PointLoc +4 through PointFrame +0x18, Texture +0x24).

// Match the retail RefCountClass release helper in its provider's size context.
#pragma optimize("gsy", on)
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/refcount.h"
#pragma optimize("", on)
#include "sharebuf.h"
#include "texture.h"
#include "vector3.h"
#include "vector4.h"

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent)
		{
			Referent->Release_Ref();
		}
	}

private:
	T *Referent;
};

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
class PointGroupClass
{
public:
	virtual ~PointGroupClass();

protected:
	ShareBufferClass<Vector3> *PointLoc;
	ShareBufferClass<Vector4> *PointDiffuse;
	ShareBufferClass<unsigned int> *APT;
	ShareBufferClass<float> *PointSize;
	ShareBufferClass<unsigned char> *PointOrientation;
	ShareBufferClass<unsigned char> *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	RefCountPtr<TextureClass> Texture;
};

// ??1PointGroupClass@@UAE@XZ
PointGroupClass::~PointGroupClass()
{
	REF_PTR_RELEASE(PointLoc);
	REF_PTR_RELEASE(PointDiffuse);
	REF_PTR_RELEASE(APT);
	REF_PTR_RELEASE(PointSize);
	REF_PTR_RELEASE(PointOrientation);
	REF_PTR_RELEASE(PointFrame);
}

void Force_PointGroup_Deleting_Destructor(PointGroupClass *group)
{
	delete group;
}
