// ?rva002B7C74@Rva002B7C74@@QAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc
class Glo012F1028Entry
{
public:
	virtual void *deleteInstance(int flags);
};

namespace _STL
{
template <typename T> class allocator;
template <typename T, typename Allocator> class vector
{
public:
	T *erase(T *first, T *last);
};
}

typedef _STL::vector<void *, _STL::allocator<void *> > Glo012F1028Vector;

class Glo012F1028EntryList
{
public:
	Glo012F1028Entry **m_begin;
	Glo012F1028Entry **m_end;
 Glo012F1028Entry **m_cap;
	Glo012F1028Entry **erase(Glo012F1028Entry **first, Glo012F1028Entry **last);
};

class Rva002B7C74
{
public:
	void rva002B7C74();
private:
	char m_pad[0xCC];
 Glo012F1028EntryList m_first;
	Glo012F1028EntryList m_entries; // +0xD8
};


void Rva002B7C74::rva002B7C74(){
 Glo012F1028EntryList* first=&m_first;
 for(unsigned i=0;i<(unsigned)(first->m_end-first->m_begin);++i)
  {Glo012F1028Entry*entry=first->m_begin[i];::operator delete(entry?entry->deleteInstance(0):0);}
 Glo012F1028EntryList* second=&m_entries;
 for(unsigned i=0;i<(unsigned)(second->m_end-second->m_begin);++i)
  {Glo012F1028Entry*entry=second->m_begin[i];::operator delete(entry?entry->deleteInstance(0):0);}
 ((Glo012F1028Vector*)first)->erase((void**)first->m_begin,(void**)first->m_end);
 ((Glo012F1028Vector*)second)->erase((void**)second->m_begin,(void**)second->m_end);
}
