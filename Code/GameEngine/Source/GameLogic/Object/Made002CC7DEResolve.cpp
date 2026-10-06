// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva005095FB@Made002CC7DE@@UAEXXZ @0x005095FB (48B).
// WeaponOCLNugget resolve slot 8 of vtable 0x00864588: base resolve
// 0x00507877 then OCL name at +0x12C via default 0x00BBAC1C else +8
// looked up in store at 0x00DFDCCC via rowed findObjectCreationList
// 0x001F07B8 into +0x128. Same slot as base rva00507877.
class ObjectCreationList;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};
extern class ObjectCreationListStore *TheObjectCreationListStore;

#include "ascii_string.h"

class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual void rva00507877();
private:
	unsigned char m_pad[0x128 - 4];
};

class Made002CC7DE : public Rva00507823
{
public:
	Made002CC7DE();
	virtual void rva005095FB();
private:
	const ObjectCreationList *m_128;
	AsciiString m_12C;
};

void Made002CC7DE::rva005095FB()
{
	Rva00507823::rva00507877();
	m_128 = TheObjectCreationListStore->findObjectCreationList(m_12C.str());
}
