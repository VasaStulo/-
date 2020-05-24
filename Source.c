#define _CRT_SECURE_NO_WARNINGS
//metoo
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
struct tree
{
    int inf;
    struct tree* L;
    struct tree* R;
    struct tree* parent;
};

void createTree(struct tree* N)
{
    struct tree* T;
    int a;
    printf("������ ������ ���� ��� %d 1/0? ", N->inf);
    scanf("%d", &a);
    if (a)
    {
        T = (struct tree*)malloc(sizeof(struct tree));
        T->L = NULL;
        T->R = NULL;
        T->parent = NULL;
        printf("������� ��������: ");
        scanf("%d", &T->inf);
        //        if((T->inf)>(N->inf))
        //        {
        //            printf("�� ������� �� ������ ������:(\n");
        //            return;
        //        }
        N->L = T;
        T->parent = N;                                      //������ ��������
        createTree(T);
    }

    printf("������ ������� ���� ��� %d 1/0? ", N->inf);
    scanf("%d", &a);
    if (a)
    {
        T = (struct tree*)malloc(sizeof(struct tree));
        T->L = NULL;
        T->R = NULL;
        T->parent = NULL;
        printf("������� ��������: ");
        scanf("%d", &T->inf);
        //        if((T->inf)<(N->inf))
        //        {
        //            printf("�� ������� �� ������ ������");
        //            return;
        //        }
        N->R = T;
        T->parent = N;                                      //������ ��������
        createTree(T);

    }
    return;
}


struct tree* minimum(struct tree* x)
{
    if ((x->L) == NULL)
        return x;
    return minimum(x->L);
}


struct tree* next(struct tree* x)                   //����� ���������� �������� ����� x
{
    struct tree* y;

    if ((x->R) != NULL)
        return minimum(x->R);


    y = x->parent;
    while ((y != NULL) && (x == y->R))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void delete(struct tree* v)                  // v - ��������� �������
{
    struct tree* nextv = NULL;
    struct tree* p = v->parent;           // ������ ���������� ��������

    if ((v->L == NULL) && (v->R == NULL))             // ��������� ������� �� ����� ��������
    {
        if ((p->L) == v)
            p->L = NULL;
        if ((p->R) == v)
            p->R = NULL;
        return;
    }

    //    else if ((v->L == NULL) || (v->R == NULL))         // ��������� ������� ����� ������ �������
    //        if (v->L == NULL)
    //        {
    //            if (p->L == v){
    //                delete(v->R);
    ////                p->L = v->R;
    //                p->L = NULL;
    //            }
    //            else{
    //                delete(v->R);
    ////                p->R = v->R;
    //                p->R = NULL;
    //            }
    //
    //            (v->R)->parent = p;
    //            return;
    //        }
    //        else
    //        {
    //            if (p->L == v){
    //                delete(v->L);
    ////                p->L = v->L;
    //                p->L = NULL;
    //            }
    //            else{
    //                delete(v->L);
    ////                p->R = v->L;
    //                p->R = NULL;
    //            }
    //
    //            (v->L)->parent = p;
    //            return;
    //        }

    else if ((v->L == NULL) || (v->R == NULL))         // ��������� ������� ����� ������ �������
        if (v->L == NULL)
        {
            if (p->L == v)
                p->L = v->R;
            else
                p->R = v->R;
            (v->R)->parent = p;
            return;
        }
        else
        {
            if (p->L == v)
                p->L = v->L;
            else
                p->R = v->L;
            (v->L)->parent = p;
            return;
        }

    else                                             // ��������� ������� ����� ���� ��������
    {
        nextv = next(v);                            //������ ��������� �� ���������
        v->inf = nextv->inf;

        if (((nextv->parent)->L) == nextv)
        {
            (nextv->parent)->L = nextv->R;
            if ((nextv->R) != NULL)
                (nextv->R)->parent = nextv->parent;
        }
        else
        {
            (nextv->parent)->R = nextv->L;
            if ((nextv->L) != NULL)
                (nextv->R)->parent = nextv->parent;
        }
    }
    return;
}

void searchel(struct tree* root)
{
    //    int key = 0;

    struct tree* el = root;

    if (el->L) {
        if ((el->L)->inf < root->inf) {
            delete(el->L);
            return;
        }
        else searchel(el->L);
    }

    if (el->R) {
        if ((el->R)->inf < root->inf)
            delete(el->R);
        else searchel(el->R);
    }



    //    if(el->inf < root->inf)
    //    {
    //        delete(el);                       //����� ������� ��������
    //        searchel(el->R)
    //    }
    //    if(key < (root->inf))
    //    {
    //        if(root->L)
    //            searchel(root->L, key);
    //    }
    //    else
    //    {
    //        if(root->R)
    //            searchel(root->R, key);
    //    }
}

void printTree(struct tree* N)          //������ ����� � ����� ������
{
    printf("%d ", N->inf);
    if (N->L)
        printTree(N->L);
    if (N->R)
        printTree(N->R);
}


//int count(struct tree *N)
//{
//    if(N->L)
//        printTree(N->L);
//        else
//            count++;
//    if(N->R)
//        printTree(N->R);
//    else
//        count++;
//    if((N->L)==NULL&&(N->R)==NULL)
//        return count;
//}


void cleanTree(struct tree* N)                  //������� ������
{
    if (N->L)
        printTree(N->L);
    if (N->R)
        printTree(N->R);
    free(N);
}

int main()
{
    struct tree* Root;
    int a;
    setlocale(LC_ALL, "Russian");
    printf("������� ������ -> ");
    scanf("%d", &a);
    if (!(Root = (struct tree*)malloc(sizeof(struct tree))))
    {
        printf("�� ������� �������� ������");
        return 0;
    }
    Root->inf = a;
    Root->L = NULL;
    Root->R = NULL;
    createTree(Root);
    //    printf("������� ���� ��� ��������: ");

    //    if(!(scanf("%d",&k)))
    //    {
    //        printf("�� ����� �� �����");
    //        return 0;
    //    }
    searchel(Root);

    printf("������� ������ ->");
    printTree(Root);

    //    count(Root);
    //    printf("count =", count);

}
