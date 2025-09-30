#include "Loader.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device { pGraphic_Device }
{
	Safe_AddRef(m_pGraphic_Device);
}

/* 절대 메인 스레드가 호출하지 않는다. 우리가 생성한 서브 스레드가 호출해준  것이다. */
_uint APIENTRY ThreadMain(void* pArg)
{
	CLoader*		pLoader = static_cast<CLoader*>(pArg);

	if (FAILED(pLoader->Loading()))
		return 1;

	return 0;

}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
	
	m_eNextLevel = eNextLevel;	

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;




	return S_OK;
}

HRESULT CLoader::Loading()
{
	switch (m_eNextLevel)
	{
	case LEVEL::LOGO:

		break;
	case LEVEL::GAMEPLAY:

		break;
	}

	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	__super::Free();

	Safe_Release(m_pGraphic_Device); 
}
