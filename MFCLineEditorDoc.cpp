
// MFCLineEditorDoc.cpp : implementation of the CMFCLineEditorDoc class
//

#include "stdafx.h"
extern Table g_table;
#include<string>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCLineEditor.h"
#endif

#include "MFCLineEditorDoc.h"

#include <propkey.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCLineEditorDoc

IMPLEMENT_DYNCREATE(CMFCLineEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCLineEditorDoc, CDocument)
END_MESSAGE_MAP()


// CMFCLineEditorDoc construction/destruction

CMFCLineEditorDoc::CMFCLineEditorDoc()
{
	// TODO: add one-time construction code here

}

CMFCLineEditorDoc::~CMFCLineEditorDoc()
{
}

BOOL CMFCLineEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCLineEditorDoc serialization

void CMFCLineEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		/*
		DataPoint d;
		d.addElement(99.9);
		d.addElement(88.8);
		g_table.setDataPoint(0,d);
		
		if(g_table.saveTable(ar, g_table.getPath()))
		{

			CSavedDlg dlg;
			dlg.DoModal();
		}
		else
		{
			CSaveFailDlg dlg;
			dlg.DoModal();
		}
		*/// TODO: add storing code here
		ar.Close();
	}
	else
	{
		/*/ TODO: add loading code here
		char temp[MAX_PATH];
		int i=0;
		WideCharToMultiByte(CP_ACP, 0,ar.GetFile()->GetFilePath().GetBuffer(),-1,temp,MAX_PATH,NULL,NULL);
		while(temp[i]>0)i++;
		temp[i]=0;
		string val(temp);
		g_table.initialize(val);
		*/
	}
}


BOOL CMFCLineEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	char temp[MAX_PATH];
	int i=0;
	WideCharToMultiByte(CP_ACP, 0,lpszPathName,-1,temp,MAX_PATH,NULL,NULL);
	while(temp[i]>0)i++;
	temp[i]=0;
	string val(temp);
	bool ret=g_table.initialize(val);
	if(!ret)
	{
		CSaveFailDlg dlg;
		dlg.DoModal();
		
	}
	return ret;
}
BOOL CMFCLineEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if(g_table.saveTable())
	{
		CSavedDlg dlg;
		dlg.DoModal();
		return true;
	}
	else
	{
		CSaveFailDlg dlg;
		dlg.DoModal();
		return false;
	}

}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCLineEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCLineEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCLineEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCLineEditorDoc diagnostics

#ifdef _DEBUG
void CMFCLineEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCLineEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCLineEditorDoc commands
