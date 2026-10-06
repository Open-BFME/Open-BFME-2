// cl: /MD
// ?rva0027C208@Rva0027C208@@QAEPAXPAX@Z @0x0027C208 16B
// Evidence: thiscall wrapper pushes incoming arg then virtual slot 0x18 then returns arg; caller 0x00281568.
class Rva0027C208Base
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6(void *x);
};

class Rva0027C208 : public Rva0027C208Base
{
public:
	void *rva0027C208(void *x);
};

void *Rva0027C208::rva0027C208(void *x)
{
	v6(x);
	return x;
}
