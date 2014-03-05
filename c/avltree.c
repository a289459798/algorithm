/*
 * avl树即平衡二叉树或高度平衡树，因为其左右两边的高度差在正负1之间，若高度差大于1则需要做相应的旋转，来平衡二叉树
 */
#include <stdio.h>
#include <malloc.h>
typedef struct AVLNode{
	int data;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
} AVLNode, *AVLTree;
AVLTree insert(AVLTree, int);
void rprint(AVLTree);
int main(void)
{
	AVLTree T;
	int opp, num;
	while(1)
	{
		printf("请选择您要执行的操作：\n1、插入		2、中序遍历		3、退出\n");
		scanf("%d", &opp);
		switch(opp)
		{
			case 1:
				printf("请输入要插入的数字：");
				scanf("%d", &num);
				T = insert(T, num);
				break;
			case 2:
				printf("遍历结果：");
				rprint(T);
				printf("\n");
				break;
			default:
				return 0;
				break;
		}
	}
	return 0;
}
//返回节点高度
int height(AVLTree T)
{
	if(T == NULL)
		return -1;
	return T->height;
}
//返回数字较大者
int max(int a, int b)
{
	return a > b ? a : b;
}
//右旋转
AVLTree rrotate(AVLTree T)
{
	AVLTree lc;
	lc = T->l;
	T->l = lc->r;
	lc->r = T;
	T->height = max(height(T->l), height(T->r)) + 1;		//重新计算高度
	lc->height = max(height(lc->l), height(lc->r)) +1;		//重新计算跟节点高度
	return lc;
}
//左旋转
AVLTree lrotate(AVLTree T)
{
	AVLTree rc;
	rc = T->r;
	T->r = rc->l;
	rc->l = T;
	T->height = max(height(T->l), height(T->r)) + 1;
	rc->height = max(height(rc->l), height(rc->r)) + 1;
	return rc;
}

AVLTree insert(AVLTree T, int num)
{
	if(T == NULL)
	{
		T = (AVLTree)malloc(sizeof(AVLNode));
		if(T == NULL)
			printf("内存分配失败...\n");
		else{
			T->data = num;
			T->height = 0;
			T->l = T->r = NULL;
		}
	}
	else
	{
		if(num < T->data){
			T->l = insert(T->l, num);
			if(height(T->l) - height(T->r) == 2){
				if(num < T->l->data){			//左左情况，右旋转
					T = rrotate(T);
				}else{							//左右情况，先左转后右转
					T = lrotate(T);
					T = rrotate(T);
				}
			}
		}else if(num > T->data){
			T->r = insert(T->r, num);
			if(height(T->r) - height(T->l) == 2){
				if(num > T->r->data){		//右右情况，左旋转
					T = lrotate(T);
				}else{						//右左情况，先右转后左转
					T = rrotate(T);
					T = lrotate(T);
				}
			
			}
		}
	}
	T->height = max(height(T->l), height(T->r))+1;
	return T;
}

void rprint(AVLTree T)
{
	if(T != NULL){
		printf("节点：%d, 高度：%d  ", T->data, T->height);
		rprint(T->l);
		rprint(T->r);
	}
}
