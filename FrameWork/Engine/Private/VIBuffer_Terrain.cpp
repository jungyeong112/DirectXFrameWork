#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer { pGraphic_Device }
{

}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype)
	: CVIBuffer { Prototype }
{

}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	/* 네모를 구성하기위한 정점들을 할당한다. */
	/* 인덱스를 이요할 것이 때문에 정점은 네개면 충분하다*/
	m_iNumVertices = iNumVerticesX * iNumVerticesZ;
	m_iNumPrimitive = (iNumVerticesX - 1) * (iNumVerticesZ - 1) * 2;
	m_iNumIndices = m_iNumPrimitive * 3;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iIndexStride = 4;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);
	m_eIndexFormat = D3DFMT_INDEX32;

	/* 정점 배열을 생성하였다. */
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iNumVertices * m_iVertexStride, /*D3DUSAGE_DYNAMIC*/0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };		
	
	/* 생성한 정점 배열에 값을 채운다.  */
	m_pVB->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);

	for (size_t i = 0; i < iNumVerticesZ; i++)
	{
		for (size_t j = 0; j < iNumVerticesX; j++)
		{
			_uint	iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = _float3(j, 0.f, i);
			pVertices[iIndex].vTexcoord = _float2(j / (iNumVerticesX - 1.f), i / (iNumVerticesZ - 1.f));
		}
	}

	m_pVB->Unlock();

	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iNumIndices * m_iIndexStride, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	_uint* pIndices = { nullptr };

	m_pIB->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	_uint		iNumIndices = {};

	for (size_t i = 0; i < iNumVerticesZ - 1; i++)
	{
		for (size_t j = 0; j < iNumVerticesX - 1; j++)
		{
			_uint	iIndex = i * iNumVerticesX + j;

			_uint	iIndices[4] = {
				iIndex + iNumVerticesX, 
				iIndex + iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			/* 오른쪽 위 삼각형을 그리기위한 삼각형의 인덱스 */
			pIndices[iNumIndices++] = iIndices[0];
			pIndices[iNumIndices++] = iIndices[1];
			pIndices[iNumIndices++] = iIndices[2];

			/* 왼쪽 아래 삼각형을 그리기위한 삼각형의 인덱스 */
			pIndices[iNumIndices++] = iIndices[0];
			pIndices[iNumIndices++] = iIndices[2];
			pIndices[iNumIndices++] = iIndices[3];
		}
	}

	m_pIB->Unlock();

	return S_OK;
}


HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{

	return S_OK;
}

CVIBuffer_Terrain* CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Terrain::Clone(void* pArg)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))	
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CVIBuffer_Terrain::Free()
{
	__super::Free();


}
