// cl: /MD
// ?Rva00531F79Chain@@YAPAVRva00531F79@@PAV1@PAG@Z 0x00531F79 34B
// Evidence: leaf with 2 callers in 0x005334DB; two virtual calls to slot 0x80 with wchar ptr then ptr+1; frameless push-esi shape matches /O1 neighbour Rva00532069Check.
class Rva00531F79
{
public:
	virtual void dummy00();
	virtual void dummy01();
	virtual void dummy02();
	virtual void dummy03();
	virtual void dummy04();
	virtual void dummy05();
	virtual void dummy06();
	virtual void dummy07();
	virtual void dummy08();
	virtual void dummy09();
	virtual void dummy10();
	virtual void dummy11();
	virtual void dummy12();
	virtual void dummy13();
	virtual void dummy14();
	virtual void dummy15();
	virtual void dummy16();
	virtual void dummy17();
	virtual void dummy18();
	virtual void dummy19();
	virtual void dummy20();
	virtual void dummy21();
	virtual void dummy22();
	virtual void dummy23();
	virtual void dummy24();
	virtual void dummy25();
	virtual void dummy26();
	virtual void dummy27();
	virtual void dummy28();
	virtual void dummy29();
	virtual void dummy30();
	virtual void dummy31();
	virtual Rva00531F79 *vslot32(unsigned short *s);
};

Rva00531F79 *Rva00531F79Chain(Rva00531F79 *obj, unsigned short *s)
{
	Rva00531F79 *t = obj->vslot32(s);
	return t->vslot32(s + 1);
}
