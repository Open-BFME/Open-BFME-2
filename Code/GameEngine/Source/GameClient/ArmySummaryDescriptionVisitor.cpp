// cl: /Oy- /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// Whole175B secondary ArmySummaryDescription visitor at220D1E..220DCD RET4.
// Rehomed after upstream moved the primary constructor/destructor and real
// builder/callers to ArmySummaryDescription.cpp. Native secondary+4 remains
// primary+8 names, secondary+10 remains primary+14 integer counts.
#include <vector>
#include "ascii_string.h"
extern void *g_00DFE490;
class ThingTemplate {
public:
	char m_prefix[0x64];
	AsciiString m_name;
};
class Player;
class ObjectFilter {
public:
	bool testTemplate(const ThingTemplate *, const Player *, const Player *);
	int m_id;
};
struct ArmyDescriptionCategory220D1E {
	AsciiString m_singular;
	AsciiString m_plural;
	ObjectFilter m_filter;
	ObjectFilter &getFilter() { return m_filter; }
};
struct ArmyDescriptionConfig220D1E {
	char m_prefix[0xC];
	ObjectFilter m_unmatchedFilter;
	_STL::vector<ArmyDescriptionCategory220D1E> m_categories;
	ArmyDescriptionCategory220D1E &getCategory(int index) { return m_categories[index]; }
};
typedef char ArmyDescriptionCategoryExtent220D1E[sizeof(ArmyDescriptionCategory220D1E) == 12 ? 1 : -1];
typedef char ArmyDescriptionConfigExtent220D1E[sizeof(ArmyDescriptionConfig220D1E) == 0x1C ? 1 : -1];
StringBase<char> *Rva000BD22FFind(StringBase<char> *, StringBase<char> *, const StringBase<char> &);
namespace _STL { template<> void vector<AsciiString>::push_back(const AsciiString &); }

// Native secondary receiver is Rva00220B04+4: its constructor installs
// BE6A64 there, whose slot points to 0x00220D1E. This is that subobject's
// measured ABI view, not another name for the complete primary receiver.
// Names at secondary+4 and counters at secondary+10 are independently
// accessed here and by BuildDescriptionString (complete receiver+8/+14).
class Rva00220D1ESecondary {
public:
	int rva00220D1E(const ThingTemplate *);
private:
	void *m_vptr;
	_STL::vector<AsciiString> m_names;
	_STL::vector<int> m_counts;
	int m_option;
};

// Full [0x00220D1E,0x00220DCD) RET4. WB ArmySummaryDescription.cpp:198
// establishes category counting; target calls the independently rowed
// ObjectFilter::testTemplate with two null Player pointers. The config's
// +10 vector and 1C allocation are also proven by ctor220C74/init220DCD.
// Result width is a target ABI view: retail explicitly returns EAX=1.
int Rva00220D1ESecondary::rva00220D1E(const ThingTemplate *thing)
{
	if (thing) {
		if (((ArmyDescriptionConfig220D1E *)g_00DFE490)->m_unmatchedFilter.testTemplate(thing, 0, 0)) {
			const AsciiString &name = thing->m_name;
			StringBase<char> *last = (StringBase<char> *)m_names.end();
			if (Rva000BD22FFind((StringBase<char> *)m_names.begin(), last, (const StringBase<char> &)name) == last)
				m_names.push_back(name);
		} else {
			int categoryCount = ((ArmyDescriptionConfig220D1E *)g_00DFE490)->m_categories.size();
			for (int index = 0; index < categoryCount; ++index) {
				if (((ArmyDescriptionConfig220D1E *)g_00DFE490)->getCategory(index).getFilter().testTemplate(thing, 0, 0)) {
					++m_counts.begin()[index];
					break;
				}
			}
		}
	}
	return true;
}
