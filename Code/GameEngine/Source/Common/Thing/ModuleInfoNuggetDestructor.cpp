// Ported from BFME1; the body is independently byte-verified in BFME2 at
// RVA 0x006CFA30.
class AsciiString
{
public:
	~AsciiString();

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
		AsciiString first;
		ModuleTagString m_moduleTag;
	};
};

ModuleInfo::Nugget::~Nugget()
{
}
