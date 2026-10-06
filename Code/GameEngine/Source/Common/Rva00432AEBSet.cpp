// cl: /MD
// ?rva00432AEB@Rva00432AEB@@QAEHH@Z, retail 0x00432AEB, 45 bytes.
// Setter at +0x1F0 returning old value; if Rva0043287E check at +0x200 passes,
// notifies TheMouse via vtable slot 0x4C with the new value.
// Evidence: callees rowed 0x0043287E, global TheMouse ?TheMouse@@3PAVMouse@@A,
// callers at 0x00320A42 0x00320E5C 0x00320FAF 0x0054CA6B.
class Rva0043287E
{
public:
	int rva0043287E();
};
class Mouse
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual void _v06();
	virtual void _v07();
	virtual void _v08();
	virtual void _v09();
	virtual void _v10();
	virtual void _v11();
	virtual void _v12();
	virtual void _v13();
	virtual void _v14();
	virtual void _v15();
	virtual void _v16();
	virtual void _v17();
	virtual void _v18();
	virtual void notify(int v);
};
extern Mouse *TheMouse;
class Rva00432AEB
{
public:
	int rva00432AEB(int v);
private:
	char m_pad[0x1F0];
	int m_1F0;
};
int Rva00432AEB::rva00432AEB(int v)
{
	int *slot = (int *)((char *)this + 0x1F0);
	int old = *slot;
	*slot = v;
	if ((unsigned char)((Rva0043287E *)this)->rva0043287E())
		TheMouse->notify(*slot);
	return old;
}
