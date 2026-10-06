// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D2D13@Rva002D2D13@@QAEXPAXH@Z
// RVA 0x002D2D13 size 32. Calls virtual slot 31 (0x7C) on obj arg twice with
// this and this+4. Evidence: callers at 0x2D649B in unclaimed 0x2D6460;
// callees are two virtual slot 31 calls (no rowed names); neighbours in
// Disp8PtrChaseDwordGetters.cpp and Disp0DwordImmSetters.cpp use defaults
// with no // cl: line for frameless shapes.

class Rva002D2D13
{
public:
	void rva002D2D13(void *obj, int unused);
};

class Slot31Object
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void slot31(void *arg);
};

void Rva002D2D13::rva002D2D13(void *obj, int unused)
{
	((Slot31Object *)obj)->slot31(this);
	((Slot31Object *)obj)->slot31((char *)this + 4);
}
