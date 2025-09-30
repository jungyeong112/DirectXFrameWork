#pragma once

#include "Client_Defines.h"
#include "Level.h"

/* 로딩씬을 구성해주기위한 객체들을 생성한다. */
/* 로딩씬자체를 업데이트하고 화면에 보여주는 역활. */

/* 다음 씬을 위한 자원(텍스쳐, 정점,인덱스버퍼, 모델, 쉐이더) 준비를 해주는  
Loader라는 객체를 생성, 삭제관리해주는 역활을 수행할거다. */

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