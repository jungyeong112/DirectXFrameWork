#pragma once

#include "Client_Defines.h"
#include "Base.h"

/* ���� ���� ���� �ڿ�(�ؽ���, ����,�ε�������, ��, ���̴�) �غ� ���ش�. */

NS_BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	HRESULT Initialize(LEVEL eNextLevel);
	HRESULT Loading();
	_bool isFinished() const {
		return m_isFinish;
	}

private:
	LEVEL						m_eNextLevel = {};
	LPDIRECT3DDEVICE9			m_pGraphic_Device = { nullptr };
	_bool						m_isFinish = { false };

private:
	HANDLE						m_hThread = {};


public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

NS_END