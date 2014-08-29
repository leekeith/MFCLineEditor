
// MFCLineEditorView.h : interface of the CMFCLineEditorView class
//

#pragma once


class CMFCLineEditorView : public CFormView
{
protected: // create from serialization only
	CMFCLineEditorView();
	DECLARE_DYNCREATE(CMFCLineEditorView)

// Attributes
public:
	CMFCLineEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	enum{IDD=IDD_GRAPHVIEW};
	CNTGraph m_graph;
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnInitialUpdate();
	afx_msg void OnClickNext();
	afx_msg void OnClickPrev();
	afx_msg void OnClickAdd();
protected:

// Implementation
public:
	virtual ~CMFCLineEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_viewIndex;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPrev();
	afx_msg void OnClickGoto();
};

#ifndef _DEBUG  // debug version in MFCLineEditorView.cpp
inline CMFCLineEditorDoc* CMFCLineEditorView::GetDocument() const
   { return reinterpret_cast<CMFCLineEditorDoc*>(m_pDocument); }
#endif

