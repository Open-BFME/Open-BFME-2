#include <new.h>

class BfmeThingDGG;

#include "../../Include/GameNetwork/Gen007F0130.h"

class Rva007FA990
{
public:
	Rva007FA990(void *arg) throw();
};

BfmeThingDGG *bfmeGoDGG(void *a)
{
	void *p = Gen007F0130::operator new(0xd8);
	if (p != 0)
		return (BfmeThingDGG *)new (p) Rva007FA990(a);
	return 0;
}
