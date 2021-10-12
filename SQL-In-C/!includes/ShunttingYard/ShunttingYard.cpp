#include "ShunttingYard.h"

void popUntilLeft(Stack<LogicalOperator*>& ops, Queue<Token*>& output);
ShuntingYard::ShuntingYard(Queue<Token*> infix) {
	_infix = infix;
	_postfix = postfix();
}
Queue<Token*>& ShuntingYard::postfix() {
	Stack<LogicalOperator*> operatorStack;
	
			//Go until the infix is empty

	while (!_infix.Empty()) {
		
		//Store the front
		Token* temp = _infix.Front();
		
				//Pop the infix could be at the end
		_infix.Pop();
		
				//Number just push 
		if (temp->typeOf() == SYMBOL) {
			
			_postfix.Push(temp);
			
		}
				//Operator then check precedence
		else if (temp->typeOf() == LOPERATOR || temp->typeOf() == COPERATOR) {
			
			LogicalOperator* theOperator = static_cast<LogicalOperator*>(temp);
			
					//theOperator->print();
					//If > precedence or ( push on top 
			if (operatorStack.Empty() || theOperator->precedence() >
				operatorStack.Top()->precedence()) {
				
				operatorStack.Push(theOperator);
				
			}
					//If less then or equal precedence pop then push to stack
			else {
				
				while (!operatorStack.Empty() && theOperator->precedence() <=
					operatorStack.Top()->precedence()) {

					_postfix.Push(operatorStack.Pop());

				}

				operatorStack.Push(static_cast<LogicalOperator*>(temp));
				

			}
		}
				//Left paren just push to stack
		else if (temp->typeOf() == LPAREN) {
			

					//"Pushed left";
			operatorStack.Push(static_cast<LeftParenthesis*>(temp));
		}
				//Right paren just pop until you get to the left paren then discard
		else if (temp->typeOf() == RPAREN) {
			

			popUntilLeft(operatorStack, _postfix);
		}
	}
			//Push all operators stil left in stack
	while (!operatorStack.Empty()) {
		

		LogicalOperator* op = operatorStack.Top();
		

		operatorStack.Pop();
		

		_postfix.Push(op);
		

	}
	

	//printTokens(_postfix);
	return _postfix;
}
void printTokens(Queue<Token*> toPrint) {
	while (!toPrint.Empty()) {
		toPrint.Front()->print(cout);
		" ";
		toPrint.Pop();
	}
}
void popUntilLeft(Stack<LogicalOperator*>& ops, Queue<Token*>& output) {
	bool done = false;
	while (!done) {
		
		if (ops.Top()->value() == "(") {
			
			done = true;
			
			ops.Pop();
			
		}
		else {
			
			LogicalOperator* op = ops.Top();
			
			output.Push(op);
			
			ops.Pop();
			
			//"Pushed ";
		}
	}
}