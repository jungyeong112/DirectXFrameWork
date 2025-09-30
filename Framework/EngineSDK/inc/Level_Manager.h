#pragma once

/* 1. ���� Ȱ��ȭ�� ������ �����ϰ� �ݺ������� ������Ʈ�� ������ ȣ�����ش�. */
/* 2. ������ ��ü �ÿ� �˾Ƽ� ���� ������ �����ϴ� ��Ȱ�� �����Ѵ�. */
/* 3. ���� ���� �� ���� �ڿ�(���Ӹ��ҽ�, ���ӿ�����Ʈ)���� ���� ���ش�. */

#include "Base.h"

NS_BEGIN(Engine)

class CLevel_Manager final : public CBase
{
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Change_Level(_uint iLevelIndex, class CLevel* pNewLevel);
	void Update(_float fTimeDelta);
	HRESULT Render();

private:
	_uint				 m_iCurrentLevelIndex = { };
	class CLevel*		 m_pCurrentLevel = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };

public:
	static CLevel_Manager* Create();
	virtual void Free() override;
};

NS_END