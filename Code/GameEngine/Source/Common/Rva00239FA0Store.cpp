// cl: /MD
// ?rva00239FA0@Rva00239FA0@@QAEXPBVRva0055A88BDwordField@@@Z @0x00239FA0 44B: nullable store via dword-field get plus findSlot at this+0x18. Evidence: callers at 0x0027108B callees get 0x0055A88B findSlot 0x0041F4E5 same shape as 0x00239C38.
class Object;
class Rva0055A88BDwordField
{
public:
	int get() const;
};
class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};
class Rva00239FA0
{
	char m_pad[0x18];
	ObjectLookupMap m_map;
public:
	void rva00239FA0(const Rva0055A88BDwordField *arg);
};
void Rva00239FA0::rva00239FA0(const Rva0055A88BDwordField *arg)
{
	if (arg) {
		int v = arg->get();
		Object **slot = m_map.findSlot(&v);
		*slot = (Object *)arg;
	}
}
