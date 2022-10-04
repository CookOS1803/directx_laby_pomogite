#pragma once
#include "NormWin.h"
#include <d3d11.h>
#include <xnamath.h>
#include <vector>
#include "Camera.h"
#include "SimpleVertex.h"
#include "SceneObject.h"

struct ConstantBuffer
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

class Graphics
{
	struct GraphicObject
	{
		SceneObject* obj = nullptr;
		XMMATRIX world;

		GraphicObject(SceneObject* obj, XMMATRIX world)
			: obj(obj), world(world) {}
	};

public:
	Graphics(HWND hWnd, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void SetFullscreenState(bool state);
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void Render();
	[[nodiscard]] ID3D11Buffer* CreateVertexBuffer(const std::vector<SimpleVertex>& newVertices);
	[[nodiscard]] ID3D11Buffer* CreateIndexBuffer(const std::vector<WORD>& newIndices);
	void AddObject(SceneObject* obj);
	
	constexpr Camera& GetCamera() noexcept {return camera;}

	static HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

private:
	void CreateDeviceAndSwapChain(const HWND& hWnd, int width, int height);
	void CreateRenderTargetView();
	[[nodiscard]] DXGI_FORMAT CreateDepthStencilTexture(int width, int height);
	void CreateDepthStencilView(DXGI_FORMAT format);
	void InitializeViewport(int width, int height);
	[[nodiscard]] ID3DBlob* CompileAndCreateVertexShader();
	void DefineAndCreateInputLayout(ID3DBlob* pVSBlob);
	void CompileAndCreatePixelShader();
	void CreateConstantBuffer();
	void InitializeMatrices(int width, int height);

	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
	ID3D11Buffer* pConstantBuffer = nullptr;
	ID3D11Texture2D* pDepthStencil = nullptr;
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;

	XMMATRIX view;
	XMMATRIX projection;

	Camera camera;

	std::vector<GraphicObject> objects;
};

