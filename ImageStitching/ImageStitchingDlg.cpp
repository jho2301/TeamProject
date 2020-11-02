
// ImageStitchingDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImageStitching.h"
#include "ImageStitchingDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageStitchingDlg ��ȭ ����



CImageStitchingDlg::CImageStitchingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGESTITCHING_DIALOG, pParent)
	, m_radio_resolution(0)
	, m_radio_calibration(0)
	, m_radio_interpolation(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageStitchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_RESOLUTION_INPUTIMAGE1, m_radio_resolution);
	DDX_Radio(pDX, IDC_RADIO_CALIBRATION_INPUTIMAGE1, m_radio_calibration);
	DDX_Radio(pDX, IDC_RADIO_INTERPOLATION_BILINEAR, m_radio_interpolation);
	DDX_Control(pDX, IDC_EDIT_INPUTIMAGE1, Edit_File_Inputimage1);
	DDX_Control(pDX, IDC_EDIT_INPUTIMAGE2, Edit_File_Inputimage2);
}

BEGIN_MESSAGE_MAP(CImageStitchingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CImageStitchingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CImageStitchingDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_RESOLUTION_INPUTIMAGE1, IDC_RADIO_RESOLUTION_INPUTIMAGE2, OnClickedRadioResolution)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_CALIBRATION_INPUTIMAGE1, IDC_RADIO_CALIBRATION_OFF, OnClickedRadioCalibration)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_INTERPOLATION_BILINEAR, IDC_RADIO_INTERPOLATION_B_SPLINE, OnClickedRadioInterpolation)
	ON_BN_CLICKED(IDC_OPENBUTTON1, &CImageStitchingDlg::OnBnClickedOpenbutton1)
	ON_BN_CLICKED(IDC_OPENBUTTON2, &CImageStitchingDlg::OnBnClickedOpenbutton2)
END_MESSAGE_MAP()


// CImageStitchingDlg �޽��� ó����

BOOL CImageStitchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CImageStitchingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CImageStitchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CImageStitchingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageStitchingDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void CImageStitchingDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CImageStitchingDlg::OnClickedRadioResolution(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_resolution)
	{
	case 0:	// Input Image 1
		break;
	case 1: // Input Image 2
		break;
	}
}

void CImageStitchingDlg::OnClickedRadioCalibration(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_calibration)
	{
	case 0: // Input Image 1
		break;
	case 1: // Input Image 2
		break;
	case 2: // Average
		break;
	case 3: // OFF
		break;
	}
}

void CImageStitchingDlg::OnClickedRadioInterpolation(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_interpolation)
	{
	case 0: // Bilinear Interpolation
		break;
	case 1: // Bicubic Interpolation
		break;
	case 2: // B-Spline Interpolation
		break;

	}
}

void CImageStitchingDlg::OnBnClickedOpenbutton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = " All Files(*.*)|*.*|";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);

	if (IDOK == dlg.DoModal())

	{

		// �̹��� ��� ȹ��

		CString img_path = dlg.GetPathName();

		// Image Path �ֱ�

		Edit_File_Inputimage1.SetWindowTextA(dlg.GetFileTitle());

		// IplImage�� �о����

		IplImage* input_img = cvLoadImage((LPSTR)(LPCSTR)img_path);

		// ȭ�� ���

		cvShowImage("Input Image 1", input_img);

	}
}


void CImageStitchingDlg::OnBnClickedOpenbutton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = " All Files(*.*)|*.*|";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);

	if (IDOK == dlg.DoModal())

	{

		// �̹��� ��� ȹ��

		CString img_path = dlg.GetPathName();

		// Image Path �ֱ�

		Edit_File_Inputimage2.SetWindowTextA(dlg.GetFileTitle());

		// IplImage�� �о����

		IplImage* input_img = cvLoadImage((LPSTR)(LPCSTR)img_path);

		// ȭ�� ���

		cvShowImage("Input Image 2", input_img);
	}
}