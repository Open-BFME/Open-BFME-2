// cl: /MD /EHsc /DNDEBUG
// ?reset@W3DSnowManager@@UAEXXZ @0x00093B3F (28B):
// W3DSnowManager reset slot 9 of vtable 0x007C8144: base SnowManager::reset
// 0x00201134, then copy helper 0x00093457, then zero m_a8 and m_50.
// Evidence: vslot, caller none, LINK none, prev 0x00093457 same flags.
class SnowManager
{
public:
	virtual void reset();
protected:
	char m_pad04[0x50 - 0x04];
	bool m_50;
	char m_pad51[0x74 - 0x51];
};
class Rva00093457
{
public:
	void rva00093457();
};
class W3DSnowManager : public SnowManager
{
public:
	virtual void reset();
private:
	char m_pad74[0xa8 - 0x74];
	int m_a8;
};
void W3DSnowManager::reset()
{
	SnowManager::reset();
	((Rva00093457 *)this)->rva00093457();
	m_a8 = 0;
	m_50 = false;
}
