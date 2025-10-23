#include "Renderer.h"
#include "GameObject.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
    : m_pGraphic_Device { pGraphic_Device }
{
    Safe_AddRef(m_pGraphic_Device);


    /*
    m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pGraphic_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);*/

    //m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    //m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    //_float4     vSourColor(지금 내가 당장 그릴려고하는 픽셀의 색), vDestColor(이미 백버퍼에 그려져있던 픽셀의 색);

    //_float4     vResultColor = vSourColor.rgb * vSourColor.a + vDestColor * (1.f - vSourColor.a)





}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroupID, CGameObject* pRenderObject)
{
    if (eGroupID >= RENDERGROUP::END)
        return E_FAIL;

    m_RenderObjects[ENUM_TO_UINT(eGroupID)].push_back(pRenderObject);

    Safe_AddRef(pRenderObject);

    return S_OK;
}

void CRenderer::Draw()
{
    Render_Priority();
    Render_NonBlend();
    Render_Blend();
    Render_UI();  
 
}

void CRenderer::Render_Priority()
{
    
    for (auto& pRenderObject : m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::PRIORITY)])
    {
        if(nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }

    m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::PRIORITY)].clear();        
}


void CRenderer::Render_NonBlend()
{
    for (auto& pRenderObject : m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::NONBLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }

    m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::NONBLEND)].clear();
}

void CRenderer::Render_Blend()
{
    for (auto& pRenderObject : m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::BLEND)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }

    m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::BLEND)].clear();
}

void CRenderer::Render_UI()
{
    for (auto& pRenderObject : m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::UI)])
    {
        if (nullptr != pRenderObject)
            pRenderObject->Render();

        Safe_Release(pRenderObject);
    }

    m_RenderObjects[ENUM_TO_UINT(RENDERGROUP::UI)].clear();
}

CRenderer* CRenderer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    return new CRenderer(pGraphic_Device);
}

void CRenderer::Free()
{
    __super::Free();

    for (size_t i = 0; i < ENUM_TO_UINT(RENDERGROUP::END); i++)
    {
        for (auto& pRenderObject : m_RenderObjects[i])
            Safe_Release(pRenderObject);
        m_RenderObjects[i].clear();
    }

    Safe_Release(m_pGraphic_Device);
}
