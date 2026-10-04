// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357F11@ScriptEngine@@QAEXHABVAsciiString@@H@Z @0x00357F11 50B
// ScriptEngine per-player timer push: m_lists1A358[index].push_back({crc,val}).
// Evidence: CRC 0x3ECA13 plus rowed list<BfmeSpecialPowerTimer8>::push_back 0x4DE74D,
// lea index*4+0x1A358, ret 0xc void 3-arg; same shape as sibling 0x00357EDF at 0x1A308.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class ScriptEngine
{
public:
	void rva00357F11(int playerIndex, const AsciiString &s, int val);
private:
	char m_pad[0x1A358];
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > m_lists1A358[20];
};

void ScriptEngine::rva00357F11(int playerIndex, const AsciiString &s, int val)
{
	BfmeSpecialPowerTimer8 timer;
	timer.m_templateID = Rva003ECA13Get(s);
	timer.m_readyFrame = (unsigned int)val;
	m_lists1A358[playerIndex].push_back(timer);
}
