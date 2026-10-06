// cl: /MD
// ?rva000E6135@Rva000E6135@@QAEXPBVRva0055A88BDwordField@@ABV?$StringBase@D@@M@Z @0x000E6135 81B
// List-update by (id name) over sentinel-circular list at +0x18 with enable
// byte at +0x20; id via rowed get 0x0055A88B matcher rowed rva000E5EC1
// 0x000E5EC1 float value to item +0x88 via movss. Precedent Rva000E5F60Lookup.
// Caller 0x0006B7E5 unclaimed; unblocks 0x0006B7BF.
template <typename T> class StringBase;

class Rva0055A88BDwordField
{
public:
	int get() const throw();
};

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const throw();
private:
	char m_pad[0x88];
public:
	float m_88;
};

struct Rva000E6135Node
{
	Rva000E6135Node *m_next;
	void *m_prev;
	Rva000E5EC1 *m_item;
};

class Rva0055A88BDwordField;
class Rva000E6135
{
public:
	void rva000E6135(const Rva0055A88BDwordField *idSrc, const StringBase<char> &name, float value);
private:
	char m_pad[0x18];
	Rva000E6135Node *m_head;
	char m_pad1[0x20 - 0x1C];
	bool m_20;
};

void Rva000E6135::rva000E6135(const Rva0055A88BDwordField *idSrc, const StringBase<char> &name, float value)
{
	if (idSrc == 0)
		return;
	if (!m_20)
		return;
	Rva000E6135Node *cur = m_head->m_next;
	if (cur == m_head)
		return;
	do
	{
		if (cur->m_item->rva000E5EC1(idSrc->get(), name))
			cur->m_item->m_88 = value;
		cur = cur->m_next;
	} while (cur != m_head);
}
