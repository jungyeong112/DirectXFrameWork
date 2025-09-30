#pragma once

#include "Client_Defines.h"
#include "Level.h"

/* �ε����� �������ֱ����� ��ü���� �����Ѵ�. */
/* �ε�����ü�� ������Ʈ�ϰ� ȭ�鿡 �����ִ� ��Ȱ. */

/* ���� ���� ���� �ڿ�(�ؽ���, ����,�ε�������, ��, ���̴�) �غ� ���ִ�  
Loader��� ��ü�� ����, �����������ִ� ��Ȱ�� �����ҰŴ�. */

NS_BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevel);
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL			m_eNextLevel = {};
	class CLoader*  m_pLoader = { nullptr };

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

NS_END