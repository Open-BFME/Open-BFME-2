// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ??_ERva000525E5@@QAEPAXI@Z, retail 0x0005277C, 75 bytes. Vector deleting dtor for 0x48-byte Miles audio element.
// Evidence: retail pushes dtor 0x000525E5 plus size 0x48 into ??_M 0x00629110 for array branch then frees via rowed vector delete 0x0002FD80; scalar calls rowed dtor 0x000525E5 then rowed scalar delete 0x0002FD60; flag bits 2+1 ret 4; caller at 0x000610F4.
void operator delete[](void *p);

class Rva000525E5
{
public:
	~Rva000525E5();
private:
	char m_pad[0x48];
};

// ?Rva000525E5DeleteArray@@YAXPAVRva000525E5@@@Z absent-from-retail
void Rva000525E5DeleteArray(Rva000525E5 *array)
{
	delete[] array;
}
