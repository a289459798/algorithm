/*
 * 红黑树
 *
 * 每一步操作都要保证以下几点：
 * 1）每个结点要么是红的，要么是黑的。
 * 2）根结点是黑的。
 * 3）每个叶结点（叶结点即指树尾端NIL指针或NULL结点）是黑的。
 * 4）如果一个结点是红的，那么它的俩个儿子都是黑的。
 * 5）对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。
 *
 *
 * 1、若插入节点的父节点为红色，且父节点为左子树：
    a、叔叔节点是红色；
		叔叔变成黑色、父节点也变成黑色、祖父节点变成红色；
	b、叔叔节点是黑色或没有；
		①该节点是右孩子；
			将以父节点为支点左旋转、该节点与父节点互换角色，此时新节点(即之前的父节点)为左孩子，进行②操作；
		②该节点是左孩子；
			父节点变成黑色、祖父节点变成红色、以祖父节点为支点进行右旋转；
   2、若插入节点的父节点为红色，且父节点为右子树：
	a、叔叔节点是红色；
		叔叔变成黑色、父节点变成黑色、祖父节点变成红色；
	b、叔叔节点是黑色或没有；
		①该节点是左孩子；
			将以父节点为支点右旋转、该节点与父节点互换角色，此时新节点(即之前的父节点)为右孩子，进行②操作；
		②该节点是右孩子；
			父节点变成黑色、祖父节点变成红色、以祖父节点为支点进行左旋转；
   最后必须保证根节点为黑色；
*/

#include <stdio.h>
#include <malloc.h>
typedef struct RBNode{
	int data;
	struct RBNode * parent;		//记录父节点
	char color;					//节点颜色
	struct RBNode *l;
	struct RBNode *r;
} RBNode, *RBTree;

RBTree rb_insert(RBTree, int);
RBTree rb_repair(RBTree, RBTree);
RBTree rb_rotate_left(RBTree, RBTree);
RBTree rb_rotate_right(RBTree, RBTree);
void rb_print(RBTree);
int main(void)
{
	RBTree root;
	int opp, num;
	while(1){
		printf("请选择您的操作：\n1、插入		2、查找		3、遍历		4、退出\n");
		scanf("%d", &opp);
		switch(opp){
			case 1:
				printf("请输入要插入的数字：");
				scanf("%d", &num);
				root = rb_insert(root, num);
				break;
			case 2:
				break;
			case 3:
				printf("遍历结果：");
				rb_print(root);
				printf("\n");
				break;
			default:
				return 0;
				break;
		}
	}
	return 0;
}
//查找节点，并返回查找到的节点
RBTree rb_search(RBTree root, int num, RBTree *insert_node)
{
	RBTree node = root;
	while(node){
		(*insert_node) = node;
		if(node->data > num)
			node = node->l;
		else if(node->data < num)
			node = node->r;
		else
			return node;
	}
	return NULL;
}

RBTree rb_insert(RBTree root, int num)
{
	RBTree parent, p;	//插入节点的父节点
	if(root == NULL){
		root = (RBTree)malloc(sizeof(RBNode));
		if(root == NULL)
			printf("内存分配失败");
		else{	//根节点的颜色必须是黑色
			root->data = num;
			root->l = root->r = root->parent = NULL;
			root->color = 'b';
		}
	}else{
		//先查找插入的位置
		if(rb_search(root, num, &parent) == NULL){
			p = (RBTree)malloc(sizeof(RBNode));
			if(p == NULL){
				printf("内存分配失败...");
				return root;
			}
			p->data = num;
			p->parent = parent;	//查找的节点肯定是待插入节点的父节点
			p->l = p->r = NULL;
			p->color = 'r';	//每个插入节点的颜色都为红色
			if(parent->data > num)
				parent->l = p;
			else
				parent->r = p;

			root = rb_repair(root, p);	//插入后，对红黑树进行修复
		}else{
			printf("该节点已经存在");
		}


	}
	return root;
}

RBTree rb_repair(RBTree root, RBTree p)
{
	RBTree parent, gparent, uncle, tmp;	//分别定义父节点、祖父节点、叔叔节点
	//不满足上面5点就一直修复
	while((parent = p->parent) && parent->color == 'r'){	//如果父节点为红色
		gparent = parent->parent;
		if(parent == gparent->l){		//如果父节点为左孩子
			uncle = gparent->r;			//叔叔节点为右孩子
			if(uncle && uncle->color == 'r'){	//叔叔节点为红色
				uncle->color = 'b';		//叔叔节点变成黑色
				parent->color = 'b';	//父节点变成黑色
				gparent->color = 'r';	//祖父节点变成红色
			}else{
				if(parent->r == p){		//当前节点是右孩子
					root = rb_rotate_left(root, parent);	//以父节点为支点进行左旋转
					tmp = parent;
					parent = p;
					p = tmp;
				}
				parent->color = 'b';	
				gparent->color = 'r';
				root = rb_rotate_right(root, gparent);
			}
		}else{	//父亲为右孩子情况
			uncle = gparent->l;	//此时叔叔为左孩子
			if(uncle && uncle->color == 'r'){
				uncle->color = 'b';
				parent->color = 'b';
				gparent->color = 'r';
			}else{
				if(parent->l == p){	//若该节点是左孩子
					root = rb_rotate_right(root, parent);
					tmp = parent;
					parent = p;
					p = tmp;
				}
				//此时该节点变成了右孩子
				parent->color = 'b';
				gparent->color = 'r';
				root = rb_rotate_left(root, gparent);
			}
		
		}
		
	}
	root->color = 'b';	//确保根节点为黑色
	return root;
}

//左旋转
RBTree rb_rotate_left(RBTree root, RBTree node)
{
	RBTree rc;
	rc = node->r;	//定义未来的父节点
	node->r = rc->l;
	if(rc->l){
		rc->l->parent = node;	//重新设置父节点，即将祖父变成父节点
	}
	rc->l = node;	//将父节点变成左孩子
	rc->parent = node->parent;	//祖父节点变成父节点
	if(node->parent){	
		//下一步确定是左孩子还是右孩子
		if(node == node->parent->l)
			node->parent->l = rc;	//左孩子
		else
			node->parent->r = rc;
	}else{
		root = rc;
	}
	node->parent = rc;	//右孩子变成父节点
	return root;
}

//右旋转
RBTree rb_rotate_right(RBTree root, RBTree node)
{
	RBTree lc;
	lc = node->l;
	node->l = lc->r;
	if(lc->r){
		lc->r->parent = node;
	}
	lc->r = node;
	lc->parent = node->parent;
	if(node->parent){
		if(node = node->parent->l)
			node->parent->l = lc;
		else 
			node->parent->r = lc;
	}
	else
		root = lc;
	node->parent = lc;
	return root;
}

void rb_print(RBTree root)
{
	if(root){
		printf("%d:%c,", root->data, root->color);
		rb_print(root->l);
		rb_print(root->r);
	}
}
