#pragma once

#include "Base.h"

/* 화면에 그려져야할 객체들을 모아둔다. != Object_Manager(내 기준의 그룹에 따라 레벨에따라 분류되어 보관된다.) */
/* 그려야하는 순서에 따라서 모아준다. */
/* 들고 있는 객체들의 렌더함수를 호출해 준다. */
/* 렌더 콜 후에 컨테이너를 전체적으로 비운다. */

NS_BEGIN(Engine)

class CRenderer final : public CBase
{
private:
	CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CRenderer() = default;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eGroupID, class CGameObject* pRenderObject);
	void Draw();

private:
	LPDIRECT3DDEVICE9					m_pGraphic_Device = { nullptr };
	/* 매 프레임마다 그려져야할 객체들을 푸쉬해주낟. */
	list<class CGameObject*>			m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::END)];

private:
	void Render_Priority();
	void Render_NonBlend();
	void Render_Blend();
	void Render_UI();


public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

NS_END