#pragma once

#include "Base.h"

NS_BEGIN(Engine)

class CGraphic_Device final : public CBase
{
private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public:
	HRESULT		Initialize(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY,LPDIRECT3DDEVICE9* ppGraphic_Device);
	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End();

private:
	LPDIRECT3D9			m_pSDK = { nullptr };			// �׷��� ����̽� ��ü
	LPDIRECT3DDEVICE9	m_pGraphicDev = { nullptr };	// �׸��� ��� �ڽ� ��ü

public:
	static CGraphic_Device* Create(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY, LPDIRECT3DDEVICE9* ppGraphic_Device);
	virtual void Free() override;
};

NS_END


// 1. ��ġ�� ����(�׷��� ī�� ���� ����) -> m_pSDK
// 2. ��� ��� ��ü�� ���� ->m_pGraphicDev(�׸��� ��� ��ü)
// 3. m_pGraphicDev�� �̿��Ͽ� ��� ��� �Լ��� ȣ��



