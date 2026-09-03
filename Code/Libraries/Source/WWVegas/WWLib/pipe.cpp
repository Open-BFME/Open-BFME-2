// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep


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
