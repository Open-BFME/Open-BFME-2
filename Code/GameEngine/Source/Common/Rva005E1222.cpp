// cl: /O1 /Oy- /MD
// ?invoke@Rva005E1222@@QAE?AURva005E1222Value@@XZ @ 0x005E1222 (36B)
// Native 005E1222..005E1246 returns an opaque eight-byte handle through
// its caller's output pointer. Target invokes a one-word member callback
// at +0xC on the object at +0x8 with a separate eight-byte output temporary.

struct Rva005E1222Value {
	void *first;
	void *second;
	Rva005E1222Value();
	Rva005E1222Value(const Rva005E1222Value &v) : first(v.first), second(v.second) {}
	~Rva005E1222Value() {}
};

class Rva005E1222Target {};

class Rva005E1222 {
	char unknown00[8];
	Rva005E1222Target *object;
	Rva005E1222Value (Rva005E1222Target::*method)();
public:
	Rva005E1222Value invoke();
};

Rva005E1222Value Rva005E1222::invoke()
{
	return (object->*method)();
}
