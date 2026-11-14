// cl: /MD /EHs
// ??1Rva005F23B2@@QAE@XZ, retail 0x005F23B2, 84 bytes.
// Evidence: chain lane calls rowed clear 0x005F22D2 plus forEach 0x005F2230 with forwarder 0x005CB260 plus member dtor 0x005F21F8 plus free 0x00030830; consecutive with ctor 0x005F2381 and method 0x005F2406.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

class Rva005F2230Listener
{
public:
	virtual void notify(void *);
};

class Rva005F2230List
{
public:
	void forEach(void (Rva005F2230Listener::*notify)(void *), void *arg);
};

#include "../../Include/Common/Rva005CB260.h"

#include "../../Include/GameClient/Rva005F22D2.h"

class Rva005F20C5
{
public:
	~Rva005F20C5();
private:
	void *m_head00;
	int m_flag04;
};

struct Rva005F23B2List
{
	void *m_begin00;
	void *m_end04;
	void *m_cap08;
	unsigned int m_index0C;
	~Rva005F23B2List()
	{
		if (m_begin00 != 0)
			free(m_begin00);
	}
};

class Rva005F23B2
{
public:
	~Rva005F23B2();
private:
	Rva005F23B2List m_list00;
	Rva005F20C5 m_tree10;
};

Rva005F23B2::~Rva005F23B2()
{
	((Rva005F22D2 *)this)->rva005F22D2();
	((Rva005F2230List *)&m_list00)->forEach((void (Rva005F2230Listener::*)(void *))static_cast<void (Rva005CB260::*)()>(&Rva005CB260::rva005CB260), this);
}
