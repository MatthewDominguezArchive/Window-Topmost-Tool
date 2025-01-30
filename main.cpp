#include <Windows.h>
#include <iostream> // debug features only

int main() {
	// Loop continues until end key is pressed on user's keyboard.
	while (!GetAsyncKeyState(VK_END)) {

		// Checks whether scroll wheel button is pressed.
		if (GetAsyncKeyState(VK_MBUTTON)) {

			// Debug.
			std::cout << "[+] Pressed" << std::endl;
			
			// Grabs handle to foreground window (returns 0 if failure).
			HWND foreground_window_handle = GetForegroundWindow();

			// Dealing with failure to obtain handle.
			if (!foreground_window_handle) {
				
				// Debug.
				std::cout << "[-] Could not retrieve handle to foreground window!" << std::endl;

				//skips rest of instructions in the loop and restarts the loop.
				continue;
			}

			// Debug.
			std::cout << "[+] Successfully retrieved handle to foreground window: " << std::hex << foreground_window_handle << std::endl;

			// Changes window position of foreground window, saves status to variable.
			bool SWP_return = SetWindowPos(foreground_window_handle, HWND_TOPMOST, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);

			// Deals with invalid status.
			if (!SWP_return) {

				// Debug.
				std::cout << "[-] Failed to reposition window, error code: " << std::hex << GetLastError();

				//skips rest of instructions in the loop and restarts the loop.
				continue;
			}

			// Debug.
			std::cout << "[+] Successfully repositioned window!" << std::endl;

			// Wait's for user to release hotkey (scroll wheel button).
			while (GetAsyncKeyState(VK_MBUTTON)) Sleep(1);
				
			// Debug.
			std::cout << "[+] Released!" << std::endl << std::endl << std::endl;
		}

		// Saves our poor wittle cpu :(
		Sleep(5);
	}

	return EXIT_SUCCESS;
}
