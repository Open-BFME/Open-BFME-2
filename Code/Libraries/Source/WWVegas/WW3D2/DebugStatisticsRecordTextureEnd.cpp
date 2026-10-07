// cl: /DNDEBUG /MD /EHsc
//
// ?Record_Texture_End@@YAXXZ, retail 0x00129E50, 948 bytes. Dedicated TU so
// the /G7 scheduling this body needs cannot disturb the TextureStatistics
// vector rows next door (their RefCountPtr assignment wants non-/G7 inc-word
// codegen). Ported from the BFME1 DebugStatisticsRecordTextureEnd donor: the
// per-frame counters freeze into the lastFrame set, then the DETAILS arm
// builds the texture report (header line, one formatted row per recorded
// texture with a kb size or N/A marker plus the texture name, then the
// legend footers). All callee rows already exist; Get_Texture_Memory_Usage
// resolves through its 0x00132B83 pin.

#include <string.h>

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer,
		unsigned int count, const char *format, ...);

// Minimal StringClass view: the out-of-line operators this TU calls
// (operator+= twice, Format) must stay calls, so the full wwstring.h inline
// bodies cannot be visible here. The inline shapes below (default/int/pointer
// constructors, destructor, const char * assignment) reproduce the inline
// expansions retail shows at the Record_Texture_End call sites.
class StringClass
{
public:
StringClass(int initial_len = 0, bool hint_temporary = false);

	// Both literal constructors expand inline in retail's Record_Texture_End.
	// Keep that expansion while ordinary C-string assignment uses its owner.
	StringClass(const char *string, bool hint_temporary = false);
	enum InlineCopy { COPY_INLINE };
	__forceinline StringClass(const char *string, bool hint_temporary, InlineCopy)
		: m_Buffer(m_EmptyString)
	{
		int len = string ? (int)strlen(string) : 0;
		if (hint_temporary || len > 0)
			Get_String(len + 1, hint_temporary);
		bfmeAssignInline(string);
	}
	~StringClass(void);
	const StringClass &operator=(const char *string);
	__forceinline const StringClass &bfmeAssignInline(const char *string)
	{
		if (string != 0)
		{
			int len = (int)strlen(string);
			Uninitialised_Grow(len + 1);
			Store_Length(len);
			memcpy(m_Buffer, string, len + 1);
		}
		return *this;
	}
	const StringClass &operator+=(const StringClass &string);
	const StringClass &operator+=(const char *string);
	int _cdecl Format(const char *format, ...);
	char *Peek_Buffer()
	{
		return m_Buffer;
	}
	const char *Peek_Buffer() const
	{
		return m_Buffer;
	}


private:
	static char *m_EmptyString;
	struct HEADER
	{
		int allocated_length;
		int length;
	};
	void Get_String(int length, bool is_temp);
	void Uninitialised_Grow(int length);
	void Free_String();
	void Store_Length(int length)
	{
		if (m_Buffer != m_EmptyString)
		{
			HEADER *header = reinterpret_cast<HEADER *>(m_Buffer - sizeof(HEADER));
			header->length = length;
		}
	}
	char *m_Buffer;
	static char m_NullChar;
};
// Keep the member body under its own compiler optimization context.
#pragma optimize("t", off)
#pragma optimize("s", on)
inline StringClass::StringClass(int initial_len, bool hint_temporary)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = m_NullChar;
	}
#pragma optimize("", on)


// StringClass::m_EmptyString: defined in wwstring.cpp (= &m_NullChar).
// StringClass::m_NullChar: defined in wwstring.cpp.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
// Add_Ref is inline so the TU emits no standalone copy: the ledger holds no
// row for it and the hook refuses undeclared definitions.
class TextureClass
{
public:
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref();
};

template<class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	// BFME's destructor does NOT null the pointer: ~TextureStatisticsStruct at
	// 0x00118800 is twelve bytes -- `mov ecx,[ecx] / test ecx,ecx / jz / jmp
	// Release_Ref` -- a tail jump with no store after it. Nulling costs the
	// tail call and ten bytes.
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
		}
	}
	T *Peek() const { return Referent; }
	unsigned int Get_Texture_Memory_Usage() const;

private:
	T *Referent;
};

// Virtual texture view for the Is_Initialized slot call in
// Record_Texture_End. Slot 0x28 is the eleventh virtual, matching the
// BFME1 Debug_Statistics donor's TextureStateView.
class TextureStateView
{
public:
	virtual void Slot_00() = 0;
	virtual void Slot_04() = 0;
	virtual void Slot_08() = 0;
	virtual void Slot_0C() = 0;
	virtual void Slot_10() = 0;
	virtual void Slot_14() = 0;
	virtual void Slot_18() = 0;
	virtual void Slot_1C() = 0;
	virtual void Slot_20() = 0;
	virtual void Slot_24() = 0;
	virtual bool Is_Initialized() = 0;
};

// Handle type owning the out-of-line Get_Texture_Name row at 0x00129D30.
// Only the declaration is visible here; the row provides the body.
class BFME2ParticleTextureHandle
{
public:
	StringClass Get_Texture_Name() const;
};

struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;
};

template<class T>
class VectorClass
{
public:
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
};

static int texture_memory;
static int texture_count;
static int lightmap_texture_memory;
static int lightmap_texture_count;
static int procedural_texture_memory;
static int procedural_texture_count;
static int record_count;
static int texture_change_count;
static DynamicVectorClass<TextureStatisticsStruct> texture_statistics;
static int lastFrameTextureMemory;
static int lastFrameTextureCount;
static int lastFrameLightmapTextureMemory;
static int lastFrameLightmapTextureCount;
static int lastFrameProceduralTextureMemory;
static int lastFrameProceduralTextureCount;
static int lastFrameRecordCount;
static int lastFrameTextureChangeCount;

class Debug_Statistics
{
public:
	enum RecordTextureMode
	{
		RECORD_TEXTURE_NONE,
		RECORD_TEXTURE_SIMPLE,
		RECORD_TEXTURE_DETAILS
	};
};

static Debug_Statistics::RecordTextureMode recordTextureMode;
static StringClass textureStatisticsString;

void Record_Texture_End()
{
	lastFrameTextureMemory = texture_memory;
	lastFrameTextureCount = texture_count;
	lastFrameLightmapTextureMemory = lightmap_texture_memory;
	lastFrameLightmapTextureCount = lightmap_texture_count;
	lastFrameProceduralTextureMemory = procedural_texture_memory;
	lastFrameProceduralTextureCount = procedural_texture_count;
	lastFrameRecordCount = record_count;
	lastFrameTextureChangeCount = texture_change_count;

	textureStatisticsString.bfmeAssignInline("");
	if (recordTextureMode == Debug_Statistics::RECORD_TEXTURE_DETAILS)
	{
		char temporary[1024];
		_snprintf(temporary, sizeof(temporary),
			"Set_DX8_Texture count: %d\nactual changes: %d\n\nid      refs changes  size      name\n--------------------------------------\n",
			lastFrameRecordCount, lastFrameTextureChangeCount);
		textureStatisticsString += temporary;
		for (int index = 0; index < texture_count; ++index)
		{
			StringClass workingString;
			RefCountPtr<TextureClass> texture = texture_statistics[index].tex;
			int id = 0;
			StringClass flash("  ", false, StringClass::COPY_INLINE);
			workingString.Format("%4.4d  %3.3d   %3.3d     %s ", id,
				texture_statistics[index].usage_count,
				texture_statistics[index].change_count, flash.Peek_Buffer());
			textureStatisticsString += workingString;

			StringClass error("", false, StringClass::COPY_INLINE);
			if (texture.Peek() != 0)
			{
				unsigned bytes = texture.Get_Texture_Memory_Usage();
				if (texture.Peek() == 0)
					goto texture_status_missing;
				bool initialized;
				initialized = reinterpret_cast<TextureStateView *>(texture.Peek())->Is_Initialized();
				if (initialized == false)
					goto texture_status_missing;
				textureStatisticsString += "  ";
				goto texture_status_done;
			texture_status_missing:
				textureStatisticsString += "*";
			texture_status_done: ;
				workingString.Format("%4.4dkb         ", bytes / 1024);
				textureStatisticsString += workingString;
			}
			else
			{
				textureStatisticsString += "N/A  ";
			}
			textureStatisticsString += reinterpret_cast<const BFME2ParticleTextureHandle &>(texture).Get_Texture_Name();
			textureStatisticsString += error;
			textureStatisticsString += "\n";
		}
		textureStatisticsString += "\nid              = id of texture. Use with command 'flash_texture [id]'\n";
		textureStatisticsString += "refs          = # of times texture is used when rendering\n";
		textureStatisticsString += "changes    = # of times texture change needed - BAD IF HIGH!\n";
		textureStatisticsString += "red         = texture reduction factor\n";
		textureStatisticsString += "size          = amount of memory needed for texture\n";
		textureStatisticsString += "(w/o red)     = size of reduction not used\n";
		textureStatisticsString += "percent    = savings of reduction system, in percents\n";
		textureStatisticsString += "\n* = thumbnail used\n";
		textureStatisticsString += "\n";
	}
}

// Native public teardown and Free_String share0x00610A40 (DX8Wrapper call proof).
#pragma comment(linker, "/alternatename:??1StringClass@@QAE@XZ=?Free_String@StringClass@@AAEXXZ")
