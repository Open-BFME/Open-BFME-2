// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// stlport
// ??1TransportAIUpdateModuleData@@UAE@XZ @0x0026E1FC 107B.
// Identity: the packet pins this address as the TransportAIUpdateModuleData
// destructor; the BFME1 destructor thunk supplies the member teardown shape.
#include "ascii_string.h"

class Rva0026E1A6
{
	void *m_header;
	unsigned int m_count;
	unsigned int m_reserved;
public:
	~Rva0026E1A6();
};

#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

#include "../../../../../Include/Common/ModuleData.h"
#include "../../../../../../../reference/shims/moduledata/Common/Snapshot.h"
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

class TransportAIUpdateModuleData : public ModuleData
{
public:
	virtual ~TransportAIUpdateModuleData();
	virtual bool isAiModuleData() const { return true; }

private:
	Rva0026E1A6 m_tree;
	int *m_p14;
	int m_f1c, m_f20, m_f24, m_f28, m_f2c;
	AsciiString m_s30;
	int m_f34, m_f38, m_f3c, m_f40, m_f44;
	AsciiString m_s44;
	int m_f48, m_f4c, m_f50, m_f54;
	std::vector<AsciiString> m_vec;
};

TransportAIUpdateModuleData::~TransportAIUpdateModuleData()
{
	if (m_p14)
		delete m_p14;
}
