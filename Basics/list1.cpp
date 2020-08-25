/*************************************************************************************************************
 * 1. create a function which add new node in list
 * 2. create a function which search a node in list
 * 3. create a function which delete a specific node.
 * 4. display all Node.
 ************************************************************************************************************/
/*************************************************************************************************************
 Including headers
 ************************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*************************************************************************************************************
 Define MACROS
 ************************************************************************************************************/
#define SUCCESS 1
#define FAILURE -1

/*************************************************************************************************************
 Definition of struct Node.
 ************************************************************************************************************/
struct Node{
    int data;
    struct Node *next;
};

/*************************************************************************************************************
 Typedef of struct Node
 ************************************************************************************************************/
typedef struct Node Node_holder_t;

/*************************************************************************************************************
 Golbal list act as Head Node
 ************************************************************************************************************/
Node_holder_t *head_node = NULL;

/*************************************************************************************************************
 @display_listc : print all the value of a list
 ************************************************************************************************************/
void display_list(){
    Node_holder_t *temp_node = head_node; 
    while(temp_node!=NULL){
        printf("%d\t",temp_node->data);
        temp_node = temp_node->next;
    }
    printf("\n");
}

/*************************************************************************************************************
 @add_Node_to_list : Adding Node in a list.
 @user_data : value of int which is adding in list
 ************************************************************************************************************/
int add_Node_to_list(int user_data){
    Node_holder_t *curr_node = NULL;
    Node_holder_t *temp_node = NULL;

    curr_node = (Node_holder_t *)malloc(sizeof(Node_holder_t));
    if(!curr_node){
        printf("Memory allocation for current Node : Failed\n");
        return FAILURE;
    }
    memset(curr_node,0,sizeof(Node_holder_t));
    curr_node->data = user_data;
    if(head_node==NULL){
        head_node = curr_node;
    }
    else{
        temp_node=head_node;
        while(temp_node->next!=NULL){
            temp_node = temp_node->next;
        }
        temp_node->next = curr_node;
    }
    return SUCCESS;
    
}

/*************************************************************************************************************
 @find_Node_in_list : Searching Node in list.
 @user_data : value of int which is Searching in list
 ************************************************************************************************************/
int find_Node_in_list(int user_data){
    int i=1;
    Node_holder_t *temp_list = head_node;
    while(temp_list!=NULL){
        if(temp_list->data==user_data){
            printf("Matched found in Node : %d\n",i);
        }
        temp_list=temp_list->next;
        i++;
    }
    return SUCCESS;
}

/*************************************************************************************************************
 @remove_Node_from_list : remove the seleted from Node
 @user_data : value of int which is delete from list
 ************************************************************************************************************/
int remove_Node_from_list(int user_data){
    Node_holder_t *curr_node = head_node;
    Node_holder_t *prev_node = NULL;
    while(curr_node!=NULL){
        if(curr_node->data == user_data)
        {
            if(prev_node==NULL)
                head_node = curr_node->next;

            else
                prev_node->next=curr_node->next;

            free((void *)curr_node);
            return SUCCESS;
            
        }
        prev_node=curr_node;
        curr_node = curr_node->next;
    }

    printf("Invaild data \n");
    return FAILURE;
}


int main(){

/*************************************************************************************************************
 Variable declaration
 ************************************************************************************************************/
    int n,data;
    printf("Enter the length of list : ");
/*************************************************************************************************************
Taking value from cmd
 ************************************************************************************************************/
    scanf("%d",&n);
    printf("Fill the value in list : ");
    for(int i=0;i<n;i++){
        scanf("%d",&data);
        add_Node_to_list(data);
    }
    printf("List : ");
    display_list();
    printf("\n");

/*************************************************************************************************************
Taking value for search from cmd
 ************************************************************************************************************/    
    printf("you want to find the value , Enter the value : ");
    scanf("%d",&data);
    find_Node_in_list(data);
    printf("\n");

/*************************************************************************************************************
Taking value from cmd to remove
 ************************************************************************************************************/
    printf("you want to remove the value , Enter the value : ");
    scanf("%d",&data);
    remove_Node_from_list(data);
    printf("Updated list : ");
    display_list();
    printf("\n");

    return 0;
}