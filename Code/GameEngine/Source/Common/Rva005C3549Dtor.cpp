// cl: /MD /EHsc
// ??1Rva005C3549@@UAE@XZ retail 0x005C3549 54B
// Evidence: vtable 0x00874478 then clear 0x000AD6F4 on +8 then vtable 0x007C6F20; callers 0x00568617 0x005C367E
class Rva000AD6F4
{
public:
	void clear();
};

class Rva005C3549Base
{
public:
	virtual ~Rva005C3549Base() {}
protected:
	int m04;
};

class Rva005C3549 : public Rva005C3549Base
{
public:
	virtual ~Rva005C3549();
private:
	Rva000AD6F4 m08;
};

Rva005C3549::~Rva005C3549()
{
	m08.clear();
}
