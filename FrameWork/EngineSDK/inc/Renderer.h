#pragma once

#include "Base.h"

/* ȭ�鿡 �׷������� ��ü���� ��Ƶд�. != Object_Manager(�� ������ �׷쿡 ���� ���������� �з��Ǿ� �����ȴ�.) */
/* �׷����ϴ� ������ ���� ����ش�. */
/* ��� �ִ� ��ü���� �����Լ��� ȣ���� �ش�. */
/* ���� �� �Ŀ� �����̳ʸ� ��ü������ ����. */

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
	/* �� �����Ӹ��� �׷������� ��ü���� Ǫ�����ֳ�. */
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