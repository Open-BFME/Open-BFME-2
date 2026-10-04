// cl: /O1
// ?rva0028ACA0@Object@@QBEPAV1@XZ @0x0028ACA0 42B: returns AIUpdate victim at +0x258 else 0; guards virtual bool slot 111 at +0x1BC then rowed getCurrentVictim.
// Evidence: between Object rows 0x0028AC7D and 0x0028AD6C; Object+0x258 holds AIUpdateInterface (Rva0033FA64Do precedent); callees rowed 0x00268D71; callers 8.
template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <>
class BfmeVirtualSlots<0>
{
};
class Object;
class AIUpdateInterface : public BfmeVirtualSlots<111>
{
public:
	virtual bool slot111() const;
	Object *getCurrentVictim() const;
private:
	char m_pad[0x40 - 4 - 0];
	int m_id40;
};
class Object
{
public:
	Object *rva0028ACA0() const;
private:
	char m_pad[0x258];
	AIUpdateInterface *m_258;
};
Object *Object::rva0028ACA0() const
{
	Object *result = 0;
	AIUpdateInterface *ai = m_258;
	if (ai != 0 && ai->slot111())
		result = m_258->getCurrentVictim();
	return result;
}
