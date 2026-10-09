// cl: /O1 /G7 /Oy- /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common /ICode/GameEngine/Include
//
// ModelConditionAudioLoopClientBehavior update and its neutral data selector.
// Identity follows the previously recovered two condition-change entries, both
// running the class's recovered 0x004CBFC7 on the primary this
// with a set of condition flags:
//   +0x0C interface slot 0 (table 0x00C5F450), retail 0x004CC07B (18 bytes):
//         with the owner's current flags at +0x258;
//   +0x10 interface slot 0 (table 0x00C5F44C), retail 0x004CC06C (15 bytes):
//         with the flags it is handed (its other two arguments unused).
// Named by address.
#include "BfmeAudioEventPrefix136.h"
enum DrawableID { InvalidDrawableID=0 };
class Rva0036CA00Str {
public:
 OpaqueRefCounted *referent;
 // ?Rva0036CA00Str::Rva0036CA00Str present-unmatched
 __forceinline Rva0036CA00Str():referent(0){}
 __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
 // ?Rva0036CA00Str::~Rva0036CA00Str present-unmatched
 __forceinline ~Rva0036CA00Str(){if(referent)referent->Release_Ref();}
};
class Rva001DFE56 { public: bool rva001DFE56(const void *,const void *) const; };
class Rva000CF0D6
{
public:
	unsigned int m_bits[19];
};
class Drawable
{
public:
	DrawableID getID() const;
	unsigned char m_pad000[0x258];
	Rva000CF0D6 m_conditionFlags;	// +0x258
};
struct Rva004CBE66Entry { Rva0036CA00Str value; Rva000CF0D6 required,exempt; };
class ModuleData;
class Rva004CBE66 {
public:
 char pad[8]; Rva004CBE66Entry *begin,*end;
 Rva0036CA00Str rva004CBE66(const Rva000CF0D6 *) const;
};
Rva0036CA00Str Rva004CBE66::rva004CBE66(const Rva000CF0D6 *flags) const {
 Rva004CBE66Entry *last=end;
 for(Rva004CBE66Entry *i=begin;i!=last;++i)
  if(reinterpret_cast<const Rva001DFE56 *>(flags)->rva001DFE56(&i->required,&i->exempt))return i->value;
 return Rva0036CA00Str();
}
class Rva004CBF9A { public:void clear(); };
class AudioManager {
public:
 virtual void pad0()=0;
 virtual void pad1()=0;
 virtual void pad2()=0;
 virtual void pad3()=0;
 virtual void pad4()=0;
 virtual void pad5()=0;
 virtual void pad6()=0;
 virtual void pad7()=0;
 virtual void pad8()=0;
 virtual void pad9()=0;
 virtual void pad10()=0;
 virtual void pad11()=0;
 virtual void pad12()=0;
 virtual void pad13()=0;
 virtual void pad14()=0;
 virtual void pad15()=0;
 virtual void pad16()=0;
 virtual void pad17()=0;
 virtual void pad18()=0;
 virtual void pad19()=0;
 virtual void pad20()=0;
 virtual void pad21()=0;
 virtual void pad22()=0;
 virtual void pad23()=0;
 virtual void pad24()=0;
 virtual unsigned addAudioEvent(const BfmeAudioEventPrefix136 *)=0;
};
extern AudioManager *TheAudio;
class ClientModuleBase
{
public:
	virtual ~ClientModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;		// +0x08
};
class Rva00C5F450Iface
{
public:
	virtual void rva004CC07B() = 0;
};
class Rva00C5F44CIface
{
public:
	virtual void rva004CC06C(const Rva000CF0D6 *flags, int a2, int a3) = 0;
};
class ModelConditionAudioLoopClientBehavior : public ClientModuleBase,
	public Rva00C5F450Iface, public Rva00C5F44CIface
{
public:
	virtual void rva004CC07B();
	virtual void rva004CC06C(const Rva000CF0D6 *flags, int a2, int a3);
	void rva004CBFC7(const Rva000CF0D6 *flags);
 unsigned handle14; OpaqueRefElement4 current18;
};
void ModelConditionAudioLoopClientBehavior::rva004CBFC7(const Rva000CF0D6 *flags) {
 Rva0036CA00Str selected=reinterpret_cast<const Rva004CBE66 *>(m_moduleData)->rva004CBE66(flags);
 OpaqueRefCounted *old=current18.referent;
 if(selected.referent!=old){
  reinterpret_cast<Rva004CBF9A *>(this)->clear();
  current18=*reinterpret_cast<const OpaqueRefElement4 *>(&selected);
  if(current18.referent){
   BfmeAudioEventPrefix136 event(current18,m_drawable->getID());
   handle14=TheAudio->addAudioEvent(&event);
  }
 }
}

// Native4CBE66..4CBEB0 establishes hidden counted-result ABI and0x9C entries
// (+0x04 required/+0x50 exempt), bounds+8/+C; original data/entry names unknown.
// Native4CBFC7..4CC06C proves selected-ref cleanup50ED3 and current-ref+18,
// handle+14; event prefix is the existing independently verified136-byte view.
// No clean BFME1/ZH audio-loop source found; existing target mask/helper
// recoveries supplied semantic and ABI dependencies rather than a donor name.
