// cl: /O1 /MD /Ireference/shims/bfme2_ascii
// stlport
// ??0BfmeStringTailRecord180@@QAE@XZ @0x000C0D7A 41B 180-byte record ctor text@0 words@4 values10 vector@0x10 heads 0x4C@0x1c/@0x68 callers 0x000C876D layout from Rva000C7720Vector180Dtor
#include <vector>
#include "ascii_string.h"

struct PlayerAITypeEntry
{
	AsciiString name;
	char unknown[12];
};

class Rva0042526Member
{
public:
	Rva0042526Member() throw();
private:
	unsigned char m_pad[0x4C];
};

class BfmeStringTailRecord180
{
public:
	BfmeStringTailRecord180();
private:
	AsciiString m_text;
	unsigned int m_word04;
	unsigned int m_word08;
	unsigned int m_word0C;
	_STL::vector<PlayerAITypeEntry> m_values10;
	Rva0042526Member m_head1C;
	Rva0042526Member m_head68;
};

BfmeStringTailRecord180::BfmeStringTailRecord180()
{
}
