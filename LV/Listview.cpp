#include "globals.h"
#include "Listview.h"

void InitLV(HWND ListView) { //, int ImgList){
	ListView_SetExtendedListViewStyle(ListView,LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);
	
	//need to insert a column for report view
	LVCOLUMN tCol;
	memset(&tCol, 0, sizeof(tCol));
	tCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
	tCol.fmt = LVCFMT_LEFT;
	tCol.pszText = "ItemName";
	//tCol.iSubItem = lCol;
	tCol.cx = 170;
	ListView_InsertColumn(ListView,0,&tCol);//(0, _T("Item Name"), LVCFMT_LEFT, nColInterval*3);

	SendMessage(ListView, LVM_SETBKCOLOR, 0, (LPARAM)ColorByName("black"));
	SendMessage(ListView, LVM_SETTEXTBKCOLOR, 0, (LPARAM)ColorByName("black"));
	SendMessage(ListView, LVM_SETTEXTCOLOR, 0, (LPARAM)ColorByName("yellow"));
}

void InitImageList(HWND LView, int ImgList){
	//HIMAGELIST hList = ImageList_Create(28, 14, ILC_COLOR16, 8, 1);
	//HBITMAP BnetIcons = LoadBitmap(DlgInst, MAKEINTRESOURCE(IDB_BNETICONS));
	//ImageList_Add(hList, BnetIcons, NULL);
	//SendMessage(LView, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)hList);
	SendMessage(LView, LVM_SETBKCOLOR, 0, (LPARAM)ColorByName("black"));
	SendMessage(LView, LVM_SETTEXTBKCOLOR, 0, (LPARAM)ColorByName("black"));
	SendMessage(LView, LVM_SETTEXTCOLOR, 0, (LPARAM)ColorByName("blue"));
}

void GetListViewItemText(HWND LView, int item, char *buf){
	char buffer[32] = "";
	LVITEM lvi;
	lvi.pszText = buffer;
	lvi.iSubItem = 0;
	lvi.cchTextMax = sizeof(buffer);
	SendMessage(LView, LVM_GETITEMTEXT, item, (LPARAM)&lvi);
	strcpy(buf, buffer);
}

int GetListViewSelectedItem(HWND LView){
	int itemcount = SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
	for(int i = 0; i < itemcount; i++){
		DWORD state = SendMessage(LView, LVM_GETITEMSTATE, i, LVIS_SELECTED);
		if(state == LVIS_SELECTED)
			return i;
	}
	return -1;
}

void InsertItem(HWND LView, char *item) {//, int icon){
	LVITEM *lvi = new LVITEM;
	lvi->mask =  LVIF_TEXT;//LVIF_IMAGE | LVIF_TEXT;
	lvi->iItem = (int)SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
	lvi->iSubItem = 0;
	lvi->pszText = item;
	//lvi->iImage = icon;
	SendMessage(LView, LVM_INSERTITEM, 0, (LPARAM)lvi);
	SendMessage(LView, LVM_ARRANGE, LVA_ALIGNLEFT, 0);
//	int itemcount = (int)SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
//	char txt[128] = "";
	//sprintf(txt, "%s (%i)", currentchannel, itemcount);
	//SetEditBoxText(IDC_CHAN, txt);
	delete(lvi);
}

int GetItemIndex(HWND LView, char *item){
	if(item == NULL) {
		//OutputDebugStringA(this->buffer.c_str());
		OutputDebugStringA("Broken at int GetItemIndex(HWND LView, char *item)\r\n");
		return -1;
	}
	//build find item here
	int i;
	LVFINDINFO plvfi={0};
	plvfi.flags=LVFI_STRING;
	plvfi.psz=item;//lpfr->lpstrFindWhat;
	i=ListView_FindItem(LView,-1,&plvfi);
	return i;
	/*
	int ItemCount = SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
	for(int i = 0; i < ItemCount; i++){
		char buffer[256] = "";
		ListView_GetItemText(LView, i, 0, buffer, sizeof(buffer));
		if(!_stricmp(buffer, item)) {
			return i;
		}
	}
	return -1;
	*/
}

void RemoveItem(HWND LView, char *item){
	if(item == NULL) {
		//OutputDebugStringA(this->buffer.c_str());
		OutputDebugStringA("Broken at void RemoveItem(HWND LView, char *item)\r\n");
		return;
	}
	int index_value = GetItemIndex(LView, item);
	if(index_value < 0) { 
		//broken
		return;
	}
	SendMessage(LView, LVM_DELETEITEM, index_value, 0);
	SendMessage(LView, LVM_ARRANGE, LVA_ALIGNLEFT, 0);
	return;
/*
	int ItemCount = SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
	for(int i = 0; i < ItemCount; i++){
		char buffer[256] = "";
		ListView_GetItemText(LView, i, 0, buffer, sizeof(buffer));
		if(!_stricmp(buffer, item)) {
			SendMessage(LView, LVM_DELETEITEM, i, 0);
		}
	}
	SendMessage(LView, LVM_ARRANGE, LVA_ALIGNLEFT, 0);
	*/

//	int itemcount = (int)SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
//	char txt[128] = "";
	//sprintf(txt, "%s (%i)", currentchannel, itemcount);
	//SetEditBoxText(IDC_CHAN, txt);
}

void ModifyItem(HWND LView, char *item){//, int icon){
//	int itemcount = SendMessage(LView, LVM_GETITEMCOUNT, 0, 0);
	int pos = GetItemIndex(LView, item);
	LVITEM lvi;
	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	lvi.iItem = pos;
	lvi.iSubItem = 0;
	lvi.pszText = item;
	//lvi.iImage = icon;
	SendMessage(LView, LVM_DELETEITEM, pos, 0);
	SendMessage(LView, LVM_INSERTITEM, 0, (LPARAM)&lvi);
}

void ClearListView(HWND LView){
	SendMessage(LView, LVM_DELETEALLITEMS, 0, 0);
}

