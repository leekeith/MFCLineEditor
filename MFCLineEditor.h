
// MFCLineEditor.h : main header file for the MFCLineEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCLineEditorApp:
// See MFCLineEditor.cpp for the implementation of this class
//

class CMFCLineEditorApp : public CWinApp
{
public:
	CMFCLineEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCLineEditorApp theApp;
