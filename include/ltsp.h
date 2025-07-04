#ifndef LTSP_H
#define LTSP_H
//extern	int main(unsigned int data_seg,unsigned int stack_start);
extern	int do_lts(struct LETTER_struct *lp2,struct LETTER_struct *lp1);
extern	int is_name(struct LETTER_struct *lp2,struct LETTER_struct *lp1);
extern	int __far lstask(void);
extern	int isdot(void);

//extern	struct LETTER_struct *parsenumber(struct LETTER_struct *llp,struct LETTER_struct *rlp,struct NUM_struct *np);
//extern	int isordinal(struct NUM_struct *np);
extern	char *wlookup(struct LETTER_struct *word,char *table);
extern	int isyear(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	void lookahead(void);
extern	void copyword(struct LETTER_struct *tlp,struct LETTER_struct *flp);
extern	int dosign(int sign);
extern	int dopartnumber(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int isapart(int c);
extern	int do2digits(struct LETTER_struct *lp);
extern	int do3digits(struct LETTER_struct *lp);
extern	int do4digits(struct LETTER_struct *lp);
extern	void dogroup(char *buf,int oflag);
extern	int donumber(struct LETTER_struct *llp,struct LETTER_struct *rlp,int oflag);
extern	int nz(char *p,int n);
extern	int istime(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int isampm(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int dotime(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int isdate(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int dodate(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int isfrac(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int dofrac(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int alpha(struct LETTER_struct *lp);
extern	int digit(struct LETTER_struct *lp);
extern	int acna_lts(struct LETTER_struct *llp,struct LETTER_struct *rlp, int def_lang, int sel_lang);
extern	int sylables(struct PHONE_T *fpp,struct PHONE_T *lpp);
extern	int iscons(struct PHONE_T *pp);
extern	int isvoc(struct PHONE_T *pp);
extern	int cluster(int f,int s);
extern	void stress(struct PHONE_T *fpp,struct PHONE_T *lpp,int pstype,int sel_lang);
extern	int unstressed(int n);
extern	int suffixscan(struct PHONE_T *fpp,struct PHONE_T *lpp);
extern	int prefixscan(struct PHONE_T *fpp,struct PHONE_T *lpp,short lang_tag);
extern	int bestdefault(void);
extern	void best2syl(void);
extern	int finalfixes(void);
extern	void allo1(struct PHONE_T *fpp,struct PHONE_T *lpp);
extern	void allo2(void);
extern	int delgemphone(struct PHONE_T *pp,int ph);
extern	int isobs(struct PHONE_T *pp);
extern	int insphone(struct PHONE_T *fpp,int sph,int uph,int stress);
extern	int delphone(struct PHONE_T *dpp);
extern	int lookup(struct LETTER_struct *llp,struct LETTER_struct *rlp,int context);
extern	int pluralize(void);
extern	int suffix_find(unsigned char __far *str_end,short which_dic);
extern	int append_pron(unsigned char *pb);
extern	int print_fc(void);
extern	int say_it(struct LETTER_struct *llp,struct LETTER_struct *rlp);
extern	int do_math(unsigned char check_char);
extern	void flush_ascky(unsigned char *str);
extern	void dectalk_main(void );
//extern	void iso_case_map(void );
extern	int blook(struct LETTER_struct *llp,struct LETTER_struct *rlp,int type);
extern	int find_word(void);
extern	int dlook(int index);
extern	int where_to_look(struct dic_entry __far *ent);
extern	int cswhere_to_look(struct dic_entry __far *ent);
extern	int ufind_word(void);
extern	int udlook(int uindex);
extern	int where_to_ulook(char __far *ent);
extern	struct dic_entry __far *homo(int index);
extern void sendphone(short ph);
extern void sendlist(char *pp);
#endif
