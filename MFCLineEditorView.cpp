
// MFCLineEditorView.cpp : implementation of the CMFCLineEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCLineEditor.h"
#endif

#include "MFCLineEditorDoc.h"
#include "MFCLineEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLineEditorView

IMPLEMENT_DYNCREATE(CMFCLineEditorView, CFormView)

BEGIN_MESSAGE_MAP(CMFCLineEditorView, CFormView)
	ON_BN_CLICKED(IDC_PREV, &CMFCLineEditorView::OnClickPrev)
	ON_BN_CLICKED(IDC_NEXT, &CMFCLineEditorView::OnClickNext)
	ON_BN_CLICKED(IDC_ADD, &CMFCLineEditorView::OnClickAdd)
	ON_BN_CLICKED(IDC_GOTO_BTN, &CMFCLineEditorView::OnClickGoto)
END_MESSAGE_MAP()

// CMFCLineEditorView construction/destruction

CMFCLineEditorView::CMFCLineEditorView():CFormView(CMFCLineEditorView::IDD)
{
	// TODO: add construction code here
	m_viewIndex=0;
}
void CMFCLineEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
    
	m_graph.SetPlotAreaColor(RGB(0,0,0));
	m_graph.SetFrameStyle(1);
	m_graph.SetYGridNumber(1);
	ResizeParentToFit(FALSE);

}

CMFCLineEditorView::~CMFCLineEditorView()
{
}

BOOL CMFCLineEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCLineEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_NTGRAPHCTRL1,m_graph);
}


// CMFCLineEditorView drawing

void CMFCLineEditorView::OnDraw(CDC* /*pDC*/)
{
	CMFCLineEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int i,j;
	DataPoint dp;
	double xmax,xmin,ymax,ymin;
	xmax=xmin=ymax=ymin=0.0;
	
	if(g_table.isValidTable())
	{
		m_graph.ClearGraph();
		m_graph.SetXLabel((CString)g_table.getHeading(0).c_str());
		this->SetDlgItemTextW(IDC_VIEW_X_TITLE, (CString)g_table.getHeading(0).c_str());
		this->SetDlgItemTextW(IDC_ADD_X_TITLE, (CString)g_table.getHeading(0).c_str());
		m_graph.SetYLabel((CString)g_table.getHeading(1).c_str());
		this->SetDlgItemTextW(IDC_VIEW_Y_TITLE, (CString)g_table.getHeading(1).c_str());
		this->SetDlgItemTextW(IDC_ADD_Y_TITLE, (CString)g_table.getHeading(1).c_str());
		m_graph.SetElementLineColor(RGB(255,255,0));
		for(i=1;i<g_table.numElements();i++)
		{
			m_graph.AddElement();
		}
		for(i=0;i<g_table.numPoints();i++)
		{
			dp=g_table.getDataPoint(i);
			if(xmax<dp.getElement(0))
				xmax=dp.getElement(0);
			if(xmin>dp.getElement(0))
				xmin=dp.getElement(0);

			for(j=1;j<g_table.numElements();j++)
			{
				if(ymax<dp.getElement(j))
					ymax=dp.getElement(j);
				if(ymin>dp.getElement(j))
					ymin=dp.getElement(j);
				
				m_graph.PlotXY(dp.getElement(0),dp.getElement(j),j-1);
			}
		}
		
		m_graph.SetRange(xmin,xmax,ymin,ymax+10);
		dp=g_table.getDataPoint(m_viewIndex);
		this->SetDlgItemTextW(IDC_VIEW_X_VAL, (CString)to_string(dp.getElement(0)).c_str());
		this->SetDlgItemTextW(IDC_VIEW_Y_VAL, (CString)to_string(dp.getElement(1)).c_str());
		m_graph.SetElementLineColor(RGB(255,255,255));
		m_graph.PlotXY(dp.getElement(0),ymin,g_table.numElements()-1);
		m_graph.PlotXY(dp.getElement(0),ymax,g_table.numElements()-1);
		m_graph.SetYGridNumber(10);
		m_graph.SetShowGrid(TRUE);
		CString text(L"of ");
		text+=(CString)to_string(g_table.numPoints()).c_str();
		this->SetDlgItemTextW(IDC_TOTAL,text);
		text=(CString)to_string(m_viewIndex+1).c_str();
		this->SetDlgItemTextW(IDC_PROGRESS,text);
		ResizeParentToFit(FALSE);
		
	}
}




// CMFCLineEditorView diagnostics

#ifdef _DEBUG
void CMFCLineEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCLineEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCLineEditorDoc* CMFCLineEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCLineEditorDoc)));
	return (CMFCLineEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCLineEditorView message handlers


void CMFCLineEditorView::OnClickPrev()
{
	// TODO: Add your control notification handler code here
	
	if(m_viewIndex>0)
		m_viewIndex--;
	this->UpdateWindow();
}

void CMFCLineEditorView::OnClickNext()
{
	// TODO: Add your control notification handler code here
	if(m_viewIndex<g_table.numPoints()-1)
		m_viewIndex++;
	this->UpdateWindow();
}

BOOL pWcharIsFloat(WCHAR* text, int sz)
{
	for(int i=0;i<sz && text[i]!=0;i++)
	{
		if(IsCharAlpha(text[i]))
		{	
			if(text[i]!='.')
				return FALSE;
		}
	}
	return TRUE;
}
void CMFCLineEditorView::OnClickAdd()
{
	// TODO: Add your control notification handler code here
	DataPoint dp;
	WCHAR text[16];
	BOOL isFloat=TRUE;
	int i;
	int length=this->GetDlgItemTextW(IDC_EDIT_X_VAL,text,16);
	if(length>0 && pWcharIsFloat(text,16))
		dp.addElement(_wtof(text));
	else isFloat=FALSE;
	length=this->GetDlgItemTextW(IDC_ADD_Y_VAL,text,16);
	if(length>0 && pWcharIsFloat(text,16) && isFloat==TRUE)
	{
		for(i=1;i<g_table.numElements();i++)
			dp.addElement(_wtof(text));
		g_table.addDataPoint(dp);
		this->SetDlgItemTextW(IDC_EDIT_X_VAL,L"");
		this->SetDlgItemTextW(IDC_ADD_Y_VAL,L"");
	}
	

	
}


void CMFCLineEditorView::OnClickGoto()
{
	// TODO: Add your control notification handler code here
	WCHAR text[16];
	int val;
	int length=this->GetDlgItemTextW(IDC_GOTO_VAL,text,16);
	if(length>0)
	{
		val=this->GetDlgItemInt(IDC_GOTO_VAL,NULL,FALSE)-1;
		if(val<g_table.numPoints())
		{
			m_viewIndex=val;
			this->SetDlgItemTextW(IDC_GOTO_VAL,L"");
			this->UpdateWindow();
		}
	}

}
