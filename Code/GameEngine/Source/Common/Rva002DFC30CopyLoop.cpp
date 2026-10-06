// cl: /MD
// ?Rva003319C9Copy@@YAPAVRva002DFC30@@PAV1@00@Z @0x003319C9 50B: forward 12-byte copy loop via rowed copy ctor 0x00331759; caller 0x00331BA2; twin backward 0x0033177E
#include <new.h>
class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other) throw();
private:
	void *m_item;
};
class Rva002DFC30
{
	int m_00;
	BfmeSubA m_04;
	char m_08;
public:
	Rva002DFC30(const Rva002DFC30 &other) throw();
};
Rva002DFC30 *Rva003319C9Copy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result) throw()
{
	int n = last - first;
	if (n <= 0)
		return result;
	__assume(result != 0);
	for (int i = 0; i < n; ++i)
	{
		__assume(result != 0);
		new (result) Rva002DFC30(*first);
		++first;
		++result;
	}
	return result;
}
Rva002DFC30 *Rva0033177ECopy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result) throw()
{
	int n = last - first;
	if (n <= 0)
		return result;
	__assume(result != 0);
	for (int i = 0; i < n; ++i)
	{
		--last;
		--result;
		__assume(result != 0);
		new (result) Rva002DFC30(*last);
	}
	return result;
}
typedef Rva002DFC30 *(__cdecl *Rva002DFC30FiveArg)(Rva002DFC30 *, Rva002DFC30 *, Rva002DFC30 *, void *, int);
typedef Rva002DFC30 *(__cdecl *Rva002DFC30FourArg)(Rva002DFC30 *, Rva002DFC30 *, Rva002DFC30 *, void *);
Rva002DFC30 *Rva00331B05Copy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result)
{
	Rva002DFC30FiveArg f = (Rva002DFC30FiveArg)Rva0033177ECopy;
	char tmp;
	return f(first, last, result, &tmp, 0);
}
Rva002DFC30 *Rva00331B8FCopy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result)
{
	Rva002DFC30FiveArg f = (Rva002DFC30FiveArg)Rva003319C9Copy;
	char tmp;
	return f(first, last, result, &tmp, 0);
}
// ?Rva00331E0DCopy@@YAPAVRva002DFC30@@PAV1@00@Z @0x00331E0D 27B: 4-arg forwarder
// over the rowed backward forwarder at 0x331B05; sole caller is 0x32028.
Rva002DFC30 *Rva00331E0DCopy(Rva002DFC30 *first, Rva002DFC30 *last, Rva002DFC30 *result)
{
	Rva002DFC30FourArg f = (Rva002DFC30FourArg)Rva00331B05Copy;
	char tmp;
	return f(first, last, result, &tmp);
}
