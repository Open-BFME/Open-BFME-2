// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Clean reconstruction of the three-field pointer-array RemoveAll operation.

// BFME releases this array through the CRT free import thunk at 0x00628F98
// (jmp [msvcr71.dll!free]), not through the game's own _free at 0x00030830.
// CrtFree is the typed project name for this existing PE-proven import veneer.
void __cdecl CrtFree(void *block);

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
		CrtFree(values);
		values = 0;
	}
	count = 0;
	capacity = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
