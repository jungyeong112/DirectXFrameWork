#pragma once

/* ���� �뺯�� */

/* Ŭ���̾�Ʈ �����ڰ� ������ ����� �̿��� �� �ֵ��� �ʿ��� �Լ��� �������ش�. */
/* ��������� �����ֱ����� �ش� ����� �����ϴ� ��ü�� GameInstance��ü������ ��� �ְ� ���� �Ѥ����� �����̤���. */
/* �������� ���ǵǴ� ��ټ��� ��ü�� �����ν��Ͻ��� ��� �־���ϴ� ��Ȳ��. */
/* ���� �ٸ� Ŭ�������� �̱����� ���� ������ ũ�� ����. */

#include "Prototype_Manager.h"

NS_BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	
	virtual ~CGameInstance() = default;

#pragma region Engine
public:
	HRESULT Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut);
	void Update_Engine(_float fTimeDelta);
	HRESULT Begin_Draw();
	HRESULT Draw();
	HRESULT End_Draw();
	HRESULT Clear(_uint iClearLevelIndex);
#pragma endregion

#pragma region LEVEL_MANAGER
public:
	HRESULT Change_Level(_uint iLevelIndex, class CLevel* pNewLevel);
#pragma endregion

#pragma region PROTOTYPE_MANAGER
public:
	HRESULT Add_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag, class CBase* pPrototype);
	CBase* Clone_Prototype(PROTOTYPE ePrototype, _uint iLevelIndex, const _wstring& strPrototypeTag, void* pArg = nullptr);
#pragma endregion


#pragma region OBJECT_MANAGER
public:	
	HRESULT Add_GameObject_ToLayer(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, _uint iLayerLevelIndex, const _wstring& strLayerTag, void* pArg = nullptr);
#pragma endregion

#pragma region RENDERER
public:
	HRESULT Add_RenderGroup(RENDERGROUP eGroupID, class CGameObject* pRenderObject);
#pragma endregion
	





private:
	class CGraphic_Device*		m_pGraphic_Device = { nullptr };
	class CLevel_Manager*		m_pLevel_Manager = { nullptr };
	class CPrototype_Manager*	m_pPrototype_Manager = { nullptr };
	class CObject_Manager*		m_pObject_Manager = { nullptr };
	class CRenderer*			m_pRenderer = { nullptr };

public:
	virtual void Free() override;

};

NS_END