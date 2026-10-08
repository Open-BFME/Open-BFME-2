// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	~Rva0030B9DD();
private:
	char unknown00[0x2C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
private:
	Rva0030B9DD container;
	bool changed;
};

Rva00330C50::Rva00330C50() : container(0)
{
	changed = true;
}

class AreaPolygonBase { public: void reserve(int); };
// Native330AA6 is an8-byte terminal jump to rowed AreaPolygonBase::reserve
// at30B96B with the measured container adjustment8. The following16 bytes
// form a separate float virtual dispatch, not part of this reserve wrapper.
void Rva00330C50::rva00330AA6(int count)
{
 reinterpret_cast<AreaPolygonBase*>(&container)->reserve(count);
}
