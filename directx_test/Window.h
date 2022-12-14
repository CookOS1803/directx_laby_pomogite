#pragma once
#include "NormWin.h"
#include <memory>
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Window
{
private:
	class WindowClass
	{
	public:
		static const wchar_t* Name() noexcept;
		static HINSTANCE HInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const wchar_t* wndClassName = L"Nu Window";
		HINSTANCE hInstance;

		static WindowClass wndClassInstance;
	};

public:
	Window(int width, int height, const wchar_t* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Graphics* Gfx() { return pGfx.get(); }

	Keyboard kbd;
	Mouse mouse;

	void EnableCursor() noexcept;
	void DisableCursor() noexcept;
	constexpr bool CursorEnabled() const noexcept { return cursorEnabled; }
	void SetTitle(std::wstring_view title);

	void ConfineCursor() noexcept;
	void FreeCursor() noexcept;
	void ShowCursor() noexcept;
	void HideCursor() noexcept;

private:


	static LRESULT CALLBACK HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width, height;
	HWND currHwnd;
	std::unique_ptr<Graphics> pGfx;
	std::vector<BYTE> rawBuffer;
	bool cursorEnabled = true;
};
