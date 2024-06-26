#include"stateMachine.hpp"

namespace Sonar {
	void stateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplceing;

		this->_newState = std::move(newState);

	}

	void stateMachine::RemoveState() {
		this->_isRemoving = true;
		  
	}

	void stateMachine::ProcessStateChanges() {
		if (this->_isRemoving && !this->_states.empty()) {
			this->_states.pop();
			

			if (!this->_states.empty()) {
				this->_states.top()->Resume();
			}
			this->_isRemoving() = false;
		}

		if (this->_isAdding) {
			if (this->_states.empty()) {
				if (this->_isReplacing) {
					this->_states.pop();
				}
				else {
					this->_states.top()->Pause();
				}
			}
			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();
			this->_isAdding = false;
		}
	}
	StateRef& stateMachine::GetActiveState() {
		return this->_states.top();
	}
}