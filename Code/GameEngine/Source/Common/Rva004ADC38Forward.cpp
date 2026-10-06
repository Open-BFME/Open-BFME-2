// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004ADC38@Rva004ADC38@@QAEXHHHHH@Z @0x004ADC38 80B ret 0x14.
// The owner lives at this-0x18. When it has no entry from 0x0028AC4E, or
// that entry's 0x001E46E1 float is not greater than zero, forward the five
// arguments to 0x004500A3 and set status 0x4A.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object;

struct Rva0028AC4EEntry;

class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	void setStatus(ObjectStatusTypes status, bool set);
};

class Rva004500A3
{
public:
	void rva004500A3(int a, int b, int c, int d, int e);
};

class Rva004ADC38
{
public:
	void rva004ADC38(int a, int b, int c, int d, int e);
};

void Rva004ADC38::rva004ADC38(int a, int b, int c, int d, int e)
{
	Object *owner = *(Object **)((char *)this - 0x18);
	const Rva0028AC4EEntry *entry = owner->rva0028AC4E();
	if (entry == 0 || ((Rva001E46E1 *)entry)->rva001E46E1(owner) != 0.0f)
	{
		((Rva004500A3 *)this)->rva004500A3(a, b, c, d, e);
		owner->setStatus((ObjectStatusTypes)0x4A, true);
	}
}
