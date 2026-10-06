// cl: /DNDEBUG /MD /EHsc
// ?rva0027F4F8@Rva0027F4F8@@QAEPAXH@Z @0x0027F4F8 33B. Linear search of
// 8-byte entries from [this+0x14] to [this+0x18]: return second dword
// where first equals int arg else NULL. Caller 0x00283845.
struct Rva0027F4F8Entry {
	int key;
	void *value;
};
class Rva0027F4F8 {
public: void *rva0027F4F8(int key);
private: char m_pad00[20];
         Rva0027F4F8Entry *m_begin;
         Rva0027F4F8Entry *m_end;
};
void *Rva0027F4F8::rva0027F4F8(int key)
{
	for (Rva0027F4F8Entry *p = m_begin; p != m_end; ++p)
		if (p->key == key)
			return p->value;
	return 0;
}
