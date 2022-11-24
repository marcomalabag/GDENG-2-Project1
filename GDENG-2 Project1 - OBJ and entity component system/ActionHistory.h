#pragma once
#include "AGameObject.h"
#include "EditorAction.h"
#include <stack>

class EditorAction;
class AGameObject;
class ActionHistory
{
public:
	typedef std::stack<EditorAction*> ActionStack;
	static  ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void recordAction(AGameObject* gameObject);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};

	static ActionHistory* sharedInstance;

	ActionStack actionsPerformed;
	ActionStack actionsCancelled;
};

