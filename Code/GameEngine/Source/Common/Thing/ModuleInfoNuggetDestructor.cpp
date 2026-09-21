// Ported from BFME1; the body is independently byte-verified in BFME2 at
// RVA 0x006CFA30.
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

class ModuleInfo
{
public:
	class Nugget
	{
	public:
		~Nugget();

	private:
		Rva006CEAD0 first;
		ModuleTagString m_moduleTag;
	};
};

ModuleInfo::Nugget::~Nugget()
{
}
