#include "RPN.h"

RPN::RPN(Queue<Token*> postFix) : _postfix(postFix) {}

RPN::~RPN()
{
}

vector<long> RPN::operator ()(Map<string, int>& fields, vector<MMap<string, long>>& indices)
{
	vector<long> temp;

	Queue<Token*> postfix = _postfix;

	Queue<Token*>::Iterator i;

	Stack<Token*> buffer;

	while (!postfix.Empty()) {

		if (postfix.Front()->typeOf() == SYMBOL) {
			buffer.Push(postfix.Pop());

		}

		else if (postfix.Front()->typeOf() == LOPERATOR) {
			vector<long> v = vector<long>();
			Symbol* condition = static_cast<Symbol*>(buffer.Pop());
			Symbol* field = static_cast<Symbol*>(buffer.Pop());

			bool isNum = isNumber(condition->string());

			MMap<string, long>::Iterator start;
			MMap<string, long>::Iterator end;

			string oper = static_cast<LogicalOperator*>(postfix.Pop())->value();

			if (oper == "=") {
				if (indices[fields[field->string()]].contains(condition->string())) {
					v = indices[fields[field->string()]][condition->string()];
				}
			}
			else if (oper == "<") {
				end = indices[fields[field->string()]].lower_bound(condition->string());
				start = indices[fields[field->string()]].begin();

				while (start != end) {
					v = getUnion(v, (*start).value_list);
					start++;
				}
			}
			else if (oper == ">"){
				end = indices[fields[field->string()]].end();
				start = indices[fields[field->string()]].upper_bound(condition->string());

				while (start != end) {
					v = getUnion(v, (*start).value_list);
					start++;
				}
			}
			else if (oper == "<=") {
				end = indices[fields[field->string()]].upper_bound(condition->string());
				start = indices[fields[field->string()]].begin();

				while (start != end) {
					v = getUnion(v, (*start).value_list);
					start++;
				}
			}
			else if (oper == ">=") {
				end = indices[fields[field->string()]].end();
				start = indices[fields[field->string()]].lower_bound(condition->string());

				while (start != end) {
					v = getUnion(v, (*start).value_list);
					start++;
				}
			}

			buffer.Push(new RecordNums(v));
			v.clear();
		}
		else if (postfix.Front()->typeOf() == COPERATOR) {
			RecordNums* r1 = static_cast<RecordNums*>(buffer.Pop());
			RecordNums* r2 = static_cast<RecordNums*>(buffer.Pop());

			string oper = static_cast<LogicalOperator*>(postfix.Pop())->value();

			if (oper == "and") {
				buffer.Push(new RecordNums(getIntersection(r1->records(), r2->records())));
			}
			else if (oper == "or") {
				buffer.Push(new RecordNums(getUnion(r1->records(), r2->records())));
			}

			/*delete r1;
			delete r2;*/
		}
	}

	vector<long> ans = static_cast<RecordNums*>(buffer.Pop())->records();

	assert(buffer.Empty());

	return ans;
}

bool isNumber(string num)
{
	for (int i = 0; i < num.size(); i++) {
		if (!isdigit(num[i]) || num[i] != '.')
			return false;
	}
	return true;
}
