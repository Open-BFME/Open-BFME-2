// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// LineGroupClass destructor, retail 0x001B3510 (213 bytes). Same shape as the
// PointGroup destructor (SEH frame, vptr reinstall, share-buffer releases with
// the /G7 shared refcount decrement, texture release last): seven share
// buffers here instead of six. Texture is a RefCountPtr (its implicit release
// is what needs the SEH states); there is no explicit texture line. Layout
// matches the matched ctor (arrays +4 through +0x1C, LineCount +0x20,
// Texture +0x24).

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
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

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/linegrp.h
class LineGroupClass
{
public:
	virtual ~LineGroupClass();

protected:
	ShareBufferClass<Vector3> *StartLineLoc;
	ShareBufferClass<Vector3> *EndLineLoc;
	ShareBufferClass<Vector4> *LineDiffuse;
	ShareBufferClass<Vector4> *TailDiffuse;
	ShareBufferClass<unsigned int> *ALT;
	ShareBufferClass<float> *LineSize;
	ShareBufferClass<float> *LineUCoord;
	int LineCount;
	RefCountPtr<TextureClass> Texture;
};

// ??1LineGroupClass@@UAE@XZ
LineGroupClass::~LineGroupClass()
{
	REF_PTR_RELEASE(StartLineLoc);
	REF_PTR_RELEASE(EndLineLoc);
	REF_PTR_RELEASE(LineDiffuse);
	REF_PTR_RELEASE(TailDiffuse);
	REF_PTR_RELEASE(ALT);
	REF_PTR_RELEASE(LineSize);
	REF_PTR_RELEASE(LineUCoord);
}
