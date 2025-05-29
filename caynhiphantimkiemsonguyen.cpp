#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TNODE

{
int key;
TNODE* pLeft;
TNODE* pRight;
} TNODE;
typedef struct TNODE* TREE;
TREE root;

void InsertTree(TREE &root , int x);
void CreateTree(TREE &root);
void NLR(TREE root);
TNODE* searchNode(TREE root, int X);
int insertNode(TREE &root, int X);
int delNode(TREE &root, int X);
void Output(TREE Root,int level);
void removeTree(TREE &root);
//Bo sung
int Nutla(TREE root); 
int Nut1con(TREE root);
int Nut2con(TREE root);
int SonutnhohonX(TREE root, int x); 
int SonutlonhonX(TREE root, int x); 
int SonutlonhonXvanhohonY(TREE root, int x, int y); 
int Chieucao(TREE root); 
void TimK(TREE root, int k); 

//25   37  10   18   29   50   3   1   6    5   12    20    35  13   32   41

int main() {
	TREE root = NULL;
	int x, y, z, k;
	CreateTree(root);
	
	printf("\nDuyet cay theo NLR:\n");
	Output(root, 0);
	
	printf("\nNhap phan tu can tim: ");
	scanf("%d", &x);
	if(searchNode(root, x)!=NULL)
		printf("\nTim thay %d", x);
	else
		printf("\nKhong tim thay %d", x);

	printf("\nNhap phan tu can xoa: ");
	scanf("%d", &y);
	printf("\nTruoc khi xoa:\n ");Output(root, 0);

	delNode(root, y);
	printf("\nSau khi xoa:\n ");Output(root, 0);

	
	printf("\nNhap phan tu can them: ");
	scanf("%d", &z);
	insertNode(root, z);
	printf("\nSau khi them:\n ");Output(root, 0);
	
	printf("\nSo nut la: %d", Nutla(root));
    printf("\nSo nut co 1 con: %d", Nut1con(root));
    printf("\nSo nut co 2 con: %d", Nut2con(root));
	
	printf("\nNhap x: ");
	scanf("%d", &x);
	printf("\nSo nut nho hon %d: %d", x, SonutnhohonX(root, x));
    printf("\nSo nut lon hon %d: %d", x, SonutlonhonX(root, x));
    
    do {
    printf("\nNhap y (y > %d): ", x);
    scanf("%d", &y);
    if (y <= x) {
        printf("Loi: y phai lon hon x. Vui long nhap lai!\n");
    	}
	} while (y <= x);
    printf("\nSo nut lon hon %d va nho hon %d: %d", x, y, SonutlonhonXvanhohonY(root, x, y));
    
    printf("\nChieu cao cua cay: %d", Chieucao(root));
	
	printf("\nNhap k: ");
	scanf("%d", &k);
	printf("\nDuong di tim kiem %d: ", k);
    TimK(root, k);
    
	printf("\nXoa cay!");
	removeTree(root);
	Output(root, 0);


	return 0;
}
int Nutla(TREE root) {
    if (root == NULL)
        return 0;
    if (root->pLeft == NULL && root->pRight == NULL)
        return 1;
    return Nutla(root->pLeft) + Nutla(root->pRight);
}

int Nut1con(TREE root) {
    if (root == NULL)
        return 0;
    if ((root->pLeft == NULL && root->pRight != NULL) || 
        (root->pLeft != NULL && root->pRight == NULL))
        return 1 + Nut1con(root->pLeft) + Nut1con(root->pRight);
    return Nut1con(root->pLeft) + Nut1con(root->pRight);
}

int Nut2con(TREE root) {
    if (root == NULL)
        return 0;
    if (root->pLeft != NULL && root->pRight != NULL)
        return 1 + Nut2con(root->pLeft) + Nut2con(root->pRight);
    return Nut2con(root->pLeft) + Nut2con(root->pRight);
}

int SonutnhohonX(TREE root, int x) {
    if (root == NULL)
        return 0;
    if (root->key < x)
        return 1 + SonutnhohonX(root->pLeft, x) + SonutnhohonX(root->pRight, x);
    return SonutnhohonX(root->pLeft, x);
}

int SonutlonhonX(TREE root, int x){
    if (root == NULL)
        return 0;
    if (root->key > x)
        return 1 + SonutlonhonX(root->pLeft, x) + SonutlonhonX(root->pRight, x);
    return SonutlonhonX(root->pRight, x);
}

int SonutlonhonXvanhohonY(TREE root, int x, int y) {
    if (root == NULL || x >= y)
        return 0;
    
    if (root->key <= x)
        return SonutlonhonXvanhohonY(root->pRight, x, y);
    else if (root->key >= y)
        return SonutlonhonXvanhohonY(root->pLeft, x, y);
    else
        return 1 + SonutlonhonXvanhohonY(root->pLeft, x, y) + SonutlonhonXvanhohonY(root->pRight, x, y);
}

int Chieucao(TREE root) {
    if (root == NULL)
        return 0;
    int leftHeight = Chieucao(root->pLeft);
    int rightHeight = Chieucao(root->pRight);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

void TimK(TREE root, int k){
    if (root == NULL) {
        printf("Khong tim thay %d trong cay\n", k);
        return;
    }
    
    printf("%d ", root->key);
    
    if (root->key == k) {
        printf("\nDa tim thay %d\n", k);
        return;
    }
    else if (root->key > k) {
        TimK(root->pLeft, k);
    }
    else {
        TimK(root->pRight, k);
    }
}

void InsertTree(TREE &root , int x){

	if(root != NULL){

		if(root->key==x) return;

		if(root-> key >x)

			InsertTree(root->pLeft,x);

		else

			InsertTree(root->pRight,x);

	}else{

		root= new TNODE;

		root->key=x;

		root->pLeft=root->pRight=NULL;

	}

}

void CreateTree(TREE &root){
	
	int x,n;

	printf("Nhap n = "); scanf("%d",&n);

	for(int i=1; i<=n;i++){
		
		scanf("%d",&x);
		
		InsertTree(root,x);

	}
	
}

void NLR(TREE root){
	
	if (root != NULL){
		
		printf("%d",root->key);
		
		NLR(root->pLeft);
		
		NLR(root->pRight);
		
	}
}

TNODE* searchNode(TREE root, int X){

	TNODE *p = root;
	while (p != NULL)
	{
		if(X == p->key)   return p;
		else    
			if(X < p->key) p = p->pLeft;
			else	p = p->pRight;
	}


	return NULL;

	}

int insertNode(TREE &root, int X){
		if (root!=NULL) {

		if(root->key == X) return 0; // đã có

		if(root->key > X)

		return insertNode(root->pLeft, X);

		else

		return insertNode(root->pRight, X);

		}

			root = (TNODE*)malloc(sizeof(TNODE));

			if (root == NULL) return -1; // thiếu bộ nhớ

			root->key = X;

			root->pLeft = root->pRight = NULL;

			return 1; // thêm vào thành công

	}

void searchStandFor(TREE &p, TREE &q){

	if(q->pRight!=NULL)

	searchStandFor(p, q->pRight);

	else

	{

		p->key = q->key;

		p = q;

		if(q->pLeft!=NULL)

		q = q->pLeft;

		else

		q = q->pRight;

	}

}

int delNode(TREE &root, int X){
 	if(root== NULL)
	return 0;

	if(root->key > X)
	delNode(root->pLeft, X);

	if(root->key < X)
	delNode(root->pRight, X);

	//T->Key == X

	if(root->key==X)

	{

		TNODE* p = root;

		if(root->pLeft == NULL)

		root = root->pRight;
	
		else

		if(root->pRight == NULL)

		root = root->pLeft;

		else // T có đủ 2 con

		searchStandFor(p, root->pLeft);

		delete p;

	}

}

void removeTree(TREE &root){

	if(root!=NULL)
	{

	removeTree(root->pLeft);

	removeTree(root->pRight);

	delNode(root,root->key);

	}

}
//Xuat cay dang folder
void Output(TREE Root,int level) {
	for(int i=1;i<=level;i++)
		printf("\t");
	if (Root != NULL) {
		printf("%d\n", Root->key);
		Output(Root->pLeft,level+1);
		Output(Root->pRight,level+1);
	}
	else
		printf("NULL\n");
}

