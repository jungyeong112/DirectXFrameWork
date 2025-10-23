#pragma once

#include "Base.h"

/* 1. 우리가 사용해야할 객체(CGameObject)들을 모아서 저장해놓는다. */
/* 1. 나는 객체들을 내가 나누고싶은 기준에 따라 나누어서(CLayer) 레벨별로 저장해준다. */
/* 2. 저장한 객체들의 각종 Update를 호출해준다. */
/* 2. 저장한 객체들의 Render를 호출해준다.(X:그룹ㄱ의 기준과 그리는 순서를 복합적으로 관리하는 것은 거의 불가능) */

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