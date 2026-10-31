// cl: /EHsc /DNDEBUG /MD
// ?clone@Rva00540845@@QBE?AVRva0053FC99@@XZ, retail 0x00540A88, 123 bytes (EH).
// Clone slot: copies the camera animation into a fresh 0x44-byte object and
// hands it back in a reference-counted pointer. The raw pointer is attached
// by the rowed 0x0053FC81 setter, copied out into the hidden result by the
// rowed 0x0053FC99 setter (single-pointer source layout matches the holder),
// and the holder's inline destructor releases through the rowed 0x0053FA32.
// Twin of 0x005421AA (0x64 bytes, copy ctor 0x00541F1F).
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

class Rva00540845
{
public:
	Rva00540845(const Rva00540845 &other);	// 0x00540845
	Rva0053FC99 clone() const;

private:
	char m_data[0x44];
};
Rva0053FC99 Rva00540845::clone() const
{
	Rva0053F8E5DwordCounter *raw = (Rva0053F8E5DwordCounter *)new Rva00540845(*this);
	{
		Rva0053FC81 holder(raw);
		return Rva0053FC99(holder);
	}
}
