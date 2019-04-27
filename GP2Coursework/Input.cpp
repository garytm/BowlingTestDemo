#include "Input.hpp"

	void Input::EventHandler(vector<SDL_Event> events)
	{
		previousKeys = currentKeys;
		previousBut = currentBut;

		for (auto e : events)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				currentKeys.push_back(e.key.keysym.sym);
				break;

			case SDL_KEYUP:
				currentKeys.remove(e.key.keysym.sym);
				break;

			case SDL_MOUSEBUTTONDOWN:
				currentBut.push_back(e.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				currentBut.remove(e.button.button);
				break;

			case SDL_MOUSEMOTION:
				previousMousePos = mousePos;
				mousePos = { e.motion.x, e.motion.y };
				break;
			}
		}
	}

	bool Input::isDown(SDL_Keycode key) const
	{
		for (auto it = currentKeys.rbegin(); it != currentKeys.rend(); ++it)
		{
			if ((*it) == key)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::isButDown(Uint8 button) const
	{
		for (auto it = currentBut.rbegin(); it != currentBut.rend(); ++it)
		{
			if ((*it) == button)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::wasDown(SDL_Keycode key) const
	{
		for (auto it = previousKeys.rbegin(); it != previousKeys.rend(); ++it)
		{
			if ((*it) == key)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::wasButDown(Uint8 button) const
	{
		for (auto it = previousBut.rbegin(); it != previousBut.rend(); ++it)
		{
			if ((*it) == button)
			{
				return true;
			}
		}
		return false;
	}
