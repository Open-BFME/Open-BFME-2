// cl: /MD
// ?rva00239C38@Rva00239C38@@QAEXPBVRva0055A88BDwordField@@@Z @0x00239C38 38B: nullable erase via dword-field get at this+0x18. Evidence: callers at 0x00239F86 0x00271075 callees get 0x0055A88B erase 0x0054883B same shape as 0x001F3C20.
class Rva0055A88BDwordField
{
public:
	int get() const;
};
class ObjectLookupMap
{
public:
	void eraseSlot(int *p);
};
class Rva00239C38
{
	char m_pad[0x18];
	ObjectLookupMap m_map;
public:
	void rva00239C38(const Rva0055A88BDwordField *arg);
};
void Rva00239C38::rva00239C38(const Rva0055A88BDwordField *arg)
{
	if (arg) {
		int v = arg->get();
		m_map.eraseSlot(&v);
	}
}
