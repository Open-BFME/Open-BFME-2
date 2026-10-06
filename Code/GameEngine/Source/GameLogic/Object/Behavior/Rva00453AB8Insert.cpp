// cl: /MD
// ?Rva00453AB8Insert@@YGPAPAXPAPAXPAXABVRva004530ED@@@Z @ 0x00453AB8 37B: list insert via rowed 0x004534A1 create then splice between pos and pos->next. Evidence: callee rowed Create; caller 0x00453B06 passes (&arg edx arg); same shape as Rva00283401Insert 0x00283401 and Rva00239D02Insert 0x00239D02.
class Rva004530ED;
void *__stdcall Rva004534A1Create(const Rva004530ED &src);

void **__stdcall Rva00453AB8Insert(void **out, void *pos, const Rva004530ED &val)
{
	void *node = Rva004534A1Create(val);
	void *next = ((void **)pos)[1];
	((void **)node)[0] = pos;
	((void **)node)[1] = next;
	((void **)next)[0] = node;
	((void **)pos)[1] = node;
	*out = node;
	return out;
}
