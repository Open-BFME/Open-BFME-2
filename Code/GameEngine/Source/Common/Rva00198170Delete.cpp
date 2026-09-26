// cl: /O2 /MD
// ?rva00198170@BfmeThingVJS@@QAEPAXI@Z, retail 0x00198170, 30 bytes.
// Gap between AABTree Load 0x00198090 and copy ctor 0x00198190; owner is
// BfmeThingVJS (same class as rowed bfmeClearVJS 0x00197F30 in
// BfmeConv1393.cpp). Calls clear then deletes this if flag&1 and returns
// this; callees rowed (clear and ??3 0x0002FD60). Honest address name for
// BfmeThingVJS method taking UINT returning void*; no donor dtor proven.
void __cdecl operator delete(void *place);

class BfmeThingVJS
{
public:
	void bfmeClearVJS(void);
	void *rva00198170(unsigned int flag);
};

void *BfmeThingVJS::rva00198170(unsigned int flag)
{
	bfmeClearVJS();
	if (flag & 1)
	{
		::operator delete(this);
	}
	return this;
}
