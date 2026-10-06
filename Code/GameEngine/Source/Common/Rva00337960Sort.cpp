// cl: /MD
// ?Rva00337960Sort@@YAXPAVRva003371B1@@0H@Z @0x00337960 57B insertion sort over 20B records.
// Evidence: retail 57B no EH loops first+1 to last calling rowed Rva003371B1 copy 0x003371B1 and rowed linear insert 0x00337819; caller 0x00337C0E final-insertion-sort threshold 16; prev vector clear 0x00337942.
class Rva002E9E70
{
public:
	Rva002E9E70(const Rva002E9E70 &other) throw();
	char m_pad[20];
};

class Rva003371B1
{
public:
	Rva003371B1(const Rva003371B1 &other);
	~Rva003371B1();
	char m_pad[20];
};

void Rva00337819Insert(Rva002E9E70 *first, Rva002E9E70 *last, Rva003371B1 value, int unused);

void Rva00337960Sort(Rva003371B1 *first, Rva003371B1 *last, int unused)
{
	if (first == last)
		return;
	for (Rva003371B1 *cur = first + 1; cur != last; ++cur)
		Rva00337819Insert((Rva002E9E70 *)first, (Rva002E9E70 *)cur, *cur, unused);
}
