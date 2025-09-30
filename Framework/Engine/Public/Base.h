#pragma once

#include "Engine_Defines.h"

/* 레퍼런스 카운트를 관리하는 기능을 제공해주는 부모클래스이다. */
/* 레퍼런스 카운트를 관리하는 기능 : AddRef, Release */
/* AddRef : 레퍼런스 카운트를 증가시키낟. */
/* Release : 레퍼런스 카운트를 감소킨디ㅏ. or 삭제한다. */

NS_BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;
public:
	// 증가하고 난 이후의 레퍼런스 카운트를 리턴한다. 
	unsigned int AddRef();

	// 감소하기 전의 레퍼런스 카운트를 리턴한다 .
	unsigned int Release();

private:
	unsigned int		m_iRefCnt = {};
public:	
	virtual void Free();
};

NS_END