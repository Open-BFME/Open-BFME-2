// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Clean reconstruction of the three-field pointer-array RemoveAll operation.

// BFME releases this array through the CRT free import thunk at 0x00628F98
// (jmp [msvcr71.dll!free]), not through the game's own _free at 0x00030830.
// The thunk row is ?ji_00628F98@@YAXXZ (void(void)); it forwards the caller's
// stack to CRT free, so the pushed pointer is passed through a cast.
void __cdecl ji_00628f98();

class Rva009F68C6PointerArray
{
public:
	void RemoveAll();

private:
	void *values;
	int count;
	int capacity;
};

void Rva009F68C6PointerArray::RemoveAll()
{
	if (values != 0) {
		((void (__cdecl *)(void *))&ji_00628f98)(values);
		values = 0;
	}
	count = 0;
	capacity = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeCallDXB@BfmeSubDXB@@QAEXXZ=?RemoveAll@Rva009F68C6PointerArray@@QAEXXZ")
