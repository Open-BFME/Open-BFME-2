// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB ED5360 / ED51E0 name ObjectFilter::DoNamesXfer / DoTemplatesXfer.
// Retail 361533..361594 and 360DB9..360E64 prove the two argument pointers,
// Xfer slots7C/6C, vector stride4, and ThingTemplate name at+64. WB preserves
// the otherwise unused ObjectFilter receiver. Pointer/reference spellings are
// a local ABI view; original parameter declarations are not available.
// The six collection offsets are also established by BFME1 ba7ddda7e8f26116's
// ObjectFilterResolveNames.cpp and the existing BFME2 resolver; these bodies
// themselves are reconstructed from retail/WB, not claimed as donor transfers.
#include <vector>
#include "ascii_string.h"
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct FilterVersion
{
    FilterVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
namespace _STL {template<>void vector<AsciiString>::push_back(const AsciiString&);}
#include "../../../Include/Common/ThingTemplate.h"
template<int N> class BitFlags;
class Player;
#include "../../../Include/GameLogic/ObjectFilter.h"
// ?DoNamesXfer@ObjectFilter@@QAEXPAVXfer@@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
void ObjectFilter::DoNamesXfer(Xfer *xfer, _STL::vector<AsciiString> *names)
{
    int count;
    (*xfer == count);
    AsciiString name;
    for (int i = 0; i < count; ++i)
    {
        (*xfer == name);
        names->push_back(name);
    }
}

// ?DoTemplatesXfer@ObjectFilter@@QAEXPAVXfer@@PAV?$vector@PAVThingTemplate@@V?$allocator@PAVThingTemplate@@@_STL@@@_STL@@1@Z
void ObjectFilter::DoTemplatesXfer(Xfer *xfer,
                                 _STL::vector<ThingTemplate *> *special,
                                 _STL::vector<ThingTemplate *> *normal)
{
    int count = special->size() + normal->size();
    (*xfer == count);
    _STL::vector<ThingTemplate *>::iterator it;
    for (it = special->begin(); it != special->end(); ++it)
    {
        AsciiString name("S:");
        name += (*it)->m_nameString;
        (*xfer == name);
    }
    for (it = normal->begin(); it != normal->end(); ++it)
        (*xfer == (*it)->m_nameString);
}

// Existing verified 218-bit flag provider; only its member ABI is used here.
template <int NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
	void xfer(Xfer *);
	bool any() const;
	bool test(const void *) const;
	bool testSetAndClear(const BitFlags &, const BitFlags &) const;
};
// Existing constructor/destructor/equality own this nonvirtual 0x94-byte
// interned record. Offset views below come from this retail transfer and are
// consistent with those providers; no new record identity is asserted.
typedef unsigned int UnsignedInt;
typedef _STL::vector<AsciiString> AsciiStringVector;
class ModuleData;
struct BfmeAttributeBits
{
	UnsignedInt m_values[7];	// BitFlags<218>
};
class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();
	bool rva00360E64(const Rva00360F55 &other);

	AsciiStringVector m_inclusionNames;							// +0x00
	AsciiStringVector m_exclusionNames;							// +0x0C
	_STL::vector<const ModuleData *> m_inclusionSTemplates;	// +0x18
	_STL::vector<const ModuleData *> m_exclusionSTemplates;	// +0x24
	_STL::vector<const ModuleData *> m_inclusionTemplates;		// +0x30
	_STL::vector<const ModuleData *> m_exclusionTemplates;		// +0x3C
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};
int Rva00361790(Rva00360F55*);
extern unsigned char*g_validityBegin;extern unsigned char*g_validityEnd;
// ?DoXfer@ObjectFilter@@QAEXPAVXfer@@@Z
// WB ED5470 names DoXfer; native362255..3623E5 supplies the record fields,
// save/load sequence, conditional version-2 field, and registry scan. The old
// resolver's ObjectFilter spelling denotes the full record: pass that verified
// provider its record view, not the four-byte index wrapper's address.
void ObjectFilter::DoXfer(Xfer *xfer)
{
    FilterVersion version(1, 2);
    (*xfer == reinterpret_cast<Xfer::Version &>(version));
    Rva00360F55 temp;
    Rva00360F55 *data;
    if (xfer->IsStoring())
    {
        if (m_objectFilterSlot00 == -1)
            m_objectFilterSlot00 = Rva00361790(&Rva00360F55());
        data = reinterpret_cast<Rva00360F55 *>(g_validityBegin) + m_objectFilterSlot00;
    }
    else
        data = &temp;
    (*xfer == data->m_enabled);
    (*xfer == reinterpret_cast<int &>(data->m_kind));
    reinterpret_cast<BitFlags<218> *>(&data->m_firstPlain)->xfer(xfer);
    reinterpret_cast<BitFlags<218> *>(&data->m_secondPlain)->xfer(xfer);
    (*xfer == reinterpret_cast<int &>(data->m_relationship));
    if (xfer->IsStoring())
    {
        DoTemplatesXfer(xfer,
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(&data->m_inclusionSTemplates),
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(&data->m_inclusionTemplates));
        DoTemplatesXfer(xfer,
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(&data->m_exclusionSTemplates),
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(&data->m_exclusionTemplates));
    }
    else
    {
        DoNamesXfer(xfer, &data->m_inclusionNames);
        DoNamesXfer(xfer, &data->m_exclusionNames);
        rva003611EFResolveNames(reinterpret_cast<ObjectFilter *>(data));
        int count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
        for (int i = 0; i < count; ++i)
        {
            if (reinterpret_cast<Rva00360F55 *>(g_validityBegin)[i].rva00360E64(*data))
            {
                m_objectFilterSlot00 = i;
                break;
            }
        }
    }
    if (version.current >= 2)
        (*xfer == reinterpret_cast<int &>(data->m_alignment));
}

class Team;
enum Relationship { Relationship0, Relationship1, Relationship2 };
// This is a measured field view, not an assertion of the template's class name.
struct FilterPlayerTemplateView { char unknown00[0x1bc]; bool alignment; };
#include "../../../Include/Common/Player.h"
extern BitFlags<116> KINDOFMASK_NONE;
// Native361B12..361CA5 and WB ED3050 ObjectFilter::testKindOf. The existing
// 69/116 mask-provider spellings both operate on seven native words. Reload
// relationship bits after the player query; its call may mutate shared state.
// Pointer/const spelling is a local ABI view of the three argument words.
bool ObjectFilter::testKindOf(const BitFlags<218> *kindOf, const Player *player, const Player *context)
{
 if(!kindOf) return false;
 if(m_objectFilterSlot00 >= (g_validityEnd-g_validityBegin)/(int)sizeof(Rva00360F55)) return false;
 if(m_objectFilterSlot00 == -1) m_objectFilterSlot00=Rva00361790(&Rva00360F55());
 Rva00360F55 *data=reinterpret_cast<Rva00360F55*>(g_validityBegin)+m_objectFilterSlot00;
 int alignment=data->m_alignment;
 if(alignment) {
  bool flag=reinterpret_cast<const FilterPlayerTemplateView *>(player->getPlayerTemplate())->alignment;
  switch(alignment) {
   case 1: if(!flag) return false; break;
   case 2: if(flag) return false; break;
  }
 }
 
 if(data->m_relationship) {
  if(!player || !context) return false;
  switch(context->getRelationship(player->getDefaultTeam())) {
   case Relationship2:
    if(!(data->m_relationship&1) && !(context->getPlayerIndex()==player->getPlayerIndex() && (data->m_relationship&8))) return false;
    break;
   case Relationship0: if(!(data->m_relationship&2)) return false; break;
   case Relationship1: if(!(data->m_relationship&4)) return false; break;
   default: return false;
  }
 }
 BitFlags<218> *reject=reinterpret_cast<BitFlags<218>*>(&data->m_secondPlain);
 if(reject->any() && reinterpret_cast<BitFlags<69>*>(reject)->test(kindOf)) return false;
 int &mode=reinterpret_cast<int &>(data->m_kind);

 switch(mode) {
  case 2: { BitFlags<218> *require=reinterpret_cast<BitFlags<218>*>(&data->m_firstPlain); if(require->any() && reinterpret_cast<BitFlags<69>*>(require)->test(kindOf)) return true; break; }
  case 1: { BitFlags<218> *require=reinterpret_cast<BitFlags<218>*>(&data->m_firstPlain); if(require->any() && reinterpret_cast<const BitFlags<116>*>(kindOf)->testSetAndClear(*reinterpret_cast<BitFlags<116>*>(require),KINDOFMASK_NONE)) return true; break; }
  case 0: mode=3; break;
 }
 bool result=mode==3; return result;
}

// Native3618B9..361B12 and WB ED2690 testTemplate. The common validation
// pattern is independently verified in testKindOf. The four explicit template
// collections precede the mask rules; name comparison and equivalence differ.
bool ObjectFilter::testTemplate(const ThingTemplate *thingTemplate, const Player *player, const Player *context)
{
 if(!thingTemplate) return false;
 if(m_objectFilterSlot00 >= (g_validityEnd-g_validityBegin)/(int)sizeof(Rva00360F55)) return false;
 if(m_objectFilterSlot00 == -1) m_objectFilterSlot00=Rva00361790(&Rva00360F55());
 Rva00360F55 *data=reinterpret_cast<Rva00360F55*>(g_validityBegin)+m_objectFilterSlot00;
 int alignment=data->m_alignment;
 if(alignment) {
  bool flag=reinterpret_cast<const FilterPlayerTemplateView *>(player->getPlayerTemplate())->alignment;
  switch(alignment) {
   case 1: if(!flag) return false; break;
   case 2: if(flag) return false; break;
  }
 }
 
 if(data->m_relationship) {
  if(!player || !context) return false;
  switch(context->getRelationship(player->getDefaultTeam())) {
   case Relationship2:
    if(!(data->m_relationship&1) && !(context->getPlayerIndex()==player->getPlayerIndex() && (data->m_relationship&8))) return false;
    break;
   case Relationship0: if(!(data->m_relationship&2)) return false; break;
   case Relationship1: if(!(data->m_relationship&4)) return false; break;
   default: return false;
  }
 }
 {
  const _STL::vector<ThingTemplate*> *list=reinterpret_cast<const _STL::vector<ThingTemplate*>*>(&data->m_inclusionSTemplates);
  int count=list->size();
  for(int i=0;i<count;++i)
   if(thingTemplate->m_nameString.compare((*list)[i]->m_nameString)==0) return true;
 }
 {
  const _STL::vector<ThingTemplate*> *list=reinterpret_cast<const _STL::vector<ThingTemplate*>*>(&data->m_exclusionSTemplates);
  int count=list->size();
  for(int i=0;i<count;++i)
   if(thingTemplate->m_nameString.compare((*list)[i]->m_nameString)==0) return false;
 }
 {
  const _STL::vector<ThingTemplate*> *list=reinterpret_cast<const _STL::vector<ThingTemplate*>*>(&data->m_inclusionTemplates);
  int count=list->size();
  for(int i=0;i<count;++i)
   if(thingTemplate->isEquivalentTo((*list)[i])) return true;
 }
 {
  const _STL::vector<ThingTemplate*> *list=reinterpret_cast<const _STL::vector<ThingTemplate*>*>(&data->m_exclusionTemplates);
  int count=list->size();
  for(int i=0;i<count;++i)
   if(thingTemplate->isEquivalentTo((*list)[i])) return false;
 }
 BitFlags<218> *reject=reinterpret_cast<BitFlags<218>*>(&data->m_secondPlain);
 if(reject->any() && reinterpret_cast<BitFlags<69>*>(reject)->test(thingTemplate->m_kindof)) return false;
 int &mode=reinterpret_cast<int &>(data->m_kind);

 switch(mode) {
  case 2: { BitFlags<218> *require=reinterpret_cast<BitFlags<218>*>(&data->m_firstPlain); if(require->any() && reinterpret_cast<BitFlags<69>*>(require)->test(thingTemplate->m_kindof)) return true; break; }
  case 1: { BitFlags<218> *require=reinterpret_cast<BitFlags<218>*>(&data->m_firstPlain); if(require->any() && reinterpret_cast<const BitFlags<116>*>(thingTemplate->m_kindof)->testSetAndClear(*reinterpret_cast<BitFlags<116>*>(require),KINDOFMASK_NONE)) return true; break; }
  case 0: mode=3; break;
 }
 bool result=mode==3; return result;
}
