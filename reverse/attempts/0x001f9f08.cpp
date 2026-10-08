// ?findParentTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@H@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?findTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@@Z
// retail 0x001F90DA (43B). Zero Hour ParticleSys.cpp:
//   ParticleSystemTemplate *sysTemplate = NULL;
//   TemplateMap::const_iterator find(m_templateMap.find(name));
//   if (find != m_templateMap.end()) sysTemplate = (*find).second;
//   return sysTemplate;
// The template map sits at +0x88 and is the Rva00056F61 bucket table whose
// iterator find (0x0041534B) is rowed; retail tests the iterator's node
// rather than comparing with end(), as the rowed sibling lookups
// (Rva0021311FGet.cpp) do. Evidence: symbols.csv pin (INI::
// parseParticleSystemTemplate's call at 0x003395BB); 8 units call it.
#include "ascii_string.h"
// stlport
#include <hash_map>

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

// BFME 1 ba7ddda7 ParticleSys.cpp findParentTemplate supplies the semantic
// lead. Existing target findTemplate proves the manager map at +88; the
// ParticleSystemTemplate parse table and native lookup prove SlaveSystem +68.
// This is a borrowed prefix, without an allocation-size claim.
namespace rts
{
    template <class T> struct hash;
    template <> struct hash<AsciiString>
    {
        unsigned int operator()(AsciiString value) const;
    };
}
class ParticleSystemTemplate
{
public:
    char prefix[0x68];
    AsciiString m_slaveSystemName;
};
typedef _STL::hash_map<AsciiString,ParticleSystemTemplate*,rts::hash<AsciiString>,_STL::equal_to<AsciiString> > TemplateMap;

typedef TemplateMap::value_type ParticleMapValue;
typedef _STL::hashtable<ParticleMapValue,AsciiString,rts::hash<AsciiString>,_STL::_Select1st<ParticleMapValue>,_STL::equal_to<AsciiString>,_STL::allocator<ParticleMapValue> > ParticleTable;
typedef _STL::_Hashtable_iterator<ParticleMapValue,AsciiString,rts::hash<AsciiString>,_STL::_Select1st<ParticleMapValue>,_STL::equal_to<AsciiString>,_STL::allocator<ParticleMapValue> > ParticleIteratorCore;
// Keep native hash and bucket-advance calls out of line. Specializations
// follow the byte-verified EvaBucketIndex/EvaBucketAdvance algorithms;
// each is admitted only as a strict byte-and-relocation ICF twin.
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *key);
namespace _STL
{
// ?_M_bkt_num_key@?$hashtable@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@@_STL@@ABEIABVAsciiString@@@Z
template<> __declspec(noinline) unsigned int ParticleTable::_M_bkt_num_key(const AsciiString &key) const
{
    unsigned int hash = Rva00055041AsciiHash(&key);
    unsigned int count = (unsigned int)_M_buckets.size();
    return hash % count;
}
// ?_M_skip_to_next@?$_Hashtable_iterator@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@@_STL@@QAEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@XZ
template<> __declspec(noinline) _Hashtable_node<ParticleMapValue>* ParticleIteratorCore::_M_skip_to_next()
{
    typedef _Hashtable_node<ParticleMapValue> Node;
    // The native bucket loop reloads begin for every slot; its count uses
    // the ordinary vector start. This borrowed vector prefix preserves both.
    struct BucketView
    {
        union { void **begin; void **volatile liveBegin; };
        void **end;
        void **capacity;
    };
    ParticleTable *table = this->_M_ht;
    unsigned int index = table->_M_bkt_num_key(this->_M_cur->_M_val.first);
    BucketView *buckets = reinterpret_cast<BucketView *>(&table->_M_buckets);
    unsigned int count = (unsigned int)(((char *)buckets->end - (char *)buckets->begin) >> 2);
    Node *head = 0;
    do
    {
        ++index;
        if (index >= count)
            break;
        head = static_cast<Node *>(buckets->liveBegin[index]);
    } while (head == 0);
    return head;
}
}

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
    ParticleSystemTemplate *findParentTemplate(const AsciiString &name, int parentNum) const;

private:
	char m_pad[0x88];
	Rva00056F61 m_templateMap;	// +0x88
};

ParticleSystemTemplate *ParticleSystemManager::findTemplate(const AsciiString &name) const
{
	ParticleSystemTemplate *sysTemplate = 0;
	Rva0041534BIter find = const_cast<Rva00056F61 &>(m_templateMap).rva0041534B(&name);
	if (find.m_node != 0)
		sysTemplate = *(ParticleSystemTemplate **)((char *)find.m_node + 8);
	return sysTemplate;
}

ParticleSystemTemplate *ParticleSystemManager::findParentTemplate(const AsciiString &name, int parentNum) const
{
    if (reinterpret_cast<const StringBase<char> *>(&name)->isEmpty())
        return 0;
    const TemplateMap &templates = reinterpret_cast<const TemplateMap &>(m_templateMap);
    TemplateMap::const_iterator begin(templates.begin()), end(templates.end());
    for (; begin != end; ++begin)
    {
        ParticleSystemTemplate *tmpl = (*begin).second;
        if (name.compare(tmpl->m_slaveSystemName) == 0 && !parentNum--)
            return tmpl;
    }
    return 0;
}
