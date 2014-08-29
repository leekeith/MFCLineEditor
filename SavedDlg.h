#pragma once
#include "resource.h"

// CSavedDlg dialog

class CSavedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSavedDlg)

public:
	CSavedDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSavedDlg();

// Dialog Data
	enum { IDD = IDD_SAVED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

class CSaveFailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveFailDlg)

public:
	CSaveFailDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveFailDlg();

// Dialog Data
	enum { IDD = IDD_SAVEFAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
