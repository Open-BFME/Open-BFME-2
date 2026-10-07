// cl: /MD /O1 /arch:SSE /G7
// ?Rva002B3ED6Get@@YAHPAVRva002B3ED6Object@@H@Z @0x002B3ED6 36B.
// Address name; caller pushes an object and index at 0x005F5D93/0x005F5DCB.
// Retail reads an IndexedField pointer at +0x78, calls its rowed get, then
// calls pinned Rva002B3E7ECheck. Field type/layout follow the rowed callee.
class Rva0040CB3AIndexedField
{
public:
	int get(int index) const;
};

class Rva002B3ED6Object
{
public:
	char m_pad00[0x78];
	Rva0040CB3AIndexedField *m_indexedField;
};

bool Rva002B3E7ECheck();

int Rva002B3ED6Get(Rva002B3ED6Object *object, int index)
{
	if (object->m_indexedField->get(index) != 0 && Rva002B3E7ECheck())
		return true;
	return false;
}
