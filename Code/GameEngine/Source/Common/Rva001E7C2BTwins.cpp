// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: x87 float-forwarding twins at 0x1E7C2B/0x1E9045 (33B
// each). Each forwards (a,b,c,d) with this to its callee (0x1E7053 /
// 0x1E8C1B). Only c/d travel via fld/fstp into two push-ecx temps; a/b are
// dword-pushed directly, so the first two params are int-sized and the last
// two are float. Address-derived names; callee types unproven (pins).

class Rva001E7053
{
public:
	// Rowed as ?rva001e7053@Rva001E7053@@QAEXIIMM@Z (Rva001E7C2BForwarders.cpp).
	void rva001e7053(unsigned int a, unsigned int b, float c, float d);
};
class Rva001E8C1B
{
public:
	void rva001E8C1B(int a, int b, float c, float d);
};
class Rva001E7C2B
{
public:
	void rva001E7C2B(int movingObject, int goal, float onPath, float speed);
};
class Rva001E9045
{
public:
	void rva001E9045(int movingObject, int goal, float onPath, float speed);
};

// ?rva001E7C2B@Rva001E7C2B@@QAEXHHMM@Z
void Rva001E7C2B::rva001E7C2B(int movingObject, int goal, float onPath, float speed)
{
	((Rva001E7053 *)this)->rva001e7053(movingObject, goal, onPath, speed);
}

// ?rva001E9045@Rva001E9045@@QAEXHHMM@Z
void Rva001E9045::rva001E9045(int movingObject, int goal, float onPath, float speed)
{
	((Rva001E8C1B *)this)->rva001E8C1B(movingObject, goal, onPath, speed);
}

class HoverConditionBits
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
	void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
	unsigned int m_words[3];
};
class Object
{
public:
	void rva0028AE6D();
	char pad[0x38];
	float x, y;
	char pad40[0x110 - 0x40];
	HoverConditionBits m_cond110;
};
static __forceinline void hoverSetCondition(Object *obj, int bit)
{
	if (obj->m_cond110.test(bit) == 0)
	{
		obj->m_cond110.set(bit);
		obj->rva0028AE6D();
	}
}
static __forceinline void hoverClearCondition(Object *obj, int bit)
{
	if (obj->m_cond110.test(bit) != 0)
	{
		obj->m_cond110.clear(bit);
		obj->rva0028AE6D();
	}
}
static __forceinline bool hoverTestBit(unsigned int word, int bit)
{
	return ((word >> bit) & 1) != 0;
}

class TerrainLogic {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual bool isUnderwater(float,float,void*,void*,void*);
};
extern TerrainLogic *TheTerrainLogic;
class Rva001E7C4C {public:void rva001E7C4C(Object*,unsigned,float,float);private:char pad[0x44];unsigned flags;};

// ?rva001E7C4C@Rva001E7C4C@@QAEXPAVObject@@IMM@Z retail 0x001E7C4C 147B: the
// 0x001E7053 move, then (ZH Locomotor hover guide) whether the Object stands
// over water by TheTerrainLogic slot 0x4C toggles locomotor flag bit 5 (+0x44)
// and model condition bit 69 (+0x118 bit 5) through the Object notifier
// 0x0028AE6D. The bit view's set/clear helpers give retail's direct memory
// test and the shared notifier tail; the flag read is the bool shift test.
void Rva001E7C4C::rva001E7C4C(Object *obj,unsigned goal,float onPath,float speed){
 ((Rva001E7053*)this)->rva001e7053((unsigned int)obj,goal,onPath,speed);
 float x = obj->x, y = obj->y;
 if (TheTerrainLogic->isUnderwater(x, y, 0, 0, 0))
 {
  if (!hoverTestBit(flags, 5))
  {
   flags |= 0x20;
   hoverSetCondition(obj, 69);
  }
 }
 else
 {
  if (hoverTestBit(flags, 5))
  {
   flags &= ~0x20;
   hoverClearCondition(obj, 69);
  }
 }
}
