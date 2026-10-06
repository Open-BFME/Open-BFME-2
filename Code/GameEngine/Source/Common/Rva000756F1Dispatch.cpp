// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva000756F1Dispatch@@YA_NHHHHH@Z 0x000756F1 52B: free function indexed via g_00DE1F2C null check then virtual slot 3 call with four args clears g_00DE1F5C on null; neighbours Rva000756BFSelect/Rva00075725Check pattern
class Rva000756F1Item
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual bool Slot3(int a1, int a2, int a3, int a4);
};

extern Rva000756F1Item * volatile g_00DE1F2C[];
extern int g_00DE1F5C;

bool __cdecl Rva000756F1Dispatch(int index, int a1, int a2, int a3, int a4)
{
	Rva000756F1Item * volatile *slot = &g_00DE1F2C[index];
	if (*slot != 0)
		return (*slot)->Slot3(a1, a2, a3, a4);
	g_00DE1F5C &= 0;
	return false;
}
