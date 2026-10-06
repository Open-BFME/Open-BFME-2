// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE2 /DNDEBUG /MD /EHsc
// ??1Rva0057D4EE@@QAE@XZ @0x0057D4EE 5B
// Evidence: 5B jmp to rowed ??1AptMapPreview@@QAE@XZ at 0x0057CF0B; novtable
// empty dtor over rowed base per 4.8; neighbours in AptMapPreviewPicture.cpp.
#include "ascii_string.h"

class AptMapPreview
{
public:
	~AptMapPreview();
};

class __declspec(novtable) Rva0057D4EE : public AptMapPreview
{
public:
	~Rva0057D4EE();
};

Rva0057D4EE::~Rva0057D4EE()
{
}
