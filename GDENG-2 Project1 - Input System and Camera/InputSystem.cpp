#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = NULL;
InputSystem::InputSystem()
{
	
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

InputSystem* InputSystem::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}

void InputSystem::destroy()
{
	if(sharedInstance != NULL)
	{
		delete sharedInstance;
	}
}

void InputSystem::addListener(InputListener* listener)
{
	this->InputListeners.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	int index = -1;
	for(int i = 0; i < this->InputListeners.size(); i++)
	{
		if(this->InputListeners[i] == listener)
		{
			index = i;
			this->InputListeners.erase(this->InputListeners.begin() + index);
			break;
		}
	}

}

void InputSystem::update()
{
	if(::GetKeyboardState(m_keys_state))
	{
		for(unsigned int i = 0; i < 256; i++)
		{
			if(m_keys_state[i] & 0x80)
			{
				this->callOnKeyDown(i);
			}
			else
			{
				this->callOnKeyUp(i);
			}

		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keys_state[i] & 0x80 && i == key) {
			return true;
		}

		else if (i == key)
		{
			return false;
		}
	}
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if(!(m_keys_state[i] & 0x80) && i == key){
			return true;
		}

		else if(i == key)
		{
			return false;
		}
	}
}

void InputSystem::callOnKeyDown(int key)
{
	for(int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onKeyUp(key);
	}
}


InputSystem::~InputSystem()
{
}



