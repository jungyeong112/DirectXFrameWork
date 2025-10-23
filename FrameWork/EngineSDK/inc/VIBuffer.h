#pragma once

#include "Component.h"

/* VIBuffer = Vertex + Index + Buffer */

NS_BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_Buffers();
	virtual HRESULT Render();

protected:
	LPDIRECT3DVERTEXBUFFER9			m_pVB = { nullptr };
	LPDIRECT3DINDEXBUFFER9			m_pIB = { nullptr };

protected:
	_uint		m_iNumVertices = {};
	_uint		m_iNumIndices = {};
	_uint		m_iVertexStride = {};
	_uint		m_iIndexStride = {};
	_ulong		m_dwFVF = {};
	D3DFORMAT	m_eIndexFormat = {};
	_uint		m_iNumPrimitive = {};
public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

NS_END