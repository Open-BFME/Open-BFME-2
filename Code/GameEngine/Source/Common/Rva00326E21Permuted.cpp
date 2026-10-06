// cl: /MD /DNDEBUG
//
// ?GadgetListBoxSetListLength@@YAXPAVGameWindow@@H@Z, retail 0x00326e21, 378 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Read-only BFME1 2791daf553 clean donor trial; native manager free slot +3C.
#include <string.h>
typedef short Short;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
#define DEBUG_ASSERTCRASH(a,b)
#define DEBUG_LOG(a)
#define assert(a)
#define NULL 0
#define NEW new
extern void *__cdecl operator new[](unsigned int);
extern void __cdecl operator delete[](void *);
enum { LISTBOX_TEXT = 1 };
class GameWindow { public: void *winGetUserData(); };
class DisplayString;
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
struct ListEntryCell { int cellType; char unknown4[8]; void *data; char unknown16[12]; };
struct ListEntryRow { char unknown0[8]; ListEntryCell *cell; char unknown12[4]; };
void computeTotalHeight(GameWindow *);
void Rva00326DE9Disable(GameWindow *);
void GadgetListBoxAddMultiSelect(GameWindow *);
struct Rva004BB8E0ListboxData
{
	Short listLength;
	Short columns;
	UnsignedByte m_pad04[7];
	Bool multiSelect;
	UnsignedByte m_pad0c[0x0c];
	ListEntryRow *listData;
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	Short endPos;
	Short insertPos;
	UnsignedByte m_pad30[4];
	Int selectPos;
	Int *selections;
	Short displayHeight;
	UnsignedByte m_pad3e[2];
	UnsignedInt doubleClickTime;
	Short displayPos;
};

class Rva004BB8E0DisplayStringManager
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0c() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1c() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void pad28() = 0;
	virtual void pad2c() = 0;
	virtual void pad30() = 0;
	virtual void pad34() = 0;
	virtual void pad38() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;
};

void GadgetListBoxSetListLength( GameWindow *listbox, Int newLength )
{
	Rva004BB8E0ListboxData *listboxData =
		(Rva004BB8E0ListboxData *)listbox->winGetUserData();


//	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
//	ListEntry *newData = (ListEntry *)malloc(newLength * sizeof(ListEntry));
	DEBUG_ASSERTCRASH(listboxData, ("We don't have our needed listboxData!"));
	if( !listboxData )
		return;
	DEBUG_ASSERTCRASH(listboxData->columns > 0,("We need at least one Column in the listbox"));
	if( listboxData->columns < 1 )
		return;
	
  Int columns = listboxData->columns;
	ListEntryRow *newData = NEW ListEntryRow[ newLength ];	
	DEBUG_ASSERTCRASH(newData, ("Unable to allocate new data structures for the Listbox"));
	if( !newData )
		return;
	Int i;
  // zero out the new Data structure
	memset( newData, 0, newLength  * sizeof( ListEntryRow ) );
	 
	// we want to copy over different amounts of data depending on if we're adding
	// to the list box or removing from the listbox
	if(newLength >= listboxData->listLength)
	{
		memcpy(newData,listboxData->listData,listboxData->listLength * sizeof( ListEntryRow ) );
	}
	else
	{
		// If we're removing entries from the listbox, we need to reset the length, 
		// position, and selection to their new places
		if( listboxData->displayPos >newLength)
			listboxData->displayPos = newLength;
		//if we're multiselect, just select no position
		if(listboxData->selectPos > newLength || listboxData->multiSelect) 
			listboxData->selectPos = -1;
    if(listboxData->insertPos > newLength)
			listboxData->insertPos = newLength;

    listboxData->endPos = newLength;
		//copy only the data that we'll be needing.		
		memcpy(newData,listboxData->listData,newLength * sizeof( ListEntryRow ) );
	}

	// Loop through and destroy any display strings we've allocated that aren't used
	for( i = 0; i < listboxData->listLength; i++ )
	{
		//We're now onto a row of cells we are not using anymore Pull off the cells and loop through them
		ListEntryCell *cells = listboxData->listData[i].cell;
		for (int j = columns - 1; j >=0; j-- )
		{			
			if(!cells)
				break;
			if ( i >= newLength )
			{
				if( cells[j].cellType == LISTBOX_TEXT  && i >= newLength)
				{
					// If we can delete the stuff that won't be showing up in the new listData struture
					if ( cells[j].data )
					{
						reinterpret_cast<Rva004BB8E0DisplayStringManager *>(TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[j].data );	
					}
				}
//			if ( cells[j].userData ) 
//					free(cells[j].userData);
			}
		}
		if ( i >= newLength )
			delete [] (listboxData->listData[i].cell);
		listboxData->listData[i].cell = NULL;
	}

	listboxData->listLength = newLength;

	if( listboxData->listData )
		delete [] ( listboxData->listData );
	listboxData->listData = newData;
	
	//reset the total height
	computeTotalHeight(listbox);

  // Sanity check that everything was created properly
	if( listboxData->listData == NULL )
	{

		DEBUG_LOG(( "Unable to allocate listbox data pointer\n" ));
		assert( 0 );
		return;

	}  // end if
	
	// adjust the selection array for multi select listboxes
	if( listboxData->multiSelect )
	{
		
		Rva00326DE9Disable( listbox );
		GadgetListBoxAddMultiSelect( listbox );

	}  // end if

}  // end GadgetListBoxSetListLength

