#pragma once

/* ������2d ���·� �׷����� ��� ��ü���� �θ�. */
/* 2d���·� �׷��������� ��ɰ� �����͸� ��� �ִ´� .*/
#include "GameObject.h"

NS_BEGIN(Engine)

class ENGINE_DLL CUIObject abstract : public CGameObject
{
protected:
	CUIObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CUIObject(const CUIObject& Prototype);
	virtual ~CUIObject() = default;
public:
	virtual HRESULT Initialize_Prototype() override; /* ������ ���� �ʱ�ȭ(����, ����) */
	virtual HRESULT Initialize(void* pArg) override; /* �纻��ü�� ���� �ʱ�ȭ */
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	_uint			m_iDepth = {};

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;

};

NS_END