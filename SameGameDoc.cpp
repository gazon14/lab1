﻿ 
 

#include "stdafx.h"
 
 
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 

IMPLEMENT_DYNCREATE(CSameGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CSameGameDoc, CDocument)
END_MESSAGE_MAP()


 

CSameGameDoc::CSameGameDoc() noexcept
{
	 
	m_board = new CSameGameBoard();
	


	 

}

CSameGameDoc::~CSameGameDoc()
{
	 
	delete m_board;
	 
	ClearUndo();
	 
	ClearRedo();

}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	 
	m_board->SetupBoard();

	 
	ClearUndo();
	ClearRedo();

	 
	 

	return TRUE;
}

void CSameGameDoc::SetNumColors(int nColors)
{
	 
	m_board->SetNumColors(nColors);
	 
	m_board->SetupBoard();
}

int CSameGameDoc::DeleteBlocks(int row, int col)
{
	 
	m_undo.push(new CSameGameBoard(*m_board));
	 
	ClearRedo();
	 
	int blocks = m_board->DeleteBlocks(row, col);
	 
	if (m_board->IsGameOver())
		ClearUndo();
	 
	return blocks;
}

void CSameGameDoc::UndoLast()
{
	 
	if (m_undo.empty())
		return;
	 
	m_redo.push(m_board);
	 
	m_board = m_undo.top();
	m_undo.pop();
}

bool CSameGameDoc::CanUndo()
{
	 
	return !m_undo.empty();
}

void CSameGameDoc::RedoLast()
{
	 
	if (m_redo.empty())
		return;
	 
	m_undo.push(m_board);
	 
	m_board = m_redo.top();
	m_redo.pop();
}

bool CSameGameDoc::CanRedo()
{
	 
	return !m_redo.empty();
}

void CSameGameDoc::ClearUndo()
{
	 
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CSameGameDoc::ClearRedo()
{
	 
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}







 

void CSameGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		 
	}
	else
	{
		 
	}
}

#ifdef SHARED_HANDLERS

 
void CSameGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	 
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

 
void CSameGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	 
	 

	 
	SetSearchContent(strSearchContent);
}

void CSameGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif  

 

#ifdef _DEBUG
void CSameGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSameGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif  


 
