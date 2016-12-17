#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>

#define ACC -10

class SemanticParse
{
public:
	using Item = struct Item_t
	{
		double value;

		enum class Type{
			INT, REAL, TYPE_ERROR
		} type;

		Item_t operator+ (Item_t &rhs)
		{
			Item temp;

			temp.value = this->value + rhs.value;
			if (this->type == Item::Type::REAL ||
				rhs.type == Item::Type::REAL)
				temp.type = Item::Type::REAL;
			else if (this->type == rhs.type)
				temp.type = rhs.type;
			else
				temp.type = Item::Type::TYPE_ERROR;

			return std::move(temp);
		}

		Item_t operator- (Item_t &rhs)
		{
			Item temp;

			temp.value = this->value - rhs.value;
			if (this->type == Item::Type::REAL ||
				rhs.type == Item::Type::REAL)
				temp.type = Item::Type::REAL;
			else if (this->type == rhs.type)
				temp.type = rhs.type;
			else
				temp.type = Item::Type::TYPE_ERROR;

			return std::move(temp);
		}

		Item_t operator* (Item_t &rhs)
		{
			Item temp;

			temp.value = this->value * rhs.value;
			if (this->type == Item::Type::REAL ||
				rhs.type == Item::Type::REAL)
				temp.type = Item::Type::REAL;
			else if (this->type == rhs.type)
				temp.type = rhs.type;
			else
				temp.type = Item::Type::TYPE_ERROR;

			return std::move(temp);
		}

		Item_t operator/ (Item_t &rhs)
		{
			Item temp;

			temp.value = this->value / rhs.value;
			if (this->type == Item::Type::REAL ||
				rhs.type == Item::Type::REAL)
				temp.type = Item::Type::REAL;
			else if (this->type == rhs.type)
				temp.type = rhs.type;
			else
				temp.type = Item::Type::TYPE_ERROR;

			return std::move(temp);
		}
	};

	SemanticParse()
	{ 
		_state.push(0);
	}

	void parse(std::ifstream& is)
	{
		auto isTerminal = [this](char ch)
		{
			return _terminalSymbol.find(ch) != _terminalSymbol.end();
		};

		std::string input;
		// 获得输入字符串
		getline(is, input);
		std::cout << "需要处理的字符串为： " << input << std::endl;
		input.push_back('$');

		std::cout << "分析过程产生式：" << std::endl;
		int num = 0;
		bool isConstructNum = false;
		bool accepted = false;

		for (int i = 0; i < input.length(); i++)
		{
			char ch = input[i];

			if (ch == ' ')
			{
				if (!isConstructNum)
					continue;
			}
			else if (isTerminal(ch))
			{
				if (isConstructNum)
				{
					i--;
				}
			}
			else if ('0' <= ch && ch <= '9')
			{
				isConstructNum = true;
				num = num * 10 + ch - '0';
				continue;
			}

			while (true)
			{
				auto getIndex = [this](char ch)
				{
					return _symbolMap.find(ch)->second;
				};

				auto state = _state.top();
				int action;

				if (isConstructNum)
					action = _action[state][getIndex('n')];
				else 
					action = _action[state][getIndex(ch)];
				
				if (action == ACC)
				{
					std::cout << "\n表达式的值为: " << _items.top().value << std::endl;
					std::cout << "表达式的类型为: ";
					if (_items.top().type == Item::Type::INT)
						std::cout << "integer" << std::endl;
					else if (_items.top().type == Item::Type::REAL)
						std::cout << "real" << std::endl;
					else
						std::cout << "type_error" << std::endl;
					
					accepted = true;
					break;
				}
				// 移进
				if (action > 0)
				{
					_state.push(action);
					if (isConstructNum)
					{
						isConstructNum = false;
						_items.emplace(Item{ (double)num, Item::Type::INT });
						num = 0;
					}
	
					break;
				}
				// 规约
				else
				{
					auto symbol = translate(-action);
					// 获得最新要转移的状态
					auto newState = _goto[_state.top()][getIndex(symbol)];
					_state.emplace(std::move(newState));
				}
			}
			if (accepted)
				break;
		}
	}
	
	char translate(int state)
	{
		_state.pop();
		char symbol; 

		auto getTwoOperand = [this]()
		{
			auto op2 = _items.top();
			_items.pop(), _state.pop();
			auto op1 = _items.top();
			_items.pop(), _state.pop();

			return std::move(std::make_pair(op1, op2));
		};

		switch (state)
		{
		case 1:
		{
			std::cout << "E → E + T";
			symbol = 'E';

			auto operands = getTwoOperand();
			_items.emplace(operands.first + operands.second);
			break;
		}
		case 2:
		{
			std::cout << "E → E - T";
			symbol = 'E';

			auto operands = getTwoOperand();
			_items.emplace(operands.first - operands.second);
			break;
		}
		case 3:
		{
			std::cout << "E → T\t";
			symbol = 'E';
			break;
		}
		case 4:
		{
			std::cout << "T → T * F";
			symbol = 'T';

			auto operands = getTwoOperand();
			_items.emplace(operands.first * operands.second);
			break;
		}
		case 5:
		{
			std::cout << "T → T / F";
			symbol = 'T';

			auto operands = getTwoOperand();
			_items.emplace(operands.first / operands.second);
			break;
		}
		case 6:
		{
			std::cout << "T → F\t";
			symbol = 'T';
			break;
		}
		case 7:
		{
			std::cout << "F → num.num";
			symbol = 'F';

			auto operands = getTwoOperand();
			auto op1 = operands.first.value;
			auto op2 = operands.second.value;
			while (op2 >= 1)
				op2 /= 10;
			

			_items.emplace(Item{ op1 + op2, Item::Type::REAL });
			break;
		}
		case 8:
		{
			std::cout << "F → ( E )";
			_state.pop(), _state.pop();
			symbol = 'F';
			break;
		}
		case 9:
		{
			std::cout << "F → num";
			symbol = 'F';
			break;
		}
		default:
			throw std::runtime_error("表达式格式错误");

		}
		std::cout << "\t\tvalue: " << _items.top().value << "\ttype: ";
		if (_items.top().type == Item::Type::INT)
			std::cout << "integer" << std::endl;
		else if (_items.top().type == Item::Type::REAL)
			std::cout << "real" << std::endl;
		else
			throw std::runtime_error("type error");

		return symbol;
	}
protected:
	std::stack<int> _state;
	std::stack<Item> _items;

	// 终结符
	const std::unordered_set<char> _terminalSymbol = {
		'+', '-', '*', '/', '(', ')', '.', '$'
	};

	// 非终结符
	const std::unordered_set<char> _nonterminalSymbol = {
		'E', 'T', 'F'
	};

	// 状态转移表，0表示无
	// 第一列为E，第二列为T， 第三列为F
	const std::vector<std::vector<int>> _goto = {
		{1, 2, 3},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{11, 2, 3},
		{0, 12, 3},
		{0, 13, 3},
		{0, 0, 14},
		{0, 0, 15},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

	const std::unordered_map<char, int> _symbolMap = {
		{'+', 0},
		{'-', 1},
		{'*', 2},
		{'/', 3},
		{'(', 4},
		{')', 5},
		{'.', 6},
		{'n', 7},
		{'$', 8},
		{'E', 0},
		{'T', 1},
		{'F', 2}
	};
	// 动作表，0表示无，ACC表示接受
	// 正数为移进，负数为规约
	// 列从左到右分别代表：+、-、*、/、(、）、.、num
	const std::vector<std::vector<int>> _action = {
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{6, 7, 0, 0, 0, 0, 0, 0, ACC}, 
		{-3, -3, 8, 9, 0, -3, 0, 0, -3}, 
		{-6, -6, -6, -6, 0, -6, 0, 0, -6}, 
		{-9, -9, -9, -9, 0, -9, 10, 0, -9}, 
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{0, 0, 0, 0, 5, 0, 0, 4, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 16, 0}, 
		{6, 7, 0, 0, 0, 17, 0, 0, 0}, 
		{-1, -1, 8, 9, 0, -1, 0, 0, -1}, 
		{-2, -2, 8, 9, 0, -2, 0, 0, -2}, 
		{-4, -4, -4, -4, 0, -4, 0, 0, -4}, 
		{-5, -5, -5, -5, 0, -5, 0, 0, -5}, 
		{-7, -7, -7, -7, 0, -7, 0, 0, -7}, 
		{-8, -8, -8, -8, 0, -8, 0, 0, -8}
	};
};


int main(int argc, char* argv[])
{
	
	// 第二个参数为输入文件名
	// 第三个参数为输出结果文件名
	try
	{
		if (argc < 1)
			throw std::runtime_error("Too few arguments");

		std::ifstream input(argv[1]);

		if (!input.is_open())
			throw std::runtime_error(std::string("Unable to open file: ") + argv[1]);

		SemanticParse parser;
		parser.parse(input);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}
	system("pause");
	return 0;
}