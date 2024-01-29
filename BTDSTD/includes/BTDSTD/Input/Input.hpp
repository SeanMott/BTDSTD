#pragma once

//defines a input manager

#include <BTDSTD/Types.hpp>
#include <BTDSTD/String.hpp>
#include <BTDSTD/Input/KeyboardKeyCode.hpp>
#include <BTDSTD/Logger.hpp>

#include <vector>

namespace BTD::Input
{
	//polls input for the OS
	void PollInput();

	//defines a input type
	enum class InputType
	{
		Key = 0, //a keyboard key

		Count
	};

	//defines a input key
	struct InputKey
	{
		InputType type = InputType::Key; //the type of input
		int32 keycode = 0; //the keycode
	};

	//defines the file extension for a key map decl file
#define BTD_INPUT_KEY_MAP_DECL_FILE_EXTENSION ".BTDKM"

	//defines a keymap
	struct KeyMap
	{
		std::string name = ""; //the name of the keymap
		
		//keyboard keys
		Keycode::KeyboardKeyCode keyboardPosKey; //the key that if true, returns 1
		Keycode::KeyboardKeyCode keyboardNegKey; //the key that if true returns -1
	
		//the controller keys
	};

	//saves the keymap to a file

	//loads the keymap from a file

	//input struct
	struct Input
	{
		//the keyboard key states
		bool lastKeyboardKey[1024];
		bool currentKeyboardKey[1024];
	
		//mouse key states

		//the axis

		//control states

		std::vector<KeyMap> keyMaps; //the key maps
		uint32 keyMapCount = 0; //the number of key maps

		//if the desired key is just pressed
		inline bool IsKeyJustPressed(const Keycode::KeyboardKeyCode& keycode)
		{
			return (lastKeyboardKey[(int32)keycode] == false && currentKeyboardKey[(int32)keycode] == true ? true : false);
		}

		//if the desired key is just released
		inline bool IsKeyJustReleased(const Keycode::KeyboardKeyCode& keycode)
		{
			return (lastKeyboardKey[(int32)keycode] == true && currentKeyboardKey[(int32)keycode] == false ? true : false);
		}

		//if the desired key is held
		inline bool IsKeyHeld(const Keycode::KeyboardKeyCode& keycode)
		{
			return (lastKeyboardKey[(int32)keycode] == true && currentKeyboardKey[(int32)keycode] == true ? true : false);
		}
		
		//if the desired key is released this frame and last
		inline bool IsKeyReleased(const Keycode::KeyboardKeyCode& keycode)
		{
			return (lastKeyboardKey[(int32)keycode] == false && currentKeyboardKey[(int32)keycode] == false ? true : false);
		}

		//if the key is either just pressed or held down
		inline bool IsKeyPressed_HeldDown(const Keycode::KeyboardKeyCode& keycode)
		{
			return (IsKeyJustPressed(keycode) || IsKeyHeld(keycode));
		}

		//gets a input key map
		inline KeyMap* GetKeyMap(const char* keyMapName, bool silenceLogging = true)
		{
			//goes through the input maps
			for (uint32 i = 0; i < keyMapCount; ++i)
			{
				if (!strcmp(keyMapName, keyMaps[i].name.c_str()))
					return &keyMaps[i];
			}

			//if none was found
			if (!silenceLogging)
				BTD::Logger::LogWarning("BTD", "Input", "GetKeyMap",
					std::string(std::string("The desired input map \"") + std::string(keyMapName) + "\" does not exist!").c_str());
			return nullptr;
		}

		//creates a key map
		inline KeyMap* CreateMapKeyMap(const char* keyMapName, bool silenceLogging = true)
		{
			//checks if it exists
			KeyMap* map = GetKeyMap(keyMapName);
			
			//if it exists, throw error and return it
			if (map)
			{
				if (!silenceLogging)
					BTD::Logger::LogWarning("BTD", "Input", "CreateMapKeyMap",
						std::string(std::string("The desired input map \"") + std::string(keyMapName) + "\" already exist!").c_str());
				return map;
			}
			
			map = &keyMaps.emplace_back(KeyMap());
			map->name = keyMapName;
			keyMapCount++;
			return map;
		}

		//checks the state of a keyboard input map
		inline int8 IsInputMap_Keyboard_HeldAndPressed(const char* keyMapName, bool silenceLogging = true)
		{
			uint8 state = 0;
			
			if (KeyMap* keyMap = GetKeyMap(keyMapName, silenceLogging))
			{
				if (IsKeyPressed_HeldDown(keyMap->keyboardPosKey))
					state += 1;
				if (IsKeyPressed_HeldDown(keyMap->keyboardNegKey))
					state -= 1;
			}

			return state;
		}
	};
}