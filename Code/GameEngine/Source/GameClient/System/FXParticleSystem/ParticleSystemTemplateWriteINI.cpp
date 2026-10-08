// cl: /O1 /Ob2 /D_CRTIMP= /arch:SSE /G7 /Oy- /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Retail export writeINI@ParticleSystemTemplate@FXParticleSystem at 001FB418, 1041B.
// BFME1 9cbfb551fe20 identifies the template writer; adjacent readable module writers
// guide stream/header/footer use. Fields, defaults, strings and helper calls are retail facts.
// The three enum-name table labels below remain descriptive structural labels.
// /Ob2 and _CRTIMP= reproduce retail inline free cleanup without changing shared headers.
#include <sstream>
#include "ascii_string.h"
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
extern const char *g_fxParticlePriorityNames[];
extern const char *g_fxParticleShaderNames[];
extern const char *g_fxParticleTypeNames[];
namespace FXParticleSystem {
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
 if(m_priority != 1) Rva001F82ABWrite(stream,flags,"Priority",&g_fxParticlePriorityNames[m_priority]);
 Rva001F89C3Write(stream,flags,"IsOneShot",&m_isOneShot);
 if(m_shader != 1) Rva001F82ABWrite(stream,flags,"Shader",&g_fxParticleShaderNames[m_shader]);
 if(m_type != 1) Rva001F82ABWrite(stream,flags,"Type",&g_fxParticleTypeNames[m_type]);
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
