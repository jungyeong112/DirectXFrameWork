#include "Camera.h"
#include "GameInstance.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject { pGraphic_Device }
{
	
}

CCamera::CCamera(const CCamera& Prototype)
	: CGameObject { Prototype }
{
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;	

	return S_OK;
}

void CCamera::Priority_Update(_float fTimeDelta)
{

}

void CCamera::Update(_float fTimeDelta)
{
	///* 가ㅣㅌ은 레벨에 존재하는ㄴ 모든 객체들이 이 카메라가 월드에서 바라본 상태로 그려지게끔 유도한다. */
	//m_pGraphic_Device->SetTransform(
	//	D3DTS_VIEW, D3DXMatrixInverse(nullptr, m_pTrasnformCom->Get_WorldMatrixPtr()));



}

void CCamera::Late_Update(_float fTimeDelta)
{
	
	
}

HRESULT CCamera::Render()
{
	
	return S_OK;
}

HRESULT CCamera::Ready_Components()
{
	
	/* Com_Transform */
	CTransform::TRANSFORM_DESC		TransformDesc{};
	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(ENUM_TO_UINT(LEVEL::STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;



	return S_OK;
}

CCamera* CCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera* pInstance = new CCamera(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCamera");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CCamera::Clone(void* pArg)
{
	CCamera* pInstance = new CCamera(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCamera");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
