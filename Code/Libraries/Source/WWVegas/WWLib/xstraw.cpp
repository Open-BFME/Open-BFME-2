// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)


#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include	"always.h"
#include	"xstraw.h"
#include	<stddef.h>
#include	<string.h>


int BufferStraw::Get(void * source, int slen)
{
	int total = 0;

	if (Is_Valid() && source != NULL && slen > 0) {
		int len = slen;
		if (BufferPtr.Get_Size() != 0) {
			int theoretical_max = BufferPtr.Get_Size() - Index;
			len = (slen < theoretical_max) ? slen : theoretical_max;
		}

		if (len > 0) {
			memmove(source, ((char*)BufferPtr.Get_Buffer()) + Index, len);
		}

		Index += len;
		total += len;
	}
	return(total);
}


int FileStraw::Get(void * source, int slen)
{
	if (Valid_File() && source != NULL && slen > 0) {
		if (!File->Is_Open()) {
			HasOpened = true;
			if (!File->Is_Available()) return(0);
			if (!File->Open(FileClass::READ)) return(0);
		}

		return(File->Read(source, slen));
	}
	return(0);
}


FileStraw::~FileStraw(void)
{
	if (Valid_File() && HasOpened) {
		File->Close();
		HasOpened = false;
		File = NULL;
	}
}
