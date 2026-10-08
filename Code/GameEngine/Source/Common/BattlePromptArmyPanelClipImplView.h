#ifndef BFME2_BATTLE_PROMPT_ARMY_PANEL_CLIP_IMPL_VIEW_H
#define BFME2_BATTLE_PROMPT_ARMY_PANEL_CLIP_IMPL_VIEW_H
#include "ascii_string.h"
#include "unicode_string.h"
#include "BattlePromptArmyPanelClipOwnerFwd.h"
#include <vector>
// Retail005FF675 initializes owner00 level04 string08 and flags3C/3D;
// the enclosing factory allocates64 bytes. Matched methods prove caches2C/30,
// eight-byte icon slots and the string-buffer name prefix used by APT calls.
// Native constructors and unwind edges establish command-map0C and image-key18
// lifetimes. SetLayout/SetImage siblings establish state24 and portrait28.
// The parent interface declares only observed call ABIs, not original names.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[0xC];
};

namespace _STL {
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
}
// Native005FF5F6 calls the existing47-byte destructor at005242D7
// for this12-byte image-key vector, clearing its registered APT images.
// Its default constructor is the genuine19-byte vector-constructor fold.
class Rva005242D7 {
public:
    Rva005242D7();
    ~Rva005242D7();
private:
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names;
};
struct BfmePod8 { int a[2]; };
class BfmePod8Vector : public _STL::vector<BfmePod8, _STL::allocator<BfmePod8> > {
public:
    __forceinline BfmePod8Vector() {}
    void resize(unsigned int, BfmePod8);
    void resize(unsigned int);
};
// Borrowed receiver interface: only invoked slots01 through05 have known ABIs.
class BattlePromptArmyPanelClipEvents {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04(int);
    virtual void slot05(int);
};
class Image;
class Rva005FF912;
class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl {
public:
    Impl(Rva005FF912 *, int, const AsciiString &);
    void SetUnitIconProperties(int, const Image *, int);
    void rva005FF5C0(const UnicodeString &);
    void SetUnitIconString(int, const char *, const UnicodeString &);
    void SetArmyNameString(const UnicodeString &);
    void SetUnitIconCount(int);
    void SetSelected(bool);
    void SetMouseOver(bool);
    void OnClicked(const char *);
    void OnRollOver(const char *);
    void OnRollOut(const char *);
    void OnUnitIconRollOver(const char *);
    void OnUnitIconRollOut(const char *);
private:
    BattlePromptArmyPanelClipEvents *m_parent00;
    unsigned int m_level;
    AsciiString m_name08;
    AptCommandMapAdder m_commands0C;
    Rva005242D7 m_images18;
    int m_state24;
    const Image *m_portrait28;
    UnicodeString m_cached2C;
    BfmePod8Vector m_icons;
    bool m_selected3C;
    bool m_over3D;
    char m_tail3E[2];
};

#endif
