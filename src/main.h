struct list_vt {
	void *(*create)(void);
	void  (*unmake)(void **list);
	void  (*insert)(void **list, int val);
	void *(*search)(void  *list, int val);
	void  (*remove)(void **list, int val);
	void  (*pprint)(void  *list);
};
