// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0044E655@Rva0044E655@@QAE_NXZ @0x0044E655 52B
// Gated idle-set predicate over +0x08 Object plus +0x7E +0x7F: unlock lane;
// callers at 0x0045224C 0x00452269 in 0x00451FA2; AI slot 0x1b8 isIdle
// precedent AIGroupIsIdle.cpp; sets +0x7F when idle observed.
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

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual bool isIdle();
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;
};

class Rva0044E655
{
public:
	bool rva0044E655();
private:
	char m_pad00[8];
	Object *m_obj08;
	char m_pad0C[0x7E - 0x0C];
	unsigned char m_7E;
	unsigned char m_7F;
};

bool Rva0044E655::rva0044E655()
{
	AIUpdateInterface *ai = m_obj08->m_ai258;
	if (ai == 0)
		return true;
	if (m_7F != 0)
		return false;
	if (m_7E == 0)
		return false;
	if (ai->isIdle())
	{
		m_7F = 1;
		return false;
	}
	return true;
}
