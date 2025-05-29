#include <stdio.h>

void nhap(int a[], int n) {
    for(int i = 1; i <= n; i++) {
        printf("Nhap phan tu thu %d: ", i);
        scanf("%d", &a[i]);
    }
}

void xuat(int a[], int n) {
    printf("Cac phan tu vua nhap: ");
    for(int i = 1; i <= n; i++) {
        printf("%d  ", a[i]);
    }
    printf("\n");
}

void InterchangeSort(int a[], int N) {
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (a[j] < a[i]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void BubleSort(int a[], int N) {
    for (int i = 1; i < N; i++) {
        for (int j = N; j > i; j--) {
            if (a[j] < a[j - 1]) {
                int t = a[j];
                a[j] = a[j - 1];
                a[j - 1] = t;    
            }
        }
    }
}

void InsertionSort(int a[], int N) {
    for (int i = 2; i <= N; i++) {
        int x = a[i];
        int pos = i - 1;
        while (pos >= 1 && a[pos] > x) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = x;
    }
}

void SelectionSort(int a[], int N) {
    for (int i = 1; i < N; i++) {
        int min = i;
        for (int j = i + 1; j <= N; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        int t = a[min];
        a[min] = a[i];
        a[i] = t;
    }
}
void QuickSort(int a[], int l, int r)
{
	int i, j;
	int x;
	x = a[(l+r)/2];
	i =l; j = r;
	do {
		while(a[i] < x) i++;
		while(a[j] > x) j--;
		if(i <= j)
		{
			//Hoanvi(a[i],a[j]);
			int t=a[i];
			a[i]=a[j];
			a[j]=t;
			i++; j--;
		}
	}while(i < j);
	if(l < j)
		QuickSort(a,l,j);
	if(i < r)
		QuickSort(a,i,r);
}
void Shift(int a[], int l, int r) {
    int x, i, j;
    i = l;
    j = 2 * i; 
    x = a[i]; 

    while (j <= r) {
        if (j < r && a[j] < a[j + 1]) {
            j++; 
        }
        if (a[j] <= x) {
            break; 
        } else {
            a[i] = a[j]; 
            i = j;
            j = 2 * i; 
        }
    }
    a[i] = x;
}
void CreateHeap(int a[], int N) {
    int l;
    l = N / 2; 
    while (l > 0) {
        Shift(a, l, N); 
        l = l - 1; 
    }
}
void HeapSort(int a[], int N) {
    int r;
    CreateHeap(a, N); 
    r = N; 
    while (r > 1) { 
        //Hoanvi(a[1], a[r]); 
        int t=a[1];
        a[1]=a[r];
        a[r]=t;
        r = r - 1; 
        Shift(a, 1, r); 
    }
}

int main() {
    int n;
    printf("Nhap n: ");
    scanf("%d", &n);
    int a[n + 1];  
    nhap(a, n);
    xuat(a, n);
    
    
    InterchangeSort(a, n);
    printf("Sap xep kieu InterchangeSort: \n");
    xuat(a, n);
    BubleSort(a, n);
    printf("Sap xep kieu BubleSort: \n");
    xuat(a, n);
    InsertionSort(a, n);
    printf("Sap xep kieu InsertionSort: \n");
    xuat(a, n);
    SelectionSort(a, n);
	printf("Sap xep kieu SelectionSort: \n");
    xuat(a, n);
    QuickSort(a, 1, n);
    printf("Sap xep kieu QuickSort: \n");
    xuat(a, n);
    HeapSort(a, n);
    printf("Sap xep kieu HeapSort: \n");
    xuat(a, n);
    return 0;
}

