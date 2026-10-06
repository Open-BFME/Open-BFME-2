// cl: /DNDEBUG /MD /EHsc
// ??0Rva0043B23E@@QAE@ABHABVRva0043B196@@@Z @0x0043B23E 29B
// Evidence: 2-arg ctor int-first plus Rva0043B196 at +4 via rowed copy ctor 0x43B196; caller 0x43B89B passes key plus 0x43B208 temp.
class Rva0043B196
{
public:
	Rva0043B196(const Rva0043B196 &src);
private:
	char m_data[0x88];
};

class Rva0043B23E
{
public:
	Rva0043B23E(const int &first, const Rva0043B196 &second);
	Rva0043B23E(const Rva0043B23E &src);
private:
	int m_first;
	Rva0043B196 m_second;
};

Rva0043B23E::Rva0043B23E(const int &first, const Rva0043B196 &second)
	: m_first(first)
	, m_second(second)
{
}

Rva0043B23E::Rva0043B23E(const Rva0043B23E &src)
	: m_first(src.m_first)
	, m_second(src.m_second)
{
}

inline void *operator new(unsigned int, Rva0043B23E *p)
{
	return p;
}

void __cdecl Rva0043B2D0Construct(Rva0043B23E *dst, const Rva0043B23E &src)
{
	if (dst != 0)
		new (dst) Rva0043B23E(src);
}
