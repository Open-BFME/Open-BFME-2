// cl: /Ob1 /EHs-c-
// stlport
#include <vector>

void __cdecl operator delete(void *);

struct Rva004DFCB0Element { unsigned word0;Rva004DFCB0Element& operator=(const Rva004DFCB0Element&b){if(this!=&b){word0=b.word0;}return *this;}bool operator<(const Rva004DFCB0Element&)const;bool operator==(const Rva004DFCB0Element&)const; };

struct Gen_001DB2C0
{
	void **m_begin;
	void **m_end;
	void **m_capacity;
	int m_key;
	Gen_001DB2C0 *m_next;

	Gen_001DB2C0(int key);
	~Gen_001DB2C0();
};

class Rva001DB3E0List
{
public:
	~Rva001DB3E0List();

private:
	Gen_001DB2C0 *m_current;
	Gen_001DB2C0 *m_head;
	void rva004DE683(int key, void *value);
};

Rva001DB3E0List::~Rva001DB3E0List()
{
	while (m_head != 0)
	{
		Gen_001DB2C0 *current = m_head;
		m_current = current;
		m_head = current->m_next;
		current->~Gen_001DB2C0();
		::operator delete(current);
	}
}


// ?rva004DE683@Rva001DB3E0List@@IAEXHPAX@Z @ 0x004DE683 (125B).
// Target evidence: m_current is reset from m_head; the chain uses Gen_001DB2C0
// keys at +0x0C and next pointers at +0x10. A matching node keeps unique
// pointers in its vector; otherwise a node is constructed and prepended.
// Constructor 0x004DE5A4 and destructor 0x004DE5D0 support the node layout;
// push_back 0x004DFCB0 is rowed. Method name and collection purpose stay opaque.
void Rva001DB3E0List::rva004DE683(int key, void *value)
{
	m_current = m_head;
	Gen_001DB2C0 *current = m_head;
	while (current != 0) {
		if (current->m_key == key) {
			_STL::vector<Rva004DFCB0Element> *values = (_STL::vector<Rva004DFCB0Element> *)current;
			for (unsigned int i = 0; i < values->size(); ++i) {
				if ((*values)[i].word0 == (unsigned)value)
					return;
			}
			values->push_back(*(const Rva004DFCB0Element *)&value);
			return;
		}
		current = current->m_next;
	}

	current = new Gen_001DB2C0(key);
	((_STL::vector<Rva004DFCB0Element> *)current)->push_back(*(const Rva004DFCB0Element *)&value);
	if (m_head != 0)
		current->m_next = m_head;
	m_head = current;
}
