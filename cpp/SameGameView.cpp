
 
 

#include "stdafx.h"
 
 
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "OptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


 

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()

	ON_COMMAND(ID_LEVEL_3COLORS, &CSameGameView::OnLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CSameGameView::OnLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CSameGameView::OnLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CSameGameView::OnLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CSameGameView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS,
		&CSameGameView::OnUpdateLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS,
		&CSameGameView::OnUpdateLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS,
		&CSameGameView::OnUpdateLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS,
		&CSameGameView::OnUpdateLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS,
		&CSameGameView::OnUpdateLevel7colors)

	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CSameGameView::OnSetupBlocksize)
	ON_UPDATE_COMMAND_UI(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnUpdateSetupBlockcount)
	ON_UPDATE_COMMAND_UI(ID_SETUP_BLOCKSIZE, &CSameGameView::OnUpdateSetupBlocksize)
	ON_COMMAND(ID_32771, &CSameGameView::On32771)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_32771, &CSameGameView::OnUpdate32771)
	
END_MESSAGE_MAP()

 

CSameGameView::CSameGameView() noexcept
{
	 

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	 
	 


	return CView::PreCreateWindow(cs);
}


 

void CSameGameView::OnDraw(CDC* pDC)  
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	int nDCSave = pDC->SaveDC();
	 
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	 
	pDC->FillSolidRect(&rcClient, clr);
	 
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	 
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			clr = pDoc->GetBoardSpace(row, col);
			 
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			 
			pDC->FillSolidRect(&rcBlock, clr);
			 
			pDC->Rectangle(&rcBlock);
		}
	}
	 
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}

 

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const  
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif  


 


void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	 
	int count = pDoc->DeleteBlocks(row, col);
	 
	if (count > 0)
	{
		 
		Invalidate();
		UpdateWindow();
		 
		if (pDoc->IsGameOver())
		{
			 
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("Нет доступных ходов\nКоличество оставшихся блоков: %d"),
				remaining);
			 
			MessageBox(message, _T("Игра Закончена"), MB_OK | MB_ICONINFORMATION);
		}
	}
	 

	CView::OnLButtonDown(nFlags, point);
}


void CSameGameView::OnInitialUpdate()
{
	
	
	CView::OnInitialUpdate();

	 
	ResizeWindow();

	 
}

void CSameGameView::ResizeWindow()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	 
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	 
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	 
	GetParentFrame()->MoveWindow(&rcWindow);
}


void CSameGameView::OnLevel3colors()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pDoc->SetNumColors(3);
	 
	Invalidate();
	UpdateWindow();

	 
}


void CSameGameView::OnUpdateLevel3colors(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);

	 
}


void CSameGameView::OnLevel4colors()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pDoc->SetNumColors(4);
	 
	Invalidate();
	UpdateWindow();

	 
}


void CSameGameView::OnUpdateLevel4colors(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
	 
}


void CSameGameView::OnLevel5colors()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pDoc->SetNumColors(5);
	 
	Invalidate();
	UpdateWindow();

	 
}


void CSameGameView::OnUpdateLevel5colors(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
	 
}


void CSameGameView::OnLevel6colors()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pDoc->SetNumColors(6);
	 
	Invalidate();
	UpdateWindow();

	 
}


void CSameGameView::OnUpdateLevel6colors(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
	 
}


void CSameGameView::OnLevel7colors()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pDoc->SetNumColors(7);
	 
	Invalidate();
	UpdateWindow();

	 
}


void CSameGameView::OnUpdateLevel7colors(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
	 
}


void CSameGameView::OnSetupBlockcount()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	COptionDialog dlg(true, this);
	 
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	 
	if (dlg.DoModal() == IDOK)
	{
		 
		pDoc->DeleteBoard();
		 
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		 
		pDoc->SetupBoard();
		 
		ResizeWindow();
	}
	 
}

void CSameGameView::OnSetupBlocksize()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	COptionDialog dlg(false, this);
	 
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	 
	if (dlg.DoModal() == IDOK)
	{
		 
		pDoc->DeleteBoard();
		 
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		 
		pDoc->SetupBoard();
		 
		ResizeWindow();
	}
	
}




void CSameGameView::OnUpdateSetupBlockcount(CCmdUI *pCmdUI)
{
	 
}


void CSameGameView::OnUpdateSetupBlocksize(CCmdUI *pCmdUI)
{
	 
}


void CSameGameView::OnEditUndo()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLast();
	 
	Invalidate();
	UpdateWindow();
}

void CSameGameView::On32771()
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();
	 
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->Enable(pDoc->CanUndo());
}

void CSameGameView::OnUpdate32771(CCmdUI *pCmdUI)
{
	 
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 
	pCmdUI->Enable(pDoc->CanRedo());
}