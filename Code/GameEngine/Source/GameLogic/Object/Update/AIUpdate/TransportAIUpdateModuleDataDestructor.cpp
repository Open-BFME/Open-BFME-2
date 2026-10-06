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

class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_moduleTagNameKey;
};

class TransportAIUpdateModuleData : public ModuleData
{
public:
	virtual ~TransportAIUpdateModuleData();

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
