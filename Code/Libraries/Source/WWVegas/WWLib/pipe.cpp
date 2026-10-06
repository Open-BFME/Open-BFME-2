// cl: /Ireference/shims/bfmerendobj /DNDEBUG /Ob0 /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#include	"pipe.h"
#include	<stddef.h>


Pipe::~Pipe(void)
{
	if (ChainTo != NULL) {
		ChainTo->ChainFrom = ChainFrom;
	}
	if (ChainFrom != NULL) {
		ChainFrom->Put_To(ChainTo);
	}

	ChainFrom = NULL;
	ChainTo = NULL;
}


void Pipe::Put_To(Pipe * pipe)
{
	if (ChainTo != pipe) {
		if (pipe != NULL && pipe->ChainFrom != NULL) {
			pipe->ChainFrom->Put_To(NULL);
			pipe->ChainFrom = NULL;
		}

		if (ChainTo != NULL) {
			ChainTo->ChainFrom = NULL;
			ChainTo->Flush();
		}

		ChainTo = pipe;
		if (ChainTo != NULL) {
			ChainTo->ChainFrom = this;
		}
	}
}


int Pipe::Put(void const * source, int length)
{
	if (ChainTo != NULL) {
		return(ChainTo->Put(source, length));
	}
	return(length);
}


int Pipe::Flush(void)
{
	if (ChainTo != NULL) {
		return(ChainTo->Flush());
	}
	return(0);
}
