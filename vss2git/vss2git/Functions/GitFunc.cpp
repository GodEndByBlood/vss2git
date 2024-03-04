#include "../StdAfx.h"
#include "GitFunc.h"

#include "FileFunc.h"
#include "Config.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void git::Create(LPCTSTR szOutputFile, LPCTSTR szWorkingDir, LPCTSTR szTime, LPCTSTR szUser, LPCTSTR szEmail, LPCTSTR szComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	if (!file::DoesFileExist(L".git"))
	{
		CString sOutputFile = szOutputFile;
		sOutputFile.Replace(L"../", L"../../"); //workaround

		CString sCommand;
		sCommand.Format(L"git init >> %s", sOutputFile.GetString());
		RUN(sCommand);

		sCommand.Format(L"ECHO. >> %s", sOutputFile.GetString());
		RUN(sCommand);

		sCommand.Format(L"ECHO. >> %s", sOutputFile.GetString());
		RUN(sCommand);

		git::Commit(szOutputFile, szWorkingDir, szTime, szUser, szEmail, szComment);
	}

	SetCurrentDirectory(sOriginalDir);
}

void git::Commit(LPCTSTR szOutputFile, LPCTSTR szWorkingDir, LPCTSTR szTime, LPCTSTR szUser, LPCTSTR szEmail, LPCTSTR szComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	CString sOutputFile = szOutputFile;
	sOutputFile.Replace(L"../", L"../../"); //workaround

	CString sCommand;
	sCommand.Format(L"git add -A >> %s", sOutputFile.GetString());
	RUN(sCommand);

	sCommand.Format(L"git config user.name %s >> %s", szUser, sOutputFile.GetString());
	RUN(sCommand);

	sCommand.Format(L"git config user.email %s >> %s", szEmail, sOutputFile.GetString());
	RUN(sCommand);


	sCommand.Format(L"env GIT_AUTHOR_DATE=\"%s 0 %s\" git commit -m '%s' >> %s",
						szTime,
						config::szTimeZone,
						szComment,
						sOutputFile.GetString());

	RUN(sCommand);

	SetCurrentDirectory(sOriginalDir);
}

void git::GetLastComment(LPCTSTR szWorkingDir, CString &sComment)
{
	CString sOriginalDir;
	GetCurrentDirectory(2000, sOriginalDir.GetBufferSetLength(2000));
	SetCurrentDirectory(szWorkingDir);
	
	CString sOutputFile = config::szDump;
	sOutputFile.Replace(L"../", L"../../"); //workaround

	CString sCommand;
	sCommand.Format(L"git log -1 >> %s", sOutputFile.GetString());
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

//	sComment = "vss2git: 12345";

	::DeleteFile(sOutputFile);

	SetCurrentDirectory(sOriginalDir);
}