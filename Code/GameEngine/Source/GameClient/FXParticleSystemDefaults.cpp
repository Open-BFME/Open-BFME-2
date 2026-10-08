// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc

// The default module key and name tables. Each of these ten accessors builds
// its string once into a function-local static and hands back the text, which
// is why they carry an EH prologue - the local static has a destructor, so its
// construction sits inside an unwind region - and why they cannot live in
// FXParticleSystem.cpp with its /GX-.

class AsciiString;

#include "ascii_string.h"

// Inline throughout: retail reaches StringBase's private constructor directly
// from the accessor rather than through a wrapper, which is what an inlined
// AsciiString constructor looks like.

namespace FXParticleSystem
{

enum ModuleCategory
{
    MODULE_CATEGORY_0, MODULE_CATEGORY_1, MODULE_CATEGORY_2, MODULE_CATEGORY_3,
    MODULE_CATEGORY_4, MODULE_CATEGORY_5, MODULE_CATEGORY_6, MODULE_CATEGORY_7,
    MODULE_CATEGORY_8
};

const char *GetKey(ModuleCategory category);
const char *GetName(ModuleCategory category);

// A struct, not a class: the U in ??4?$DefaultModuleKey@$0A@@... says so.
template <int CATEGORY>
struct DefaultModuleKey
{
public:
    static const char *const VALUE;

private:
    static const char *GetValue();
};

template <int CATEGORY>
const char *DefaultModuleKey<CATEGORY>::GetValue()
{
    static bool built = false;
    static AsciiString value("Default");

    if (!built) {
        ((StringBase<char> *)&value)->concat(GetKey((ModuleCategory)CATEGORY));
        built = true;
    }

    return value.str();
}

template <int CATEGORY>
const char *const DefaultModuleKey<CATEGORY>::VALUE = DefaultModuleKey<CATEGORY>::GetValue();

// A struct, not a class: the U in ??4?$DefaultModuleName@$0A@@... says so.
template <int CATEGORY>
struct DefaultModuleName
{
public:
    static const char *const VALUE;

private:
    static const char *GetValue();
};

template <int CATEGORY>
const char *DefaultModuleName<CATEGORY>::GetValue()
{
    static bool built = false;
    static AsciiString value("Default ");

    if (!built) {
        ((StringBase<char> *)&value)->concat(GetName((ModuleCategory)CATEGORY));
        built = true;
    }

    return value.str();
}

template <int CATEGORY>
const char *const DefaultModuleName<CATEGORY>::VALUE = DefaultModuleName<CATEGORY>::GetValue();

// The six categories that have a default module.
template class DefaultModuleKey<0>;
template class DefaultModuleKey<1>;
template class DefaultModuleKey<2>;
template class DefaultModuleKey<3>;
template class DefaultModuleKey<6>;
template class DefaultModuleKey<7>;

template class DefaultModuleName<0>;
template class DefaultModuleName<1>;
template class DefaultModuleName<2>;
template class DefaultModuleName<3>;
template class DefaultModuleName<6>;
template class DefaultModuleName<7>;


// The generated assignments - nothing to copy, so all twelve fold onto the one
// address every empty assignment in this family shares.
#define FX_FORCE_DEFAULT_ASSIGN(N, TAG)                                                                DefaultModuleKey<N> &(DefaultModuleKey<N>::*g_defaultModuleKeyAssign##TAG)(                            const DefaultModuleKey<N> &) = &DefaultModuleKey<N>::operator=;                                DefaultModuleName<N> &(DefaultModuleName<N>::*g_defaultModuleNameAssign##TAG)(                         const DefaultModuleName<N> &) = &DefaultModuleName<N>::operator=;

FX_FORCE_DEFAULT_ASSIGN(0, 0)
FX_FORCE_DEFAULT_ASSIGN(1, 1)
FX_FORCE_DEFAULT_ASSIGN(2, 2)
FX_FORCE_DEFAULT_ASSIGN(3, 3)
FX_FORCE_DEFAULT_ASSIGN(6, 6)
FX_FORCE_DEFAULT_ASSIGN(7, 7)

}
