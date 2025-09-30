#include "MainApp.h"
#include "Graphic_Device.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance { CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Initialize()
{
	ENGINE_DESC		EngineDesc{};

	EngineDesc.hWnd = g_hWnd;
	EngineDesc.eMode = WINMODE::WIN;
	EngineDesc.iWinSizeX = g_iWinSizeX;
	EngineDesc.iWinSizeY = g_iWinSizeY;

	if(FAILED(m_pGameInstance->Initialize_Engine(EngineDesc, &m_pGraphic_Device)))
		return E_FAIL;


	if (FAILED(Start_Level(LEVEL::LOGO)))
		return E_FAIL;
	
	return S_OK;
}

void CMainApp::Update(float fTimeDelta)
{
	m_pGameInstance->Update_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
	if (FAILED(m_pGameInstance->Begin_Draw()))
		return E_FAIL;

	if (FAILED(m_pGameInstance->End_Draw()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eStartLevel)
{
	m_pGameInstance->Change_Level(ENUM_TO_UINT(LEVEL::LOADING),
		CLevel_Loading::Create(m_pGraphic_Device, eStartLevel));
			
	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{

	__super::Free();

	/* 내멤버를 삭제한다. */	
	Safe_Release(m_pGraphic_Device);

	Safe_Release(m_pGameInstance);
}
