// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001B5018@SubsystemInterfaceList@@QAEXPAVSubsystemInterface@@@Z, retail 0x001B5018 (71 bytes, ret 4).
// Same list as the rowed rva001B4FE9 (SubsystemInterfaceListRva001B4FE9.cpp): register a subsystem once. A
// null one is ignored, one already in the 8-byte records at +0x00 is ignored, and otherwise it is appended
// to the pointer list at +0x0C unless that already holds it (the search is the folded 4-byte find, rowed
// under its int spelling at 0x0020E873). Zero Hour has no equivalent; the method keeps its address token.
#include <vector>

class SubsystemInterface;
class ModuleData;

struct SubsystemInterfaceRecord
{
	SubsystemInterface *m_subsystem;
	int m_extra;
};

class SubsystemInterfaceList
{
public:
	void rva001B5018(SubsystemInterface *subsystem);

private:
	_STL::vector<SubsystemInterfaceRecord> m_records;	// +0x00
	_STL::vector<const ModuleData *> m_known;				// +0x0C
};

void SubsystemInterfaceList::rva001B5018(SubsystemInterface *subsystem)
{
	if (subsystem == 0)
		return;
	for (_STL::vector<SubsystemInterfaceRecord>::iterator it = m_records.begin(); it != m_records.end(); ++it) {
		if (it->m_subsystem == subsystem)
			return;
	}
	const ModuleData *&item = (const ModuleData *&)subsystem;
	const ModuleData **last = m_known.end();
	if ((const ModuleData **)_STL::find((int *)m_known.begin(), (int *)last, (const int &)item) == last)
		m_known.push_back(item);
}
