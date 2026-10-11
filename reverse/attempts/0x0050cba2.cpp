// ?rva0050CBA2@Rva0050CBA2@@QAE_NPAX@Z
// partial score=0.956 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP=
// Open-BFME5 conversions.
// Native dump50C69D loads the fprintf IAT at00BBA5C4; use that import
// instead of an unresolved synthetic global. The ten four-byte handles use
// BFME2's shared AsciiString: their native destructor calls all target the
// complete releaseBuffer worker36410. All home bodies retain exact bytes.
// Original diagnostic owner names remain address-derived donor views.

#include "ascii_string.h"
extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);


class Rva0013A820
{
public:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	int m_24;
	AsciiString m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	AsciiString m_44;

	void reset();
};

class INIStatsRecord : public Rva0013A820
{
public:
	INIStatsRecord(const char *filename);
	// Inline: the stats writer 0x0050CBA2 inlines the fclose ahead of the base
	// destructor, while its unwind funclet calls the out-of-line copy.
	~INIStatsRecord() { fclose(m_bfme48); }
	void bfmeDump1191(void);
	void rva0050C90D();
	char *m_bfme48;
};

INIStatsRecord::INIStatsRecord(const char *filename)
{
	reset();
	m_bfme48 = (char *)fopen(filename, "w+");
	GetLastError();
	fprintf(m_bfme48, "Thing,Class,Draw,Tag,Model,Verts,Polys,Skel,Anim,Frames,Texture,Width,Height,Depth,TexTotl,File,Line,Desc\n");
}

void INIStatsRecord::bfmeDump1191(void)
{
	const char *s0 = m_00.str();
	int (__cdecl *fn)(void *dst, const char *fmt, ...) = fprintf;

	fn(m_bfme48, (char *)"%s,", s0);
	fn(m_bfme48, (char *)"%s,", m_04.str());
	fn(m_bfme48, (char *)"%s,", m_08.str());
	fn(m_bfme48, (char *)"%s,", m_0C.str());
	fn(m_bfme48, (char *)"%s,", m_10.str());
	fn(m_bfme48, (char *)"%d,", m_14);
	fn(m_bfme48, (char *)"%d,", m_18);
	fn(m_bfme48, (char *)"%s,", m_1C.str());
	fn(m_bfme48, (char *)"%s,", m_20.str());
	fn(m_bfme48, (char *)"%d,", m_24);
	fn(m_bfme48, (char *)"%s,", m_28.str());
	fn(m_bfme48, (char *)"%d,", m_2C);
	fn(m_bfme48, (char *)"%d,", m_30);
	fn(m_bfme48, (char *)"%d,", m_34);
	fn(m_bfme48, (char *)"%d,", m_38);
	fn(m_bfme48, (char *)"%s,", m_3C.str());
	fn(m_bfme48, (char *)"%d,", m_40);
	fn(m_bfme48, (char *)"%s\n", m_44.str());
}

// Native50C90D..50C91D16B calls diagnostic dump50C69D then tailcalls reset50C45A
// on the same receiver. Both complete callees already verify in their homes.
// This establishes dump/reset behavior and the consumed existing record view;
// the wrapper's original name is unknown. No adjacency-based type claim.
void INIStatsRecord::rva0050C90D()
{
    bfmeDump1191();
    reset();
}

// Native string copy-outs use the same shared four-byte AsciiString contract.
class ModuleData;
struct ModuleInfoNugget
{
    unsigned char m_bytes[0x14];
};
class ModuleInfo
{
public:
    AsciiString getNthName(int index) const;
    const ModuleData *getNthData(int index) const;
    int getCount() const { return m_finish - m_start; }
private:
    ModuleInfoNugget *m_start;
    ModuleInfoNugget *m_finish;
    ModuleInfoNugget *m_end;
};

class Rva0050C807
{
public:
    AsciiString rva0050C807(int index) const;
};

class Rva000B4A9F
{
public:
    const char *rva000B4A9F();
};

extern const char *const BfmeThingClassNames[];

// The rowed memberwise record copiers (Rva0050C2E6Copy.cpp): 0x0050C2E6
// copies the argument into the receiver, 0x0050C395 the receiver into it.
class Rva0050C2E6
{
public:
    void rva0050C2E6(const Rva0050C2E6 &other);
    void rva0050C395(Rva0050C2E6 &other);
};

class Rva0050CBA2
{
public:
    bool rva0050C91D(Rva0013A820 *record, ModuleInfo *modules,
                     const void *thing, Rva000B4A9F *draw, int index);
    bool rva0050C9EF(Rva0013A820 *record, int index);
    bool rva0050CBA2(void *filename);
};

bool Rva0050CBA2::rva0050C91D(Rva0013A820 *record, ModuleInfo *modules,
                              const void *thing, Rva000B4A9F *draw, int index)
{
    record->m_00.setCopyInline(*(const AsciiString *)((const char *)thing + 0x64));
    record->m_04 = BfmeThingClassNames[*(const signed char *)((const char *)thing + 0x5F6)];
    record->m_08 = modules->getNthName(index);
    record->m_0C = ((const Rva0050C807 *)modules)->rva0050C807(index);
    // This existing helper's pointer names a four-byte string handle: the
    // native caller passes it to StringBase::set(copy), not set(characters).
    record->m_10.setCopyInline(*(const AsciiString *)draw->rva000B4A9F());
    record->m_1C.setCopyInline(*(const AsciiString *)((const char *)draw + 0x58));
    if (((const StringBase<char> *)&record->m_10)->isEmpty()) {
        record->reset();
        return false;
    }
    return true;
}

// The stats writer's views. A thing template keeps its draw-module info at
// +0x2F0 and the next template at +0x484; the factory's first template is
// at +0x0C. Draw module data slot 18 returns the model-draw data whose two
// state vectors (252-byte condition states at +0x18, 248-byte transition
// states at +0x24) are copied through their rowed STLport constructors.
class ThingFactory;
extern ThingFactory *TheThingFactory;
struct Rva0050CBA2Template
{
    unsigned char m_000[0x2F0];
    ModuleInfo m_drawModules;
    unsigned char m_2FC[0x484 - 0x2FC];
    Rva0050CBA2Template *m_next;
};
struct Rva0050CBA2Factory
{
    unsigned char m_00[0x0C];
    Rva0050CBA2Template *m_firstTemplate;
};
struct BfmePod252
{
    unsigned char m_bytes[0xFC];
};
class Rva000B4926
{
public:
    const AsciiString &rva000B4926() const;
private:
    unsigned char m_bytes[0x40];
};
struct BfmePod248
{
    unsigned char m_00[0x50];
    Rva000B4926 *m_animStart;
    Rva000B4926 *m_animFinish;
    unsigned char m_58[0xF8 - 0x58];
};
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
    vector(const vector &);
    ~vector();
    T *m_start;
    T *m_finish;
    T *m_end;
};
}
typedef _STL::vector<BfmePod252, _STL::allocator<BfmePod252> > Rva0050CBA2StateVector;
typedef _STL::vector<BfmePod248, _STL::allocator<BfmePod248> > Rva0050CBA2TransitionVector;
struct Rva0050CBA2DrawData
{
    unsigned char m_00[0x18];
    Rva0050CBA2StateVector m_conditionStates;
    Rva0050CBA2TransitionVector m_transitionStates;
};
class ModuleData
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17();
    virtual const Rva0050CBA2DrawData *getAsW3DModelDrawModuleData() const;
};
// RefCountClass-derived render and animation objects: slot 0 deletes, the
// count sits at +4.
struct Rva0050CBA2RefCounted
{
    virtual void Delete_This();
    void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }
    int m_numRefs;
};
struct Rva0050CBA2RenderObj : Rva0050CBA2RefCounted
{
    virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09();
    virtual int Get_Num_Polys() const;
    virtual int Get_Num_Verts() const;
};
struct Rva0050CBA2Anim : Rva0050CBA2RefCounted
{
    virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual int Get_Num_Frames();
};
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *name);
class HTreeClass;
HTreeClass *Rva0014CF5F_GetAnimTree(const char *name);

bool Rva0050CBA2::rva0050CBA2(void *filename)
{
    INIStatsRecord record((const char *)filename);
    float count = 0.0f;
    Rva0050CBA2Template *thing;
    for (thing = ((Rva0050CBA2Factory *)TheThingFactory)->m_firstTemplate; thing; thing = thing->m_next)
        count += 1.0f;
    for (thing = ((Rva0050CBA2Factory *)TheThingFactory)->m_firstTemplate; thing && count > 0.0f; thing = thing->m_next)
    {
        ModuleInfo *modules = &thing->m_drawModules;
        int moduleCount = modules->getCount();
        for (int i = 0; i < moduleCount; ++i)
        {
            const ModuleData *data = modules->getNthData(i);
            if (!data)
                continue;
            const Rva0050CBA2DrawData *draw = data->getAsW3DModelDrawModuleData();
            if (!draw)
                continue;
            Rva0050CBA2StateVector states(draw->m_conditionStates);
            Rva0050CBA2TransitionVector transitions(draw->m_transitionStates);
            Rva0013A820 saved;
            for (BfmePod252 *state = states.m_start; state != states.m_finish; ++state)
            {
                if (rva0050C91D(&record, modules, thing, (Rva000B4A9F *)state, i))
                {
                    Rva0050CBA2RenderObj *robj = (Rva0050CBA2RenderObj *)Create_Render_Obj(record.m_10.str());
                    if (robj)
                    {
                        record.m_18 = robj->Get_Num_Polys();
                        record.m_14 = robj->Get_Num_Verts();
                        rva0050C9EF(&record, i);
                        robj->Release_Ref();
                    }
                    ((Rva0050C2E6 *)&record)->rva0050C395(*(Rva0050C2E6 *)&saved);
                    record.bfmeDump1191();
                }
                record.reset();
            }
            ((Rva0050C2E6 *)&record)->rva0050C2E6(*(const Rva0050C2E6 *)&saved);
            AsciiString previous;
            for (BfmePod248 *transition = transitions.m_start; transition != transitions.m_finish; ++transition)
            {
                for (Rva000B4926 *anim = transition->m_animStart; anim != transition->m_animFinish; ++anim)
                {
                    if (anim->rva000B4926() == previous)
                        continue;
                    record.m_20 = anim->rva000B4926();
                    previous = anim->rva000B4926();
                    Rva0050CBA2Anim *hanim = (Rva0050CBA2Anim *)Rva0014CF5F_GetAnimTree(anim->rva000B4926().str());
                    if (hanim)
                    {
                        record.m_24 = hanim->Get_Num_Frames();
                        hanim->Release_Ref();
                    }
                    record.bfmeDump1191();
                }
            }
            record.reset();
        }
    }
    return true;
}
