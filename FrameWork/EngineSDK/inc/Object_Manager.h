#pragma once

#include "Base.h"

/* 1. �츮�� ����ؾ��� ��ü(CGameObject)���� ��Ƽ� �����س��´�. */
/* 1. ���� ��ü���� ���� ��������� ���ؿ� ���� �����(CLayer) �������� �������ش�. */
/* 2. ������ ��ü���� ���� Update�� ȣ�����ش�. */
/* 2. ������ ��ü���� Render�� ȣ�����ش�.(X:�׷줡�� ���ذ� �׸��� ������ ���������� �����ϴ� ���� ���� �Ұ���) */

NS_BEGIN(Engine)

class CObject_Manager final : public CBase
{
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	HRESULT Add_GameObject_ToLayer(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, _uint iLayerLevelIndex, const _wstring& strLayerTag, void* pArg);
	void Priority_Update(_float fTimeDelta);
	void Update(_float fTimeDelta);
	void Late_Update(_float fTimeDelta);
	void Clear(_uint iLevelIndex);

private:
	map<const _wstring, class CLayer*>* m_pLayers = { nullptr };
	_uint		m_iNumLevels = {};

private:
	class CGameInstance* m_pGameInstance = { nullptr };

private:
	class CLayer* Find_Layer(_uint iLevelIndex, const _wstring& strLayerTag);

public:
	static CObject_Manager* Create(_uint iNumLevels);
	virtual void Free() override;

};

NS_END