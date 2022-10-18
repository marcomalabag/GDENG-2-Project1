#pragma once
#include <iostream>
#include "InputListener.h"
#include <vector>
#include <Windows.h>
#include <unordered_set>

typedef std::vector<InputListener*> List;

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void update();

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	

private:
	static InputSystem* sharedInstance;
	List InputListeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

private:
	InputSystem();
	~InputSystem();


};

