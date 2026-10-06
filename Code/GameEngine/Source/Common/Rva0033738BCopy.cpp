// cl: /MD
// ?Rva0033738BCopy@@YAPAVRva002E9E70@@PAV1@00@Z @0x0033738B (50B): forward
// 20-byte copy loop via rowed copy ctor 0x003372EC; stride 0x14 from the
// retail idiv. Shape matches the 50B forward loop at 0x003319C9 in
// Rva002DFC30CopyLoop.cpp. Caller is 0x00337533.
#include <new.h>
class Rva002E9E70
{
	char _m[0x14];
public:
	Rva002E9E70(const Rva002E9E70 &other) throw();
};
Rva002E9E70 *Rva0033738BCopy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result) throw()
{
	int n = last - first;
	if (n <= 0)
		return result;
	__assume(result != 0);
	for (int i = 0; i < n; ++i)
	{
		__assume(result != 0);
		new (result) Rva002E9E70(*first);
		++first;
		++result;
	}
	return result;
}
typedef Rva002E9E70 *(__cdecl *Rva002E9E70FiveArg)(Rva002E9E70 *, Rva002E9E70 *, Rva002E9E70 *, void *, int);
Rva002E9E70 *Rva00337533Copy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result)
{
	Rva002E9E70FiveArg f = (Rva002E9E70FiveArg)Rva0033738BCopy;
	char tmp;
	return f(first, last, result, &tmp, 0);
}
Rva002E9E70 *Rva00337501Copy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result) throw()
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
		new (result) Rva002E9E70(*last);
	}
	return result;
}
Rva002E9E70 *Rva00337638Copy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result)
{
	Rva002E9E70FiveArg f = (Rva002E9E70FiveArg)Rva00337501Copy;
	char tmp;
	return f(first, last, result, &tmp, 0);
}
typedef Rva002E9E70 *(__cdecl *Rva002E9E70FourArg)(Rva002E9E70 *, Rva002E9E70 *, Rva002E9E70 *, void *);
Rva002E9E70 *Rva003377A1Copy(Rva002E9E70 *first, Rva002E9E70 *last, Rva002E9E70 *result)
{
	Rva002E9E70FourArg f = (Rva002E9E70FourArg)Rva00337638Copy;
	char tmp;
	return f(first, last, result, &tmp);
}
