// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CC5E5..5CC61E: primary +0, vbptr +4, shared virtual
// reference-counted base +8 and its count +C. RET4 consumes MSVC's
// hidden most-derived flag; there are no explicit constructor arguments.
class Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07() {}
private:
	unsigned int count;
};

class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
	Rva005CC5E5();
	virtual void slot0();
	virtual ~Rva005CC5E5();
};

Rva005CC5E5::Rva005CC5E5()
{
}
