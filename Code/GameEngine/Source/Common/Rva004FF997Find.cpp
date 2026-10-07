// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FF997 (31B): map-find via pinned 0x388F63 on the +0x1C container
// with the int arg by address; when the result equals the +0x1C header
// return 0 else the +0x14 field. Identities unproven.

class Rva00388F63Map
{
public:
	void *find(int *key);
};

class Rva004FF997Owner
{
public:
	int rva004FF997(int key);

private:
	char m_pad[0x1C];	// +0x00..0x1B
	void *m_1C_head;	// +0x1C header/end for the find compare
};

int Rva004FF997Owner::rva004FF997(int key)
{
	void *node = ((Rva00388F63Map *)&m_1C_head)->find(&key);
	if (node == m_1C_head)
		return 0;
	return *(int *)((char *)node + 0x14);
}
