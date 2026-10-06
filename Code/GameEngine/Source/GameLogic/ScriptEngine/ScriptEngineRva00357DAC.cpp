// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00357DAC@ScriptEngine@@QAEXABVAsciiString@@@Z @0x00357DAC 38B
// ScriptEngine::rva00357DAC: crc AsciiString arg via rowed 0x003ECA13 then
// push_back int to list at +0x1A260 (matched dtor m_list1A260).
// Target evidence: caller 0x0021670E passes TheScriptEngine plus AsciiString,
// callees rowed realcrc 0x003ECA13 and list<int> push_back 0x0005548F,
// layout +0x1A260 from ScriptEngine_dtor. Owner proven by caller, honest
// address name (real method identity not proven).

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
	void rva00357DAC(const AsciiString &s);

private:
	char m_pad[0x1A260];
	_STL::list<int, _STL::allocator<int> > m_list1A260; // +0x1A260
};

void ScriptEngine::rva00357DAC(const AsciiString &s)
{
	unsigned long crc = Rva003ECA13Get(s);
	m_list1A260.push_back((int)crc);
}
