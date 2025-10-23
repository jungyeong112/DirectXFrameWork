#include "Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent { pGraphic_Device }
{

}

CTransform::CTransform(const CTransform& Prototype)
	: CComponent{ Prototype }
	, m_WorldMatrix { Prototype.m_WorldMatrix }
{

}

_float3 CTransform::Get_Scaled()
{
	_float3		vRight = Get_State(STATE::RIGHT);
	_float3		vUp = Get_State(STATE::UP);
	_float3		vLook = Get_State(STATE::LOOK);

	return _float3(
		D3DXVec3Length(&vRight),
		D3DXVec3Length(&vUp),
		D3DXVec3Length(&vLook)
	);
}

HRESULT CTransform::Initialize_Prototype()
{
	D3DXMatrixIdentity(&m_WorldMatrix);

	return S_OK;
}

HRESULT CTransform::Initialize(void* pArg)
{
	TRANSFORM_DESC*	pDesc = static_cast<TRANSFORM_DESC*>(pArg);

	m_fSpeedPerSec = pDesc->fSpeedPerSec;
	m_fRotationPerSec = pDesc->fRotationPerSec;

	return S_OK;
}

HRESULT CTransform::Bind_Resource()
{
	return m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);	
}

void CTransform::Go_Straight(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE::POSITION);
	_float3		vLook = Get_State(STATE::LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_fSpeedPerSec * fTimeDelta;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Backward(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE::POSITION);
	_float3		vLook = Get_State(STATE::LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_fSpeedPerSec * fTimeDelta;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE::POSITION);
	_float3		vRight = Get_State(STATE::RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_fSpeedPerSec * fTimeDelta;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE::POSITION);
	_float3		vRight = Get_State(STATE::RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_fSpeedPerSec * fTimeDelta;

	Set_State(STATE::POSITION, vPosition);
}
/* 항등기준으로 내가 원하는 각도만큼 회전시켜 놓는다. */
void CTransform::Rotation(const _float3& vAxis, _float fRadian)
{
	_float3		vScaled = Get_Scaled();

	_float3		vRight = _float3(1.0f, 0.f, 0.f) * vScaled.x;
	_float3		vUp = _float3(0.f, 1.f, 0.f) * vScaled.y;
	_float3		vLook = _float3(0.f, 0.f, 1.f) * vScaled.z;

	_float4x4	RotationMatrix = {};
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadian);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(STATE::RIGHT, vRight);
	Set_State(STATE::UP, vUp);
	Set_State(STATE::LOOK, vLook);
}
/* 현재 객체의 상태에 더해서 정해진 속도만큼 원하는 방향으로 회전시킨다 */
void CTransform::Turn(const _float3& vAxis, _float fTimeDelta)
{
	_float3		vRight = Get_State(STATE::RIGHT);
	_float3		vUp = Get_State(STATE::UP);
	_float3		vLook = Get_State(STATE::LOOK);

	_float4x4	RotationMatrix = {};
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_fRotationPerSec * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(STATE::RIGHT, vRight);
	Set_State(STATE::UP, vUp);
	Set_State(STATE::LOOK, vLook);
}

CTransform* CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTransform* pInstance = new CTransform(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTransform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CTransform::Clone(void* pArg)
{
	CTransform* pInstance = new CTransform(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CTransform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();
}
