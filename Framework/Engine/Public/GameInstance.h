#pragma once

/* ���� �뺯�� */

/* Ŭ���̾�Ʈ �����ڰ� ������ ����� �̿��� �� �ֵ��� �ʿ��� �Լ��� �������ش�. */
/* ��������� �����ֱ����� �ش� ����� �����ϴ� ��ü�� GameInstance��ü������ ��� �ְ� ���� �Ѥ����� �����̤���. */
/* �������� ���ǵǴ� ��ټ��� ��ü�� �����ν��Ͻ��� ��� �־���ϴ� ��Ȳ��. */
/* ���� �ٸ� Ŭ�������� �̱����� ���� ������ ũ�� ����. */

#include "Base.h"

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


private:
	class CGraphic_Device*		m_pGraphic_Device = { nullptr };
	class CLevel_Manager*		m_pLevel_Manager = { nullptr };
	class CPrototype_Manager*	m_pPrototype_Manager = { nullptr };
	class CObject_Manager*		m_pObject_Manager = { nullptr };

public:
	virtual void Free() override;

};

NS_END