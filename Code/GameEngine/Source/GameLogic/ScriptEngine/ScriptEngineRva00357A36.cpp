// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357A36@ScriptEngine@@QAE_NABVAsciiString@@_N@Z, retail 0x00357A36 97B unlock.
// Evidence: CRC Rva003ECA13Get 0x3ECA13, std::find ObjectID 0x29B694,
// list erase 0x438539 folded ObjectID via pin; list at +0x1A254 from ScriptEngine_dtor.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class ScriptEngine
{
public:
	bool rva00357A36(const AsciiString &s, bool remove);

private:
	char m_pad[0x1A254];
	_STL::list<ObjectID, _STL::allocator<ObjectID> > m_list1A254; // +0x1A254
};

bool ScriptEngine::rva00357A36(const AsciiString &s, bool remove)
{
	ObjectID crc = (ObjectID)Rva003ECA13Get(s);
	_STL::list<ObjectID, _STL::allocator<ObjectID> >::iterator it = _STL::find(m_list1A254.begin(), m_list1A254.end(), crc);
	if (it != m_list1A254.end())
	{
		if (remove)
			m_list1A254.erase(it);
		return true;
	}
	return false;
}
