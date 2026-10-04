// cl: /O1
// ?rva00357D86@ScriptEngine@@QAEXABVAsciiString@@@Z @0x00357D86 38B
// ScriptEngine::rva00357D86: crc AsciiString arg via rowed 0x003ECA13 then
// push_back int to list at +0x1A254.
// Target evidence: callees rowed realcrc 0x003ECA13 and list<int> push_back 0x0005548F,
// same 38B shape as sibling 0x00357DAC at +0x1A260; owner ScriptEngine by neighbours.

class AsciiString;

unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class T, class A>
	class list
	{
	public:
		void push_back(const T &v);

	private:
		void *m_node;
	};
}

class ScriptEngine
{
public:
	void rva00357D86(const AsciiString &s);

private:
	char m_pad[0x1A254];
	_STL::list<int, _STL::allocator<int> > m_list1A254; // +0x1A254
};

void ScriptEngine::rva00357D86(const AsciiString &s)
{
	unsigned long crc = Rva003ECA13Get(s);
	m_list1A254.push_back((int)crc);
}
