// cl: /DNDEBUG /MD /EHsc
// ?rva00483C9F@Rva00483C9F@@QAE_NPAVObject@@@Z 0x00483C9F 80B evidence: gap between Disp8 getter 0x00483C75 and pool-key 0x00483CF4; thiscall bool(Object*) via ret 4 plus al returns; rowed isUsingAirborneLocomotor 0x0028B81E plus pinned rva0028CE7B plus virtual slot 8 on +0x254 with cmp 3; honest Rva name
class Object;
struct LocoSlot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual int v8();
};

class Object
{
public:
	signed char rva0028CE7B() const;
	bool isUsingAirborneLocomotor() const;
};

class Rva00483C9F
{
public:
	bool rva00483C9F(Object *obj);

private:
	char m_00[8];
	Object *m_08;
	signed char m_0c;
};

bool Rva00483C9F::rva00483C9F(Object *obj)
{
	if (m_0c != 0) {
		signed char c = obj->rva0028CE7B();
		if (m_0c > c)
			return false;
	}
	if (obj == m_08)
		return false;
	if (obj->isUsingAirborneLocomotor())
		return false;
	LocoSlot *loc = *(LocoSlot **)((char *)obj + 0x254);
	if (loc == 0)
		return true;
	int v = loc->v8();
	return v != 3;
}
