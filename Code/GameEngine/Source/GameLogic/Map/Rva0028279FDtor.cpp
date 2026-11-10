// cl: /MD /EHs /D_CRTIMP=
// Native 0x0028279F..0x002827F3: clear, notify slot-zero listeners with
// this, destroy the record vector at +0x14, then release the listener buffer.
// Caller 0x002833E7 owns this object's lifetime. The separate clear helper
// at 0x002827F3 has pointer vectors at +4/+0x10, unlike this object's layout;
// its address-derived class name is therefore not this destructor's identity.
#include <stdlib.h>

struct TargetRef00217D4C;
struct Rva0027EA49
{
    ~Rva0027EA49();
    int m_00;
    TargetRef00217D4C *m_04;
};

namespace _STL
{
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
    ~vector();
    T *m_start;
    T *m_finish;
    T *m_end_of_storage;
};
}

#include "../../../Include/Common/Rva00281A15Listener.h"

struct Rva00280B1ACall;
class Rva00281A15List
{
public:
	void forEach(void (Rva00281A15Listener::*notify)(void *), void *arg);
	void apply(const Rva00280B1ACall &call);
	~Rva00281A15List()
	{
	    if (m_begin)
	        free(m_begin);
	}
	Rva00281A15Listener **m_begin; // +0x00 +0x00
	Rva00281A15Listener **m_end; // +0x04 +0x04
	Rva00281A15Listener **m_capacity; // +0x08 +0x08
	unsigned int m_index; // +0x0C +0x0C
};

class Rva00282135
{
public:
    void rva00282135();
};

class Rva0028279F : public Rva00281A15List
{
public:
    ~Rva0028279F();
private:
    unsigned int m_word10;
    _STL::vector<Rva0027EA49, _STL::allocator<Rva0027EA49> > m_records14;
};

Rva0028279F::~Rva0028279F()
{
    reinterpret_cast<Rva00282135 *>(this)->rva00282135();
    forEach(&Rva00281A15Listener::notify, this);
}
