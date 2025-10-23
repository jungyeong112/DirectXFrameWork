#pragma once

#include "Texture.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Terrain.h"

/*  �� ���ӳ��� ������Ÿ�� ������ ������ Ȱ���ϴ� ��ü���� ����(CGameObject, CComponet)�� ���夾���� .*/
/*  �������� �����Ͽ� �����Ѵ� .*/

NS_BEGIN(Engine)

class CPrototype_Manager final : public CBase
{
private:
	CPrototype_Manager();
	virtual ~CPrototype_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag, class CBase* pPrototype);
	CBase* Clone_Prototype(PROTOTYPE ePrototype, _uint iLevelIndex, const _wstring& strPrototypeTag, void* pArg);
	void Clear(_uint iLevelIndex);
private:
	map<const _wstring, class CBase*>* m_pPrototypes = { nullptr };
	

	_uint		m_iNumLevels = {};	

private:
	CBase* Find_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag);

public:
	static CPrototype_Manager* Create(_uint iNumLevels);
	virtual void Free() override;
};

NS_END