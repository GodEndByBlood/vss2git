// vss2git.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include "Stdafx.h"

#include "Functions/Processor.h"
#include "Functions/FileFunc.h"
#include "Functions/Config.h"

#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int main()
{
	RUN("COLOR 0A");

	printf("WARNING!!!\n");
	printf("\n");

	printf("1) These VSS environment variables must be set (eg.):\n");
	printf("    ssDir  = C:\\VSS\\MyVssDatabaseDir\n");
	printf("    ssUser = Admin\n");
	printf("    ssPwd  =\n");
	printf("\n");

	printf("   Currently:\n");
	printf("    ");
	RUN("SET ssDir");
	printf("    ");
	RUN("SET ssUser");
	printf("    ");
	RUN("SET ssPwd");
	printf("\n");

	printf("2) Your locale date-time should be in one of these formats\n");
	printf("   '2010.10.10 10:10'  '2010-10-10 10:10'\n");
	printf("\n");

	printf("3) Create file '%s' with date-time string (see above)\n", (LPCSTR)config::szFromDate);
	printf("   to import/append only from specified date (e.g. update imported database)\n");
	printf("\n");

	processor::Run();

	printf("\nDONE!   (press ENTER to exit)\n");
	getchar();
	return 0;
}
