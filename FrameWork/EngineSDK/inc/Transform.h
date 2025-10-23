#pragma once

#include "Component.h"

/* 객체의 월드 상태로 변환시켜 줄 수 있는 월드 행렬을 보관하고 컨트롤한다. */

NS_BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		_float		fSpeedPerSec;
		_float		fRotationPerSec;
	}TRANSFORM_DESC;
private:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& Prototype);
	virtual ~CTransform() = default;

public:
	_float3 Get_State(STATE eState) {
		return *reinterpret_cast<_float3*>(&m_WorldMatrix.m[ENUM_TO_UINT(eState)][0]);
	}

	_float3 Get_Scaled();

	void Set_State(STATE eState, const _float3& vState) {
		memcpy(&m_WorldMatrix.m[ENUM_TO_UINT(eState)][0], &vState, sizeof(_float3));
	}

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;



public:
	HRESULT Bind_Resource();

public:
	void Go_Straight(_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);	
public:
	/* 항등기준으로 내가 원하는 각도만큼 회전시켜 놓는다. */
	void Rotation(const _float3& vAxis, _float fRadian);

	/* 현재 객체의 상태에 더해서 정해진 속도만큼 원하는 방향으로 회전시킨다 */
	void Turn(const _float3& vAxis, _float fTimeDelta);


private:
	_float4x4				m_WorldMatrix = {};
	_float					m_fSpeedPerSec = {};
	_float					m_fRotationPerSec = {};

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

NS_END