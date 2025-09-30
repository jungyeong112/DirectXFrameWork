#include "Level_Loading.h"
#include "Loader.h"

#include "GameInstance.h"
#include "Level_Logo.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel { pGraphic_Device }
{

}


HRESULT CLevel_Loading::Initialize(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	m_pLoader = CLoader::Create(m_pGraphic_Device, eNextLevel);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Update(_float fTimeDelta)
{
	if (true == m_pLoader->isFinished() &&
		GetKeyState(VK_SPACE) & 0x8000)
	{
		CLevel* pNewLevel = { nullptr };

		switch (m_eNextLevel)
		{
		case LEVEL::LOGO:
			pNewLevel = CLevel_Logo::Create(m_pGraphic_Device);
			break;
		case LEVEL::GAMEPLAY:
			pNewLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
			break;
		}
		if (nullptr == pNewLevel)
			return;

		if (FAILED(m_pGameInstance->Change_Level(ENUM_TO_UINT(m_eNextLevel), pNewLevel)))
			return;
			
		return;
	}

}

HRESULT CLevel_Loading::Render()
{
	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);
}
