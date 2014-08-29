// SavedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCLineEditor.h"
#include "SavedDlg.h"
#include "afxdialogex.h"


// CSavedDlg dialog

IMPLEMENT_DYNAMIC(CSavedDlg, CDialogEx)

CSavedDlg::CSavedDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSavedDlg::IDD, pParent)
{

}

CSavedDlg::~CSavedDlg()
{
}

void CSavedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSavedDlg, CDialogEx)
END_MESSAGE_MAP()


// CSavedDlg message handlers

IMPLEMENT_DYNAMIC(CSaveFailDlg, CDialogEx)

CSaveFailDlg::CSaveFailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveFailDlg::IDD, pParent)
{

}

CSaveFailDlg::~CSaveFailDlg()
{
}

void CSaveFailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveFailDlg, CDialogEx)
END_MESSAGE_MAP()
