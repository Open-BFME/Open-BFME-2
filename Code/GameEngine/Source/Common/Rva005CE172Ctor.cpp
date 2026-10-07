// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CE172..5CE1EB: primary +0, vbptr +4, base payload +8,
// derived context +C, shared reference-counted virtual base +10.
// The third explicit argument supplies the +8 object whose +20 field
// receives this instance. The base call receives all three arguments.
class Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07() {}
private:
	unsigned int count;
};

struct Rva005CE172Link
{
	char unknown00[0x20];
	void *owner;
};

struct Rva005CE172Context
{
	char unknown00[8];
	Rva005CE172Link *link;
};

class Rva005E87E0 : public virtual Rva0007DF07
{
public:
	Rva005E87E0(void *, void *, Rva005CE172Context *);
	virtual void slot0();
	virtual ~Rva005E87E0();
private:
	void *payload;
};

class Rva005CE172 : public Rva005E87E0
{
public:
	Rva005CE172(void *, void *, Rva005CE172Context *);
	virtual ~Rva005CE172();
private:
	Rva005CE172Link *context;
};

Rva005CE172::Rva005CE172(void *a, void *b, Rva005CE172Context *c)
	: Rva005E87E0(a, b, c), context(c->link)
{
	context->owner = this;
}
