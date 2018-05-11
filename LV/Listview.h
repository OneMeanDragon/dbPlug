
void InitLV(HWND ListView);
void InitImageList(HWND LView, int ImgList);
void GetListViewItemText(HWND LView, int item, char *buf);
int GetListViewSelectedItem(HWND LView);
void InsertItem(HWND LView, char *item);//, int icon);
int GetItemIndex(HWND LView, char *item);
void RemoveItem(HWND LView, char *item);
void ModifyItem(HWND LView, char *item);//, int icon);
void ClearListView(HWND LView);
