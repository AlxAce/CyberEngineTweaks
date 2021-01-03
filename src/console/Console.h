#pragma once

using TClipToCenter = HWND(RED4ext::CGameEngine::UnkC0* apThis);

struct Image;
struct Console
{
	static void Initialize(Image* apImage);
	static void Shutdown();
	static Console& Get();

	~Console();

	void Toggle();
	bool IsEnabled() const;
	
	void Log(const std::string& acpText);
	void GameLog(const std::string& acpText) { if (!m_disabledGameLog) Log(acpText); }
	
	void Update(float deltaTime);

	LRESULT OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	
	void Hook(Image* apImage);
	
	static BOOL ClipToCenter(RED4ext::CGameEngine::UnkC0* apThis);

private:

	Console();
	
	std::recursive_mutex m_outputLock;
	std::vector<std::string> m_outputLines;
	bool m_outputShouldScroll{ true };
	bool m_outputScroll{ false };
	bool m_inputClear{ true };
	bool m_disabledGameLog{ true };
	
	TClipToCenter* m_realClipToCenter{ nullptr };
	
	bool m_enabled{ false };
	bool m_focusConsoleInput{ false };
};
