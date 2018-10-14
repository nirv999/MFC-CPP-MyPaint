#include "stdafx.h"
#include "MyPaint.h"
#include "MyPaintDlg.h"
#include "MyShape.h"
#include "MyEllipse.h"
#include "MySquare.h"
#include "MyRectangle.h"
#include "MyLine.h"
#include "afxdialogex.h"
#include "AddCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CMyPaintDlg::CMyPaintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPaintDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyPaintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CMyPaintDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMyPaintDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMyPaintDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMyPaintDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMyPaintDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPaintDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPaintDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyPaintDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyPaintDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyPaintDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyPaintDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyPaintDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDOK, &CMyPaintDlg::OnBnClickedOk)
	//MOVEABLE shape func's:
	ON_BN_CLICKED(IDC_BUTTON9, &CMyPaintDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyPaintDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CMyPaintDlg message handlers

BOOL CMyPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	isPressed = false;
	ifSelected = false;
	static MyLineFactory lineFactory;
	factory = &lineFactory;

	backGroundColor = RGB(0, 100, 200);
	borderColor = RGB(200, 100, 0);
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPaintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CMyPaintDlg::OnPaint()
{

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i]->draw(dc);

		CDialogEx::OnPaint();
	}
}


HCURSOR CMyPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
		MyShape *s = factory->create();

		s->setBackGroundColor(backGroundColor);
		s->setBorderColor(borderColor);

		Command *command = new AddCommand(shapes, s);
		done.push(command);
		command->perform();

		s->setBegin(MyPoint(point.x, point.y));
		isPressed = true;
	
		CDialogEx::OnLButtonDown(nFlags, point);
}

void CMyPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	isPressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMyPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	if (isPressed)
	{
		shapes[shapes.size() - 1]->setEnd(MyPoint(point.x, point.y));
		Invalidate();
	}
	/*
	else if (ifSelected) {
		
		MyPoint oldEndPoint, oldBeginPoint;
		int jumpX, jumpY;
		//draw the tempShpae that erase in RBclick
		tempShape->draw(dc);
		beginMove = endMove;
		endMove = point;
		//init 
		oldEndPoint = tempShape->getEnd();
		oldBeginPoint = tempShape->getBegin();
		//calculte the gap
		jumpX = endMove.x - beginMove.x;
		jumpY = endMove.y - beginMove.y;
		//UPDATE new point location
		oldBeginPoint.addX(jumpX);
		oldBeginPoint.addY(jumpY);
		oldEndPoint.addX(jumpX);
		oldEndPoint.addY(jumpY);
		//UPDATE shape points
		tempShape->setBegin(oldBeginPoint);
		tempShape->setEnd(oldEndPoint);
		//draw currentShape for momvement
		tempShape->draw(dc);
	}*/
	
	

	CDialogEx::OnMouseMove(nFlags, point);
}

//Line
void CMyPaintDlg::OnBnClickedRadio1()
{
	static MyLineFactory lineFactory;
	factory = &lineFactory;
}

//Rectangle
void CMyPaintDlg::OnBnClickedRadio2()
{
	static MyRectangleFactory rectangleFactory;
	factory = &rectangleFactory;
}

//Ellipse
void CMyPaintDlg::OnBnClickedRadio3()
{
	static MyEllipseFactory ellipseFactory;
	factory = &ellipseFactory;
}

//Triangle
void CMyPaintDlg::OnBnClickedRadio4()
{
	static MyTriangleFactory TriangleFactory;
	factory = &TriangleFactory;
}

//Square 
void CMyPaintDlg::OnBnClickedRadio5()
{
	static MySquareFactory SquareFactory;
	factory = &SquareFactory;
}

//BackGround color
void CMyPaintDlg::OnBnClickedButton1()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		backGroundColor = dlg.GetColor();
	}
}

//Border color
void CMyPaintDlg::OnBnClickedButton2()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		borderColor = dlg.GetColor();
	}
}

// UNDO
void CMyPaintDlg::OnBnClickedButton3()
{
	if (done.empty())
		return;
	Command *command = done.top();
	done.pop();
	undone.push(command);
	command->rollback();
	Invalidate();
}

// UNDO ALL - meaning reset the pane
void CMyPaintDlg::OnBnClickedButton4()
{
	while(!done.empty())
	{
		OnBnClickedButton3();	
	}
	return;
	
}

// REDO
void CMyPaintDlg::OnBnClickedButton5()
{
	if (undone.empty())
		return;
	Command *command = undone.top();
	undone.pop();
	done.push(command);
	command->perform();
	Invalidate();	
}

// SAVE
void CMyPaintDlg::OnBnClickedButton6()
{
	CFile file(L"shapes.bin", CFile::modeCreate | CFile::modeWrite);
	CArchive archive(&file, CArchive::store);
	archive << shapes.size();
	for (int i = 0; i < shapes.size(); ++i)
		archive << shapes[i];
}



//LOAD
void CMyPaintDlg::OnBnClickedButton7()
{
	CFile file(L"shapes.bin", CFile::modeRead);
	CArchive archive(&file, CArchive::load);
	int count;
	archive >> count;
	for (int i = 0; i < count; ++i)
	{
		MyShape *s;
		archive >> s;
		shapes.push_back(s);
	}
	Invalidate();
}

void CMyPaintDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


//MOVEABLE shapes func not working

void CMyPaintDlg::OnBnClickedButton9()
{
	ifSelected = 0;
}

void CMyPaintDlg::OnBnClickedButton10()
{
	ifSelected = 1;
}
