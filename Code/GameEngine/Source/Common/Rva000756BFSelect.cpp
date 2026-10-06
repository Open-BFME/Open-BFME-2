// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva000756BFSelect@@YA_NHHH@Z 0x000756BF 50B: free function indexed via g_00DE1F2C null check then virtual slot 2 call with two args stores index to g_00DE1F5C on true; neighbours Rva00075695Notify/Rva00075725Check pattern
class Rva000756BFItem
{
public:
	virtual void f0();
	virtual void f1();
	virtual bool Slot2(int a1, int a2);
};

extern Rva000756BFItem * volatile g_00DE1F2C[];
extern int g_00DE1F5C;

bool __cdecl Rva000756BFSelect(int index, int a1, int a2)
{
	Rva000756BFItem * volatile *slot = &g_00DE1F2C[index];
	if (*slot != 0) {
		bool ok = (*slot)->Slot2(a1, a2);
		if (ok)
			g_00DE1F5C = index;
		return ok;
	}
	return false;
}
