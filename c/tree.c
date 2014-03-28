#include <stdio.h>
#include <malloc.h>
#define ERROR -1
#define OK 1
typedef int ElementType;
typedef struct Node Node, *Tree;
struct Node
{
    ElementType data;
    Tree left;
    Tree right;
};



/** 树存在，搜索树\brief
 *
 * Tree head\param
 * ElementType data\param
 * Tree *node\param
 * int\return
 *
 */

int searchTree(Tree head, ElementType data, Tree *node)
{
    if(head != NULL)
    {

        if(head->data < data)
        {
            *node = head;
            searchTree(head->right, data, node);
        }
        else if(head->data > data)
        {
            *node = head;
            searchTree(head->left, data, node);
        }
        else
        {
            return OK;  //找到该节点，此时的node为搜索节点的父节点
        }//end if

    }
    else
    {
        return ERROR;
    }
}

/** 树存在，插入节点\brief
 *
 * Tree *head\param
 * ElementType data\param
 * void\return
 *
 */

void insertTree(Tree *head, ElementType data)
{
    Tree tmp = *head, ptr; //存储插入节点的位置与新节点
    if(*head == NULL)
    {
        *head = (Tree)malloc(sizeof(Node));
        if(*head == NULL)
        {
            printf("memory error");
            exit(1);
        }
        (*head)->data = data;
        (*head)->left = (*head)->right = NULL;
    }
    else
    {
        if(searchTree(*head, data, &tmp) == ERROR)
        {
            ptr = (Tree)malloc(sizeof(Node));
            if(ptr == NULL)
            {
                printf("memory error");
                exit(1);
            }

            ptr->data = data;
            ptr->left = ptr->right = NULL;
            if(tmp == NULL)
            {
                tmp = ptr;
            }
            else if(tmp->data < data)
            {
                tmp->right = ptr;
            }
            else if(tmp->data > data)
            {
                tmp->left = ptr;
            }//end if

            //free(ptr);
        }//end if

    }//end if
}

/** 树不为空，并且该节点存在，删除\brief
 *  1、删除的节点无左右子树，直接删除
 *  2、删除的节点只有左子树，将该节点的前驱指向该节点的左子树，删除该节点
 *  3、删除的节点只有右子树，将该节点的前驱指向该节点的右子树，删除该节点
 *  4、删除的节点有左右子树，将该节点的值替换成该节点左子树的最右节点或该节点右子树的最左节点，删除最左（最右）节点
 * Tree head\param
 * ElementType data\param
 * int\return
 *
 */
int deleteTree(Tree *head, ElementType data)
{
    Tree parent = *head, ptr, child, prev;
    if((*head)->data == data)   //删除根节点，清空二叉树
    {
        if(emptyTree(head))
            return OK;
        return ERROR;
    }
    if(searchTree(*head, data, &parent) == ERROR)  //未找到该节点
    {
        return ERROR;
    }


    ptr = (parent->left && parent->left->data == data) ? parent->left : parent->right;
    if(ptr->left == NULL && ptr->right == NULL) //删除节点无左右子树
    {
        (parent->left && parent->left->data == data) ? (parent->left = NULL) : (parent->right = NULL);
    }
    else if(ptr->left == NULL)  //有右子树无左子树
    {
        //将父节点指向右子树
        (parent->left && parent->left->data == data) ? (parent->left = ptr->right) : (parent->right = ptr->right);

    }
    else if(ptr->right == NULL)   //有左子树无右子树
    {
        //将父节点指向右子树
        (parent->left && parent->left->data == data) ? (parent->left = ptr->left) : (parent->right = ptr->left);
    }
    else    //左右子树均存在
    {
        //将该节点的值替换成最后一个右节点即左子树中最大或右子树最左的节点即右子树中最小节点的值，本例用左子树的最右节点代替
        child = ptr->left;
        prev = ptr; //记录最右节点的前驱节点
        while(child->right != NULL) //查找最右节点
        {
            prev = child;
            child = child->right;
        }
        ptr->data = child->data;    //将最右节点的值替换删除节点的值

        if(child->left != NULL) //若该最右节点有左子树，将该最右节前驱的右孩子指向该最右节点有左子树
        {
            if(prev == ptr)  //若最右为删除节点的左子树，即没有右节点
            {
                ptr->left =  child->left;
            }
            else
            {
                prev->right = child->left;
            }
        }
        else
        {
            if(prev != ptr) //将最右节点的前驱指向NULL
            {
                prev->right = NULL;
            }
            else
            {
                ptr->left = NULL;
            }
        }

        free(child);
        child = NULL;
        return OK;
    }//end if

    free(ptr);
    ptr = NULL;
    return OK;
}


/** 树存在，清空二叉树\brief
 *
 * Tree *head\param
 * int\return
 *
 */
int emptyTree(Tree *head)
{
    if(*head != NULL)
    {
        emptyTree(&(*head)->left);
        emptyTree(&(*head)->right);
        free((*head));
        *head = NULL;
    }
}


/** 树存在，遍历二叉树\brief
 *
 * Tree head\param
 * void\return
 *
 */

void printTree(Tree head)
{
    if(head != NULL)
    {
        printTree(head->left);
        printf("%3d", head->data);
        printTree(head->right);
    }
}
