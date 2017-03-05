/**
 * Introduction to Compiler Design by Prof. Yi Ping You
 * Prjoect 3 main function
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "symtab.h"

extern int yydebug;	/* declared by yacc */

extern int yyparse();	/* declared by yacc */
extern FILE* yyin;	/* declared by lex */

extern struct SymTable *symbolTable;
extern struct PType *funcReturn;
extern char fileName[256];
extern char output_fileName[256];

FILE* yyout;

int  main( int argc, char **argv )
{
	if( argc != 2 ) {
		fprintf(  stdout,  "Usage:  ./parser  [filename]\n"  );
		exit(0);
	}

	FILE *fp = fopen( argv[1], "r" );

	if( fp == NULL )  {
		fprintf( stdout, "Open  input file  error\n" );
		exit(-1);
	}

	// parse argv[1] and setup fileName
	const char* slashPos = strrchr(argv[1], '/');
	size_t fileNameLength;
	if( slashPos )
		strcpy(fileName, slashPos+1);
	else
		strcpy(fileName, argv[1]);
	fileNameLength = strlen(fileName);


	if( fileName[fileNameLength-2] != '.' || fileName[fileNameLength-1] != 'p' ) {
		fprintf( stdout, "input file: %s \tshould be [fileName].p \n", fileName );	
		exit(-1);
	}
	fileName[fileNameLength-2] = '\0';

	yyin = fp;

	// initial symbol table
	symbolTable = (struct SymTable *)malloc(sizeof(struct SymTable));
	initSymTab( symbolTable );

	// initial function return recoder

	yydebug = 0;

	//printf("!!!: %s\n",fileName);
	strcpy(output_fileName,fileName);
	strcat(output_fileName,".j");
	//printf("???: %s\n",output_fileName);


	FILE *fp_out = fopen( output_fileName, "w+t" );
	if( fp_out == NULL )  {
		fprintf( stdout, "Open  output file  error\n" );
		exit(-1);
	}

	yyout = fp_out;

	yyparse();	/* primary procedure of parser */

	fclose(fp);
	fclose(fp_out);

	exit(0);
}

