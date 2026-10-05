// cl: /O1 /DNDEBUG /MD
//
// Three ebp-frame thiscall wrappers from dump range 18 (2x37B + 40B) that
// chain the Rva003EE900 family's rowed two-int forwards. Each builds a
// 12-byte task block on the stack, resolves it through the pinned 0x003EE7CA
// virtual-dispatch helper (thiscall int (int, int*), returns its pointer
// argument), then forwards to its rowed second callee. The casts reuse the
// home TU's reinterpret-cast idiom (Rva003EE900Forward.cpp); every cast is
// free at the call sites.
//
// ?rva003EEE8E@Rva003EEE8E@@QAEXH@Z @0x003EEE8E: nested second-first flow
// into rowed 0x003EEB9F.
// ?rva003EEF13@Rva003EEF13@@QAEXH@Z @0x003EEF13: nested second-first flow
// into rowed 0x003EEBC4.
// ?rva003EE8D8@Rva003EE8D8@@QAEXH@Z @0x003EE8D8: sequential flow (block
// re-pushed) into rowed 0x003EE89E.
class Rva003EE7CA
{
public:
	int rva003EE7CA(int a, int b);
};

class Rva003EE89E
{
public:
	void rva003EE89E(int a, int b);
};

class Rva003EEB9F
{
public:
	void rva003EEB9F(int a, int b);
};

class Rva003EEBC4
{
public:
	void rva003EEBC4(int a, int b);
};

class Rva003EEE8E
{
public:
	void rva003EEE8E(int arg);
};

class Rva003EEF13
{
public:
	void rva003EEF13(int arg);
};

class Rva003EE8D8
{
public:
	void rva003EE8D8(int arg);
};

void Rva003EEE8E::rva003EEE8E(int arg)
{
	int tmp[3];
	int r = ((Rva003EE7CA *)this)->rva003EE7CA((int)tmp, arg);
	((Rva003EEB9F *)this)->rva003EEB9F(arg, r);
}

void Rva003EEF13::rva003EEF13(int arg)
{
	int tmp[3];
	int r = ((Rva003EE7CA *)this)->rva003EE7CA((int)tmp, arg);
	((Rva003EEBC4 *)this)->rva003EEBC4(arg, r);
}

void Rva003EE8D8::rva003EE8D8(int arg)
{
	int tmp[3];
	((Rva003EE7CA *)this)->rva003EE7CA((int)tmp, arg);
	((Rva003EE89E *)this)->rva003EE89E(arg, (int)tmp);
}
