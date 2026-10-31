// cl: /EHsc /DNDEBUG /MD
// ?clone@Rva00541F1F@@QBE?AVRva0053FC99@@XZ, retail 0x005421AA, 123 bytes (EH).
// Clone slot: copies the animation into a fresh 0x64-byte object and
// hands it back in a reference-counted pointer. The raw pointer is attached
// by the rowed 0x0053FC81 setter, copied out into the hidden result by the
// rowed 0x0053FC99 setter (single-pointer source layout matches the holder),
// and the holder's inline destructor releases through the rowed 0x0053FA32.
// Twin of 0x00540A88 (0x44 bytes, copy ctor 0x00540845).
class Rva0053F8E5DwordCounter;
class Rva0053FA0A
{
public:
	void release();
};

struct Rva0053FC99Src
{
	Rva0053F8E5DwordCounter *m_ptr;
};

class Rva0053FC81
{
public:
	Rva0053FC81 *rva0053FC81(Rva0053F8E5DwordCounter *p);
	Rva0053FC81(Rva0053F8E5DwordCounter *ptr) { rva0053FC81(ptr); }
	~Rva0053FC81()
	{
		if (m_ptr)
			((Rva0053FA0A *)m_ptr)->release();
	}

	Rva0053F8E5DwordCounter *m_ptr;
};

class Rva0053FC99
{
public:
	Rva0053FC99 *rva0053FC99(Rva0053FC99Src *s);
	Rva0053FC99(const Rva0053FC81 &h) { rva0053FC99((Rva0053FC99Src *)&h); }

	~Rva0053FC99()
	{
		if (m_ptr)
			((Rva0053FA0A *)m_ptr)->release();
	}

private:
	Rva0053F8E5DwordCounter *m_ptr;
};

#include <new>

class Rva00541F1F
{
public:
	Rva00541F1F(const Rva00541F1F &other);	// 0x00541F1F
	Rva0053FC99 clone() const;

private:
	char m_data[0x64];
};
Rva0053FC99 Rva00541F1F::clone() const
{
	Rva0053F8E5DwordCounter *raw = (Rva0053F8E5DwordCounter *)new Rva00541F1F(*this);
	{
		Rva0053FC81 holder(raw);
		return Rva0053FC99(holder);
	}
}
