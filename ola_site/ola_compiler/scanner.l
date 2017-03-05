%{
#define LIST               strcat(buf, yytext)
#define tokenString(t)     {LIST; if (Opt_T) printf("<%s>\n", t);}
#define tokenChar(t)       {LIST; if (Opt_T) printf("<%c>\n", (t));}
#define tokenInteger(t, i) {LIST; if (Opt_T) printf("<%s: %d>\n", #t, (i));}
#define tokenId(t, s)  {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define MAX_LINE_LENG      256

#include "y.tab.h"
int Opt_S = 0;
int Opt_T = 0;
int Opt_D = 0;
int linenum = 1;
char buf[MAX_LINE_LENG];
char *pch;
%}

%Start comment mcomment
space [ \t]+
digit [0-9]

%%
{space} LIST;
<mcomment>\n {
          LIST;
          if (Opt_S)
            printf("%d: %s", linenum, buf);
          linenum++;
          buf[0] = '\0';
        }
<comment>\n  {
          LIST;
          if (Opt_S)
            printf("%d: %s", linenum, buf);
          linenum++;
          buf[0] = '\0';
	  BEGIN INITIAL;
        }
<INITIAL>\n      {
          LIST;
          if (Opt_S)
            printf("%d: %s", linenum, buf);
          linenum++;
          buf[0] = '\0';

        }

<INITIAL>\/\/     {LIST; BEGIN comment;}
<INITIAL>\/\/&S\+ {LIST; BEGIN comment;  Opt_S=1;}
<INITIAL>\/\/&S\- {LIST; BEGIN comment;  Opt_S=0;}
<INITIAL>\/\/&T\+ {LIST; BEGIN comment;  Opt_T=1;}
<INITIAL>\/\/&T\- {LIST; BEGIN comment;  Opt_T=0;}
<INITIAL>\/\/&D\+ {LIST; BEGIN comment;  Opt_D=1;}
<INITIAL>\/\/&D\- {LIST; BEGIN comment;  Opt_D=0;}
<INITIAL>\/\*     {LIST; BEGIN mcomment;}
<comment>.*       {LIST;}

<mcomment>.*\*\/    {LIST;
		  BEGIN INITIAL;}
<mcomment>.*   {LIST;}

<INITIAL>0|[1-9]{digit}* { yylval.num=atoi(yytext);  tokenId(integer,yytext); return Lint;}
<INITIAL>0[0-7]* tokenId(oct_integer,yytext);
<INITIAL>{digit}+\.{digit}+ { yylval.idname=strdup(yytext); tokenId(float,yytext); return Lreal;}
<INITIAL>\".*\"  {
			LIST;
			char *tmp=strdup(yytext);
			pch=strtok(yytext,"\"");
			if(Opt_T)
				printf("<string: %s>\n",pch);
			yylval.idname=tmp;
			return Lstring;
			}

<INITIAL>"ゝ"     {tokenChar(','); return ',';}
<INITIAL>"ʖ"     {tokenChar(';'); return ';';}
<INITIAL>"つ"     {tokenChar(':'); return ':';}

<INITIAL>"ᖘ"     { tokenChar('('); return '(';}
<INITIAL>"ᖗ"     {tokenChar(')'); return ')';}
<INITIAL>"ᕦ"     {tokenChar('['); return '[';}
<INITIAL>"ᕥ"     {tokenChar(']'); return ']';}

<INITIAL>"┏(＾0＾)┛"	{tokenChar('+'); return '+';}
<INITIAL>"┗(＾0＾)┓"	{tokenChar('-'); return '-';}
<INITIAL>"└|∵┌|"	{tokenChar('*'); return '*';}
<INITIAL>"|┐∵|┘"	{tokenChar('/'); return '/';}
<INITIAL>"┌|*ﾟ-ﾟ|┘"	{tokenString("mod"); return mod;}

<INITIAL>"☜( ﾟ∀ﾟ☜)"	{tokenString(":="); return assign;}
<INITIAL>"(‘▿’ʃʃ"	{tokenChar('<'); return '<';}
<INITIAL>"ᕙ། – ڡ – །─∈"	{tokenString("<="); return lte;}
<INITIAL>"ᕙ། – ڡ – །ᕗ"	{tokenString("<>"); return gl;}
<INITIAL>"3-། – ڡ – །ᕗ"	{tokenString(">="); return gte;}
<INITIAL>"ƪƪ’▿’)"	{tokenChar('>'); return '>';}
<INITIAL>"(๑￫‿￩๑)"	{tokenChar('='); return '=';}

<INITIAL>"‹(⁽˙́ʷ˙̀⁾ )∨( ⁽˙́ʷ˙̀⁾)›"	{tokenString("and"); return and;}
<INITIAL>"(v〃∇〃)ﾊ(〃∇〃v)"	{tokenString("or"); return or;}
<INITIAL>"⁄(⁄ ⁄•⁄-⁄•⁄ ⁄)⁄"	{tokenString("not");return not;}

<INITIAL>"(=ↀωↀ=)"   {  tokenString("KWvar"); return KWvar;}
<INITIAL>"⊂((υ⊥υ))⊃" {yylval.idname=strdup(yytext); tokenString("KWinteger"); return KWinteger;}
<INITIAL>"( ´(00)`)"    {yylval.idname=strdup(yytext); tokenString("KWreal"); return KWreal;}
<INITIAL>"／(≡・ x ・≡)＼"  {yylval.idname=strdup(yytext); tokenString("KWboolean"); return KWboolean;}
<INITIAL>"ʕ•ᴥ•ʔ"  {yylval.idname=strdup(yytext); tokenString("KWstring"); return KWstring;}
<INITIAL>"<º))))><"   {yylval.idname=strdup(yytext); tokenString("KWarray"); return KWarray;}


<INITIAL>"(´･ω･)o━━"   {tokenString("KWbegin"); return KWbegin;}
<INITIAL>"━━o(･ω･｀)"     {tokenString("KWend"); return KWend;}

<INITIAL>"ಠ_ಠ"   {tokenString("KWprint"); return KWprint;}
<INITIAL>"｡◕‿◕｡"    {tokenString("KWread"); return KWread;}
<INITIAL>"(⊃‿⊂)"  { yylval.idname=strdup(yytext); tokenString("KWreturn"); return KWreturn;} 
<INITIAL>"(｢･ω･)｢"   {tokenString("KWwhile"); return KWwhile;}
<INITIAL>"◉_◉"       {tokenString("KWdo"); return KWdo;} 


<INITIAL>"ಠ‿↼"     {tokenString("KWfor"); return KWfor;} 
<INITIAL>"ʘ‿ʘ"      {tokenString("KWif"); return KWif;}
<INITIAL>"⚆ _ ⚆"    {tokenString("KWelse"); return KWelse;}
<INITIAL>"¬_¬"      {tokenString("KWof"); return KWof;}
<INITIAL>"ರ_ರ"    {tokenString("KWthen"); return KWthen;}
<INITIAL>"◔ ⌣ ◔"      {tokenString("KWto"); return KWto;} 

<INITIAL>"(T＿T)"    {yylval.idname=strdup(yytext); tokenString("KWtrue"); return KWtrue;} 
<INITIAL>"(┬(●●)┬ )"   {yylval.idname=strdup(yytext); tokenString("KWfalse");return KWfalse;} 
<INITIAL>[a-zA-Z][a-zA-Z0-9]* { yylval.idname=strdup(yytext); tokenId(id,yytext); return id;}



%%
int mainLex( int argc, char **argv )
{
  if( argc != 2 ) {
    fprintf( stderr, "Usage: ./scanner [filename]\n" );
    exit(0);
  }
	
  FILE *fp = fopen( argv[1], "r" );
  if( fp == NULL ) {
    fprintf( stderr, "Open file error\n" );
    exit(-1);
  }
	
  yyin = fp;

  yylex();

  exit(0);
}
