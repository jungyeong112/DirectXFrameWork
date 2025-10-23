#pragma once

#include "Component.h"

/* ��ü�� ���� ���·� ��ȯ���� �� �� �ִ� ���� ����� �����ϰ� ��Ʈ���Ѵ�. */

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
	/* �׵�������� ���� ���ϴ� ������ŭ ȸ������ ���´�. */
	void Rotation(const _float3& vAxis, _float fRadian);

	/* ���� ��ü�� ���¿� ���ؼ� ������ �ӵ���ŭ ���ϴ� �������� ȸ����Ų�� */
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