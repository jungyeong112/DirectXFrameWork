#include "Graphic_Device.h"

CGraphic_Device::CGraphic_Device()	
{

}

HRESULT CGraphic_Device::Initialize(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY, LPDIRECT3DDEVICE9* ppGraphic_Device)
{
	// 1. 그래픽 카드의 성능을 조사할 객체 생성
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (nullptr == m_pSDK)
		return E_FAIL;

	// 2. 그래픽 카드 성능을 조사
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// D3DADAPTER_DEFAULT : 현재 컴퓨터에 설치된 기본 그래픽 카드
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
		return E_FAIL;

	_ulong	dwFlag(0);


	/* 변환 */
	/* 렌더링을 위해 필수적으로 필요한 변환(월드, 뷰, 투영) dx가 알아서 수행해준다. */
	/* 정점의 데이터(위치)를 내가 만들어서 장치에게 전달해줘야하고, 위에 필요한 필수적인 연산을 위한 행렬또한 내가 만들어서 장치에게 전달해주는 형태. */

	/* 조명 */
	/* 정점단위로 연산이 되었어야할 빛 연산또한 장치가 알아서 해준다. */
	/* 정점의 데이터(노멀)를 내가 만들어서 장치에게 전달해줘야하고 빛의 정보를 내가 만들어서 장치에게 전달해주면 알아서 빛연산을 수행해준다 .*/

	// vp = 정점의 변환 + 명암(조명) 연산 -> 모델을 렌더링했다. -> 모델을 고정기능렌더링파이프라인을 수행하여 렌더링하였다. 
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		dwFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = iSizeX;
	d3dpp.BackBufferHeight = iSizeY;

	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD = 1,	// 스왑 체인 방식
	// D3DSWAPEFFECT_FLIP = 2,		// 버퍼 하나를 뒤집으면서 사용
	// D3DSWAPEFFECT_COPY = 3,		// 더블 버퍼링과 흡사

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;

	d3dpp.Windowed = static_cast<_bool>(eMode);		// TRUE(창 모드)

	// target : 일반적인 그리기 버퍼
	// stencil : 
	// depth(z) : 깊이 값을 저장하는 용도의 버퍼

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//3. 그리기 객체 생성
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		dwFlag,
		&d3dpp,
		&m_pGraphicDev)))
	{
		return E_FAIL;
	}

	*ppGraphic_Device = m_pGraphicDev;

	return S_OK;
}

// 후면 버퍼의 동작 원리

// 1. 화면을 지운다.
// 2. 다시 그릴 화면 준비
void CGraphic_Device::Render_Begin(D3DXCOLOR Color)
{


	m_pGraphicDev->Clear(0,		// 렉트의 개수
		NULL,					// 렉트의 주소
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		Color,				// 삭제 이후에 후면 버퍼 색상
		1.f,					// !!!!!!!z버퍼의 초기화값!!!!!
		0);			// 스텐시버퍼 초기화 값

	m_pGraphicDev->BeginScene();

}


// 3. 여기까지 한 프레임을 그릴 것이라고 장치에게 통보
// 4. 전면 버퍼와 서피스 교환
void CGraphic_Device::Render_End()
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(NULL, NULL, NULL, NULL);

	// 1, 2 인자 : 렉트의 주소
	// 1, 2, 4 인자 : D3DSWAPEFFECT_COPY 옵션일 때만 사용 가능
	// !!!!3인자 : 창 핸들!!!!
}


CGraphic_Device* CGraphic_Device::Create(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY, LPDIRECT3DDEVICE9* ppGraphic_Device)
{
	CGraphic_Device* pInstance = new CGraphic_Device();

	if (FAILED(pInstance->Initialize(hWnd, eMode, iSizeX, iSizeY, ppGraphic_Device)))
	{
		MSG_BOX("Failed to Created : CGraphic_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGraphic_Device::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}
