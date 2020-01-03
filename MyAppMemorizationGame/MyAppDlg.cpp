
// MyAppDlg.cpp : 구현 파일
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
#define SW_X        30    // 좌측 상단의 X축 좌표
#define SW_Y       200    // 좌측 상단의 Y축 좌표
#define SW_RADIUS   30    // 네모의 한변 길이
#define SW_DISTANCE 50    // 네모와 네모 사이의 거리
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMyAppDlg 대화 상자



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


// CMyAppDlg 메시지 처리기

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bConnected = FALSE;
	m_hComm = NULL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//네모 도형 9개 그리기
		CPaintDC dc(this);
		for (int i = 0; i < 9; i++) {
			DrawSwitch(&dc, i, 0);
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CallCommSetDlg();
}

bool gamestatus = false;

void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
  // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
  CString str;			// 통신연결 상태표시용 문자열
  char cParity;			// 패리티 표시용 문자변수
  char* cStopBits;	// Stop bit 표시용 문자열 포인터
  CommConfigData *pCommCfg = new CommConfigData;

// 통신포트 연결여부 확인
  if(!m_bConnected){
    GetCommCfgData(pCommCfg);
    pCommCfg->hOwner = m_hWnd;
	// 통신 포트 연결
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
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("게임 접속 완료"));
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("게임 종료"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);

	   Send(0x06, VC_PIN_EVENT_MASK, 0, 0x00); //스위치 비활성화
	   Send(0x06, 0x31, 0, 0x00); //1000의 자리 비활성화
	   Send(0x06, 0x32, 0, 0x00); //100의 자리 비활성화
	   Send(0x06, 0x33, 0, 0x00); //10의 자리 비활성화
	   Send(0x06, 0x34, 0, 0x3f); //1의 자리에 0 출력
    }
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }
  // 통신포트 연결해제
 else{
	  // Mode 상태 초기화
	  GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("Easy Mode"));
	  GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("Normal Mode"));
	  GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("Hard Mode"));

	  CClientDC dc(this);
	  // Display 모든 표시 제거 + 모든 LED OFF
	  for (int i = 0; i < 9; i++) {
		  DrawSwitch(&dc, i, 0);
		  Send(0x05, VC_PORTA, i, 0x00);
	  }
	  Send(0x06, 0x53, 0x00, 000); // RGB 비활성화
	  Send(0x06, VC_PIEZO_ENABLE, 0, 0); // 피에조 비활성화
	  Send(0x06, VC_FND, 0, 0); // FND -> 0000
	  gamestatus = false;
     
	 CommClose();
     m_bConnected = FALSE;
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(_T("게임 접속 종료"));
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("게임 접속"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);

  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_bConnected){
		CommClose();
	}

	CDialogEx::OnClose();
}


VOID CMyAppDlg::Send(int fun, int add, int hd, int ld)
{
	// TODO: 여기에 구현 코드 추가.
	_MyBusFrame Q;
	if (m_bConnected == FALSE) return;

	Q.ui8Func = fun;
	Q.ui8Addr = add;
	Q.ui8DataH = hd;
	Q.ui8DataL = ld;
	MyBusSendFrame(&Q);
	return VOID();
}


CString input; //입력한 정답
CString answer; //문제 정답
int input_cnt = 0; //입력한 정답 개수
int delay = 0; //문제 난이도를 결정지을 LED ON/OFF사이의 시간 간격

//게임 시작 전 준비
void CMyAppDlg::StageReady()
{
	input = ""; // 입력값 초기화
	input_cnt = 0; //입력한 정답 개수 초기화
	Send(0x06, 0x53, 0x00, 0xff); // RGB 활성화
	Send(0x06, VC_PIEZO_ENABLE, 0, 1); // 피에조 활성화
	Send(0x06, VC_PIN_EVENT_MASK, 0, 0x00); // 문제 출제중 스위치 비활성화
	gamestatus = true;
	Send(0x06, 0x34, 0, 0x4f); // FND 3
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 삐 -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x5b); // FND 2
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 삐 -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x06); // FND 1
	Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 삐 -
	Sleep(1000);
	Send(0x06, 0x34, 0, 0x3f); // FND 0
	Send(0x06, VC_PIEZO_TONE, 36 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 삐 !
}

//Easy Mode
void CMyAppDlg::OnBnClickedButtonGame()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 400; // LED ON/OFF 사이 시간 간격 -> 난이도를 결정지음
		GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("In Game")); // Display에 게임중임을 표시
		StageReady(); // 게임 시작 카운트
		StageStart(); // 게임 시작
	}
}

//Normal Mode
void CMyAppDlg::OnBnClickedButtonGame2()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 200; // LED ON/OFF 사이 시간 간격 -> 난이도를 결정지음
		GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("In Game")); // Display에 게임중임을 표시
		StageReady(); // 게임 시작 카운트
		StageStart(); // 게임 시작
	}
}

//Hard Mode
void CMyAppDlg::OnBnClickedButtonGame3()
{
	if (!gamestatus) {
		if (m_bConnected == FALSE) return;
		delay = 100; // LED ON/OFF 사이 시간 간격 -> 난이도를 결정지음
		GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("In Game")); // Display에 게임중임을 표시
		StageReady(); // 게임 시작 카운트
		StageStart(); // 게임 시작
	}
}


// 발생한 난수에 따른 LED를 일정 delay를 간격으로 ON/OFF
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

//게임 시작
void CMyAppDlg::StageStart()
{	
	srand((unsigned int)time(0));
	//8자리 난수 발생
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

	answer = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8; // 정답
	
	//게임 시작
	Sleep(1000);
	LED_OnOff(num1);
	LED_OnOff(num2);
	LED_OnOff(num3);
	LED_OnOff(num4);
	LED_OnOff(num5);
	LED_OnOff(num6);
	LED_OnOff(num7);
	LED_OnOff(num8);

	Send(0x06, VC_PIN_EVENT_MASK, 0, 0x10); // 정답을 입력할 스위치 활성화
	Send(0x06, 0x50, 0x00, 0xff); // 정답입력가능을 알리는 RGB 파란색 ON
}


//Display에 9개의 네모 표시 및 상황별 색 변화 설정
void CMyAppDlg::DrawSwitch(CDC* pDC, UINT nSW, int ok)
{
	CPen Pen;
	CPen *oldPen;
	CBrush Brush;
	CBrush *oldBrush;
	if (nSW < 9) { 
		Pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		if (ok == 0) {
			Brush.CreateSolidBrush(pDC->GetBkColor()); // 바탕색
		}
		else if (ok == 1) {
			Brush.CreateSolidBrush(RGB(0, 255, 0));  // 녹색
		}
		else if (ok == 2){
			Brush.CreateSolidBrush(RGB(255, 0, 0));  // 빨간색
		}

		oldPen = pDC->SelectObject(&Pen);
		oldBrush = pDC->SelectObject(&Brush);

		pDC->Rectangle(SW_X + nSW * SW_DISTANCE, SW_Y,
			SW_X + nSW * SW_DISTANCE + SW_RADIUS, SW_Y + SW_RADIUS);

		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
	}

}


//스위치 입력 반환
afx_msg LRESULT CMyAppDlg::OnMyBusSwitchUpdate(WPARAM wParam, LPARAM lParam)
{
	long i = lParam & 0xff;
	CString p;
	CClientDC dc(this);
	switch (i) {
	case 0x7f:  // 첫번째 스위치 0111 1111
		if(input.GetLength() < 8) input += "8";
		if(input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display에 스위치 입력 표시
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // 입력 수만큼 LED 표시
		input_cnt++; // 입력 수 +
		break;
	case 0xbf:   // 두번쨰 스위치 1011 1111
		if (input.GetLength() < 8) input += "6";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display에 스위치 입력 표시
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // 입력 수만큼 LED 표시
		input_cnt++; // 입력 수 +
		break;
	case 0xdf:   // 세번째 스위치  1101 1111
		if (input.GetLength() < 8) input += "4";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display에 스위치 입력 표시
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // 입력 수만큼 LED 표시
		input_cnt++; // 입력 수 +
		break;
	case 0xef:	// 네번째 스위치 1110 1111
		if (input.GetLength() < 8) input += "2";
		if (input_cnt < 8) DrawSwitch(&dc, input_cnt, 1); // Display에 스위치 입력 표시
		Send(0x05, VC_PORTA, 7 - input_cnt, 0xff); // 입력 수만큼 LED 표시
		input_cnt++; // 입력 수 +
		break;
	}
	// 정답을 전부 입력했을 경우 자동 정답 제출
	if (input_cnt == 8) {
		Sleep(500);
		submit();
	}
	return afx_msg LRESULT();
}


//정답 제출
void CMyAppDlg::submit()
{
	Send(0x06, 0x50, 0x00, 0x00); // 파란색 OFF
	CClientDC dc(this);
	// Display 모든 표시 제거 + 모든 LED OFF
	for (int i = 0; i < 9; i++) {
		DrawSwitch(&dc, i, 0);
		Send(0x05, VC_PORTA, i, 0x00);
	}
	// 정답일경우
	if (input.Compare(answer) == 0) {
		DrawSwitch(&dc, 8, 1); // Display 녹색 표시
		Send(0x06, 0x52, 0x00, 0x255); // RGB 녹색 ON
		Send(0x06, VC_PIEZO_TONE, 33 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 딩
		Sleep(350);
		Send(0x06, VC_PIEZO_TONE, 36 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 동
		Sleep(350);
		Send(0x06, VC_PIEZO_TONE, 56 & 0x0fff, ((100 / 100) & 0x000f) << 12); // 댕
		Sleep(500);
		Send(0x06, 0x52, 0x00, 0x00); // RGB 녹색 OFF
		DrawSwitch(&dc, 8, 0); // Display 녹색 표시 제거
	}
	// 오답일경우
	else {
		DrawSwitch(&dc, 8, 2); // Display 빨간색 표시
		Send(0x06, 0x51, 0x00, 0x255); // RGB 빨간색 ON
		Send(0x06, VC_PIEZO_TONE, 32 & 0x0fff, ((1000 / 100) & 0x000f) << 12); // 삐 -
		Sleep(1000);
		Send(0x06, 0x51, 0x00, 0x00); // RGB 빨간색 OFF
		DrawSwitch(&dc, 8, 0); // Display 빨간색 표시 제거
	}
	// Mode 상태 초기화
	GetDlgItem(IDC_BUTTON_GAME)->SetWindowText(_T("Easy Mode"));
	GetDlgItem(IDC_BUTTON_GAME2)->SetWindowText(_T("Normal Mode"));
	GetDlgItem(IDC_BUTTON_GAME3)->SetWindowText(_T("Hard Mode"));
	Send(0x06, 0x53, 0x00, 0x00); // RGB 비활성화
	Send(0x06, VC_PIEZO_ENABLE, 0, 0); // 피에조 비활성화
	gamestatus = false; // 게임 상태 변경
}