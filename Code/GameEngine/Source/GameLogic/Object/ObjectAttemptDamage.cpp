// cl: /O1 /arch:SSE /DNDEBUG /MD /GX-
//
// ?attemptDamage@Object@@QAEXPAVDamageInfo@@@Z, retail 0x0029848E, 70B.
// Name: pinned from Object::kill's call at 0x0029850D (BFME1 kill passes its
// DamageInfo local to attemptDamage). BFME2 body (not Zero Hour's body-module
// forward): under object status 0x48 the DamageInfo's +0x28 float is forced
// to 1.0; a positive +0x28 queues a copy of the 124-byte DamageInfo on the
// list at Object+0x440 (rowed list<BfmePod124>::push_back 0x002947D6), else
// the DamageInfo goes straight to 0x002975AC. Field and callee names past
// that are placeholders. Flags follow ObjectKill.cpp, the kill row beside it.
typedef bool Bool;
typedef float Real;

enum ObjectStatusTypes
{
	OBJECT_STATUS_48 = 0x48
};

struct BfmePod124
{
	unsigned char m_bytes[124];
};

namespace _STL
{
template <class T> class allocator {};
template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &x);	// 0x002947D6
private:
	void *m_node;
};
}

class DamageInfo
{
public:
	unsigned char m_pad0[0x28];
	Real m_x28;			// +0x28, forced to 1.0 under status 0x48
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes status) const;	// 0x0004E536
	void attemptDamage(DamageInfo *damageInfo);
	void rva002975AC(DamageInfo *damageInfo);		// 0x002975AC

private:
	unsigned char m_pad0[0x440];
	_STL::list<BfmePod124> m_x440;			// +0x440
};

void Object::attemptDamage(DamageInfo *damageInfo)
{
	if (testStatus(OBJECT_STATUS_48))
		damageInfo->m_x28 = 1.0f;

	if (damageInfo->m_x28 > 0.0f)
		m_x440.push_back(*(const BfmePod124 *)damageInfo);
	else
		rva002975AC(damageInfo);
}
