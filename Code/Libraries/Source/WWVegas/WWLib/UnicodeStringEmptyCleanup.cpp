// cl: /O1 /Ireference/shims/bfme2_ascii
// Native 007B9C10..007B9C1A: the atexit callback registered by 007B6740.
// That initializer constructs UnicodeString::TheEmptyString at VA00E0C898
// through 00326BE6 and passes this callback to atexit. The callback calls
// the rowed UnicodeString destructor at 005B804E with the same object.
// Keep the address in the helper name: retail's compiler-local name is unknown.
#include "unicode_string.h"

// Declaration-only ABI view keeps the retail out-of-line destructor call.
class UnicodeStringCleanup
{
public:
    void destroy();
};
#pragma comment(linker, "/alternatename:?destroy@UnicodeStringCleanup@@QAEXXZ=??1UnicodeString@@QAE@XZ")

void rva007B9C10DestroyEmptyUnicodeString()
{
    reinterpret_cast<UnicodeStringCleanup *>(&UnicodeString::TheEmptyString)->destroy();
}
