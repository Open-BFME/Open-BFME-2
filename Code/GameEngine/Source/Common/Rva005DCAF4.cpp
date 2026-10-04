// cl: /O1 /MD
// ?rva005DCAF4@Rva005DC87B@@QAE_NXZ @ 0x005DCAF4 25B
// Bool getter via pinned 0x005DCAE5 Object then bit0 at +0x438; caller v7 0x005A9BBF.
class Object
{
public:
	unsigned char m_pad438[0x438];
	unsigned char m_438;
};
class Rva005DC87B
{
public:
	bool rva005DCAF4();
	class Object *rva005DCAE5();
};
bool Rva005DC87B::rva005DCAF4()
{
	class Object *obj = rva005DCAE5();
	return !obj || (obj->m_438 & 1);
}
