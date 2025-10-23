#pragma once

/* 유아이2d 형태로 그려지는 모든 객체들의 부모. */
/* 2d형태로 그려지기위한 기능과 데이터를 쥐고 있는다 .*/
#include "GameObject.h"

NS_BEGIN(Engine)

class ENGINE_DLL CUIObject abstract : public CGameObject
{
protected:
	CUIObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CUIObject(const CUIObject& Prototype);
	virtual ~CUIObject() = default;
public:
	virtual HRESULT Initialize_Prototype() override; /* 원형을 위한 초기화(서버, 파일) */
	virtual HRESULT Initialize(void* pArg) override; /* 사본객체를 위한 초기화 */
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