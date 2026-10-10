// The donor PDB names this AptValueSet<AptValue *>::has. Target instructions
// establish a 16-bit count at +2 and an array pointer at +4; target callers
// pass AptValue pointers after checking AptValue::isCIH. Field names and the
// read-only qualifier are source-level descriptions, not binary symbols.
class AptValue;

template <class T>
class AptValueSet
{
public:
	bool has(T value) const
	{
		const int count = m_count;
		int index = 0;
		if (count > 0)
		{
			T *item = m_items;
			do
			{
				if (*item == value)
					return true;
				++index;
				++item;
			} while (index < count);
		}
		return false;
	}

private:
	unsigned short m_reserved;
	unsigned short m_count;
	T *m_items;
};

template class AptValueSet<AptValue *>;

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
// Native add6E9A40..6E9AE3 confirms the two unsigned16-bit counters and
// pointer array prefix. The matching assertions name _AptSet.h; WB1787120
// identifies AptValueSet<AptCIH*>::add and supplies the original for-loop.
// Keep the existing address-derived receiver/callee spelling used by retail
// consumers; this prefix does not claim a complete AptCIH layout or slot name.
class AptCIH {public:virtual void slot0();};
class Rva006E9A40List {
public:
 unsigned short mnElements,mnMaxElements;AptCIH **maElements;
 void add(AptCIH *element);
};
void Rva006E9A40List::add(AptCIH *element){
 if(!(mnElements<mnMaxElements)){
  g_bfmeAptAssertAtE17734("mnElements < mnMaxElements","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptSet.h",0x27);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 for(int i=0;i<mnMaxElements;++i){
  if(maElements[i]==element){
   g_bfmeAptAssertAtE17734("maElements[i] != element","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptSet.h",0x2D);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
 }
++mnElements;int index;for(index=mnElements;maElements[index];++index){if(index>=mnMaxElements)index=0;}maElements[index]=element;element->slot0();
}
