// cl: /O1 /Ob2 /D_CRTIMP= /arch:SSE /G7 /Oy- /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport46
// Retail export writeINI@ParticleSystemTemplate@FXParticleSystem at 001FB418, 1041B.
// BFME1 9cbfb551fe20 identifies the template writer; adjacent readable module writers
// guide stream/header/footer use. Fields, defaults, strings and helper calls are retail facts.
// The three enum-name table labels below remain descriptive structural labels.
// /Ob2 and _CRTIMP= reproduce retail inline free cleanup without changing shared headers.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <sstream>
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::_M_construct_null(char *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::_M_construct_null_aux(char *, __true_type const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::fill(char); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::pbackfail(int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_ostream<char, char_traits<char> > * basic_ios<char, char_traits<char> >::tie(basic_ostream<char, char_traits<char> > *); }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??1?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@UAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_ostringstream<char,char_traits<char>,allocator<char> >::~basic_ostringstream(); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// STLport 4.6 inherits these proxy allocation methods from allocator<char>;
// the former 4.5.3 proxy specializations do not declare members in this mode.
class File { public: virtual ~File(); virtual bool open(const char*,int=0); virtual void close(); virtual int read(void*,int); virtual int write(const void*,int); };
struct Rva001F458BText { const char *m_start,*m_finish; };
File &Rva001F458BWrite(File&,const Rva001F458BText&);
void Rva003AFBC1Write(const char*,File*,unsigned*);
void Rva003AFC6BWrite(File*,unsigned*);
class Rva001FA7CE { public: void rva001FA7CE(int,int); };
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > NarrowString;
typedef _STL::basic_string<unsigned short,_STL::char_traits<unsigned short>,_STL::allocator<unsigned short> > WideString;
typedef _STL::basic_ostream<char,_STL::char_traits<char> > Stream;
NarrowString Rva001F949DConvert(const WideString&,char);
NarrowString Rva001F9524Concat(const NarrowString&,const char*);
struct S001F87D5 { int type; float x,y; };
struct S001F3744 { int type; float x,y; };
struct Vec001F8810 { float x,y,z; };
struct TreeHintPayload001F8ACB { unsigned long value; };
bool Rva001F3744IsZero(const S001F3744*);
void Rva001F82ABWrite(Stream&,unsigned,const char*,const char**);
void Rva001F89C3Write(Stream&,unsigned,const char*,const bool*);
void Rva001F82EEWrite(Stream&,unsigned,const char*,const AsciiString&);
void Rva001F89E2Write(Stream&,unsigned,const char*,const Vec001F8810&);
void Rva001F8B5FWrite(Stream&,unsigned,const char*,const S001F87D5&);
void Rva001F9006Write(Stream&,unsigned,const char*,const TreeHintPayload001F8ACB&);
namespace FXParticleSystem {
// Defined by ParticleSystemTemplate.cpp (retail VAs 0x00C1B6A4, 0x00C1B610, 0x00C1B640).
extern const char *ParticlePriorityNames[];
extern const char *ParticleShaderTypeNames[];
extern const char *ParticleTypeNames[];
class ParticleSystemTemplate { public: void writeINI(File&,unsigned) const;
private:
 void *m_vtable; bool m_isOneShot; char gap5[3]; int m_shader,m_type;
 AsciiString m_particleName; S001F87D5 m_lifetime;
 TreeHintPayload001F8ACB m_systemLifetime,m_sortLevel;
 S001F87D5 m_size,m_startSizeRate; int gap40; S001F87D5 m_burstDelay,m_burstCount,m_initialDelay;
 AsciiString m_slaveSystem; Vec001F8810 m_slavePosOffset; AsciiString m_attachedSystem;
 int m_priority; bool m_groundAligned,m_aboveGround,m_upToEmitter,m_useMaximumHeight,m_shroudEmitter;
 char gap85[0x17]; AsciiString m_name; int gapA0; Rva001FA7CE m_modules;
};
void ParticleSystemTemplate::writeINI(File &file,unsigned flags) const {
 Rva003AFBC1Write(Rva001F9524Concat(Rva001F949DConvert((const WideString&)NarrowString("FXParticleSystem"),' '),m_name.str()).c_str(),&file,&flags);
 Rva003AFBC1Write("System",&file,&flags);
 _STL::basic_ostringstream<char,_STL::char_traits<char>,_STL::allocator<char> > stream(16);
 if(m_priority != 1) Rva001F82ABWrite(stream,flags,"Priority",&ParticlePriorityNames[m_priority]);
 Rva001F89C3Write(stream,flags,"IsOneShot",&m_isOneShot);
 if(m_shader != 1) Rva001F82ABWrite(stream,flags,"Shader",&ParticleShaderTypeNames[m_shader]);
 if(m_type != 1) Rva001F82ABWrite(stream,flags,"Type",&ParticleTypeNames[m_type]);
 Rva001F82EEWrite(stream,flags,"ParticleName",m_particleName);
 if(!m_slaveSystem.isEmpty()) {
  Rva001F82EEWrite(stream,flags,"SlaveSystem",m_slaveSystem);
  Rva001F89E2Write(stream,flags,"SlavePosOffset",m_slavePosOffset);
 }
 if(!m_attachedSystem.isEmpty()) Rva001F82EEWrite(stream,flags,"PerParticleAttachedSystem",m_attachedSystem);
 if(!Rva001F3744IsZero((const S001F3744*)&m_lifetime)) Rva001F8B5FWrite(stream,flags,"Lifetime",m_lifetime);
 Rva001F9006Write(stream,flags,"SystemLifetime",m_systemLifetime);
 Rva001F9006Write(stream,flags,"SortLevel",m_sortLevel);
 if(!Rva001F3744IsZero((const S001F3744*)&m_size)) Rva001F8B5FWrite(stream,flags,"Size",m_size);
 if(!Rva001F3744IsZero((const S001F3744*)&m_startSizeRate)) Rva001F8B5FWrite(stream,flags,"StartSizeRate",m_startSizeRate);
 if(!Rva001F3744IsZero((const S001F3744*)&m_burstDelay)) Rva001F8B5FWrite(stream,flags,"BurstDelay",m_burstDelay);
 if(!Rva001F3744IsZero((const S001F3744*)&m_burstCount)) Rva001F8B5FWrite(stream,flags,"BurstCount",m_burstCount);
 if(!Rva001F3744IsZero((const S001F3744*)&m_initialDelay)) Rva001F8B5FWrite(stream,flags,"InitialDelay",m_initialDelay);
 Rva001F89C3Write(stream,flags,"IsGroundAligned",&m_groundAligned);
 Rva001F89C3Write(stream,flags,"IsEmitAboveGroundOnly",&m_aboveGround);
 Rva001F89C3Write(stream,flags,"IsParticleUpTowardsEmitter",&m_upToEmitter);
 Rva001F89C3Write(stream,flags,"UseMaximumHeight",&m_useMaximumHeight);
 Rva001F89C3Write(stream,flags,"ShroudEmitter",&m_shroudEmitter);
 Rva001F458BWrite(file,(const Rva001F458BText&)stream.str());
 Rva003AFC6BWrite(&file,&flags);
 ((Rva001FA7CE*)&m_modules)->rva001FA7CE((int)&file,flags);
 Rva003AFC6BWrite(&file,&flags);
}
}
