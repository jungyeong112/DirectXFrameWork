#pragma once

#include "Client_Defines.h"
#include "Base.h"

/* 다음 씬을 위한 자원(텍스쳐, 정점,인덱스버퍼, 모델, 쉐이더) 준비를 해준다. */
NS_BEGIN(Engine)
class CGameInstance;
NS_END

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


public:
	void Output() {
		SetWindowText(g_hWnd, m_szLoadingText);
	}

private:
	LEVEL						m_eNextLevel = {};
	LPDIRECT3DDEVICE9			m_pGraphic_Device = { nullptr };
	CGameInstance*				m_pGameInstance = { nullptr };

private:
	_tchar						m_szLoadingText[MAX_PATH] = {};
	_bool						m_isFinish = { false };

private:
	HANDLE						m_hThread = {};
	CRITICAL_SECTION			m_CriticalSectionKey = {};

private:
	HRESULT Loading_ForLogoLevel();
	HRESULT Loading_ForGamePlayLevel();




public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

NS_END