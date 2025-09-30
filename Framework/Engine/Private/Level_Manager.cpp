#include "Level_Manager.h"

#include "Level.h"
#include "GameInstance.h"

CLevel_Manager::CLevel_Manager()
	: m_pGameInstance { CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CLevel_Manager::Change_Level(_uint iLevelIndex, class CLevel* pNewLevel)
{	
	if(nullptr != m_pCurrentLevel)	
		m_pGameInstance->Clear(m_iCurrentLevelIndex);	

	if (0 != Safe_Release(m_pCurrentLevel))
		return E_FAIL;

	m_pCurrentLevel = pNewLevel;

	m_iCurrentLevelIndex = iLevelIndex;

	return S_OK;
}

void CLevel_Manager::Update(_float fTimeDelta)
{
	m_pCurrentLevel->Update(fTimeDelta);
}

HRESULT CLevel_Manager::Render()
{
	return m_pCurrentLevel->Render();	
}

CLevel_Manager* CLevel_Manager::Create()
{
	return new CLevel_Manager();
}

void CLevel_Manager::Free()
{
	__super::Free();

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pCurrentLevel);
}