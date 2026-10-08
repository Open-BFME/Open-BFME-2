// cl: /MD
// ?Rva001FB912Init@@YAXPAX@Z @0x001FB912 43B
// ?Rva001FBAB2Init@@YAXPAX@Z @0x001FBAB2 38B
// ?Rva001FBC69Init@@YAXPAX@Z @0x001FBC69 38B
// ?Rva001FC010Init@@YAXPAX@Z @0x001FC010 38B
// ?Rva001FC37DInit@@YAXPAX@Z @0x001FC37D 38B
// ?Rva001FC477Init@@YAXPAX@Z @0x001FC477 38B
// ?Rva001FD022Init@@YAXPAX@Z @0x001FD022 38B
// Free __cdecl init storing FXParticleSystem GetKey(8) token at +0x80 and parse
// 0x001FA8DD at +0x84 with zeros at +0x88 and +0x8C. Evidence: push 8 GetKey
// rowed 0x003AFD16; stores mirror 0x001FBAB2 at +0x70 and 0x001FBC69 at +0x60;
// caller 0x001FBAB2 becomes ready; honest Rva free-function name.
namespace FXParticleSystem
{
    enum ModuleCategory
    {
        CAT_6 = 6,
        CAT_7 = 7,
        CAT_8 = 8
    };
    const char * __cdecl GetKey(ModuleCategory category);
};

class INI;
void __cdecl Rva001FA8DDParse();

struct Obj80
{
    char pad[0x80];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FB912Init(void *obj_)
{
    Obj80 *obj = (Obj80 *)obj_;
    const char *key = FXParticleSystem::GetKey(FXParticleSystem::CAT_8);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001FA8DDParse;
}

void __cdecl Rva001F8751Parse(INI *ini, void *store);

struct Obj70
{
    char pad[0x70];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FBAB2Init(void *obj_)
{
    Obj70 *obj = (Obj70 *)obj_;
    const char *key = FXParticleSystem::GetKey(FXParticleSystem::CAT_7);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F8751Parse;
    Rva001FB912Init(obj_);
}

void __cdecl Rva001F86E3Parse(INI *ini, void *store);

struct Obj60
{
    char pad[0x60];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FBC69Init(void *obj_)
{
    Obj60 *obj = (Obj60 *)obj_;
    const char *key = FXParticleSystem::GetKey(FXParticleSystem::CAT_6);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F86E3Parse;
    Rva001FBAB2Init(obj_);
}

void __cdecl Rva001F8675Parse(INI *ini, void *store);

struct Obj50
{
    char pad[0x50];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FC010Init(void *obj_)
{
    Obj50 *obj = (Obj50 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)5);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F8675Parse;
    Rva001FBC69Init(obj_);
}

void __cdecl Rva001F8607Parse(INI *ini, void *store);

struct Obj40
{
    char pad[0x40];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FC37DInit(void *obj_)
{
    Obj40 *obj = (Obj40 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)4);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F8607Parse;
    Rva001FC010Init(obj_);
}

void __cdecl Rva001F8599Parse(INI *ini, void *store);

struct Obj30
{
    char pad[0x30];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FC477Init(void *obj_)
{
    Obj30 *obj = (Obj30 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)3);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F8599Parse;
    Rva001FC37DInit(obj_);
}

void __cdecl Rva001F852BParse(INI *ini, void *store);

struct Obj20
{
    char pad[0x20];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FD022Init(void *obj_)
{
    Obj20 *obj = (Obj20 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)2);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F852BParse;
    Rva001FC477Init(obj_);
}

void __cdecl Rva001F84BDParse(INI *ini, void *store);

struct Obj10
{
    char pad[0x10];
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FD048Init(void *obj_)
{
    Obj10 *obj = (Obj10 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)1);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F84BDParse;
    Rva001FD022Init(obj_);
}

void __cdecl Rva001F83C9Parse(INI *ini, void *store);

struct Obj00
{
    const char *token;
    void *parse;
    void *userdata;
    int offset;
};

void __cdecl Rva001FD06EInit(void *obj_)
{
    Obj00 *obj = (Obj00 *)obj_;
    const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)0);
    obj->userdata = 0;
    obj->offset = 0;
    obj->token = key;
    obj->parse = (void *)Rva001F83C9Parse;
    Rva001FD048Init(obj_);
}
