#ifndef __Config_H__
#define __Config_H__
#pragma once


namespace config
{
	const LPCTSTR szEmail                = L"none@matrix-software.lt";
	const LPCTSTR szTimeZone             = L"+0200";
	const LPCTSTR szFromDate             = L"../tmp/FromDate.cfg";

	//see vss command line help on -I param
	//const LPCTSTR szVssGetQuestionAnswer = "";    //User must enter in console Y/N (recomended)
	const LPCTSTR szVssGetQuestionAnswer = L"-I-Y";  //Auto answer Y
	//const LPCTSTR szVssGetQuestionAnswer = "-I-"; //Auto answer N

	const LPCTSTR szTmpDir               = L"../tmp";
	const LPCTSTR szWorkingDir           = L"../tmp/Working";
	const LPCTSTR szDump                 = L"../tmp/dump.txt";
	const LPCTSTR szCounters             = L"../tmp/Counters.txt";
	
	const LPCTSTR szImportProgress       = L"../tmp/ImportProgress.txt";
	const LPCTSTR szImportProgress_D     = L"../tmp/D_ImportProgress.txt";

	//STEPS

	const LPCTSTR szStep1_VssDir         = L"../tmp/Step1_VssDir.txt";
	const LPCTSTR szStep2_Paths          = L"../tmp/Step2_Info.txt";
	const LPCTSTR szStep2_SkippedPaths   = L"../tmp/Step2_SkippedPaths.txt";
	const LPCTSTR szStep3_Grouped        = L"../tmp/Step3_Grouped.txt";
	const LPCTSTR szStep4_Import         = L"../tmp/Step4_Import.txt";

	const LPCTSTR szStep1_VssDir_D       = L"../tmp/D_Step1_VssDir.txt";
	const LPCTSTR szStep2_Paths_D        = L"../tmp/D_Step2_Info.txt";
	const LPCTSTR szStep2_SkippedPaths_D = L"../tmp/D_Step2_SkippedPaths.txt";
	const LPCTSTR szStep3_Grouped_D      = L"../tmp/D_Step3_Grouped.txt";
	const LPCTSTR szStep4_Import_D       = L"../tmp/D_Step4_Import.txt";
}




#endif //__Config_H__
