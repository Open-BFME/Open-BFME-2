// cl: /O1 /DNDEBUG /MD
//
// ?rva003EF041@Rva003EF041@@QAEXXZ @0x003EF041 37B, dump range 18. Guards on
// this+0x14: resolves a 12-byte stack task block through the pinned
// 0x003EE7CA virtual dispatch, then forwards the result to the pinned
// 0x003EEE64 chain worker. The block address taken is 8 into the 12-byte
// frame with the array base itself (the helper's int-typed first slot
// carries a pointer, as in the Rva003EEE8EChain sisters).
class Rva003EE7CA
{
public:
	int rva003EE7CA(int a, int b);
};

class Rva003EEE64
{
public:
	void rva003EEE64(int x);
};

class Rva003EF041
{
public:
	void rva003EF041();
private:
	char m_pad[0x14];
	int m_14;
};

void Rva003EF041::rva003EF041()
{
	if (m_14 != 0) {
		int tmp[3];
		int r = ((Rva003EE7CA *)this)->rva003EE7CA((int)tmp, m_14);
		((Rva003EEE64 *)this)->rva003EEE64(r);
	}
}
