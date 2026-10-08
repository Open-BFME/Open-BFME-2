// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// class-gate: allow AsciiString the shared shim inlines isEmpty and compare; retail calls out-of-line 0x1E2F and 0x69D6
// ?rva002E1CA7@Rva002E2903Player@@QAE_NPAVUnitRevivalEntry@@@Z @0x002E1CA7 123B
// Living-world player test on a revival entry: true when TheGameLogic reports
// the 0x0023C6A4 mode, otherwise walks the player's element vector and returns
// true when an element with a non-empty name refuses the entry's +0xD4 string.
// Evidence: TheGameLogic global 0xDFE78C; element name AsciiString at +0x18;
// vector begin/end at +0x1B8/+0x1BC; helper 0x004069D6 is address-named.
#include <vector>

class GameLogic;
extern GameLogic *TheGameLogic;
class UnitRevivalEntry;

class Rva0023C6A4
{
public:
	bool rva0023C6A4();
};

class AsciiString
{
public:
	bool isEmpty() const;
	int compare(const AsciiString &) const;
private:
	void *m_data;
};

struct Rva002E2903Element
{
	char m_pad00[0x18];
	AsciiString m_name;
};

class Rva002E2903Player
{
public:
	bool rva002E1CA7(UnitRevivalEntry *entry);
private:
	char m_pad00[0x1B8];
	_STL::vector<Rva002E2903Element *> m_elements;
};

bool Rva002E2903Player::rva002E1CA7(UnitRevivalEntry *entry)
{
	if (((Rva0023C6A4 *)TheGameLogic)->rva0023C6A4())
	{
		return true;
	}
	bool result = false;
	for (unsigned int i = 0; i < m_elements.size(); ++i)
	{
		Rva002E2903Element *element = m_elements[i];
		if (element->m_name.isEmpty())
		{
			continue;
		}
		if (element->m_name.compare(*reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(entry) + 0xD4)) == 0)
		{
			result = true;
			break;
		}
	}
	return result;
}
