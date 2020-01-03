
// MyAppDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "afxdialogex.h"
#include "MyBusDll.h"
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#define SW_X        30    // ���� ����� X�� ��ǥ
#define SW_Y       200    // ���� ����� Y�� ��ǥ
#define SW_RADIUS   30    // �׸��� �Ѻ� ����
#define SW_DISTANCE 50    // �׸�� �׸� ������ �Ÿ�
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMyAppDlg ��ȭ ����



CMyAppDlg::CMyAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAppDlg::IDD, pParent)
	, m_bConnected(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_COMM_CONFIG, &CMyAppDlg::OnBnClickedBtnCommConfig)
	ON_BN_CLICKED(IDC_BTN_COMM_OPEN_CLOSE, &CMyAppDlg::OnBnClickedBtnCommOpenClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GAME, &CMyAppDlg::OnBnClickedButtonGame)
	ON_BN_CLICKED(IDC_BUTTON_GAME2, &CMyAppDlg::OnBnClickedButtonGame2)
	ON_BN_CLICKED(IDC_BUTTON_GAME3, &CMyAppDlg::OnBnClickedButtonGame3)
	ON_MESSAGE(WM_MYBUS_SWITCH_UPDATE, &CMyAppDlg::OnMyBusSwitchUpdate)
END_MESSAGE_MAP()


// CMyAppDlg �޽��� ó����

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_bConnected = FALSE;
	m_hComm = NULL;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMyAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyAppDlg::OnPaint()
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
		//�׸� ���� 9�� �׸���
		CPaintDC dc(this);
		for (int i = 0; i < 9; i++) {
			DrawSwitch(&dc, i, 0);
		}
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CallCommSetDlg();
}

bool gamestatus = false;

void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�
  CString str;			// ��ſ��� ����ǥ�ÿ� ���ڿ�
  char cParity;			// �и�Ƽ ǥ�ÿ� ���ں���
  char* cStopBits;	// Stop bit ǥ�ÿ� ���ڿ� ������
  CommConfigData *pCommCfg = new CommConfigData;

// �����Ʈ ���Ῡ�� Ȯ��
  if(!m_bConnected){
    GetCommCfgData(pCommCfg);
    pCommCfg->hOwner = m_hWnd;
	// ��� ��Ʈ ����
    if((m_hComm=CommOpen(*pCommCfg)) != NULL){
       m_bConnected = TRUE;

       if(pCommCfg->Parity == EVENPARITY) cParity = 'E';
       else if(pCommCfg->Parity == ODDPARITY) cParity = 'O';
       else cParity = 'N';

       if(pCommCfg->StopBits == TWOSTOPBITS) cStopBits = "2";
       else if(pCommCfg->StopBits == ONE5STOPBITS) cStopBits = "1.5";
       else cStopBits = "1";

       //str.Format(_T("COM%d,%d,%c,%d,%s"), pCommCfg->PortNum,
       //   pCommCfg->BaudRate,cParity,pCommCfg->ByteSize,cStopBits);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("���� ���� �Ϸ�"));
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("���� ����"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);

	   Send(0x06, VC_PIN_EVENT_MASK, 0, 0x00); //����ġ ��Ȱ��ȭ
	   Send(0x06, 0x31, 0, 0x00); //1000�� �ڸ� ��Ȱ��ȭ
	   Send(0x06, 0x32, 0, 0x00); //100�� �ڸ� ��Ȱ��ȭ
	   Send(0x06, 0x33, 0, 0x00); //10�� �ڸ� ��Ȱ��ȭ
	   Send(0x06, 0x34, 0, 0x3f); //1�� �ڸ��� 0 ���
    }
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }
  // �����Ʈ ��������
 else{
	  // Mode ���� �ʱ�ȭ
	  GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("Easy Mode"));
	  GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("Normal Mode"));
	  GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("Hard Mode"));

	  CClientDC dc(this);
	  // Display ��� ǥ�� ���� + ��� LED OFF
	  for (int i = 0; i < 9; i++) {
		  DrawSwitch(&dc, i, 0);
		  Send(0x05, VC_PORTA, i, 0x00);
	  }
	  Send(0x06, 0x53, 0x00, 000); // RGB ��Ȱ��ȭ
	  Send(0x06, VC_PIEZO_ENABLE, 0, 0); // �ǿ��� ��Ȱ��ȭ
	  Send(0x06, VC_FND, 0, 0); // FND -> 0000
	  gamestatus = false;
     
	 CommClose();
     m_bConnected = FALSE;
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("���� ���� ����"));
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("���� ����"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);

  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bConnected){
		CommClose();
	}

	CDialogEx::OnClose();
}


VOID CMyAppDlg::Send(int fun, int add, int hd, int ld)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	_MyBusFrame Q;
	if (m_bConnected == FALSE) return;

	Q.ui8Func = fun;
	Q.ui8Addr = add;
	Q.ui8DataH = hd;
	Q.ui8DataL = ld;
	MyBusSendFrame(&Q);
	return VOID();
}


CString input; //�Է��� ����
CString answer; //���� ����
int input_cnt = 0; //�Է��� ���� ����
int delay = 0; //���� ���̵��� �������� LED ON/OFF������ �ð� ����

//���� ���� �� �غ�
void CMyAppDlg::StageReady()
{
	input = ""; // �Է°� �ʱ�ȭ
	input_cnt = 0; //�Է��� ���� ���� �ʱ�ȭ
	Send(0x06, 0x53, 0x00, 0xff); // RGB Ȱ��ȭ
	Send(0x06, VC_PIEZO_ENABLE, 0, 1); // �ǿ��� Ȱ��ȭ
	Send(0x06, VC_PIN_EVENT_MASK, 0, 0x00); // ���� ������ ����ġ ��Ȱ��ȭ
	gamestatus = true;
	Send(0x06, 0x34, 0, 0x4f); // FND 3
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // �� -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x5b); // FND 2
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // �� -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x06); // FND 1
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // �� -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x3f); // FND 0
	Send(0x06, VC_PIEZO_TONE, 36 & 0x0fff, ((100 / 100) & 0x000f) << 12); // �� !
}

//Easy Mode
void CMyAppDlg::OnBnClickedButtonGame()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 400; // LED ON/OFF ���� �ð� ���� -> ���̵��� ��������
		GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("In Game")); // Display�� ���������� ǥ��
		StageReady(); // ���� ���� ī��Ʈ
		StageStart(); // ���� ����
	}
}

//Normal Mode
void CMyAppDlg::OnBnClickedButtonGame2()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 200; // LED ON/OFF ���� �ð� ���� -> ���̵��� ��������
		GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("In Game")); // Display�� ���������� ǥ��
		StageReady(); // ���� ���� ī��Ʈ
		StageStart(); // ���� ����
	}
}

//Hard Mode
void CMyAppDlg::OnBnClickedButtonGame3()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 100; // LED ON/OFF ���� �ð� ���� -> ���̵��� ��������
		GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("In Game")); // Display�� ���������� ǥ��
		StageReady(); // ���� ���� ī��Ʈ
		StageStart(); // ���� ����
	}
}


// �߻��� ������ ���� LED�� ���� delay�� �������� ON/OFF
void CMyAppDlg::LED_OnOff(CString num)
{
	//LED ON
	Send(0x05, VC_PORTA, _ttoi(num) - 1, 0xff);
	Send(0x05, VC_PORTA, _ttoi(num) - 2, 0xff);
	Sleep(delay);
	//LED OFF
	Send(0x05, VC_PORTA, _ttoi(num) - 1, 0x00);
	Send(0x05, VC_PORTA, _ttoi(num) - 2, 0x00);
	Sleep(delay);
}

//���� ����
void CMyAppDlg::StageStart()
{	
	srand((unsigned int)time(0));
	//8�ڸ� ���� �߻�
	CString str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num1 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num2 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num3 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num4 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num5 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num6 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num7 = str;
	str.Format(_T("%d"), (rand() % 4 + 1) * 2);
	CString num8 = str;

	answer = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8; // ����
	
	//���� ����
	Sleep(1000);
	LED_OnOff(num1);
	LED_OnOff(num2);
	LED_OnOff(num3);
	LED_OnOff(num4);
	LED_OnOff(num5);
	LED_OnOff(num6);
	LED_OnOff(num7);
	LED_OnOff(num8);

	Send(0x06, VC_PIN_EVENT_MASK, 0, 0x10); // ������ �Է��� ����ġ Ȱ��ȭ
	Send(0x06, 0x50, 0x00, 0xff); // �����Է°����� �˸��� RGB �Ķ��� ON
}


//Display�� 9���� �׸� ǥ�� �� ��Ȳ�� �� ��ȭ ����
void CMyAppDlg::DrawSwitch(CDC* pDC, UINT nSW, int ok)
{
	CPen Pen;
	CPen *oldPen;
	CBrush Brush;
	CBrush *oldBrush;
	if (nSW < 9) { 
		Pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		if (ok == 0) {
			Brush.CreateSolidBrush(pDC->GetBkColor()); // ������
		}
		else if (ok == 1) {
			Brush.CreateSolidBrush(RGB(0, 255, 0));  // ���
		}
		else if (ok == 2){
			Brush.CreateSolidBrush(RGB(255, 0, 0));  // ������
		}

		oldPen = pDC->SelectObject(&Pen);
		oldBrush = pDC->SelectObject(&Brush);

		pDC->Rectangle(SW_X + nSW * SW_DISTANCE, SW_Y,
			SW_X + nSW * SW_DISTANCE + SW_RADIUS, SW_Y + SW_RADIUS);

		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
	}

}


//����ġ �Է� ��ȯ
afx_msg LRESULT CMyAppDlg::OnMyBusSwitchUpdate(WPARAM wParam, LPARAM lParam)
{
	long i = lParam & 0xff;
	CString p;
	CClientDC dc(this);
	switch (i) {
	case 0x7f:  // ù��° ����ġ 0111 1111
		if(input.GetLength() < 8) input += "8";
		if(input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display�� ����ġ �Է� ǥ��
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // �Է� ����ŭ LED ǥ��
		input_cnt++; // �Է� �� +
		break;
	case 0xbf:   // �ι��� ����ġ 1011 1111
		if (input.GetLength() < 8) input += "6";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display�� ����ġ �Է� ǥ��
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // �Է� ����ŭ LED ǥ��
		input_cnt++; // �Է� �� +
		break;
	case 0xdf:   // ����° ����ġ  1101 1111
		if (input.GetLength() < 8) input += "4";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display�� ����ġ �Է� ǥ��
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // �Է� ����ŭ LED ǥ��
		input_cnt++; // �Է� �� +
		break;
	case 0xef:	// �׹�° ����ġ 1110 1111
		if (input.GetLength() < 8) input += "2";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display�� ����ġ �Է� ǥ��
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // �Է� ����ŭ LED ǥ��
		input_cnt++; // �Է� �� +
		break;
	}
	// ������ ���� �Է����� ��� �ڵ� ���� ����
	if (input_cnt == 8) {
		Sleep(500);
		submit();
	}
	return afx_msg LRESULT();
}


//���� ����
void CMyAppDlg::submit()
{
	Send(0x06, 0x50, 0x00, 0x00); // �Ķ��� OFF
	CClientDC dc(this);
	// Display ��� ǥ�� ���� + ��� LED OFF
	for (int i = 0; i < 9; i++) {
		DrawSwitch(&dc, i, 0);
		Send(0x05, VC_PORTA, i, 0x00);
	}
	// �����ϰ��
	if (input.Compare(answer) == 0) {
		DrawSwitch(&dc, 8, 1); // Display ��� ǥ��
		Send(0x06, 0x52, 0x00, 0x255); // RGB ��� ON
		Send(0x06, VC_PIEZO_TONE, 33 & 0x0fff, ((100 / 100) & 0x000f) << 12); // ��
		Sleep(350);
		Send(0x06, VC_PIEZO_TONE, 36 & 0x0fff, ((100 / 100) & 0x000f) << 12); // ��
		Sleep(350);
		Send(0x06, VC_PIEZO_TONE, 56 & 0x0fff, ((100 / 100) & 0x000f) << 12); // ��
		Sleep(500);
		Send(0x06, 0x52, 0x00, 0x00); // RGB ��� OFF
		DrawSwitch(&dc, 8, 0); // Display ��� ǥ�� ����
	}
	// �����ϰ��
	else {
		DrawSwitch(&dc, 8, 2); // Display ������ ǥ��
		Send(0x06, 0x51, 0x00, 0x255); // RGB ������ ON
		Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((1000 / 100) & 0x000f) << 12); // �� -
		Sleep(1000);
		Send(0x06, 0x51, 0x00, 0x00); // RGB ������ OFF
		DrawSwitch(&dc, 8, 0); // Display ������ ǥ�� ����
	}
	// Mode ���� �ʱ�ȭ
	GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("Easy Mode"));
	GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("Normal Mode"));
	GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("Hard Mode"));
	Send(0x06, 0x53, 0x00, 0x00); // RGB ��Ȱ��ȭ
	Send(0x06, VC_PIEZO_ENABLE, 0, 0); // �ǿ��� ��Ȱ��ȭ
	gamestatus = false; // ���� ���� ����
}