// cl: /O2 /arch:SSE /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /G7 /Ireference/shims/bfmerendobj /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// LineGroupClass::Set_Arrays, retail 0x001B3790, 268 bytes.
// Zero Hour LineGroupClass::Set_Arrays over the real share-buffer and line
// group headers (linegrp.cpp's flags and views): REF_PTR_SET inlines the
// dword refcount and Delete_This at vtable slot 0.

#include "wwdebug.h"
#include "sharebuf.h"
#include "linegrp.h"

void LineGroupClass::Set_Arrays(
	ShareBufferClass<Vector3> *startlocs,
	ShareBufferClass<Vector3> *endlocs,
	ShareBufferClass<Vector4> *diffuse,
	ShareBufferClass<Vector4> *taildiffuse,
	ShareBufferClass<unsigned int> *alt,
	ShareBufferClass<float> *sizes,
	ShareBufferClass<float> *ucoords,
	int active_line_count
	)
{
	// The Line locations arrays are NOT optional!
	WWASSERT(startlocs);
	WWASSERT(endlocs);

	// Ensure lengths of all arrays are the same:
	WWASSERT(startlocs->Get_Count() == endlocs->Get_Count());
	WWASSERT(!diffuse || startlocs->Get_Count() == diffuse->Get_Count());
	WWASSERT(!alt || startlocs->Get_Count() == alt->Get_Count());
	WWASSERT(!sizes || startlocs->Get_Count() == sizes->Get_Count());
	WWASSERT(!ucoords || startlocs->Get_Count() == ucoords->Get_Count());
	WWASSERT(!taildiffuse || startlocs->Get_Count() == taildiffuse->Get_Count());

	REF_PTR_SET(StartLineLoc,startlocs);
	REF_PTR_SET(EndLineLoc,endlocs);
	REF_PTR_SET(LineDiffuse,diffuse);
	REF_PTR_SET(TailDiffuse,taildiffuse);
	REF_PTR_SET(ALT,alt);
	REF_PTR_SET(LineSize,sizes);
	REF_PTR_SET(LineUCoord,ucoords);

	if (ALT) {
		LineCount = active_line_count;
	} else {
		LineCount = (active_line_count >= 0) ? active_line_count : StartLineLoc->Get_Count();
	}
}
