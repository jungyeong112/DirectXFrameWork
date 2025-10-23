#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Terrain;
NS_END

NS_BEGIN(Client)

class CCamera final : public CGameObject
{
private:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype()override; 
	virtual HRESULT Initialize(void* pArg)override; 
	void Priority_Update(_float fTimeDelta)override;
	void Update(_float fTimeDelta)override;
	void Late_Update(_float fTimeDelta)override;
	HRESULT Render()override;

private:

	CTexture*				m_pTextureCom = { nullptr };
	CTransform*				m_pTransformCom = { nullptr };
	CVIBuffer_Terrain*		m_pVIBufferCom = { nullptr };

private:
	HRESULT	Ready_Components();

public:
	static CCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg)override;
	virtual void Free() override;
};

NS_END