// cl: /G7 /DNDEBUG /MD /EHsc
//
// ShareBufferClass<float> destructor pair for the FX particle size buffer.
//
// The CategoryModule<CAT_DRAW> constructor at 0x001A7B80 builds the
// m_sizeBuffer ("FXParticleSystem::CategoryModule<CAT_DRAW>::m_sizeBuffer")
// as a NEW_REF(ShareBufferClass<float>) — the BFME1 donor at
// W3DParticleSys.cpp:77 names the same buffer ShareBufferClass<float>, and
// the retail constructor scales the count by 4. The constructor installs
// vtable 0xBD71C0, whose slot 1 is the deleting destructor at 0x001A7F70,
// which calls this body at 0x001A7F90.
//
// Same explicit-specialization recipe as the ShaderClass pair in
// sharebuf_shader_copy_ctor.cpp: the specialization is declared before any
// use so it wins over the primary template, and the deleting destructor
// needs no source of its own (the compiler emits it once this row lands).

extern void __cdecl operator delete[](void *) throw();

// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call, e.g. TileDataGetRGBDataForWidth's TU);
// this TU builds /G7 which emits add esp,4 instead. Compile just the base
// class for size so our COMDAT matches the first copy in link order.
// Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};
#pragma optimize("", on)

template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	~ShareBufferClass();

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

// ??1?$ShareBufferClass@M@@UAE@XZ, retail 0x001A7F90 (29 bytes).
// Owns a raw float array (particle sizes); the destructor frees it.
template <>
inline ShareBufferClass<float>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}
#pragma inline_depth(0)
// ?bfmeEmitsharebuf_float_dtor@@YAXPAV?$ShareBufferClass@M@@@Z present-unmatched
void bfmeEmitsharebuf_float_dtor(ShareBufferClass<float> *p)
{
	p->ShareBufferClass<float>::~ShareBufferClass();
}
#pragma inline_depth()
