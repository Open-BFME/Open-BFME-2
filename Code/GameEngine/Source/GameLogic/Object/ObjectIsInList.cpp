// cl: /O1 /DNDEBUG /MD /EHsc

// ?isInList@Object@@QBE_NPAPAV1@@Z, retail 0x0028B47C (31 bytes).
// Object::isInList checks the intrusive list links at +0x8C/+0x90.
// Evidence: BFME1 donor Object.cpp:3124 `Bool result = m_prev || m_next ||
// *pListHead == this`, and the sole retail caller GameLogic::friend_awakenUpdateModule
// (0x0024297F) passes &GameLogic+0xAC as pListHead with this=obj.

typedef bool Bool;

class Object
{
public:
	Bool isInList(Object **pListHead) const;

private:
	unsigned char m_pre[0x8C];
	Object *m_next; // +0x8C
	Object *m_prev; // +0x90
};

Bool Object::isInList(Object **pListHead) const
{
	Bool result = m_prev || m_next || *pListHead == this;
	return result;
}
