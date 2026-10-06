// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00326F9B, 33 bytes.
// Frameless vector-range wrapper over GadgetListBoxSetSelected (0x003247BE):
// begin==end returns, else count=(end-begin) and forwards (win,begin,count).
// Evidence: callees all rowed, callers at 0x005AFBDC/0x005D53B9/0x005D6BE5/0x005D6F62,
// prev 0x00326CF0 same page flags.

class GameWindow;

void GadgetListBoxSetSelected(GameWindow *listbox, const int *values, int count);

void Rva00326F9BSet(GameWindow *win, const int **range)
{
	const int *begin = range[0];
	const int *end = range[1];
	if (begin == end)
		return;
	GadgetListBoxSetSelected(win, begin, end - begin);
}
