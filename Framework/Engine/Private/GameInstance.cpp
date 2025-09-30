#include "GameInstance.h"
#include "Graphic_Device.h"
#include "Level_Manager.h"

IMPLEMENT_SINGLETON(CGameInstance);

CGameInstance::CGameInstance()
{

}

#pragma region ENGINE

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut)
{
	m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, ppOut);
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Update_Engine(_float fTimeDelta)
{
	m_pLevel_Manager->Update(fTimeDelta);
}
	
HRESULT CGameInstance::Begin_Draw()
{
	if (nullptr != m_pGraphic_Device)
		m_pGraphic_Device->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));	
	return S_OK;
}

HRESULT CGameInstance::Draw()
{
	return m_pLevel_Manager->Render();
}

HRESULT CGameInstance::End_Draw()
{
	if (nullptr != m_pGraphic_Device)
		m_pGraphic_Device->Render_End();

	return S_OK;
}

HRESULT CGameInstance::Clear(_uint iClearLevelIndex)
{
	return S_OK;
}

#pragma endregion

#pragma region LEVEL_MANAGER

HRESULT CGameInstance::Change_Level(_uint iLevelIndex, class CLevel* pNewLevel)
{
	return m_pLevel_Manager->Change_Level(iLevelIndex, pNewLevel);
}

#pragma endregion

void CGameInstance::Free()
{
	__super::Free();

	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pGraphic_Device);
}
