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
	LPDIRECT3D9			m_pSDK = { nullptr };			// 그래픽 디바이스 모체
	LPDIRECT3DDEVICE9	m_pGraphicDev = { nullptr };	// 그리기 담당 자식 객체

public:
	static CGraphic_Device* Create(HWND hWnd, WINMODE eMode, _uint iSizeX, _uint iSizeY, LPDIRECT3DDEVICE9* ppGraphic_Device);
	virtual void Free() override;
};

NS_END


// 1. 장치를 조사(그래픽 카드 성능 조사) -> m_pSDK
// 2. 출력 담당 객체를 생성 ->m_pGraphicDev(그리기 담당 객체)
// 3. m_pGraphicDev를 이용하여 출력 담당 함수를 호출



