// ?m009EFD40@Q1Receiver0134FAAC@@QAEXPAUQ1ReceiverLocalSet@@@Z
// partial score=0.98 date=2026-10-09
// ?m009EFD40@Q1Receiver0134FAAC@@QAEXPAUQ1ReceiverLocalSet@@@Z
// partial score=0.98 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Target identity: WB AssetManagerImpl::AddDependentAssets at 0x01678D00
// maps to native 0x006217F0..0x006219F1, 513 bytes, RET4. The existing
// WB pairing's 502-byte extent ends inside the epilogue; native RET4 proves 513.
// Q1Receiver0134FAAC::m009EFD40 pin is retained for owned callers.
// Semantic reference: BFME1 ba7ddda7 assetmanager_impl.cpp,
// AssetRegistryKeySet009EF7D0.cpp and AssetRegistryQueueKeys009EFBF0.cpp
// establish the shared copy wrapper, tree and registry ABI; native and WB
// independently provide the complete fixed-point dependency walk.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_USE_MALLOC 1
#include <set>
#include <hash_map>

struct Gen_t_009ee8e0_k4
{
    int a[1];
    Gen_t_009ee8e0_k4();
    Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
    ~Gen_t_009ee8e0_k4();
    Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};
bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;
struct Rva001408C0Target;
typedef Rva001408C0Target *AssetDependencyKey;
typedef _STL::set<AssetDependencyKey> AssetDependencySet;
void j_00015d7a();

struct Q1ReceiverTreeStorage
{
    Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
    ~Q1ReceiverTreeStorage()
    {
        typedef void (Q1ReceiverSet::*TreeDestructor)();
        union { void (*raw)(); TreeDestructor member; } destroy;
        destroy.raw = j_00015d7a;
        (get().*destroy.member)();
    }
    Q1ReceiverSet &get() { return *(Q1ReceiverSet *)m_storage; }
    const Q1ReceiverSet &get() const { return *(const Q1ReceiverSet *)m_storage; }
    AssetDependencySet &keys() { return *(AssetDependencySet *)m_storage; }
    int m_storage[3];
};
struct Q1ReceiverLocalSet
{
    Q1ReceiverTreeStorage m_set;
    unsigned int m_count;
    bool m_active;
    Q1ReceiverLocalSet(const Q1ReceiverLocalSet &other)
        : m_set(other.m_set.get())
    {
        m_count = 0;
        m_active = true;
    }
    void clear()
    {
        m_set.keys().clear();
        m_active = true;
    }
};
struct AssetDependencyRecord
{
    char m_prefix[0xc];
    AssetDependencyKey *m_dependencies;
};
typedef _STL::hash_map<int, AssetDependencyRecord *> GenAssetHash;
class Q1Receiver0134FAAC
{
public:
    void m009EFD40(Q1ReceiverLocalSet *source);
private:
    char m_prefix[0x4c];
    GenAssetHash m_assets;
};

void Q1Receiver0134FAAC::m009EFD40(Q1ReceiverLocalSet *source)
{
    Q1ReceiverLocalSet frontier(*source);
    while (!frontier.m_set.keys().empty())
    {
        Q1ReceiverLocalSet previous(frontier);
        frontier.clear();
        for (AssetDependencySet::const_iterator it=previous.m_set.keys().begin();
             it!=previous.m_set.keys().end(); ++it)
        {
            const int key=(int)*it;
            if (!key)
                continue;
            GenAssetHash::const_iterator found=m_assets.find(key);
            if (found==m_assets.end())
                continue;
            AssetDependencyRecord *asset=found->second;
            AssetDependencyKey *deps=asset->m_dependencies;
            if (!deps)
                continue;
            for (int n=0; asset->m_dependencies[n]; ++n)
            {
                AssetDependencyKey dependency=asset->m_dependencies[n];
                if (source->m_set.keys().find(dependency)==source->m_set.keys().end())
                {
                    frontier.m_set.keys().insert(dependency);
                    source->m_set.keys().insert(dependency);
                }
            }
        }
    }
}
