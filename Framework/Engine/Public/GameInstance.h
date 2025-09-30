#pragma once

/* 엔진 대변인 */

/* 클라이언트 개발자가 엔진의 기능을 이용할 수 있도록 필요한 함수를 ㄹ보여준다. */
/* 여러기능을 보여주기위해 해당 기능을 제공하는 객체를 GameInstance자체적으로 들고 있게 만ㄷ ㅡㄹ어줄 생각이ㅏㄷ. */
/* 엔진에서 정의되는 대다수의 객체는 게임인스턴스가 들고 있어야하는 상황이. */
/* 굳이 다른 클래스들을 싱글턴을 만들 이유가 크게 없다. */

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