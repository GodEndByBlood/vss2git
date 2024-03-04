#include "../StdAfx.h"

#ifdef _GIT

#include "Dest.h"
#include "FileFunc.h"
#include "Config.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void destination::Create(LPCTSTR szOutputFile, LPCTSTR szWorkingDir, LPCTSTR szTime, LPCTSTR szUser, LPCTSTR szEmail, LPCTSTR szComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	if (!file::DoesFileExist(_T(".git")))
	{
		CString sOutputFile = szOutputFile;
		sOutputFile.Replace(L"../", L"../../"); //workaround

		//git init

		CString sCommand;
		sCommand.Format(L"git init >> %s", (LPCTSTR)sOutputFile);
		RUN(sCommand);

		sCommand.Format(L"ECHO. >> %s", (LPCTSTR)sOutputFile);
		RUN(sCommand);

		sCommand.Format(L"ECHO. >> %s", (LPCTSTR)sOutputFile);
		RUN(sCommand);

		//.gitignore

		CString sGitIgnore(szWorkingDir);
		sGitIgnore += "/.gitignore";
		::DeleteFile(sGitIgnore);
		RUN(FormatStr("ECHO *.scc>> %s", sGitIgnore));
		RUN(FormatStr("ECHO *.obj>> %s", sGitIgnore));

		destination::Commit(szOutputFile, szWorkingDir, szTime, szUser, szEmail, szComment);
	}

	SetCurrentDirectory(sOriginalDir);
}

void destination::Commit(LPCTSTR szOutputFile, LPCTSTR szWorkingDir, LPCTSTR szTime, LPCTSTR szUser, LPCTSTR szEmail, LPCTSTR szComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	CString sOutputFile = szOutputFile;
	sOutputFile.Replace(L"../", L"../../"); //workaround

	CString sCommand;
	sCommand.Format(L"git add -A >> %s", (LPCTSTR)sOutputFile);
	RUN(sCommand);

	sCommand.Format(L"git config user.name %s >> %s", szUser, (LPCTSTR)sOutputFile);
	RUN(sCommand);

	sCommand.Format(L"git config user.email %s >> %s", szEmail, (LPCTSTR)sOutputFile);
	RUN(sCommand);


	sCommand.Format(L"env GIT_AUTHOR_DATE=\"%s 0 %s\" git commit -m '%s' >> %s",
						szTime,
						config::szTimeZone,
						szComment,
						(LPCTSTR)sOutputFile);

	RUN(sCommand);

	SetCurrentDirectory(sOriginalDir);
}

void destination::GetLastComment(LPCTSTR szWorkingDir, CString &sComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	CString sOutputFile = config::szDump;
	sOutputFile.Replace(L"../", L"../../"); //workaround

	CString sCommand;
	sCommand.Format(L"git log -1 >> %s", (LPCTSTR)sOutputFile);
	RUN(sCommand);

	CStdioFile file;
	if (file.Open(sOutputFile, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		file.ReadString(sComment);
		file.ReadString(sComment);
		file.ReadString(sComment);
		file.ReadString(sComment);
		file.ReadString(sComment);
		sComment.TrimLeft();
		file.Close();
	}

	::DeleteFile(sOutputFile);

	SetCurrentDirectory(sOriginalDir);
}

LPCTSTR destination::GetCommentPrefix()
{
	return _T("vss2git");
}

#endif //_GIT


