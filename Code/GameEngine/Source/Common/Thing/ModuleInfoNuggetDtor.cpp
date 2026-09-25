// cl: /O1 /EHsc /MD
//
// ModuleInfo::Nugget destructor, retail 0x002CF51B, 53 bytes. Nugget opens
// with two AsciiStrings (name at +0, module tag at +4, Zero Hour
// ThingTemplate.h layout; BFME2 appends a POD tail the teardown never
// touches) so the compiler-generated teardown destroys +4 then +0 through
// the folded narrow-string dtor at 0x00364110 with one EH state. Called from
// vector<ModuleInfo::Nugget>::erase at 0x0033C3E6.

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

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
