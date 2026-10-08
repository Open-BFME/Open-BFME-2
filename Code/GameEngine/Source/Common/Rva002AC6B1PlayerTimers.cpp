// cl: /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common
// stlport
// Semantic donor: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/Player.cpp (pointer6d9434269)
// addNewSharedSpecialPowerTimer/getOrStartSpecialPowerReadyFrame. Native2AC6B1/48 and
//2AC7A0/70 independently prove list+704, ID from finaloverride+14 and frame40.
// Receiver is an ABI prefix, not a recovered complete Player definition.
#include <list>
#include "BfmeSpecialPowerTimer8.h"
namespace _STL {
template<> void list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::push_back(const BfmeSpecialPowerTimer8 &);
}
class Overridable { public:const Overridable *friend_getFinalOverride()const; };
class SpecialPowerTemplate;
struct Rva002AC6B1TemplateView { unsigned char prefix[0x14];unsigned id;unsigned char pad18[8];unsigned reloadTime; };
class GameLogic;extern GameLogic *TheGameLogic;
struct Rva002AC6B1FrameView { unsigned char prefix[0x40];unsigned frame; };
class Rva002AC6B1PlayerTimers {
public:
 void addTimer(const SpecialPowerTemplate *,unsigned);
 unsigned getOrStart(const SpecialPowerTemplate *);
 void resetOrStart(const SpecialPowerTemplate *);
 void rva002AC75C(const SpecialPowerTemplate *,unsigned);
 unsigned char prefix[0x6F8];
 float reloadScale;
 unsigned char pad6FC[8];
 _STL::list<BfmeSpecialPowerTimer8> timers;
};
void Rva002AC6B1PlayerTimers::addTimer(const SpecialPowerTemplate *temp,unsigned frame) {
 BfmeSpecialPowerTimer8 timer;
 timer.m_templateID=((const Rva002AC6B1TemplateView*)((const Overridable*)temp)->friend_getFinalOverride())->id;
 timer.m_readyFrame=frame;
 timers.push_back(timer);
}
// ?resetOrStart@Rva002AC6B1PlayerTimers@@QAEXPBVSpecialPowerTemplate@@@Z @0x002AC6E1 123B
// (WorldBuilder 0xC1DDD0 by callgraph; ZH Player::resetOrStartSpecialPowerReadyFrame).
// Matching timers rearm at now plus the final override's reload (+20) and that
// reload scaled by the player float at +6F8 when the scaled part is smaller.
void Rva002AC6B1PlayerTimers::resetOrStart(const SpecialPowerTemplate *temp) {
 unsigned lookupID=((const Rva002AC6B1TemplateView*)((const Overridable*)temp)->friend_getFinalOverride())->id;
 unsigned now=((Rva002AC6B1FrameView*)TheGameLogic)->frame;
 for(_STL::_List_node_base *it=timers.begin()._M_node;it!=timers.end()._M_node;it=it->_M_next) {
  BfmeSpecialPowerTimer8 &timer=((_STL::_List_node<BfmeSpecialPowerTimer8>*)it)->_M_data;
  if(timer.m_templateID==lookupID) {
   unsigned reload=((const Rva002AC6B1TemplateView*)((const Overridable*)temp)->friend_getFinalOverride())->reloadTime;
   unsigned scaled=(unsigned)(reload*reloadScale);
   timer.m_readyFrame=now+(reload>scaled?reload+scaled:0);
   return;
  }
 }
 addTimer(temp,now);
}
unsigned Rva002AC6B1PlayerTimers::getOrStart(const SpecialPowerTemplate *temp) {
 unsigned lookupID=((const Rva002AC6B1TemplateView*)((const Overridable*)temp)->friend_getFinalOverride())->id;
 unsigned now=((Rva002AC6B1FrameView*)TheGameLogic)->frame;
 // Native list-node traversal avoids emitting competing iterator COMDATs.
 for(_STL::_List_node_base *it=timers.begin()._M_node;it!=timers.end()._M_node;it=it->_M_next) {
  const BfmeSpecialPowerTimer8 &timer=((_STL::_List_node<BfmeSpecialPowerTimer8>*)it)->_M_data;
  if(timer.m_templateID==lookupID)return timer.m_readyFrame;
 }
 addTimer(temp,now);
 return now;
}

void Rva002AC6B1PlayerTimers::rva002AC75C(const SpecialPowerTemplate *temp, unsigned frame)
{
 _STL::_List_node_base *head=timers.end()._M_node;
 for(_STL::_List_node_base *it=timers.begin()._M_node;it!=head;it=it->_M_next) {
  const BfmeSpecialPowerTimer8 &timer=((_STL::_List_node<BfmeSpecialPowerTimer8>*)it)->_M_data;
  if(timer.m_templateID==((const Rva002AC6B1TemplateView*)((const Overridable*)temp)->friend_getFinalOverride())->id) {
   ((_STL::_List_node<BfmeSpecialPowerTimer8>*)it)->_M_data.m_readyFrame=frame;
   return;
  }
 }
 addTimer(temp,frame);
}
