// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// The BFME1 BufferedFileClass constructor is a plain field initializer.  This
// focused TU keeps the BFME2 claim independent from the larger file-factory
// implementation while the retail body verifies the inherited layout.
#include "always.h"
#include "bufffile.h"

BufferedFileClass::BufferedFileClass(void) :
	RawFileClass(),
	Buffer(NULL),
	BufferSize(0),
	BufferAvailable(0),
	BufferOffset(0)
{
}
