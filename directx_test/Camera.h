#pragma once
#include "NormWin.h"
#include <DirectXMath.h>

class Camera
{
public:

	Camera();

	void SetPosition(float newX, float newY, float newZ);
	void SetRotation(DirectX::XMVECTOR euler);
	void SetRotation(float aroundX, float aroundY, float aroundZ);
	void Translate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR euler);
	void Rotate(float aroundX, float aroundY, float aroundZ);

	[[nodiscard]] constexpr DirectX::XMVECTOR Position() const noexcept {return position;}
	[[nodiscard]] constexpr DirectX::XMVECTOR LookAt() const noexcept {return lookAt;}
	[[nodiscard]] constexpr DirectX::XMVECTOR UpVector() const noexcept {return upVector;}
	[[nodiscard]] constexpr DirectX::XMVECTOR ForwardVector() const noexcept {return forwardVector;}

private:

	DirectX::XMVECTOR position;
	DirectX::XMVECTOR lookAt;
	DirectX::XMVECTOR upVector;
	DirectX::XMVECTOR forwardVector;
	DirectX::XMVECTOR eulerAngles;
};

