#include "Graphic_Device.h"

CGraphic_Device::CGraphic_Device()	
{

}

HRESULT CGraphic_Device::Initialize(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY, LPDIRECT3DDEVICE9* ppGraphic_Device)
{
	// 1. �׷��� ī���� ������ ������ ��ü ����
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (nullptr == m_pSDK)
		return E_FAIL;

	// 2. �׷��� ī�� ������ ����
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// D3DADAPTER_DEFAULT : ���� ��ǻ�Ϳ� ��ġ�� �⺻ �׷��� ī��
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
		return E_FAIL;

	_ulong	dwFlag(0);


	/* ��ȯ */
	/* �������� ���� �ʼ������� �ʿ��� ��ȯ(����, ��, ����) dx�� �˾Ƽ� �������ش�. */
	/* ������ ������(��ġ)�� ���� ���� ��ġ���� ����������ϰ�, ���� �ʿ��� �ʼ����� ������ ���� ��Ķ��� ���� ���� ��ġ���� �������ִ� ����. */

	/* ���� */
	/* ���������� ������ �Ǿ������ �� ������� ��ġ�� �˾Ƽ� ���ش�. */
	/* ������ ������(���)�� ���� ���� ��ġ���� ����������ϰ� ���� ������ ���� ���� ��ġ���� �������ָ� �˾Ƽ� �������� �������ش� .*/

	// vp = ������ ��ȯ + ���(����) ���� -> ���� �������ߴ�. -> ���� ������ɷ����������������� �����Ͽ� �������Ͽ���. 
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

	// D3DSWAPEFFECT_DISCARD = 1,	// ���� ü�� ���
	// D3DSWAPEFFECT_FLIP = 2,		// ���� �ϳ��� �������鼭 ���
	// D3DSWAPEFFECT_COPY = 3,		// ���� ���۸��� ���

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;

	d3dpp.Windowed = static_cast<_bool>(eMode);		// TRUE(â ���)

	// target : �Ϲ����� �׸��� ����
	// stencil : 
	// depth(z) : ���� ���� �����ϴ� �뵵�� ����

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//3. �׸��� ��ü ����
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

// �ĸ� ������ ���� ����

// 1. ȭ���� �����.
// 2. �ٽ� �׸� ȭ�� �غ�
void CGraphic_Device::Render_Begin(D3DXCOLOR Color)
{


	m_pGraphicDev->Clear(0,		// ��Ʈ�� ����
		NULL,					// ��Ʈ�� �ּ�
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		Color,				// ���� ���Ŀ� �ĸ� ���� ����
		1.f,					// !!!!!!!z������ �ʱ�ȭ��!!!!!
		0);			// ���ٽù��� �ʱ�ȭ ��

	m_pGraphicDev->BeginScene();

}


// 3. ������� �� �������� �׸� ���̶�� ��ġ���� �뺸
// 4. ���� ���ۿ� ���ǽ� ��ȯ
void CGraphic_Device::Render_End()
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(NULL, NULL, NULL, NULL);

	// 1, 2 ���� : ��Ʈ�� �ּ�
	// 1, 2, 4 ���� : D3DSWAPEFFECT_COPY �ɼ��� ���� ��� ����
	// !!!!3���� : â �ڵ�!!!!
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
