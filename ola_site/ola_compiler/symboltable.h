#include <stdio.h> 
#include <stdlib.h>
int level=-1;
int number=-1;

struct node { 
    char *name;
    char *kind;
    char *type;
    char *attribute;
    int level; 
    struct node *next; 
}; 

struct localNode {
    char *name;
    int number;
    struct localNode *next;
};

typedef struct node Node;

typedef struct localNode LocalNode;

struct root {
    Node *node;
    struct root *next;
};  

typedef struct root Root;

LocalNode* createLocal(){
	return NULL;
}

LocalNode* addLocal(LocalNode* top,char *name){
	LocalNode* newLocal;
	newLocal=(LocalNode*) malloc(sizeof(LocalNode));
	if(newLocal == NULL) { 
        printf("\nMemory allocation fails！"); 
        exit(1); 
    	}
	number++;
	newLocal->name=strdup(name);
	newLocal->number=number;
	newLocal->next=top;
	top=newLocal;
	return top;
}

LocalNode* addBlock(LocalNode* top){
	LocalNode* newLocal;
	newLocal=(LocalNode*) malloc(sizeof(LocalNode));
	if(newLocal == NULL) { 
        printf("\nMemory allocation fails！"); 
        exit(1); 
    	}
	newLocal->name="";
	newLocal->number=-1;
	newLocal->next=top;
	top=newLocal;
	return top;
}

int searchLocal(LocalNode* top,char *name){
    LocalNode* tmpnode;
    if(top==NULL)
    {
        //printf("\nNode is NULL");
    } 
    while(top != NULL) { 
	tmpnode=top;
	if(strcmp(tmpnode->name,name)==0)
		return tmpnode->number;
	top=top->next;
    }
    return -1; 

}


LocalNode* freeLocal(LocalNode* top) {
    LocalNode* tmpnode;
    if(top==NULL)
    {
        //printf("\nNode is NULL");
    } 
    while(top != NULL && top->number!=-1) { 
	tmpnode=top;
	top=top->next;
	free(tmpnode);
    }
    if(top!=NULL)
    {
	tmpnode=top;
	top=top->next;
	free(tmpnode);
    }
    number=-1;
    return top;   
} 


Root* creates() { 
    return NULL; 
}

Root* addRoot(Root* top) {
    Root* newroot; 

    newroot = (Root*) malloc(sizeof(Root)); 

    if(newroot == NULL) { 
        printf("\nMemory allocation fails！"); 
        exit(1); 
    }
    level++;
    newroot->next=top; 
    top=newroot;
    top->node=NULL;
    
    return top;
} 

void addNode(Root* top, char* name, char* kind, char* type, char* attribute) {
    Node* newnode; 

    newnode = (Node*) malloc(sizeof(Node)); 

    if(newnode == NULL) { 
        exit(1); 
    }
    newnode->name = strdup(name);
    newnode->kind = strdup(kind);  
    newnode->type = strdup(type);
    newnode->attribute = strdup(attribute);
    newnode->level=level;
    newnode->next = top->node; 
    top->node = newnode; 
}

Node* createNode() { 
    return NULL; 
}

Node *addFromNode(Node* top, char* name, char* kind, char* type, char* attribute,int level) {
    Node* newnode; 

    newnode = (Node*) malloc(sizeof(Node)); 

    if(newnode == NULL) { 
        exit(1); 
    }
    newnode->name = strdup(name);
    newnode->kind = strdup(kind);  
    newnode->type = strdup(type); 
    newnode->attribute = strdup(attribute); 
    newnode->level=level;
    newnode->next = top; 
    top = newnode;
    return top; 
}

void freeNode(Node* top) {
    Node* tmpnode;
    if(top==NULL)
    {
        //printf("\nNode is NULL");
    } 
    while(top != NULL) { 
	tmpnode=top;
	top=top->next;
	free(tmpnode);
    }   
} 

Node* lookupNode(char * s, Node* top) {
	Node* tmpnode;
	tmpnode=top;
	while(tmpnode!=NULL)
	{
		if(strcmp(tmpnode->name,s)==0)
		{
			return tmpnode;
		}
		tmpnode=tmpnode->next;
	}
	return NULL;
}


Root* freeStack(Root* top) {
    level--; 
    Node* tmpnode;
    if(top==NULL)
    {
        printf("\nRoot is NULL");
        exit(1);
    } 
    while(top->node != NULL) { 
	tmpnode=top->node;
	top->node=top->node->next;
	free(tmpnode);
    }
    Root* tmproot;
    tmproot=top;
    top=top->next;
    free(tmproot);
    return top;     
} 

void list(Root* top,int opt) { 
	if(opt){
	int i;
        Node* tmpnode, *buffer;
        tmpnode=top->node;
	buffer=NULL;
	while(tmpnode!=NULL)
	{
		Node* newbuffer;
		newbuffer = (Node*) malloc(sizeof(Node)); 
		newbuffer->name=tmpnode->name;
		newbuffer->kind=tmpnode->kind;
		newbuffer->type=tmpnode->type;
		newbuffer->attribute=tmpnode->attribute;
		newbuffer->next=buffer;
		buffer=newbuffer;
		tmpnode=tmpnode->next;
	}
	printf("%-32s\t%-11s\t%-11s\t%-17s\t%-11s\t\n","Name","Kind","Level","Type","Attribute");
	for(i=0;i< 110;i++)
		printf("-");
	printf("\n");
        while(buffer!=NULL)
	{
		printf("%-32s\t", buffer->name);
		printf("%-11s\t", buffer->kind);
		if(level==0)
			printf("%d%-10s\t", level,"(global)");
		else
			printf("%d%-10s\t", level,"(local)");
		printf("%-17s\t", buffer->type);
		printf("%-11s\t", buffer->attribute);
		printf("\n");
		buffer=buffer->next;
	}
	for(i=0;i< 110;i++)
		printf("-");
	printf("\n"); 
	while(buffer != NULL) { 
		tmpnode=buffer;
		buffer=buffer->next;
		free(tmpnode);
	}}
}

Node* lookup(char * s, Root* top) {
	Root* tmproot;
	Node* tmpnode;
	tmproot=top;
	tmpnode=tmproot->node;
	while(tmpnode!=NULL)
	{
		if(strcmp(tmpnode->name,s)==0)
		{
			return tmpnode;
		}
		tmpnode=tmpnode->next;
	}
	return NULL;
}

Node* EntireLookup(char * s, Root* top){

	Root* tmproot;
	Node* tmpnode;
	tmproot=top;
	tmpnode=tmproot->node;

	while(tmproot!=NULL)
	{ 
		
		tmpnode=tmproot->node;
		while(tmpnode!=NULL)
		{
			
			
			if(strcmp(tmpnode->name,s)==0)
			{
				return tmpnode;
			}
			tmpnode=tmpnode->next;
		}
		tmproot=tmproot->next;
	}

}

Node* LookupGlobal(char * s, Root* top){

	Root* tmproot;
	Node* tmpnode;
	tmproot=top;
	tmpnode=tmproot->node;
	
	if(tmproot==NULL)
	{
		printf("wrong symbol table!\n");
		exit(1);
	}
	while(tmproot->next!=NULL)
	{ 
		tmproot=tmproot->next;
	}
	tmpnode=tmproot->node;
	while(tmpnode!=NULL)
	{
		if(strcmp(tmpnode->name,s)==0)
		{
			return tmpnode;
		}
		tmpnode=tmpnode->next;
	}

}


