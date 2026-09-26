// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// STLport five-argument __copy_ptrs worker over ModuleInfo::Nugget, retail
// 0x002CF0BE (50 bytes). The rowed four-argument forwarder at 0x002CF2B8
// (ModuleInfoNuggetErase.cpp) reaches this body with a by-reference
// __false_type tag plus zero; the false path inlines to the random-access
// __copy loop (count via idiv 0x14, per-element copy through the pinned
// Nugget operator= at 0x002CEFCD). Nugget layout is the erase TU's model
// verbatim (two AsciiStrings, a ModuleData pointer, an Int, three Bools).

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class ModuleData
{
};

class ModuleInfo
{
public:
	struct Nugget
	{
		~Nugget();
		Nugget &operator=(const Nugget &other);

		AsciiString m_first;
		AsciiString m_moduleTag;
		const ModuleData *m_data;
		int m_interfaceMask;
		unsigned char m_copiedFromDefault;
		unsigned char m_inheritable;
		unsigned char m_overrideableByLikeKind;
		unsigned char m_pad;
	};
};

namespace _STL
{

struct __false_type
{
};

template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter __first, _InputIter __last,
	_OutputIter __result, const __false_type *__tag, int __extra)
{
	(void)__tag;
	(void)__extra;
	for (int __n = __last - __first; __n > 0; --__n) {
		*__result = *__first;
		++__first;
		++__result;
	}
	return __result;
}

}

template ModuleInfo::Nugget *_STL::__copy_ptrs<ModuleInfo::Nugget *,
	ModuleInfo::Nugget *>(ModuleInfo::Nugget *, ModuleInfo::Nugget *,
	ModuleInfo::Nugget *, const _STL::__false_type *, int);
