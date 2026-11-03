// cl: /DNDEBUG /MD
//
// Three AnimationSoundClientBehavior overrides that hand the object to the
// container TheAnimationSoundModuleManager (0x00E032D0, the one its matched dtor
// 0x004C9DC9 leaves) as an Rva00432F23Node, through the rowed list members
// 0x00432E5D and 0x00432EC0. The ctor installs the primary vtable 0x00C5EE80
// and 0x00C5EE74 at +0x0C; the +0x0C slots are compiled with that subobject
// this and pass the full object. Names are by address.
//
// ?rva004C9E1F@AnimationSoundClientBehavior@@UAEXHHH@Z, retail 0x004C9E1F, 20
// bytes: primary slot 11 (three arguments, none read) adds the object.
// ?rva004C9E33@AnimationSoundClientBehavior@@UAEXXZ, retail 0x004C9E33, 21
// bytes: +0x0C slot 0 adds it; ?rva004C9E48@AnimationSoundClientBehavior@@UAEXXZ,
// retail 0x004C9E48, 21 bytes: +0x0C slot 1 takes it out (0x00432EC0).

class Rva00432F23Node;

class AnimationSoundModuleManager
{
public:
	void rva00432EC0(Rva00432F23Node*);
	void rva00432E5D(Rva00432F23Node*);
	void remove(Rva00432F23Node *node);
	void rva00432F7D(Rva00432F23Node *node);
};

extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;

template <int N> class Rva004C9E1FSlots : public Rva004C9E1FSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C9E1FSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class ModuleData;
class Drawable;

#include "../../../../Include/Common/DrawableModule.h"

class Rva004C9E33Iface
{
public:
	virtual void rva004C9E33() = 0;
	virtual void rva004C9E48() = 0;
};

class AnimationSoundClientBehavior : public DrawableModule, public Rva004C9E33Iface
{
public:
	virtual void rva004C9E1F(int a1, int a2, int a3);
	virtual void rva004C9E33();
	virtual void rva004C9E48();
private:
	Rva00432F23Node *node() { return (Rva00432F23Node *)(DrawableModule *)this; }
};

// ?rva004C9E1F@AnimationSoundClientBehavior@@UAEXHHH@Z @0x004C9E1F
void AnimationSoundClientBehavior::rva004C9E1F(int, int, int)
{
	if (TheAnimationSoundModuleManager)
		TheAnimationSoundModuleManager->rva00432E5D(node());
}

// ?rva004C9E33@AnimationSoundClientBehavior@@UAEXXZ @0x004C9E33
void AnimationSoundClientBehavior::rva004C9E33()
{
	if (TheAnimationSoundModuleManager)
		TheAnimationSoundModuleManager->rva00432E5D(node());
}

// ?rva004C9E48@AnimationSoundClientBehavior@@UAEXXZ @0x004C9E48
void AnimationSoundClientBehavior::rva004C9E48()
{
	if (TheAnimationSoundModuleManager)
		TheAnimationSoundModuleManager->rva00432EC0(node());
}
