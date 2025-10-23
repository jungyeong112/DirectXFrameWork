#include "VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent { pGraphic_Device }
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& Prototype)
	: CComponent{ Prototype }
	, m_pVB { Prototype.m_pVB }
	, m_pIB { Prototype.m_pIB }
	, m_iNumVertices{ Prototype.m_iNumVertices }
	, m_iNumIndices{ Prototype.m_iNumIndices }
	, m_iVertexStride{ Prototype.m_iVertexStride }
	, m_iIndexStride{ Prototype.m_iIndexStride }
	, m_dwFVF{ Prototype.m_dwFVF }
	, m_eIndexFormat{ Prototype.m_eIndexFormat }
	, m_iNumPrimitive { Prototype.m_iNumPrimitive }
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Bind_Buffers()
{
	/* 정점버퍼를 장치에 바인딩하낟. */
	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iVertexStride);

	/* 인덱스버퍼를 장치에 바인딩하낟. */
	m_pGraphic_Device->SetIndices(m_pIB);	

	/* 내 정점이 이렇게 생겼다!!!! */
	m_pGraphic_Device->SetFVF(m_dwFVF);

	return S_OK;
}

HRESULT CVIBuffer::Render()
{


	m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumPrimitive);

	return S_OK;
}


void CVIBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
