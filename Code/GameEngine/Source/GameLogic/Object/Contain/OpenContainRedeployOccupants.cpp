// cl: /O1 /GF- /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
// Target identity: WB VA 0x01198D60 explicitly names OpenContain::privateRedeployOccupants.
// Target boundary: game.dat RVA 0x00465972..0x00465EF1, 1407 bytes, RET 8.
// Native access proves owner +8, secondary contain interface +0x20, names +0x3C,
// module-data conditions +0x4C / turret +0x85, Object ID +0x74 / transform +8.
// WB supplies the bulk-redeployment control flow; native supplies these layouts
// and slot 44 status / slot 27 placement / primary slot 14 orientation calls.
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD OpenContain.cpp supplies
// putObjAtNextFirePoint purpose, and WWMath matrix3d.h/vector4.h supply row copies.
// The bulk extension and 19-word condition values are target evidence, not ZH layout.
// Neutral Rva helpers retain the ledger identities; mask/slot views below assert
// only the accessed ABI, not a complete class or enum reconstruction.
#include <map>
#include <list>
// Keep template bodies visible for nonescape analysis; use existing providers
// for their out-of-line copies. Declaration-only operator[] changes ESP homes.
// These four unchanged STLport accessor bodies must stay inline-only.
namespace _STL {
template <> __declspec(dllimport) __forceinline less<int> _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::key_comp() const {return _M_key_compare;}
template <> __declspec(dllimport) __forceinline _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::iterator _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > >::end() {return iterator(this->_M_header._M_data);}
template <> __declspec(dllimport) __forceinline less<int> map<int,int>::key_comp() const {return _M_t.key_comp();}
template <> __declspec(dllimport) __forceinline map<int,int>::iterator map<int,int>::end() {return _M_t.end();}
}
// The comparators, the pair constructor and the base-iterator != only inline
// here; their out-of-line copies lose to the kept/retail ones, so keep the
// template members inline-only (bodies verbatim) and compare typed tree/list
// iterators through TU-local overloads (CaveContainOnRemoving.cpp precedent).
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &__x, const int &__y) const { return __x < __y; }
template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(const unsigned int &__x, const unsigned int &__y) const { return __x < __y; }
template <> __declspec(dllimport) __forceinline pair<const int, int>::pair(const int &__a, const int &__b) : first(__a), second(__b) {}
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L> &a, const _Rb_tree_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits> &a, const _List_iterator<T, Traits> &b)
{ return a._M_node != b._M_node; }
}
extern template class _STL::map<int,int>;
extern template class _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > >;

#include <stdlib.h>
#include "ascii_string.h"
// Read-only BF1/GeneralsMD matrix3d.h supplies the 3-by-4 float copy contract.
// Native32 arrays each invoke three16B default row constructors.
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "Lib/Coord3D.h"
enum ObjectStatusTypes
{
    STATUS_DUMMY=-1
};
enum WhichTurretType
{
    TURRET_DUMMY=-1
};
class Object;
#include "../../../Common/Thing/thing.h"
class Rva00463235
{
public:
    AsciiString rva00463235(Thing*);
};
#include "../../../../Include/GameLogic/Module/Rva001E42F2.h"
#include "../../../../Include/GameLogic/Module/Rva001E431E.h"
class Rva000B6253
{
public:
    Rva000B6253 *rva000B6253(int,unsigned,unsigned,unsigned,unsigned,unsigned);
    operator const int*()const
    {
        return words;
    }
    int words[19];
};
class Object
{
public:
    int getID()const
    {
        return id;
    }
    const Matrix3D *getTransformMatrix()const
    {
        return &transform;
    }
    bool testStatus(ObjectStatusTypes)const;
    void setStatus(ObjectStatusTypes,bool);
    int getMultiLogicalBonePosition(const char*,int,Coord3D*,Matrix3D*,bool,int)const;
    bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
    bool getSingleLogicalBonePositionOnTurret(WhichTurretType,const char*,Coord3D*,Matrix3D*)const;
    char pad[8];
    Matrix3D transform;
    char pad38[0x74-0x38];
    int id;
};
struct RedeployStatusMask
{
    unsigned words[4];
    bool test(int bit)const
    {
        return (unsigned char)(words[bit>>5]>>(bit&31))&1;
    }
};
template<int N>class RedeploySlots:public RedeploySlots<N-1>
{
public:
    virtual void slot(char(*)[N])=0;
};
template<>class RedeploySlots<0>
{
};
class RedeployContain27:public RedeploySlots<27>
{
public:
    virtual void placement(Object*,bool);
};
class RedeployContain44:public RedeploySlots<44>
{
public:
    virtual RedeployStatusMask getStatus(Object*);
};
class Rva004650A0:public _STL::map<int,AsciiString>
{
public:
    AsciiString &rva004650A0(const int&);
};
struct RedeployModelMask
{
    unsigned words[19];
};
struct RedeployModuleData
{
    char pad[0x4C];
    _STL::map<unsigned,RedeployModelMask> conditions;
    char pad58[0x85-0x4C-sizeof(_STL::map<unsigned,RedeployModelMask>)];
    bool turret;
};
class OpenContain:public RedeploySlots<14>
{
public:
    virtual bool orient(Object*);
private:
    __declspec(dllimport) __forceinline Object *getObject()const
    {
        return owner;
    }
    void privateRedeployOccupants(const _STL::list<Object*>*,_STL::map<int,int>*);
    const RedeployModuleData *data;
    Object *owner;
    char pad0C[0x20-0x0C];
    char contain[4];
    char pad24[0x3C-0x24];
    Rva004650A0 names;
};
static __forceinline void appendChar(AsciiString &asciiString,char c)
{
    ((StringBase<char>*)&asciiString)->concat(&c,1);
}
void OpenContain::privateRedeployOccupants(const _STL::list<Object*> *objects,_STL::map<int,int> *oldPoints)
{
    AsciiString lastBone("");
    bool multiple=true;
    Matrix3D firePoints[32];
    int indices[32];
    int loaded=0;
    for(_STL::list<Object*>::const_iterator it=objects->begin();it!=objects->end();++it)
    {
        Object *object=*it;
        if(object->testStatus((ObjectStatusTypes)0x28))continue;
        AsciiString bone=((Rva00463235*)this)->rva00463235((Thing*)object);
        if(bone!=lastBone)
        {
            loaded=getObject()->getMultiLogicalBonePosition(bone.str(),32,0,firePoints,true,(int)indices);
            lastBone=bone;
            if(!loaded)
            {
                if(getObject()->getSingleLogicalBonePosition(bone.str(),0,firePoints))
                {
                    loaded=1;
                    multiple=false;
                }
            }
        }
        int objectID=object->id;
        int point=-1;
        if(oldPoints->find(objectID)!=oldPoints->end())
        {
            int oldPoint=(*oldPoints)[objectID];
            if(oldPoint<loaded)point=oldPoint;
        }
        else
        {
            int p;
            bool taken=false;
            for(p=0;p<loaded;)
            {
                taken=false;
                AsciiString candidate(bone);
                if(multiple)
                {
                    char suffix[8];
                    _itoa(p+1,suffix,10);
                    // Retail tests point (-1 here), so this prefix is unconditional.
                    if(point<10)
                    {
                        appendChar(candidate,'0');
                    }
                    candidate+=suffix;
                }
                for(Rva004650A0::const_iterator n=names.begin();n!=names.end();++n)
                {
                    if(n->second==candidate)
                    {
                        taken=true;
                        ++p;
                        break;
                    }
                }
                if(!taken)break;
            }
            if(!taken)
            {
                point=p;
                (*oldPoints)[objectID]=point;
            }
        }
        Matrix3D placement;
        if(point!=-1)
        {
            if(((RedeployContain44*)&contain)->getStatus(object).test(1)&&!((RedeployContain44*)&contain)->getStatus(object).test(61))object->setStatus((ObjectStatusTypes)5,false);
            AsciiString fullBone(bone);
            if(multiple)
            {
                char suffix[8];
                _itoa(point+1,suffix,10);
                if(point<10)
                {
                    appendChar(fullBone,'0');
                }
                fullBone+=suffix;
            }
            names.rva004650A0(object->getID())=fullBone;
            const RedeployModuleData *moduleData=data;
            if(moduleData->turret)
            {
                getObject()->getSingleLogicalBonePositionOnTurret((WhichTurretType)0,fullBone.str(),0,&placement);
            }
            else
            {
                placement=firePoints[point];
                Rva000B6253 mask;
                ((Rva001E42F2*)object)->rva001E42F2(mask.rva000B6253(0,0xC2,0xC3,0xC4,0xC5,0xC6)->words);
                unsigned boneIndex=indices[point];
                _STL::map<unsigned,RedeployModelMask>::const_iterator mod=moduleData->conditions.find(boneIndex);
                if(mod!=moduleData->conditions.end())((Rva001E431E*)object)->rva001E431E((const int*)mod->second.words);
            }
            ((RedeployContain27*)contain)->placement(object,((RedeployContain44*)&contain)->getStatus(0).test(61));
        }
        else
        {
            if(((RedeployContain44*)&contain)->getStatus(object).test(1)&&!((RedeployContain44*)&contain)->getStatus(object).test(61))object->setStatus((ObjectStatusTypes)5,true);
            placement.Row[0]=owner->transform.Row[0];
            placement.Row[1]=owner->transform.Row[1];
            placement.Row[2]=owner->transform.Row[2];
            ((RedeployContain27*)contain)->placement(object,true);
        }
        if(!((RedeployContain44*)&contain)->getStatus(0).test(61)&&orient(object))((Thing*)object)->setTransformMatrix(&placement);
        else
        {
            Coord3D pos;
            pos.x=placement[0][3];
            pos.y=placement[1][3];
            pos.z=placement[2][3];
            ((Thing*)object)->setPosition(&pos);
        }
    }
}
