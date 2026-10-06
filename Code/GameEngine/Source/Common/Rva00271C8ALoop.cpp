// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00271C8A@Rva00271C8A@@QAEXPBH0@Z retail 0x00271C8A 44 bytes.
// 19-dword loop this[i] = ((~a[i] & this[i]) | b[i]). Unlocks 7 callers
// including 0x00274176 0x0027434D 0x00275376. Prev/next in Common with /O1.
// Evidence: 7 callers plus prev 0x00271892 plus next 0x002722AA plus /O1
// push-pop 19 plus dec-jne count-down.
class Rva00271C8A
{
public:
	void rva00271C8A(const int *a, const int *b);
};
void Rva00271C8A::rva00271C8A(const int *a, const int *b)
{
	int *t = (int *)this;
	for (int i = 0; i < 19; ++i)
	{
		t[i] = ((~a[i] & t[i]) | b[i]);
	}
}
