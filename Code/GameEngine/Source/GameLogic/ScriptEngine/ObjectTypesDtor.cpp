// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1ObjectTypes@@UAE@XZ @0x00376ADF 63B: ObjectTypes dtor.
// Evidence: destroys vector<AsciiString> m_objectTypes at +8 through rowed
// 0x0002CC70 (EH state 1), then AsciiString m_listName at +4 through rowed
// releaseBuffer 0x00036410 (EH state 0), then restores Snapshot base vtable
// 0x00BBB554. No derived vtable store. Paired with default ctor 0x003769F9
// (vtable 0x00C18630) and copy-assign 0x00376A9C on the same 0x14 object.
// Callers 0x003CA322 0x003C9F4B 0x003BA7FF. Shape follows SpawnBehavior
// ModuleData dtor (TU-local Snapshot with inline BBB554 restore, novtable
// derived to suppress entry store, empty body).
#include <vector>

class Xfer;

#include "Common/Snapshot.h"

#include "ascii_string.h"


class __declspec(novtable) ObjectTypes : public Snapshot
{
public:
	virtual ~ObjectTypes();
private:
	AsciiString m_listName; // +4
	_STL::vector<AsciiString> m_objectTypes; // +8
};

ObjectTypes::~ObjectTypes()
{
}
