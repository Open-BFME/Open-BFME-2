// Retail 0x006CFA30, 76 bytes. Original class identity is unknown.
// This is not ModuleInfo::Nugget: its member destructors at 0x006CEAD0
// and 0x006CE7F0 contradict the two AsciiStrings at 0x002CF51B.
//
// BFME1's first member is an AsciiString, but BFME2 tears the +0 member down
// through 0x006CEAD0 (matched opaquely as Rva006CEAD0::drainChain in
// ModuleInfoNuggetChainDrain.cpp), not the string release at 0x00036410. The
// member is typed with that opaque class, and its destructor is pinned at the
// address the byte-true call proves.
class Rva006CEAD0
{
public:
	~Rva006CEAD0();

private:
	unsigned char m_pad[4];
};

class ModuleTagString
{
public:
	~ModuleTagString();

private:
	unsigned char m_pad[4];
};

class Rva006CFA30
{
public:
	class Members
	{
	public:
		~Members();

	private:
		Rva006CEAD0 first;
		ModuleTagString m_moduleTag;
	};
};

Rva006CFA30::Members::~Members()
{
}
