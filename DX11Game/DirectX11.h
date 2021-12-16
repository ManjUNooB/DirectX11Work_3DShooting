#ifndef __DIRECT_X_11_H_
#define __DIRECT_X_11_H_

#include <d3d11.h>
#include <DirectXMath.h>

//ƒ‰ƒCƒuƒ‰ƒŠ‚ÌƒŠƒ“ƒN
#pragma comment (lib,"d3d11")

class DirectX11
{
public:


private:
	ID3D11Device*			m_pDevice;		
	ID3D11DeviceContext*	m_pContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D*		m_pDepthStencilTexture;
	ID3D11DepthStencilView* m_pDepthStencilView;
	UINT					m_uSyncInterval = 0;
	ID3D11RasterizerState*  m_pRs[MAX_CULLMODE];

};

#endif
