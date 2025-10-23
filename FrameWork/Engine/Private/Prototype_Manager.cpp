#include "Prototype_Manager.h"
#include "GameObject.h"

CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(_uint iNumLevels)
{
	m_pPrototypes = new map<const _wstring, class CBase*>[iNumLevels];

	m_iNumLevels = iNumLevels;

	return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag, CBase* pPrototype)
{
	if (nullptr != Find_Prototype(iLevelIndex, strPrototypeTag))
		return E_FAIL;

	m_pPrototypes[iLevelIndex].emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

CBase* CPrototype_Manager::Clone_Prototype(PROTOTYPE ePrototype, _uint iLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
	CBase*	pPrototype = Find_Prototype(iLevelIndex, strPrototypeTag);
	if (nullptr == pPrototype)
		return nullptr;

	CBase* pCloneObject = { nullptr };

	if (PROTOTYPE::GAMEOBJECT == ePrototype)
		pCloneObject = dynamic_cast<CGameObject*>(pPrototype)->Clone(pArg);
	else
		pCloneObject = dynamic_cast<CComponent*>(pPrototype)->Clone(pArg);

	if (nullptr == pCloneObject)
		return nullptr;

	return pCloneObject;
}

void CPrototype_Manager::Clear(_uint iLevelIndex)
{
	if (iLevelIndex >= m_iNumLevels)
		return;

	for (auto& Pair : m_pPrototypes[iLevelIndex])
		Safe_Release(Pair.second);

	m_pPrototypes[iLevelIndex].clear();
}

CBase* CPrototype_Manager::Find_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag)
{
	if(iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = m_pPrototypes[iLevelIndex].find(strPrototypeTag);
	if (iter == m_pPrototypes[iLevelIndex].end())
		return nullptr;

	return iter->second;
		

	
}

CPrototype_Manager* CPrototype_Manager::Create(_uint iNumLevels)
{
	CPrototype_Manager* pInstance = new CPrototype_Manager();

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Failed to Created : CPrototype_Manager");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CPrototype_Manager::Free()
{
	__super::Free();

	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pPrototypes[i])		
			Safe_Release(Pair.second);		

		m_pPrototypes[i].clear();
	}

	Safe_Delete_Array(m_pPrototypes);
}
