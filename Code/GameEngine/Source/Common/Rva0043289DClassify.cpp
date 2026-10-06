// cl: /MD
// ?Rva0043289DClassify@@YAHH@Z, retail 0x0043289D, 59 bytes.
// Maps message type to category: 4/5/6/8->0, 10/11/12/13->1, 14/15/16/18->2,
// else 3. Callers 0x00432B44 (778B dispatch). Prev/next share /O1 flags.
int Rva0043289DClassify(int type)
{
	switch (type) {
	case 4:
	case 5:
	case 6:
	case 8:
		return 0;
	case 10:
	case 11:
	case 12:
	case 13:
		return 1;
	case 14:
	case 15:
	case 16:
	case 18:
		return 2;
	default:
		return 3;
	}
}
