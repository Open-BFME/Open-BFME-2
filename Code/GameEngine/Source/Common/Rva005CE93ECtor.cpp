// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CE93E..5CE9B4: primary +0, vbptr +4, base payload +8,
// derived pointer +C, Rva0007DF07 virtual base +10 and count +14.
// The derived pointer is the third explicit argument's +14 field.
class Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07() {}
private:
	unsigned int count;
};

struct Rva005CE93EContext
{
	char unknown00[0x14];
	void *source;
};

class Rva005CC698 : public virtual Rva0007DF07
{
public:
	Rva005CC698(void *, void *, Rva005CE93EContext *);
	virtual void slot0();
	virtual ~Rva005CC698();
private:
	void *payload;
};

class Rva005CE93E : public Rva005CC698
{
public:
	Rva005CE93E(void *, void *, Rva005CE93EContext *);
	virtual ~Rva005CE93E();
private:
	void *source;
};

Rva005CE93E::Rva005CE93E(void *a, void *b, Rva005CE93EContext *c)
	: Rva005CC698(a, b, c), source(c->source)
{
}
