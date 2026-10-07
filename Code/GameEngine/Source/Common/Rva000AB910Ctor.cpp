// cl: /MD /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// stlport
// ??0Rva000AB910@@QAE@ABVAsciiString@@@Z @ 0x000AB910, 70 bytes. Retail
// copies a narrow string and initializes two hash maps; member identities are inferred from offsets.
#include "ascii_string.h"
#include <hash_map>

struct Rva000AB8F1Element { char bytes[1]; bool operator<(const Rva000AB8F1Element&) const; bool operator==(const Rva000AB8F1Element&) const; };
namespace _STL { template<> struct hash<Rva000AB8F1Element> { unsigned operator()(const Rva000AB8F1Element&) const; }; }

class Rva000AB910
{
public:
	Rva000AB910(const AsciiString &name);
private:
	AsciiString m_name;
	int m_value;
	_STL::hash_map<int, Rva000AB8F1Element> m_first;
	_STL::hash_map<int, Rva000AB8F1Element> m_second;
};

Rva000AB910::Rva000AB910(const AsciiString &name)
:
	m_name(name),
	m_value(0),
	m_first(),
	m_second()
{
}
