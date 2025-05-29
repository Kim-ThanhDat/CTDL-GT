#include <stdio.h>
#include <stdlib.h>

#define ORDER  5
#define Ndiv2 2     /* =ORDER/2 */
#define TRUE   1    
#define FALSE  -1
typedef struct tagNODE {
    int NumTree;        /* so cay con cua nut hien hanh */
    int Key[ORDER-1];    /* mang luu tru cac khoa cua nut */
    tagNODE* Branch[ORDER];     /* mang luu tru cac con tro chi den cac nut con */
} *NODEPTR; /* con tro nut va cac kieu con tro nut */
NODEPTR Root; /* con tro nut goc */

void Init(), Input (NODEPTR &Root), OutputTree(NODEPTR p,int level), DelKey(int k);
int SearchNode(NODEPTR p, int x) ;

int main() {
    Init();
    int x,a,b,c;
	Input(Root);
	OutputTree(Root, 0);

	printf("\nNhap khoa can tim: "); scanf("%d", &x);
	if(SearchNode(Root, x))
		printf("\nDa tim thay %d", x);
	else
    	printf("\nKhong tim thay %d", x);
    	
	printf("\nNhap khoa can xoa: "); scanf("%d", &c);
	DelKey(c);
	OutputTree(Root, 0);
    
    return 0;
}


void Init() {
    Root = NULL ;
}
 
//Tìm kiếm trên B-Tree
int NodeSearch (NODEPTR p, int k) {
    int i = 0;
    for (i=0; i< p->NumTree-1 && p->Key[i] < k; i++);
    return i;
}
NODEPTR Search(int k, int &Position, int &Found){
    int   i = 0;
    NODEPTR   p = Root, q = NULL;    
    while (p !=NULL) {
        i = NodeSearch (p, k);
        if (i< p->NumTree-1 && k == p->Key[i]) {
            Found = TRUE;
            Position = i; /* Vi tri tim thay khoa k */
            return p;           /* Nut co chua khoa k */
        }
        q = p;
        p = p ->Branch[i];
    }
    /* Khong tim thay, luc nay p = NULL, và q la nut la co the them khoa k vao nut nay, Position là vi tri co the chen khoa k */
    Found = FALSE;
    Position = i;
    return q; /* Tra ve nut la */
}
//Duyệt cây B-Tree
int SearchNode(NODEPTR p, int x) {
    if (p== NULL)
        return 0;
    else {
        /* Vong lap duyet nhanh con Branch[i] va khoa Key[i] cua nut p */ 
        for (int i = 0; i < p-> NumTree-1; i++){
            SearchNode(p->Branch[i], x);
            if(p->Key[i]==x)
            return 1;
        }
        /* Duyet nhanh con cuoi cung cua nut p */ 
        SearchNode (p-> Branch[p-> NumTree-1], x);
    }
}

void OutputTree(NODEPTR p,int level) {
    if (p== NULL){
        return;
    }
    else {
        /* In so ky tu tab theo muc cua nut */
        for (int i = 0; i < level; i++)
            printf ("\t");
        /* In cac khoa cua nut */
        for (int i = 0; i < p->NumTree-1; i++)  {
            printf (".%d", p-> Key[i]);
        }
        printf (".\n");
        /* In cac cay con */
        for (int i = 0; i < p->NumTree; i++)  {
            OutputTree(p->Branch[i],level+1);
        }
    }
}
//Thêm khóa vào B-Tree

//Chèn khóa newkey vào vị trí pos của nút chưa đầy p,và chèn nhánh cây con newnode vào vị trí bên phải của khóa newkey
void InsNode(NODEPTR p, int newkey, NODEPTR newnode, int pos) {
    /* Doi cac nhanh con va cac khóa tu vi tri pos tro ve sau tang mot vi tri */
    for (int i = p->NumTree - 1; i >= pos+1; i--) {
        p -> Branch[i+1] = p -> Branch[i];
        p -> Key[i] = p -> Key[i - 1];
    }
    /* Gan khoa newkey vao vi tri pos */
    p -> Key[pos] = newkey;
    /* Gan nhanh newnode la nhanh cay con ben phai cua khoa newkey */
    p -> Branch[pos + 1] = newnode;
    /* Tang so nhanh cay con cua node p len 1 */
    p -> NumTree ++;
}
//Chép các khóa (và nhánh cây con) từ vị trí first đến vị trí last của nút nd (nút nửa trái) sang nút nd2 (nửa nút phải). Hàm này được gọi bởi hàm Split
void Copy(NODEPTR nd, int first, int last, NODEPTR nd2) {
    /* Sao chep cac khoa tu nut nd qua nut nd2 */
    for (int i = first; i <= last; i++)
        nd2 -> Key[i-first] = nd -> Key[i];
    /* Sao chep cac nhanh tu nut nd qua nut nd2 */
    for (int i = first; i <= last+1; i++)
        nd2 -> Branch[i-first] = nd -> Branch[i];
    /* So cay con cua nut nd2 */
    nd2->NumTree = last - first +2;
}
//Tạo nút rỗng
NODEPTR GetNode(){
    NODEPTR p;
    p=new tagNODE;
    p->NumTree=0;
    return p;
}
//Tách node đầy nd, phép toán này được gọi bởi phép toán InsertLeaf
void Split(NODEPTR nd, int newkey, NODEPTR newnode, int pos, NODEPTR &nd2, int &midkey) {
    NODEPTR p;
    p = GetNode(); /* Tao nut moi chua nut nua phai */
    /* Truong hop chen newkey va newnode vào node nua phai */
    if (pos > Ndiv2) {
        Copy(nd, Ndiv2+1, ORDER - 2, p);
        InsNode (p, newkey, newnode, pos-Ndiv2 -1);
        nd->NumTree = Ndiv2+1; /* So nhanh cay con con lai cua nut nua trai */
        midkey = nd -> Key[Ndiv2];
        nd2 = p;
        return;
    }
    /* Truong hop newkey la midkey */
    else
        if (pos == Ndiv2) {
            Copy(nd, Ndiv2, ORDER-2, p);
            nd->NumTree = Ndiv2+1; /* So nhanh cay con con lai cua nut nua trai */
            /* Hieu chnh lai nut con dau tien cua nut nua phai */
            p -> Branch[0] = newnode;
            midkey = newkey;
            nd2 = p;
            return ;
        }
        /* Truong hop chen newkey va newnode vao nut nua trai */
        else
            if (pos < Ndiv2) {
                Copy(nd, Ndiv2, ORDER-2, p);
                nd->NumTree = Ndiv2; /* So nhanh cay con con lai cua nut nua trai */
                midkey = nd -> Key[Ndiv2 - 1];
                InsNode(nd, newkey, newnode, pos);
                nd2 = p;
                return;
            }
}
//Tìm nút cha của nút nd, nếu nd là nút gốc trả về giá trị NULL
NODEPTR Father(NODEPTR nd){
    NODEPTR p=Root;
    int i;
    if (p == nd)
        return NULL;
    else {
        i= NodeSearch(p, nd->Key[0]);
        /* Vong lap di xuong nhanh con co chua nut nd */
        while((p->Branch[i]!=nd)){
            p=p->Branch[i];
            i= NodeSearch(p, nd->Key[0]);
        }
        return p;
    }
}
//Tạo nút mới với khóa k
NODEPTR MakeRoot(int k) {
    NODEPTR p;
    p=new tagNODE;
    p->Key[0]=k;
    p->Branch[0]=NULL;
    p->Branch[1]=NULL;
    p->NumTree=2;
    return p;
}
//Thêm khóa k vào vị trí position của nút lá s (s và position do phép toán Search( ) trả về) 
void InsertLeaf(NODEPTR s, int k, int position) {
    NODEPTR nd = s, nd2, f = Father(nd), newnode = NULL;
    int pos = position, newkey = k, midkey;
    /* Vong lap tach cac node day */
    while (f != NULL && nd->NumTree == ORDER) {
        Split(nd, newkey, newnode, pos, nd2, midkey);
        /* Gan lai cac gia tri sau khi tach node */ 
        nd = f;
        newkey = midkey;
        newnode = nd2;
        pos = NodeSearch (f, midkey);
        f = Father (nd);
    }
    /* Truong hop node nd chua day va khong phai la node goc */
    if (nd -> NumTree < ORDER) {
        /* Chen newkey và newnode tai vi tri pos cua node nd */
        InsNode (nd, newkey, newnode, pos);
        return;
    }
    /* Truong hop nd là node goc bi day, tach node goc va tao node goc moi */
    Split (nd, newkey, newnode, pos, nd2, midkey);
    /* Tao node goc moi và gan cac node nd và nd2 vào goc */
    Root = MakeRoot (midkey);
    Root -> Branch[0] = nd;
    Root -> Branch[1] = nd2;
}
//Thêm một khóa k vào B-Tree:
void InsertKey(int k) {
    int pos,found;
    NODEPTR s;
    if (Root == NULL)
        Root = MakeRoot(k);
    else {
        s = Search(k, pos, found);
        if (found == TRUE)
            printf ("Bi trung khoa, khong them khoa %d vao B-Tree duoc", k);
        else
            InsertLeaf(s, k, pos);
    }
}
void Input (NODEPTR &Root) {
	int n,x;
	printf("\nNhap n pt: "); scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &x);
		InsertKey(x);
	}
}

//Xóa khóa ra khỏi B-Tree


//Loại bỏ 1 khóa và 1 nhánh con ở vị trí pos.
void DelNode(NODEPTR p, int pos) {
/* Doi cac nhanh con va cac khoa tu vi tri pos+1 tro ve sau giam mot vi tri */
    for (int i = pos ; i < p->NumTree - 2; i++) {
        p -> Branch[i] = p -> Branch[i+1];
        p -> Key[i] = p -> Key[i+1];
    }
    p -> Branch[p->NumTree-2] = p -> Branch[p->NumTree-1];
    p -> NumTree--;
}
//Hợp nhất khóa ở vị trí pos và nút con pos+1 (right)  vào nút con pos (left), được gọi bởi hàm DelLeaf
void Combine(NODEPTR &p, int pos) {
    NODEPTR left=p->Branch[pos];
    NODEPTR right=p->Branch[pos+1];
    /* Them khoa o vi tri pos nut p, cac khoa va nhanh con cua nut right vao nut left */
    left->Key[left->NumTree-1]=p->Key[pos];
    left->NumTree++;
    for(int i=0;i<right->NumTree-1;i++){
        left->Key[left->NumTree-1+i]=right->Key[i];
        left->Branch[left->NumTree-1+i]=right->Branch[i];
    }
    left->NumTree=left->NumTree+right->NumTree-1;
    left->Branch[left->NumTree-1]=right->Branch[right->NumTree-1];
    /* Xoa 1 khoa nut cha p da hop nhat o vi tri pos */
    DelNode(p, pos);
    /* Gan lai nhanh con cua p o vi tri pos la left va xoa nut right */
    p->Branch[pos]=left;
    delete right;
    /* Truong hop p=Root va so cay con con it hơn 2: xoa nut goc Root va gan Root moi = Left*/
    if((p==Root)&&(p->NumTree<2)){
        delete Root;
        Root=left;
        p = Root;
    }
}
//Mượn khóa anh em kế cận và được gọi bởi hàm DelLeaf. 
void BorrowBrother(NODEPTR p,int pos){
    NODEPTR left=p->Branch[pos];
    NODEPTR right=p->Branch[pos+1];
    /* Truong hop muon ben trai (xoay phai) */
    if (left->NumTree>Ndiv2+1){
        /* Doi cac nhanh con va cac khoa tu vi tri pos tro ve sau tang mot vi tri tren nut right*/
        for (int i = p->NumTree - 1; i >= 0; i--) {
            right -> Branch[i+1] = right -> Branch[i];
            right -> Key[i] = right -> Key[i - 1];
        }
        /* chen khoa cua nut cha vao con ben phai,... cap nhat lai 3 nut */
        right->Key[0]=p->Key[pos];
        right->Branch[0]=left->Branch[left->NumTree-1];
        right->NumTree++;
        p->Key[pos]=left->Key[left->NumTree-2];
        left->NumTree--;
        return;
    }
    /* Truong hop muon ben phai (xoay trai) */
    if (right->NumTree>Ndiv2+1){
        /* chen khoa cua nut cha vao con ben trai,... cap nhat lai 3 nut */
        left->Key[left->NumTree-1]=p->Key[pos];
        left->Branch[left->NumTree]=right->Branch[0];
        left->NumTree++;
        p->Key[pos]=right->Key[0];
        /* xoa khoa vi tri 0 cua nut right */
        DelNode(right, 0);
    }
}
//Xóa một khóa ở nút lá p tại vị trí pos:
void DelLeaf(NODEPTR p, int pos) {
    NODEPTR q= Father(p);
    int i;
    /* Loai bo khoa o vi tri pos */
    DelNode(p, pos);
    /* Truong hop so cay con cua p < Ndiv2+1 va p dang xet khac nut goc*/
    while ((p->NumTree<Ndiv2+1)&&(p!=Root)) {
    /* Truong hop 1: muon khoa cua anh em ke can neu co */
        i=NodeSearch (q, p->Key[0]);
        /* Truong hop nut p la tan cung trai (xoay phai) */
        if((i==0)&&(q->Branch[i+1]->NumTree>Ndiv2+1)){
            BorrowBrother(q,i);
            return;
        }
        /* Truong hop nut p la tan cung phai (xoay trai) */
        if((i==q->NumTree-1)&&(q->Branch[i-1]->NumTree>Ndiv2+1)){
            BorrowBrother(q,i-1);
            return;
        }
        /* Truong hop nut p nam giua */
        if((i>0)&&(i<q->NumTree-1)) {
            /* Truong hop nut ben phai p thua khoa (xoay trai) */
            if(q->Branch[i+1]->NumTree>Ndiv2+1) {
                BorrowBrother(q,i);
                return;
            }
            /* Truong hop nut ben trai p thua khoa (xoay phai) */
            if(q->Branch[i-1]->NumTree>Ndiv2+1){
                BorrowBrother(q,i-1);
                return;
            }
        }
    /* Truong hop 2: hop nhat 2 nut anh em ke can va 1 khoa o nut cha, xet tiep nut cha */
        if (i==q->NumTree-1){
            Combine(q,i-1); /* Hop nhat voi nut anh em ke can ben trai */
        }
        else {
            Combine(q,i);  /* Hop nhat voi nut anh em ke can ben phai */
        }
        p=q;
        q=Father(p);
    }
}
//Xóa một khóa k khỏi B-Tree:
void DelKey(int k){
    int pos, found;
    NODEPTR p=Search(k, pos, found);
    /* Khong tim thay khoa k */
    if (found==FALSE){
        printf("\nKhong tim thay khoa %d de xoa\n",k);
        return;
    }
    /* Truong hop 1:  k thuoc nut la */
    if (p->Branch[0]==NULL){
        DelLeaf(p, pos); /* Xoa khoa o vi tri pos cua nut la p */
    }
    /* Truong hop 2: k thuoc nut khac la */
    else {
        /* Tim va thay the k bang phan tu tan cung phai cua cay con trai vi tri pos*/
        NODEPTR q=p->Branch[pos];
        while (q->Branch[q->NumTree-1]!=NULL){
            q=q->Branch[q->NumTree-1];
        }
        p->Key[pos]=q->Key[q->NumTree-2];
        DelLeaf(q,q->NumTree-2); /* Xoa khoa tan cung ben phai cua nut la q */
    }
}




