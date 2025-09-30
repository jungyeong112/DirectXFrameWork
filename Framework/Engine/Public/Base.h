#pragma once

#include "Engine_Defines.h"

/* ���۷��� ī��Ʈ�� �����ϴ� ����� �������ִ� �θ�Ŭ�����̴�. */
/* ���۷��� ī��Ʈ�� �����ϴ� ��� : AddRef, Release */
/* AddRef : ���۷��� ī��Ʈ�� ������Ű��. */
/* Release : ���۷��� ī��Ʈ�� ����Ų��. or �����Ѵ�. */

NS_BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;
public:
	// �����ϰ� �� ������ ���۷��� ī��Ʈ�� �����Ѵ�. 
	unsigned int AddRef();

	// �����ϱ� ���� ���۷��� ī��Ʈ�� �����Ѵ� .
	unsigned int Release();

private:
	unsigned int		m_iRefCnt = {};
public:	
	virtual void Free();
};

NS_END