// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00357DD2@ScriptEngine@@QAEXABVAsciiString@@@Z @0x00357DD2 38B
// ScriptEngine::rva00357DD2: crc AsciiString arg via rowed 0x003ECA13 then
// push_front int to list at +0x1A264 (matched dtor m_list1A264 sibling of
// 0x00357DAC m_list1A260 which uses push_back).
// Target evidence: same shape as 0x00357DAC (38B frame push ebp), callees
// rowed realcrc 0x003ECA13 and list<int> push_front 0x00392076, layout
// +0x1A264 from ScriptEngine_dtor. Owner proven by sibling, honest address.

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
		void push_front(const T &v);

	private:
		void *m_node;
	};
}

class ScriptEngine
{
public:
	void rva00357DD2(const AsciiString &s);

private:
	char m_pad[0x1A264];
	_STL::list<int, _STL::allocator<int> > m_list1A264; // +0x1A264
};

void ScriptEngine::rva00357DD2(const AsciiString &s)
{
	unsigned long crc = Rva003ECA13Get(s);
	m_list1A264.push_front((int)crc);
}
