// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ModuleInfo::Nugget destructor, retail 0x002CF51B, 53 bytes. Nugget opens
// with two AsciiStrings (name at +0, module tag at +4, Zero Hour
// ThingTemplate.h layout; BFME2 appends a POD tail the teardown never
// touches) so the compiler-generated teardown destroys +4 then +0 through
// the folded narrow-string dtor at 0x00036410 with one EH state. Called from
// vector<ModuleInfo::Nugget>::erase at 0x0033C3E6.

#include "ascii_string.h"

class ModuleInfo
{
public:
	struct Nugget
	{
		~Nugget();

		AsciiString m_name; // +0
		AsciiString m_moduleTag; // +4
		// ... BFME2 POD tail (see ModuleInfoNuggetCopyCtor.cpp); the
		// destructor never touches it.
	};
};

// ??1Nugget@ModuleInfo@@QAE@XZ @0x002CF51B
ModuleInfo::Nugget::~Nugget()
{
}

// The independently matched 20-byte record constructors and vector append
// use this address-derived spelling for the same native element.
#pragma comment(linker, "/alternatename:??1BfmeStringRecord002CF4C6@@QAE@XZ=??1Nugget@ModuleInfo@@QAE@XZ")
