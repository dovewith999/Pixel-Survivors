#include "..\Public\VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube & rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Cube::NativeConstruct_Prototype()
{

#pragma region VERTEX_BUFFER
	m_iNumVertices = 8;
	m_iStride = sizeof(VTXCUBETEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 12;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXCUBETEX*		pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	
	pVertices[0].vPosition = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vTexUV = pVertices[0].vPosition;

	pVertices[1].vPosition = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].vTexUV = pVertices[1].vPosition;

	pVertices[2].vPosition = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].vTexUV = pVertices[2].vPosition;

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].vTexUV = pVertices[3].vPosition;

	pVertices[4].vPosition = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vTexUV = pVertices[4].vPosition;

	pVertices[5].vPosition = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vTexUV = pVertices[5].vPosition;

	pVertices[6].vPosition = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].vTexUV = pVertices[6].vPosition;

	pVertices[7].vPosition = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].vTexUV = pVertices[7].vPosition;

	m_pVB->Unlock();

#pragma endregion

#pragma region INDEX_BUFFER
	m_iPrimitiveIndicesSize = sizeof(FACEINDICES16);
	m_eIndexFormat = D3DFMT_INDEX16;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES16*		pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
		
	/* +X */
	pIndices[0]._0 = 1; pIndices[0]._1 = 5; pIndices[0]._2 = 6;
	pIndices[1]._0 = 1; pIndices[1]._1 = 6; pIndices[1]._2 = 2;

	/* -X */
	pIndices[2]._0 = 4; pIndices[2]._1 = 0; pIndices[2]._2 = 3;
	pIndices[3]._0 = 4; pIndices[3]._1 = 3; pIndices[3]._2 = 7;

	/* +Y */
	pIndices[4]._0 = 4; pIndices[4]._1 = 5; pIndices[4]._2 = 1;
	pIndices[5]._0 = 4; pIndices[5]._1 = 1; pIndices[5]._2 = 0;

	/* -Y */
	pIndices[6]._0 = 3; pIndices[6]._1 = 2; pIndices[6]._2 = 6;
	pIndices[7]._0 = 3; pIndices[7]._1 = 6; pIndices[7]._2 = 7;

	/* +Z */
	pIndices[8]._0 = 5; pIndices[8]._1 = 4; pIndices[8]._2 = 7;
	pIndices[9]._0 = 5; pIndices[9]._1 = 7; pIndices[9]._2 = 6;

	/* -Z */
	pIndices[10]._0 = 0; pIndices[10]._1 = 1; pIndices[10]._2 = 2;
	pIndices[11]._0 = 0; pIndices[11]._1 = 2; pIndices[11]._2 = 3;

	m_pIB->Unlock();


#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Cube::NativeConstruct(void * pArg)
{
	return S_OK;
}

CVIBuffer_Cube * CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX(TEXT("Failed to Created : CVIBuffer_Cube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone(void * pArg)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX(TEXT("Failed to Cloned : CVIBuffer_Cube"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();
}
