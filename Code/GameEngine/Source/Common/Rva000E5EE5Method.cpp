// cl: /MD /EHsc
// ?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@@Z @0x000E5EE5 123B
// Target facts: 123B thiscall ret 8 (field ptr + by-value StringBase<char>),
// list at +0x18 (head->next, item at +0x08) like Rva000E5F60Lookup, null check
// on first arg, id via rowed get 0x0055A88B, matcher rowed rva000E5EC1
// 0x000E5EC1, on match clears dword at item+0x2C and sets byte at +0x9C.
// Donor: Code/GameEngine/Source/Common/Rva000E5F60Lookup.cpp (loop shape,
// by-value temp with __forceinline dtor) + Rva000E6135Method.cpp (get+matcher).
template <typename T> class StringBase
{
public:
	__forceinline ~StringBase() { releaseBuffer(); }
	int compare(const StringBase<T> &other) const;
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const;
	char m_pad0[0x2C];
	int m_2c;
	char m_pad1[0x4C - 0x2C - 4];
	int m_id;
	char m_pad2[0x8C - 0x4C - 4];
	StringBase<char> m_name;
	char m_pad3[0x9C - 0x8C - 4];
	bool m_9c;
};

struct Rva000E5EE5Node
{
	Rva000E5EE5Node *m_next;
	void *m_prev;
	Rva000E5EC1 *m_item;
};

class Rva000E5EE5
{
public:
	void rva000E5EE5(const Rva0055A88BDwordField *idSrc, StringBase<char> name);
private:
	char m_pad[0x18];
	Rva000E5EE5Node *m_head;
};

void Rva000E5EE5::rva000E5EE5(const Rva0055A88BDwordField *idSrc, StringBase<char> name)
{
	if (idSrc == 0)
		return;
	Rva000E5EE5Node *cur = m_head->m_next;
	while (cur != m_head)
	{
		if (cur->m_item->rva000E5EC1(idSrc->get(), name))
		{
			Rva000E5EC1 *item = cur->m_item;
			item->m_2c = 0;
			item->m_9c = true;
			return;
		}
		cur = cur->m_next;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@VAsciiString@@@Z=?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@@Z")
