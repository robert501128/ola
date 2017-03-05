%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

char filename[32];
extern int linenum;             /* declared in lex.l */
extern FILE *yyin;              /* declared by lex */
extern char *yytext;            /* declared by lex */
extern char buf[256];           /* declared in lex.l */
extern int Opt_D;
Root *top;
Node *fortop;
LocalNode *ltop;
int isFunc;
int FuncComp;
int isMain;
char *funcname;
int semError;
char content[4194304];
int number;
int labelNumber;



char* typetoJava(char *a)
{
	char *s=(char*)malloc(sizeof(char));
	if(strcmp(a,"integer")==0)
	{
		s[0]='I';
		return s;
	}
	if(strcmp(a,"string")==0)
	{
		s[0]='Z';
		return s;
	}
	if(strcmp(a,"real")==0)
	{
		s[0]='F';
		return s;
	}
	if(strcmp(a,"boolean")==0)
	{
		s[0]='Z';
		return s;
	}
	if(strcmp(a,"void")==0)
	{
		s[0]='V';
		return s;
	}
	
}
void loadFunc(char *name, char *type, char *attribute)
{
	strcat(content,"invokestatic ");
	strcat(content,filename);
	strcat(content,"/");
	strcat(content,name);
	strcat(content,"(");
	
	char buf[1000];
	char *pch;
	strcpy(buf,attribute);
	pch=strtok(buf,",");
	while(pch!=NULL)
	{
		strcat(content,typetoJava(pch));
		pch=strtok(NULL,",");
	}
		
	strcat(content,")");	
	strcat(content,typetoJava(type));
	strcat(content,"\n");
	
}

void loadConst(char *attribute, char *type)
{
	if(strcmp(type,"integer")==0)
	{
		strcat(content,"sipush ");
		strcat(content,attribute);
		strcat(content,"\n");
	}
	else if(strcmp(type,"boolean")==0)
	{
		if(strcmp(attribute,"true")==0){					
		strcat(content,"iconst_1");
		strcat(content,"\n");}
		else{
		strcat(content,"iconst_0");
		strcat(content,"\n");}
	}
	else
	{
	
		strcat(content,"ldc ");
		strcat(content,attribute);
		strcat(content,"\n");
	}
}

void loadVar(char* name,char* kind, char* type, char* attribute, int innerlevel)
{
	if(strcmp(kind,"constant")==0)
	{
		
		if(strcmp(type,"integer")==0)
		{
			strcat(content,"sipush ");
			strcat(content,attribute);
			strcat(content,"\n");
		}
		else if(strcmp(type,"boolean")==0)
		{
			if(strcmp(attribute,"true")==0){					
			strcat(content,"iconst_1");
			strcat(content,"\n");}
			else{
			strcat(content,"iconst_0");
			strcat(content,"\n");}
		}
		else
		{
			
			strcat(content,"ldc ");
			strcat(content,attribute);
			strcat(content,"\n");
		}
	}
	else if(innerlevel==0)
	{

		strcat(content,"getstatic ");
		strcat(content,filename);
		strcat(content,"/");
		strcat(content,name);
		strcat(content," ");
		strcat(content,typetoJava(type));
		strcat(content,"\n");
	}else
	{
		
		int num=searchLocal(ltop,name);
		if(num>=0){
		if(strcmp(type,"real")==0)
		{

			char snum[10];
			sprintf(snum,"%d",num);
			strcat(content,"fload ");
			strcat(content,snum);
			strcat(content,"\n");
		}
		else
		{
			char snum[10];
			sprintf(snum,"%d",num);
			strcat(content,"iload ");
			strcat(content,snum);
			strcat(content,"\n");
		}			
		}
	}
}

void publicStore(char *name,char *type)
{
	strcat(content,"putstatic ");
	strcat(content,filename);
	strcat(content,"/");
	strcat(content,name);
	strcat(content," ");
	strcat(content,typetoJava(type));
	strcat(content,"\n");
}

void localStore(char *name,char *type)
{
	int num=searchLocal(ltop,name);
	if(num>=0){
	if(strcmp(type,"real")==0)
	{

		char snum[10];
		sprintf(snum,"%d",num);
		strcat(content,"fstore ");
		strcat(content,snum);
		strcat(content,"\n");
	}
	else
	{
		char snum[10];
		sprintf(snum,"%d",num);
		strcat(content,"istore ");
		strcat(content,snum);
		strcat(content,"\n");
	}			
	}
}

void createLabel(char *L1)
{
	strcpy(L1,"L");
	char num[10];
	sprintf(num,"%d",labelNumber++);
	strcat(L1,num);	
}

void createRelCode(char *Op,char *L1, char *L2)
{
	strcat(content,Op);
	strcat(content," ");
	strcat(content,L1);
	strcat(content,"\n");
	strcat(content,"iconst_0\n");
	strcat(content,"goto ");
	strcat(content,L2);
	strcat(content,"\n");
	strcat(content,L1);
	strcat(content,":\n");
	strcat(content,"iconst_1\n");
	strcat(content,L2);
	strcat(content,":\n");
}


%}
%code requires{
	struct data {
		char *idname;
		char *type;
		struct data *next;
	};
	typedef struct data Data;



	
}


%union {
	char *idname;
	struct s1 { char *r; } *state;
	struct s2 { char *toString; int start;} array;
	struct s3 { char *idname; char *type;} all;
	struct s4 { char *idname; char *type; char *kind; char *attribute; int level;} simulateNode;
	struct s5 { char *type; int pointer;} forE;
	struct s6 { char back[10],next[10]; char *idname; } forFor;
	struct data *aarrg;
	char forLabel[10];
	int num;
	
}


%token KWvar '(' ',' ';' ':' ')' '[' ']' '+' '-' '*' '/' mod '>' '=' and or not KWbegin KWinteger KWreal KWprint KWend KWarray KWboolean KWdo KWelse KWfalse KWfor KWif KWof KWread KWstring KWthen KWto KWtrue KWreturn KWwhile id '<' assign lte gte gl Lstring Lreal Lint
%type <idname> id KWreturn RETURN KWinteger KWreal MORE_E KWstring KWboolean TYPE PorR ID_List BeginId  L_BOOL Lreal Lstring KWfalse KWtrue FBeginId
%type <num> Lint REF
%type <array> SC_TYPE
%type <all> L_CONSTANT CPN
%type <aarrg> ARG ZorARG
%type <simulateNode> VAR_REF FUNC_INV FUNCID
%type <forE> E BE
%type <forLabel> CONDBE CONDSTMT CONTROLWHILE
%type <forFor> FORINITIALIZE






%left or
%left and
%left not
%left '<' lte '=' gte '>' gl 
%left '+' '-'
%left '*' '/' mod
%right KWelse

%%
START: BeginId';' GlZorVDEC ZorFDEC MAIN COMP CEND EndId ;
BeginId: id{ if(strcmp($1,filename)!=0){ semError=1; 
		//program beginning ID inconsist with file name
        printf("%d (ꐦ°᷄д°᷅): Please give us A+, please~ please!!\n", linenum);}
		top=addRoot(top);
		addNode(top,$1,"program","void","");
		$$=$1;
		strcat(content,".class public ");
		strcat(content,filename);
		strcat(content,"\n");
		strcat(content,".super java/lang/Object\n");
		strcat(content,".field public static _sc Ljava/util/Scanner;\n");	
	
		};
MAIN: { isMain=1;
	strcat(content,".method public static main([Ljava/lang/String;)V\n");
	strcat(content,".limit stack 20  ;\n");
	strcat(content,".limit locals 20\n");
	strcat(content,"new java/util/Scanner\ndup\ngetstatic java/lang/System/in Ljava/io/InputStream;\n");
	strcat(content,"invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V\nputstatic ");
	strcat(content,filename);
	strcat(content,"/_sc Ljava/util/Scanner;\n");
	ltop=addLocal(ltop,"");
	};

CEND: KWend {isMain=0;
		strcat(content,"    return\n");
		strcat(content,".end method\n");
	};

EndId: id{
		if(strcmp($<idname>-5,$1)!=0)
		{semError=1;
		//program beginning ID inconsist with ending ID
        printf("%d ☜(`o´): Please give us A+. \n", linenum);}
		list(top,Opt_D);
		top=freeStack(top);
	};
GlZorVDEC: ;
GlZorVDEC: GlZorVDEC GlVDEC;
GlVDEC: KWvar ID_List ':' GlALLTYPE ';' ;
GlALLTYPE: SC_TYPE 
	{
		char *buffer=$<idname>-1;
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
			{
				addNode(top,pch,"variable",$1.toString,"");
				strcat(content,".field public static ");
				strcat(content,pch);
				strcat(content," ");
				strcat(content,typetoJava($1.toString));
				strcat(content,"\n");
			}	
			else{ semError=1;
                //Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
		
	};
GlALLTYPE: L_CONSTANT
	{		
		char *buffer=$<idname>-1;
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
				addNode(top,pch,"constant",$1.type,$1.idname);
			else{ semError=1;
				//Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
	};
ZorVDEC: ;
ZorVDEC: ZorVDEC VDEC;
VDEC: KWvar ID_List ':' ALLTYPE ';' ;
ZorFDEC:   ;
ZorFDEC: ZorFDEC FDEC;
FDEC: FBeginId  COMP KWend FEndId;
FBeginId: id '(' ZorARG ')' PorR ';' {

	Data *data=$3;
	Data *reverse=NULL;
	Data *tmpdata;
	int s=1;
	char w[10000];
	memset(w,0,sizeof(w));	
	while(data!=NULL)
	{
		tmpdata=data;		
		data=data->next;
		tmpdata->next=reverse;
		reverse=tmpdata;
	}
	tmpdata=reverse;
	while(tmpdata!=NULL)
	{	
		if(s){strcat(w,tmpdata->type); s=0; }
		else {strcat(w,","); strcat(w,tmpdata->type);}
		tmpdata=tmpdata->next;
	}
	
	if(lookup($1,top)==NULL)
	{
		strcat(content,".method public static ");
		strcat(content,$1);
		strcat(content,"(");
		tmpdata=reverse;
		while(tmpdata!=NULL)
		{
		 strcat(content,typetoJava(tmpdata->type));
		 tmpdata=tmpdata->next;
		}
		if($5==NULL)      	
		{
	         addNode(top,$1,"function","void",w);
		 strcat(content,")V\n");
		}
		else
		{
	      	 addNode(top,$1,"function",$5,w);
		 strcat(content,")");
		 strcat(content,typetoJava($5));
		 strcat(content,"\n");
		}
		$$=$1;
		strcat(content,".limit stack 20\n");
		strcat(content,".limit locals 20\n");
	}
	else{   semError=1;
		//Function redeclare
        printf("%d .·´¯`(>▂<)´¯`·. : I’ve seen that Heart Eye Face.\n", linenum);
		$$=NULL;  }
	top=addRoot(top);
	tmpdata=reverse;
	while(tmpdata!=NULL)
	{
		if(lookup(tmpdata->idname,top)==NULL)
		{
			addNode(top,tmpdata->idname,"parameter",tmpdata->type,"");
			ltop=addLocal(ltop,tmpdata->idname);
		}
		else{semError=1;
			//Parameter redeclare
            printf("%d ᕙ(⇀‸↼‶)ᕗ :Same name for this kind of pet.\n", linenum);}
		tmpdata=tmpdata->next;
		}
	tmpdata=reverse;
	Data *tmpdata2;
	while(tmpdata!=NULL)
	{
		tmpdata2=tmpdata;
		tmpdata=tmpdata->next;
		free(tmpdata2);
	}
	isFunc=1;
	FuncComp=0;
	funcname=$$;
	};
FEndId: id 
	{	isFunc=0;
		
		char *beginid=$<idname>-2;		
		if(beginid!=NULL)
		{
			if(strcmp(beginid,$1)!=0)
			{semError=1;
                //program beginning ID inconsist with ending ID
                printf("%d ☜(`o´): Please give us A+. \n", linenum);}
		}
		Node *node=EntireLookup($1,top);
		if(!strcmp(node->type,"void")) strcat(content,"return\n");
		strcat(content,".end method\n");
		list(top,Opt_D);
		top=freeStack(top);
		ltop=freeLocal(ltop);
	};
PorR: {$$=NULL;};
PorR: ':' TYPE {$$=$2;};
ZorARG:  {$$=NULL;};
ZorARG: ARG {$$=$1;};
ARG: ID_List ':' SC_TYPE 
	{
		Data *data=NULL;
		char *pch;		
		pch=strtok($1,",");
		while(pch!=NULL)
		{
			Data *x=(Data*)malloc(sizeof(Data));
			x->next=data;
			data=x;
			data->idname=strdup(pch);
			data->type=$3.toString;
			pch=strtok(NULL,",");
		}
		$$=data;
	};
ARG: ARG ';' ID_List ':' SC_TYPE 
	{
		Data *data=$1;
		char *pch;		
		pch=strtok($3,",");
		while(pch!=NULL)
		{
			Data *x=(Data*)malloc(sizeof(Data));
			x->next=data;
			data=x;
			data->idname=strdup(pch);
			data->type=$5.toString;
			pch=strtok(NULL,",");
		}
		$$=data;
	};

ID_List: id { $$=$1; };
ID_List: ID_List ',' id
	{ $$=$1; 
	  strcat($$,",");
	  strcat($$, $3);	
	};
ALLTYPE: SC_TYPE 
	{
		char *buffer=$<idname>-1;
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
			{
				addNode(top,pch,"variable",$1.toString,"");
				ltop=addLocal(ltop,pch);
			}
			else{ semError=1;
				//Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
			
		}
		
	};
ALLTYPE: L_CONSTANT
	{		
		char *buffer=$<idname>-1;
		char *pch;
		pch=strtok(buffer,",");
		while(pch!=NULL)
		{
			if(lookup(pch,top)==NULL)
				addNode(top,pch,"constant",$1.type,$1.idname);
			else{ semError=1;
                //Variable redeclare
                printf("%d ◢▆▅▄▃-╰(〒皿〒)╯-▃▄▅▆◣ : I’ve seen that Cat Face. \n", linenum);}
			pch=strtok(NULL,",");
		}
		
	};
SC_TYPE: TYPE 	{$$.toString=$1; $$.start=-1; };
SC_TYPE: KWarray Lint KWto Lint KWof SC_TYPE
	{
		if(strcmp($6.toString,"error")!=0){		
		if($2>=$4)
        {   //Declare a wrong array: Starting number is bigger or equal than ending number
            printf("%d (ノಠ益ಠ)ノ彡┻━┻ : Wrong hand instruction; Hand up and turn right.\n", linenum);}
            semError=1;
            $$.toString="error";}
		else
		{
			if($6.start<0)
			{
				char num[64];
				sprintf(num,"%d",$4-$2+1);
				char *cats=(char*)malloc(strlen(num)*sizeof(char)+2*sizeof(char));
				memset(cats,0,sizeof(cats));
				int i,j;
				cats[0]='[';
				for(i=1,j=0;j<strlen(num);i++,j++)
				{cats[i]=num[j];}

				cats[i]=']';
				char *s=(char*)malloc(sizeof(cats)+sizeof($6.toString));
				memset(s,0,sizeof(s));
				strcpy(s,$6.toString);
				strcat(s,cats);
				free($6.toString);
				free(cats);
				$$.toString=s;
			}
			else
			{				
				char num[64];
				sprintf(num,"%d",$4-$2+1);
				char *cats=(char*)malloc(strlen(num)*sizeof(char)+2*sizeof(char));
				memset(cats,0,sizeof(cats));
				int i,j;
				cats[0]='[';
				for(i=1,j=0;j<strlen(num);i++,j++)
				{cats[i]=num[j];}

				cats[i]=']';
				char *s=(char*)malloc(sizeof(cats)+sizeof($6.toString));
				memset(s,0,sizeof(s));
				int pos;
				pos=strcspn($6.toString,"[");
				for(i=0;i<pos;i++)
					s[i]=$6.toString[i];
				for(j=0;j<strlen(cats);j++,i++)
					s[i]=cats[j];
				for(j=pos;j<strlen($6.toString);j++,i++)
					s[i]=$6.toString[j];
				free($6.toString);
				free(cats);
				$$.toString=s;
			}
			
		}
	};
TYPE: KWinteger {$$=$1;};
TYPE: KWreal 	{$$=$1;};
TYPE: KWstring 	{$$=$1;};
TYPE: KWboolean	{$$=$1;};
L_CONSTANT: Lint
	{
		char num[64];
		sprintf(num,"%d",$1);
		char *buffer=(char*)malloc(strlen(num)*sizeof(char));
		strcpy(buffer,num);
		$$.idname=buffer; $$.type="integer";};
L_CONSTANT: Lreal{$$.idname=$1; $$.type="real";};
L_CONSTANT: Lstring{$$.idname=$1; $$.type="string";};
L_CONSTANT: L_BOOL{$$.idname=$1; $$.type="boolean";};
L_BOOL: KWtrue{$$=$1;};
L_BOOL: KWfalse{$$=$1;};
STMT: STMT  COMP 	;
STMT: STMT  SIMPLE 	;
STMT: STMT  E ';' 	;
STMT: STMT  COND 	;
STMT: STMT WHILE 	;
STMT: STMT  FOR 	;
STMT: STMT  RETURN 	;
STMT: ;
COMPBEGIN: KWbegin
	{
		if(isFunc)FuncComp++;
		if(FuncComp!=1){
		top=addRoot(top);
		ltop=addBlock(ltop);}
	};
COMP: COMPBEGIN ZorVDEC STMT KWend 
	{
		
		if(FuncComp!=1){
		list(top,Opt_D);
		top=freeStack(top);
		ltop=freeLocal(ltop);}
		if(isFunc) FuncComp--;
	};

SIMPLE: VAR_REF assign E ';' 
	{
		
		if($3.type==NULL)
		;
		else if($1.type!=NULL && $1.idname!=NULL){
			if(lookupNode($1.idname,fortop)!=NULL){ semError=1;
			// Loop variable %s can not be assigned
            printf("%d ⁽⁽(੭ꐦ •̀Д•́ )੭*⁾⁾ ᑦᵒᔿᵉ ᵒᐢᵎᵎ : Loop Cat Face %s can not be assigned.\n", linenum,$1.idname);}
			else
			{
			char *id1, *id3,*pch1[1000],*pch3[1000],*buf1,*buf3;
			int i=0;
			buf1=strdup($1.type);
			buf3=strdup($3.type);
			id1=strtok(buf1,"[]");
			pch1[i]=strtok(NULL,"[]");
			for(i=1;pch1[i-1]!=NULL;i++)
			{
				pch1[i]=strtok(NULL,"[]");
			}
			id3=strtok(buf3,"[]");
			i=0;
			pch3[i]=strtok(NULL,"[]");
			for(i=1;pch3[i-1]!=NULL;i++)
			{
				pch3[i]=strtok(NULL,"[]");
			}
			int same=1;
			Node *node=EntireLookup($1.idname,top);
			if(strcmp(node->kind,"constant")==0){ semError=1;
			//Constant variable %s can not be assigned
            printf("%d o͡͡͡͡͡͡╮(ꐦ ꈨຶ皿ꈨຶ)╭o͡͡͡͡͡͡ : Symbolic Cat Face %s can not be assigned.\n", linenum,$1.idname);}
			else if(strcmp(id1,"real")==0 && strcmp(id3,"integer")==0)
			{
				
				for(i=0;pch1[i]!=NULL || pch3[i]!=NULL;i++)
				{
					
					if(pch1[i]==NULL||pch3[i]==NULL) same=0;
					else if(strcmp(pch1[i],pch3[i])!=0) same=0; 
				}
				strcat(content,"i2f\n");
				if(node->level==0)
				publicStore($1.idname,$1.type);
				else
				localStore($1.idname,$1.type);						
			}		
			else if(strcmp($1.type,$3.type)!=0){ semError=1;
			//Assign statement mismatch Left
            printf("%d (۶ૈ ۜ ᵒ̌▱๋ᵒ̌ )۶ૈ=͟͟͞͞ ⌨ : Assign Face statement mismatch Left: %s Right: %s.\n", linenum,$1.type, $3.type);}
			else{
				if(node->level==0)
				publicStore($1.idname,$1.type);
				else
				localStore($1.idname,$1.type);				
			}
			if(same==0){ semError=1;
                //Assign statement mismatch Left
                printf("%d (۶ૈ ۜ ᵒ̌▱๋ᵒ̌ )۶ૈ=͟͟͞͞ ⌨ : Assign Face statement mismatch Left: %s Right: %s.\n", linenum,$1.type, $3.type);}
			}
		}
	};
SIMPLE: PRINTCODE E ';' 
	{
		if($2.type!=NULL)
			if(strcmp($2.type,"real")!=0 && strcmp($2.type,"boolean")!=0 && strcmp($2.type,"integer")!=0 && strcmp($2.type,"string")!=0){ semError=1;
			//Print statement operand is array type
            printf("%d o͡͡͡͡͡͡╮(ꐦ ꈨຶ皿ꈨຶ)╭o͡͡͡͡͡͡ : Long Eyelash Face statement operand is in a Fish type.\n", linenum);}
			else{
			 strcat(content,"invokevirtual java/io/PrintStream/print(");
			 if(!strcmp($2.type,"string")) strcat(content,"Ljava/lang/String;");
			 else if(!strcmp($2.type,"integer")) strcat(content,"I");
			 else if(!strcmp($2.type,"boolean")) strcat(content,"Z");
			 else strcat(content,"F");
			 strcat(content,")V\n");
			}
	};
PRINTCODE: KWprint {strcat(content,"getstatic java/lang/System/out Ljava/io/PrintStream;\n");};
SIMPLE: KWread VAR_REF ';'
	{
		if($2.type!=NULL)
			if(strcmp($2.type,"real")!=0 && strcmp($2.type,"boolean")!=0 && strcmp($2.type,"integer")!=0 && strcmp($2.type,"string")!=0)
			{ semError=1;
			//Read statement operand is array type
            printf("%d ( ｰ̀εｰ́ ): Dot Cheek Face statement operand is in a Fish type.\n", linenum);}
			else
			{
			 strcat(content,"getstatic ");
			 //printf("hello:%s\n",filename);
			 strcat(content,filename);
			 strcat(content,"/_sc Ljava/util/Scanner;\n");
			 strcat(content,"invokevirtual java/util/Scanner/");
			 if(!strcmp($2.type,"integer"))
			  strcat(content,"nextInt()I\n");
			 else if(!strcmp($2.type,"boolean"))
			  strcat(content,"nextBoolean()Z\n");
			 else
			  strcat(content,"nextFloat()F\n");
			 if($2.level==0)
			  publicStore($2.idname,$2.type);
			 else
			  localStore($2.idname,$2.type);
			

			}
	};
VAR_REF: id
	{
		Node *node=EntireLookup($1,top);
		$$.idname=NULL;
		$$.type=NULL;
		if(node==NULL){ semError=1;
			// Variable does not exist
            printf("%d ⎧ᴿᴵᴾ⎫◟◟◟◟◟◟◟◟ ❀◟(ó ̯ ò, ): This Cat Face %s is dead.\n", linenum,$1);}
		else
		{
			$$.idname=node->name;
			$$.type=node->type;
			$$.kind=node->kind;
			$$.attribute=node->attribute;
			$$.level=node->level;
		}
		
		
	};
VAR_REF: id REF
	{
		
		$$.idname=NULL;
		$$.type=NULL;	
		Node *node=EntireLookup($1,top);
		if(node==NULL){ semError=1;
            // Variable does not exist
            printf("%d ⎧ᴿᴵᴾ⎫◟◟◟◟◟◟◟◟ ❀◟(ó ̯ ò, ): This Cat Face %s is dead.\n", linenum,$1);}
		else
		{
			$$.idname=node->name;
			char *pch;
			char *buffer=strdup(node->type);
			char *idname;
			idname=strtok(buffer,"[]");
			pch=strtok(NULL,"[]");
			$2--;
			int error=1;
			while(pch!=NULL)
			{
				if($2==0) { error=0; break;}
				pch=strtok(NULL,"[]");
				$2--;
			}
			if(error){ semError=1;
				//Reference too much!(Out of Bound)
                printf("%d (✖╭╮✖) :You know too much.\n", linenum,$1);}
			else
			{
				pch=strtok(NULL,"");
				if(pch!=NULL)
					strcat(idname,pch);
				$$.type=idname;
			}
		}
		
		
	};
REF: '[' LE ']' { $$=1; };
REF: REF '[' LE ']'{$$++;};
LE: '-' LE %prec '*';
LE: LE '*' LE;
LE: LE '/' LE;
LE: LE mod LE;
LE: LE '+' LE;
LE: LE '-' LE;
LE: RCPN;
RCPN: FUNC_INV
	{
		if($1.type!=NULL && $1.idname!=NULL)
		{
			if(strcmp($1.type,"integer")!=0){ 
				semError=1;
                //Array index wrong type
                printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,$1.idname,$1.type);
            }
		}
	};
RCPN: L_CONSTANT
	{
		if($1.type!=NULL && $1.idname!=NULL)
		{
			if(strcmp($1.type,"integer")!=0){ semError=1;
			//Array index wrong type
            printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,$1.idname,$1.type);}
		}
	};
RCPN: VAR_REF
	{
		if($1.type!=NULL && $1.idname!=NULL)
		{
			if(strcmp($1.type,"integer")!=0){ semError=1;
                //Array index wrong type
                printf("%d ლ(ಠ益ಠ)ლ: The index of parts in the Fish Face %s can not be %s type.\n", linenum,$1.idname,$1.type);}
		}
	};
E: '-' E %prec '*'
	{
		$$.type=NULL;
		if($2.type!=NULL)
		{
			if(strcmp($2.type,"integer")!=0 && strcmp($2.type,"real")!=0){ semError=1;
			//Operand after - wrong type.\n
            printf("%d (#ಠQಠ#): Operand after Sub Dance Face can not be %s type.\n", linenum,$2.type);}
			else if(!strcmp($2.type,"integer"))
			{
				strcat(content,"ineg\n");
				$$.type=$2.type;
			}
			else
			{
				strcat(content,"fneg\n");
				$$.type=$2.type;
			}
		}
		$$.pointer=strlen(content);
	};
E: E '*' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")==0 && strcmp($3.type,"integer")==0)
			{	
				$$.type=$1.type; strcat(content,"imul\n");
			}
			else if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0)
			{ 	semError=1;
				//printf(Operands between * wrong type
            	printf("%d ˚‧º·(˚ ˃̣̣̥᷄⌓˂̣̣̥᷅ )‧º·˚: Operand after Mulo Dance Face can not be %s/%s type.\n", linenum,$1.type,$3.type);
            }
			else if(!strcmp($1.type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+$1.pointer);
				content[$1.pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fmul\n");
				$$.type="real";
			}
			else if(!strcmp($3.type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fmul\n");
				$$.type="real";
			}
			else
			{
				strcat(content,"fmul\n");
				$$.type="real";
			}
		}
		$$.pointer=strlen(content);
	};
E: E '/' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")==0 && strcmp($3.type,"integer")==0)
			{	$$.type=$1.type; strcat(content,"idiv\n");}
			else if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0)
			{ 	semError=1;
				//Operands between / wrong type
            	printf("%d o(o･`з･´o)ﾉ: Operand between And Face can not be %s/%s type\n", linenum,$1.type,$3.type);
			}
			else if(!strcmp($1.type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+$1.pointer);
				content[$1.pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fdiv\n");
				$$.type="real";
			}
			else if(!strcmp($3.type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fdiv\n");
				$$.type="real";
			}
			else
			{
				strcat(content,"fdiv\n");
				$$.type="real";
			}
		}
		$$.pointer=strlen(content);
	};
E: E mod E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")==0 && strcmp($3.type,"integer")==0)
			{	$$.type=$1.type; strcat(content,"irem\n");}
			else{ 
				semError=1; 
				//Operands between mod wrong type
            	printf("%d (*￣(ｴ)￣*): Operand between Mode Dance Face can not be %s/%s type.\n", linenum,$1.type,$3.type);}
		}
		$$.pointer=strlen(content);
	};
E: E '+' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")==0 && strcmp($3.type,"integer")==0)
			{	$$.type=$1.type; strcat(content,"iadd\n");}
			else if(strcmp($1.type,"string")==0 && strcmp($3.type,"string")==0)
				$$.type=$1.type;
			else if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0)
			{	semError=1;
				//Operands between + wrong type
            	printf("%d ξ(｡◕ˇ◊ˇ◕｡)ξ: Operand between Add Dance Face can not be %s/%s type.\n", linenum,$1.type,$3.type);
            }
			else if(!strcmp($1.type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+$1.pointer);
				content[$1.pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fadd\n");
				$$.type="real";
			}
			else if(!strcmp($3.type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fadd\n");
				$$.type="real";
			}
			else
			{
				strcat(content,"fadd\n");
				$$.type="real";
			}
		}
		$$.pointer=strlen(content);
	};
E: E '-' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")==0 && strcmp($3.type,"integer")==0)
			{	$$.type=$1.type; strcat(content,"isub\n");}
			else if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
                //Operand after - wrong type.\n
                printf("%d (#ಠQಠ#): Operand after Sub Dance Face can not be %s type.\n", linenum,$3.type);}
            
			else if(!strcmp($1.type,"integer"))
			{
				char buf[50];
				strcpy(buf,content+$1.pointer);
				content[$1.pointer]='\0';
				strcat(content,"i2f\n");
				strcat(content,buf);
				strcat(content,"fsub\n");
				$$.type="real";
			}
			else if(!strcmp($3.type,"integer"))
			{
				strcat(content,"i2f\n");
				strcat(content,"fsub\n");
				$$.type="real";
			}
			else
			{
				strcat(content,"fsub\n");
				$$.type="real";
			}
		}
		$$.pointer=strlen(content);
	};
BE: E '<' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand after < wrong type
            printf("%d ／(￣ ∈∋ ￣)＼: Operand after Hands Up and Face Right can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("iflt",L1,L2);
				$$.type="boolean";
			}
		}
	};
BE: E lte E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand after <= wrong type
            printf("%d (ↀДↀ): Operand after Fork Hand Directing to Right can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
								char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifle",L1,L2);
				$$.type="boolean";
			}
		}
	};
BE: E '=' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand after = wrong type
            printf("%d ๐·°(৹˃̵﹏˂̵৹)°·๐: Operand after Equal Face can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifeq",L1,L2);
				$$.type="boolean";
			}
		}
	};
BE: E gte E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand after >= wrong type
            printf("%d ( ᵒ̴̶̷̥́ _ᵒ̴̶̷̣̥̀ ): Operand after Hand Directing to Left can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifge",L1,L2);
				$$.type="boolean";
			}
		}
	};
BE: E '>' E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand after > wrong type
            printf("%d（　(≪●≫)　）Д（　(≪●≫)　） : Operand after Hands Up and Face Left can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifgt",L1,L2);
				

				$$.type="boolean";
			}
		}
	};
BE: E gl E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"integer")!=0 && strcmp($1.type,"real")!=0 || strcmp($3.type,"integer")!=0 && strcmp($3.type,"real")!=0){ semError=1;
			//Operand between <> wrong type
            printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{
				if(!strcmp($1.type,"integer") && !strcmp($3.type,"integer"))
				strcat(content,"isub\n");
				else if(!strcmp($1.type,"real") && !strcmp($3.type,"integer"))
				{
					char buf[50];
					strcpy(buf,content+$1.pointer);
					content[$1.pointer]='\0';
					strcat(content,"i2f\n");
					strcat(content,buf);
					strcat(content,"fsub\n");
				}
				else if(!strcmp($1.type,"integer") && !strcmp($3.type,"real"))
					strcat(content,"i2f\nfsub\nf2i\n");
				else
					strcat(content,"fsub\nf2i\n");
				
				char L1[10],L2[10];
				createLabel(L1);				
				createLabel(L2);
				createRelCode("ifne",L1,L2);
				$$.type="boolean";
			}
		}
	};
BE: not E
	{
		$$.type=NULL;
		if($2.type!=NULL)
		{
			if(strcmp($2.type,"boolean")!=0){ semError=1;
			//Operand after not wrong type
            printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand after Not Face can not be %s type.\n", linenum,$2.type);}
			else
			{	$$.type="boolean"; strcat(content,"ixor\n");}
		}
		$$.pointer=strlen(content);
	};
BE: E and E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"boolean")!=0 && strcmp($3.type,"boolean")!=0){ semError=1;
                //Operand between <> wrong type
                printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{	$$.type="boolean"; strcat(content,"iand\n");}
		}
		$$.pointer=strlen(content);
	};
BE: E or E
	{
		$$.type=NULL;
		if($1.type!=NULL && $3.type!=NULL )
		{
			if(strcmp($1.type,"boolean")!=0 && strcmp($3.type,"boolean")!=0){ semError=1;
                //Operand between <> wrong type
                printf("%d ヾ(｡ꏿ﹏ꏿ)ﾉﾞ: Operand between Hands Up Dancing Face can not be %s/%s type.\n", linenum,$1.type,$3.type);}
			else
			{	$$.type="boolean"; strcat(content,"ior\n");}
		}
		$$.pointer=strlen(content);
	};
E: BE {$$.type=$1.type; $$.pointer=$1.pointer; };
E: '(' E ')'{$$.type=$2.type; $$.pointer=$2.pointer; };
E: CPN {$$.type=$1.type; $$.pointer=strlen(content);};
CPN: FUNC_INV{$$.idname=$1.idname;$$.type=$1.type;
	loadFunc($1.idname,$1.type,$1.attribute);
	
	};
CPN: L_CONSTANT{$$.idname=$1.idname;$$.type=$1.type;
		loadConst($1.idname,$1.type);};
CPN: VAR_REF {$$.idname=$1.idname;$$.type=$1.type;
	      loadVar($1.idname,$1.kind,$1.type,$1.attribute,$1.level);
		};
FUNC_INV: FUNCID '(' ZorE ')'
	{
		
		$$.idname=$1.idname;
		$$.type=$1.type;
		$$.attribute=$1.attribute;
		
	};
FUNCID: id {
		Node *node=EntireLookup($1,top);
		$$.idname=$1;
		$$.type=NULL;
		if(node==NULL){ semError=1;
		//Function %s does not exist
        printf("%d ฅ=͟͟͞͞((꒪∆꒪;)ฅ : This Heart Eye Face %s does not exist.\n", linenum,$1);}
		else
		{
		 $$.type=node->type;
		 $$.attribute=node->attribute;
		}
	}
ZorE: ;
ZorE: MORE_E ;
MORE_E: E {$$=strdup($<simulateNode>-1.attribute);
	   char *pch;
	   pch=strtok($$,",");
	   if(pch!=NULL)
	   {
		if(!strcmp(pch,"real")&&!strcmp($1.type,"integer"))
		strcat(content,"i2f\n");
		else if(strcmp(pch,$1.type)!=0)
		{ semError=1;
		//Parameter mismatch
        printf("%d (☉ε　⊙ﾉ)ﾉ: Pet Face mismatch.\n", linenum);}
	   }
	  };
MORE_E: MORE_E ',' E
	{ 		
		$$=$1;
		char *pch=strtok($$,","); 
		if(pch!=NULL)
		{
		 if(!strcmp(pch,"real")&&!strcmp($3.type,"integer"))
		  strcat(content,"i2f\n");
		 else if(strcmp(pch,$3.type)!=0)
		 { semError=1;
             //Parameter mismatch
             printf("%d (☉ε　⊙ﾉ)ﾉ: Pet Face mismatch.\n", linenum);}
		}
	};
COND: KWif CONDBE KWthen CONDSTMT KWelse STMT KWend KWif
{
	strcat(content,$4);
	strcat(content,":\n");
};
CONDBE: '(' BE ')'
{
	if(!strcmp($2.type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy($$,L1);
};
CONDBE: BE
{
	if(!strcmp($1.type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy($$,L1);
};
CONDBE: '(' CPN ')'
{
	if(!strcmp($2.type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy($$,L1);
};
CONDBE: CPN
{
	if(!strcmp($1.type,"real"))
	strcat(content,"f2i\n");
	char L1[10];
	createLabel(L1);
	strcat(content,"ifeq ");
	strcat(content,L1);
	strcat(content,"\n");
	strcpy($$,L1);
};
CONDSTMT: STMT
{
	char L2[10];
	createLabel(L2);
	strcat(content,"goto ");
	strcat(content,L2);
	strcat(content,"\n");
	strcat(content,$<forLabel>-1);
	strcat(content,":\n");
	strcpy($$,L2);
};
COND: KWif CONDBE KWthen STMT KWend KWif
{
	strcat(content,$2);
	strcat(content,":\n");
};

WHILE: CONTROLWHILE CONDBE KWdo STMT KWend KWdo
{
	strcat(content,"goto ");
	strcat(content,$1);
	strcat(content,"\n");
	strcat(content,$2);
	strcat(content,":\n");
};
CONTROLWHILE: KWwhile
{
	char L1[10];
	createLabel(L1);
	strcat(content,L1);
	strcat(content,":\n");
	strcpy($$,L1);
};
FOR: FORINITIALIZE KWdo STMT KWend KWdo
	{
		if(fortop!=NULL)
		{
			Node *node=fortop->next;
			free(fortop);
			fortop=node;
		}
		loadVar($1.idname,"variable","integer","",1);
		strcat(content,"sipush 1\niadd\n");
		localStore($1.idname,"integer");
		strcat(content,"goto ");
		strcat(content,$1.back);
		strcat(content,"\n");
		strcat(content,$1.next);
		strcat(content,":\n");
		ltop=freeLocal(ltop);
	};
FORINITIALIZE: KWfor id assign Lint KWto Lint
	{
		if($4<0){ semError=1;
		//lower bound can not be negative
        printf("%d (งಠ_ಠ)ง: It’s too sad.\n", linenum);}
		if($6<0){ semError=1;
        //lower bound can not be negative
        printf("%d (งಠ_ಠ)ง: It’s too sad.\n", linenum);}
		if($6-$4<=0){ semError=1;
		//lower bound can not be bigger or equal than upper bound
        printf("%d (งಠ_ಠ)ง: You are sadder than happiness.\n", linenum);}
		if(lookupNode($2,fortop)==NULL)
		{	
			char num[10],num1[10];
			sprintf(num,"%d",$4);
			sprintf(num1,"%d",$6);

			fortop=addFromNode(fortop,$2,"","","",level);
			ltop=addBlock(ltop);
			ltop=addLocal(ltop,$2);
			strcat(content,"sipush ");
			strcat(content,num);
			strcat(content,"\n");
			localStore($2,"integer");
			char L1[10],L2[10];
			createLabel(L1);
			createLabel(L2);
			strcat(content,L1);
			strcat(content,":\n");
			strcat(content,"sipush ");
			strcat(content,num1);
			strcat(content,"\n");
			loadVar($2,"variable","integer","",1);
			strcat(content,"isub\n");
			strcat(content,"ifle ");
			strcat(content,L2);
			strcat(content,"\n");
			strcpy($$.back,L1);
			strcpy($$.next,L2);
			$$.idname=$2;			
		}
		else{ semError=1;
		//Variable has been assigned at the outer loop
        printf("%d ୧(๑•̀ᗝ•́)૭ : The cat is found elsewhere.\n", linenum);}
	};
RETURN: KWreturn E ';'
	{
		if(isFunc && funcname!=NULL)
		{
			char *returntype=$2.type;
			Node *node=LookupGlobal(funcname,top);
			if(strcmp(node->type,"void")==0){ semError=1;
			//Function type void does not need return statement
            printf("%d ヾ( ･`⌓´･)ﾉﾞ: How dare you give me that face! \n", linenum);}
			else if(!strcmp(node->type,"real") && !strcmp(returntype,"integer"))
			{
			  strcat(content,"i2f\n");
			  strcat(content,"freturn\n");
			}
			else if(strcmp(node->type,returntype)!=0){ semError=1;
                //Function type is different from the return type
            printf("%d (ﾉ｀Д´)ﾉ : Could you give me another breed?\n", linenum);}
			else
			{
			 if(!strcmp(returntype,"real"))
			  strcat(content,"freturn\n");
			 else
			  strcat(content,"ireturn\n");
			}
		}
		if(isMain){ semError=1;
		//Main function can not have return statement
        printf("%d ┗(｀ム´)=З : How dare you give me that face! \n", linenum);}
	};


%%





int yyerror( char *msg )
{
    fprintf( stderr, "\n|--------------------------------------------------------------------------\n" );
    fprintf( stderr, "（（（（（（BOMB）））））） ⌒⌒⌒⌒⌒／(x~x)＼ %d: %s\n", linenum, buf );
	fprintf( stderr, "|\n" );
	fprintf( stderr, "( ✖ ਊ ✖) %s\n", yytext );
        fprintf( stderr, "|--------------------------------------------------------------------------\n" );
        exit(-1);
}

int  main( int argc, char **argv )
{
	
	if( argc != 2 ) {
		fprintf(  stdout,  "Usage:  ./parser  [filename]\n"  );
		exit(0);
	}
	semError=0;
	ltop=createLocal();
	top=creates();
        fortop=createNode();
	char *buffer,*buffer2;
	labelNumber=0;
	buffer=(char*)malloc(sizeof(argv[1])-sizeof(char)*2);
	strncpy(buffer,argv[1],strlen(argv[1])-2);
	buffer2=strtok(buffer,"/");
	while(buffer2!=NULL)
	{
		strcpy(filename,buffer2);
		buffer2=strtok(NULL,"/");
	}

	FILE *fp = fopen( argv[1], "r" );
	
	if( fp == NULL )  {
		fprintf( stdout, "Open  file  error\n" );
		exit(-1);
	}

	yyin = fp;
	yyparse();
	if(!semError){
        FILE *fptr;
	strcat(filename,".j");
	fptr=fopen(filename,"w");
        fwrite(content,1,strlen(content),fptr);
	fclose(fptr);
	}
	exit(0);
}
