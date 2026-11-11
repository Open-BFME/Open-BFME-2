// cl: /DNDEBUG /MD /EHsc
// ?rva00538CEF@Rva00538CEF@@QAEPAVRva0020E89C@@XZ @0x00538CEF 40B: returns view lookup of last vector element or null.
// Evidence: retail cmp [ecx] [ecx+4] je null then global g_009FEF10 +0xB0 view call rowed 0x0020EAF6 with [edx-4]; callers at 0x31A5FC 0x538D44.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020E89C;
#include "../../../Include/GameLogic/Rva0020EAF6View.h"

class Rva002BA8F1Logic
{
public:
	char m_pad00[0xB0];
	Rva0020EAF6View *m_B0;
};

#include "../../../Include/Common/LivingWorldArmyIcon.h"
class Rva003FDE50 {public:void rva003FDE50(unsigned int);};
struct Position00538D3B {float x,y,z; Position00538D3B(float a,float b,float c):x(a),y(b),z(c){} };
class Vector3;
#include "../../../Include/Common/Rva002BF4F3.h"
class Rva002D3627Host;class LivingWorld; extern LivingWorld *TheLivingWorld;
struct Record00538D3B {int unused;float x,y,z;};
struct Rva00538CEFPair {int a,b;};
class Rva00538CEF
{
public:
	Rva0020E89C *rva00538CEF();
	void rva00538D3B(int);
	bool rva00538D17(Rva00538CEFPair *out);
	void rva00538DC1(const Rva00538CEFPair *values,int word);
private:
	int *m_start;
	int *m_finish;
	int unused08;
	LivingWorldArmyIcon *owner;
};

Rva0020E89C *Rva00538CEF::rva00538CEF()
{
	if (m_start != m_finish) {
		Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
		if (logic) {
			Rva0020EAF6View *view = logic->m_B0;
			if (view)
				return view->rva0020EAF6(m_finish[-1]);
		}
	}
	return 0;
}

// Native538D3B..538DC1 RET4; receiver538CEF resolves current back element.
// Target record stride16 and XY4/8; ownerC accepts context/position/flag then visibility and ground position.
// Rowed neutral providers retain ABI names; behavior follows own retail calls and data flow.
void Rva00538CEF::rva00538D3B(int flag) {
 Rva0020E89C *context=rva00538CEF();
 if(!context) {
  owner->rva003FDE8C(0);
  ((Rva003FDE50*)owner)->rva003FDE50((unsigned int)((char*)owner+0x18));
 } else {
  Record00538D3B *record=(Record00538D3B*)m_finish-1;
  owner->rva003FDD41((int)&record->x,(int)context,flag);
  owner->rva003FDE8C(1);
  Position00538D3B point(record->x,record->y,0.0f);
  ((Rva002BF4F3*)((Rva002D3627Host *)TheLivingWorld))->rva002BF5B0((const Vector3*)&record->x,(Vector3*)&point);
  ((Rva003FDE50*)owner)->rva003FDE50((unsigned int)&point);
 }
}

// Native538D17..538D3B,36B; WB1434B10 confirms the unsigned16-byte
// record count and conditional copy of the last record's words4/8.
// No original coordinate type or member name is asserted by this view.
bool Rva00538CEF::rva00538D17(Rva00538CEFPair *out){
 int *span=(int*)this;int *end=m_finish;
 if((unsigned)((span[1]-span[0])>>4)>0){
  out->a=end[-3];out->b=end[-2];return true;
 }
 return false;
}

// Native538DC1..538DEA,41B; independent WB1434B60 uses the same
// unsigned16-byte count and copies input words to the last record4/8,
// then forwards the unchanged context word to the owned position helper.
void Rva00538CEF::rva00538DC1(const Rva00538CEFPair *values,int word){
 int *span=(int*)this;int *end=m_finish;
 if((unsigned)((span[1]-span[0])>>4)>0){
  end[-3]=values->a;end[-2]=values->b;rva00538D3B(word);
 }
}
