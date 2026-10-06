// cl: /DNDEBUG /MD /EHsc
// ?rva004A8DDE@DelayedLuaEventList@@QAEAAV1@ABV1@@Z @0x004A8DDE 44B
// __thiscall DelayedLuaEventList& (const DelayedLuaEventList&): copy 3x 0x18
// elements at +4 via rowed Rva0028BC20 copy ctor 0x004A8D17, return *this.
// Evidence: unlock lane, callees rowed; callers 0x004A8F1D passes m_events
// at +0x24 plus source; prev 0x004A8D99 abuts, next 0x004A8E0A xfer;
// array layout +4 3x0x18 from rowed default ctor 0x000B6D8B and xfer 0x003316D2.
class Rva0028BC20
{
public:
	Rva0028BC20(const Rva0028BC20 &other);
private:
	char m_data[0x18];
};

class DelayedLuaEventList
{
public:
	virtual ~DelayedLuaEventList();
	DelayedLuaEventList &rva004A8DDE(const DelayedLuaEventList &other);
private:
	Rva0028BC20 m_arr[3];
};

DelayedLuaEventList &DelayedLuaEventList::rva004A8DDE(const DelayedLuaEventList &other)
{
	for (int i = 0; i < 3; ++i)
		m_arr[i].Rva0028BC20::Rva0028BC20(other.m_arr[i]);
	return *this;
}
