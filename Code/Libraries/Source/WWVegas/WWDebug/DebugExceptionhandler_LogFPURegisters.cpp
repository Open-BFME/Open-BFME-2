// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// DebugExceptionhandler::LogFPURegisters, retail 0x0003CD30 (635 bytes),
// converted from the Zero Hour debug_except.cpp body; ExceptionFilter
// (0x0003DCD0) calls it right after LogRegisters. The only BFME2 change is
// the Debug layout: width at +0x9F50 and fill character at +0x9F54, as in
// DebugExceptionhandler_LogRegisters.cpp.

struct FLOATING_SAVE_AREA
{
	unsigned long ControlWord;
	unsigned long StatusWord;
	unsigned long TagWord;
	unsigned long ErrorOffset;
	unsigned long ErrorSelector;
	unsigned long DataOffset;
	unsigned long DataSelector;
	unsigned char RegisterArea[80];
	unsigned long Cr0NpxState;
};

struct _CONTEXT
{
	unsigned long ContextFlags;
	unsigned long Dr[6];
	FLOATING_SAVE_AREA FloatSave;
};

struct _EXCEPTION_POINTERS
{
	void *ExceptionRecord;
	struct _CONTEXT *ContextRecord;
};

// Local ABI view of the BFME Debug interface. MSVC places an overload
// group at its first slot in reverse declaration order, so the stream
// writers land at 0x1C (double) through 0x38 (const char *), matching the
// retail vtable; SetPrefixAndRadix sits at 0x50.
class Debug
{
public:
	class Hex {};
	class Dec {};
	class Bin {};

	class Width
	{
		friend class Debug;
		int m_width;

	public:
		explicit Width(int width) : m_width(width) {}
	};

	class FillChar
	{
		friend class Debug;
		char m_fill;

	public:
		explicit FillChar(char fill = ' ') : m_fill(fill) {}
	};

	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual Debug &operator<<(const char *);
	virtual Debug &operator<<(int);
	virtual Debug &operator<<(unsigned);
	virtual Debug &operator<<(long);
	virtual Debug &operator<<(unsigned long);
	virtual Debug &operator<<(bool);
	virtual Debug &operator<<(float);
	virtual Debug &operator<<(double);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void SetPrefixAndRadix(const char *, int);

	Debug &operator<<(const Hex &)
	{
		SetPrefixAndRadix("0x", 16);
		return *this;
	}

	Debug &operator<<(const Dec &)
	{
		SetPrefixAndRadix("", 10);
		return *this;
	}

	Debug &operator<<(const Bin &)
	{
		SetPrefixAndRadix("%", 2);
		return *this;
	}

	Debug &operator<<(const Width &width)
	{
		m_width = width.m_width;
		return *this;
	}

	Debug &operator<<(const FillChar &fill)
	{
		m_fillChar = fill.m_fill;
		return *this;
	}

private:
	unsigned char m_pad[0x9f4c];
	int m_width;                         // +0x9F50
	char m_fillChar;                     // +0x9F54
};

class DebugExceptionhandler
{
	static void LogFPURegisters(Debug &, struct _EXCEPTION_POINTERS *);
};

// ?LogFPURegisters@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::LogFPURegisters(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
{
	struct _CONTEXT &ctx = *exptr->ContextRecord;

	if (!(ctx.ContextFlags & 0x10008)) // CONTEXT_FLOATING_POINT
	{
		dbg << "FP registers not available\n";
		return;
	}

	FLOATING_SAVE_AREA &flt = ctx.FloatSave;
	dbg << Debug::Bin() << Debug::FillChar('0')
		<< "CW:" << Debug::Width(16) << (flt.ControlWord & 0xffff) << "\n"
		<< "SW:" << Debug::Width(16) << (flt.StatusWord & 0xffff) << "\n"
		<< "TW:" << Debug::Width(16) << (flt.TagWord & 0xffff) << "\n"
		<< Debug::Hex()
		<< "ErrOfs:      " << Debug::Width(8) << flt.ErrorOffset
		<< " ErrSel:  " << Debug::Width(8) << flt.ErrorSelector << "\n"
		<< "DataOfs:     " << Debug::Width(8) << flt.DataOffset
		<< " DataSel: " << Debug::Width(8) << flt.DataSelector << "\n"
		<< "Cr0NpxState: " << Debug::Width(8) << flt.Cr0NpxState << "\n";

	for (unsigned k = 0; k < 80 / 10; ++k)
	{
		dbg << Debug::Dec() << "ST(" << k << ") ";
		dbg.SetPrefixAndRadix("", 16);

		unsigned char *value = flt.RegisterArea + k * 10;
		for (unsigned i = 0; i < 10; i++)
			dbg << Debug::Width(2) << value[i];

		double fpVal;

		// convert from temporary real (10 byte) to double
		__asm
		{
			mov eax, value
			fld tbyte ptr [eax]
			fstp qword ptr [fpVal]
		}

		dbg << " " << fpVal << "\n";
	}
	dbg << Debug::FillChar() << Debug::Dec();
}
