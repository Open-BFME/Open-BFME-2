// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Opaque destructors that free a heap member at +0x04 (null-checked), the
// same shape seven times with distinct vtables. The free target at
// 0x00030830 resolves via the matched _free row. Owner identities are
// unproven (opaque Rva names). One ledger row per destructor, landed one
// commit at a time.

extern "C" void free(void *ptr);

class Rva0025BFE3
{
public:
	virtual ~Rva0025BFE3();

private:
	void *m_ptr04;
};

Rva0025BFE3::~Rva0025BFE3()
{
	if (m_ptr04)
		free(m_ptr04);
}

class Rva0030F42E
{
public:
	virtual ~Rva0030F42E();

private:
	void *m_ptr04;
};

Rva0030F42E::~Rva0030F42E()
{
	if (m_ptr04)
		free(m_ptr04);
}

class Rva004FCD14
{
public:
	virtual ~Rva004FCD14();

private:
	void *m_ptr04;
};

Rva004FCD14::~Rva004FCD14()
{
	if (m_ptr04)
		free(m_ptr04);
}

class Rva004FCD49
{
public:
	virtual ~Rva004FCD49();

private:
	void *m_ptr04;
};

Rva004FCD49::~Rva004FCD49()
{
	if (m_ptr04)
		free(m_ptr04);
}

class Rva00578C0E
{
public:
	virtual ~Rva00578C0E();

private:
	void *m_ptr04;
};

Rva00578C0E::~Rva00578C0E()
{
	if (m_ptr04)
		free(m_ptr04);
}

class Rva0057BCEC
{
public:
	virtual ~Rva0057BCEC();

private:
	void *m_ptr04;
};

Rva0057BCEC::~Rva0057BCEC()
{
	if (m_ptr04)
		free(m_ptr04);
}

// The constructor 0x005D66E7 proves a vector base at +4. Its automatic
// destruction emits the already verified null-checked free at 0x005D639A.
#include <vector>
struct BfmeE8 { void *p; unsigned char flag; char pad[3]; };
#include "../../Include/Common/Rva005D639A.h"

Rva005D639A::~Rva005D639A() {}

class Rva004FCA9C
{
public:
	~Rva004FCA9C();
};

class Rva004FCAC9
{
public:
	~Rva004FCAC9();
};

class Rva004FCAF6
{
public:
	~Rva004FCAF6();
};

class Rva004FCD5E
{
public:
	void rva004FCD5E();
};

void Rva004FCD5E::rva004FCD5E()
{
	((Rva004FCA9C *)this)->~Rva004FCA9C();
}

class Rva004FCD63
{
public:
	void rva004FCD63();
};

void Rva004FCD63::rva004FCD63()
{
	((Rva004FCAC9 *)this)->~Rva004FCAC9();
}

class Rva004FCD68
{
public:
	void rva004FCD68();
};

void Rva004FCD68::rva004FCD68()
{
	((Rva004FCAF6 *)this)->~Rva004FCAF6();
}

