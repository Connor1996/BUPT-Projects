#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::endl;
using std::string;
using std::vector;


class Grammar
{	
	friend class SyntaxParse;
public:
	Grammar(std::ifstream& is)
	{
		string line;
		size_t row = 0;

		while (getline(is, line))
		{
			row++;
			auto leftAndRight = Split(line, "->"); //根据->将生成规则分为左部和右部
			if (row == 1)	//规定第一行的为起始生成符
				_startSymbol = leftAndRight[0];
			if (leftAndRight[0].find(' ') != string::npos) //在
				throw std::runtime_error("Too much symbols in the left of rule in line " + std::to_string(row));
			if (leftAndRight.size() != 2)
				throw std::runtime_error("Illegal production rule in line " + std::to_string(row));

			_nonterminalSymbols.emplace(leftAndRight[0]);
			auto rights = Split(leftAndRight[1], "|"); // 生成规则的右部分

			vector<vector<string>> statements;
			for (const auto& right : rights)
			{
				statements.emplace_back(Split(right, " "));
			}
			_rules.emplace(std::make_pair(leftAndRight[0], statements));
		}
		EliminateRecursion();
		GetTable();
	}

	void PrintRule(std::ofstream& os)
	{
		os << "Starting Symbol:" << endl;
		os << '\t' << _startSymbol << endl;
		os << "Non Terminal Symbols:" << endl << '\t';
		for (const auto& symbol : _nonterminalSymbols)
			os << symbol << ' ';
		os << endl << "Terminal Symbols:" << endl << '\t';
		for (const auto& symbol : _terminalSymbols)
			os << symbol << ' ';
		os << endl << "Production Rules:" << endl;
		for (const auto& pair : _rules)
		{
			os << '\t' << pair.first << " -> ";
			for (const auto& rule : pair.second)
			{
				for (const auto & symbol : rule)
					os << symbol << ' ';
				os << "| ";
			}
			os << endl;
		}
	}

	void PrintTable(std::ofstream& os)
	{
		os << "LL1 Table: " << endl;
		os << string(84, '-') << endl;
		os << "| " << std::setw(8) << "symbol";
		for (const auto& terminal : _terminalSymbols)
			os << std::setw(8) << terminal;
		os << " |" << endl;
		for (const auto& pair : _table)
		{
			os << "| " << std::setw(8) << pair.first;
			for (const auto& terminal : _terminalSymbols)
			{
				auto pos = pair.second.find(terminal);

				if (pos != pair.second.end())
				{
					string str;
					for (const auto& vec : pos->second)
						for (const auto& s : vec)
							str += s;
					os << std::setw(8) << str;
				}
				else
					os << std::setw(8) << " ";
			}
			os << " |" << endl;
		}
		os << string(84, '-') << endl;
	}

private:
	std::unordered_set<string> _nonterminalSymbols;
	std::unordered_set<string> _terminalSymbols = { string{'$'} };
	string _startSymbol;

	std::unordered_map<string, vector<vector<string>>> _rules;
	std::unordered_map<string, std::unordered_set<string>> _first;
	std::unordered_map<string, std::unordered_set<string>> _follow;


	inline decltype(auto) findFollow(string str)
	{
		return std::move(_follow.find(str)->second);
	}

	inline decltype(auto) isNonterminal(string str)
	{
		if (str == "epsilon")
			return false;

		if (_nonterminalSymbols.find(str) != _nonterminalSymbols.end())
			return true;
		else
		{
			_terminalSymbols.emplace(str);
			return false;
		}
	}

	inline decltype(auto) isTerminal(string str)
	{
		if (str == "epsilon")
			return true;

		if (_nonterminalSymbols.find(str) == _nonterminalSymbols.end())
		{
			_terminalSymbols.emplace(str);
			return true;
		}
		else
			return false;
	}

	decltype(auto) hasNone(std::unordered_set<string> set)
	{
		for (const auto& str : set)
		{
			if (str == string{ "epsilon" })
				return true;
		}
		return false;
	}
	
	decltype(auto) findFirst(string str) 
	{
//		if (_first.find(str) != _first.end())
//			return _first.find(str)->second;

		if (isTerminal(str))
			return std::unordered_set<string>{ str };
		
		decltype(_first.begin()->second) first;

		for (const auto& rule : _rules.find(str)->second) // 某个非终结字符的每个生成式
		{
			if (rule[0] == string{ "epsilon" })
				first.emplace(string{ "epsilon" });
			else if (isTerminal(rule[0])) // 首字符为终结字符
				first.emplace(rule[0]);
			else  // 首字符为非终结字符
			{
				auto mark = false;
				for (const auto& str : rule)
				{
					auto __first = findFirst(str);
					_first.insert(std::make_pair(str, __first));

					if (!hasNone(__first))
					{
						mark = true;
						first.insert(__first.begin(), __first.end());
						break;
					}
					else
					{
						__first.erase(string{ "epsilon" });
						first.insert(__first.begin(), __first.end());
					}
				}
				if (!mark)
					first.insert(string{ "epsilon" });
			}
		}
		
		return first;
	}

	inline decltype(auto) getFollow(string symbol)
	{
		return _follow.find(symbol)->second;
	}

	decltype(auto) getFirst(string symbol)
	{
		if (isTerminal(symbol))
			return std::unordered_set<string>{ symbol };
		else
			return _first.find(symbol)->second;
	}

	void constructFollowSet()
	{
		auto addFollow = [&](string symbol, std::unordered_set<string>& set)
		{
			auto pos = _follow.find(symbol);

			if (pos != _follow.end())
				pos->second.insert(set.begin(), set.end());
			else
				_follow.insert(std::make_pair(symbol, std::move(set)));
		};

		_follow.insert(std::make_pair(_startSymbol, std::unordered_set<string>{ string{ '$' } }));

		for (const auto& nonterminal : _nonterminalSymbols)
		{
			for (const auto& rule : _rules.find(nonterminal)->second)
			{
				for (auto it = rule.begin(); it != rule.end(); it++)
				{
					auto symbol = *it;

					if (isNonterminal(symbol))
					{
						if ((it + 1) != rule.end())
						{
							auto first = getFirst(*(it + 1));
							if (hasNone(first))
							{
								auto follow = getFollow(nonterminal);
								addFollow(symbol, std::move(follow));
							}
							first.erase(std::move(string{ "epsilon" }));
							addFollow(symbol, std::move(first));
						}
						else
						{
							auto follow = getFollow(nonterminal);
							addFollow(symbol, std::move(follow));
						}
					}
				}
			}
		}
	}


	std::unordered_map<string, 
		std::unordered_map<string, vector<string>>> _table;

	void constructTable()
	{
		// 加入sync

		for (const auto& nonterminal : _nonterminalSymbols)
		{
			decltype(_table.begin()->second) row; // 分析预测表中每个非终结符对应的一行

			auto addRule = [&](string symbol, vector<string>& set)
			{
				if (symbol == "epsilon")
					return;

				if (row.find(symbol) != row.end())
					throw std::runtime_error("Conflict in table, it's not LL(1) grammar");
				else
					row.insert(std::make_pair(symbol, set));
			};

			for (auto rule : _rules.find(nonterminal)->second)
			{
				auto first = getFirst(rule[0]);

				for (auto symbol : first)
				{
					if (isTerminal(symbol))
						addRule(symbol, rule);
				}
				if (hasNone(first))
				{
					auto follow = getFollow(nonterminal);
					for (auto symbol : follow)
					{
						addRule(symbol, rule);
					}
				}
			}

			auto follow = getFollow(nonterminal);
			for (const auto& symbol : follow)
			{
				if (row.find(symbol) == row.end())
					addRule(symbol, std::move(vector<string>{ string{ "sync" } }));
			}

			_table.emplace(std::make_pair(nonterminal, std::move(row)));
		}
		

		
	}

	void constructFirstSet()
	{
		for (const auto& nonterminal : _nonterminalSymbols)
		{
			auto first = findFirst(nonterminal);	//当前非终结字符的first集
			auto pos = _first.find(nonterminal);

			if (pos == _first.end())
				_first.insert(std::make_pair(nonterminal, first));
			else
				pos->second.insert(first.begin(), first.end());
		}
	}

	void EliminateRecursion()
	{
		for (const auto& nonterminal : _nonterminalSymbols)
		{
			auto & rules = _rules.find(nonterminal)->second;
			decltype(_rules.begin()->second) newSymbol = { vector<string>{ string{ "epsilon" } } };
			auto mark = false; //是否包含左递归

			for (auto it = rules.begin(); it != rules.end();)
			{
				if ((*it)[0] == nonterminal)
				{
					mark = true;
					it->emplace_back(nonterminal + '\'');
					newSymbol.emplace_back(vector<string>(it->begin() + 1, it->end()));
					it = rules.erase(it);
				}
				else
					it++;
			}
			if (mark)
			{
				for (auto& vec : rules)
				{
					vec.emplace_back(nonterminal + '\'');
				}
				_rules.insert(std::make_pair(nonterminal + '\'', newSymbol));
				_nonterminalSymbols.emplace(nonterminal + '\'');
			}
		}

	}

	void GetTable()
	{
		decltype(_first) __first;
		do {
			__first = _first;
			constructFirstSet();
		} while (__first != _first);	//不断循环直到集合不再增大

		decltype(_follow) __follow;
		do {
			__follow = _follow;
			constructFollowSet();
		} while (__follow != _follow);

		constructTable();
	}


	static vector<string> Split(string str, const string& pattern)
	{
		vector<string> vec;
		size_t pos = 0;

		str += pattern; //在最后加一个分隔符，方便分割
		while ((pos = str.find(pattern, 0)) != string::npos)
		{
			vec.emplace_back(Trim(str.substr(0, pos)));
			pos += pattern.size();
			while (str[pos] == ' ') // 继续向后探索空格，防止以空格为分割符时将连续两个空格作为一个分割部分
				pos++;
			str.erase(0, pos);
		}

		return std::move(vec);
	}

	static string Trim(string& str)
	{
		size_t begin = str.find_first_not_of(' ');
		size_t end = str.find_last_not_of(' ');
		return std::move(str.substr(begin, end - begin + 1));

	}
};



class SyntaxParse
{
public:
	SyntaxParse(std::ifstream& is) 
		: _grammar(is)
	{ }

	void parse(std::ifstream& is, std::ofstream& os)
	{
		_grammar.PrintRule(os);
		_grammar.PrintTable(os);

		string symbol;
		string stackStr = '$'+ _grammar._startSymbol;
		std::stack<string> stack;
		
		stack.push("$");
		stack.push(_grammar._startSymbol);

		os << "Prcess:" << endl;

		vector<string> input;
		string inputStr;
		while (is >> symbol)
		{
			inputStr += symbol;
			input.emplace_back(symbol);
		}

		inputStr += "$";
		input.emplace_back(string{ '$' });

		for(const auto& symbol : input)
		{
			while(1)
			{
				os << std::setiosflags(std::ios::left) << std::setw(25) << stackStr;
				os << std::setiosflags(std::ios::left) << std::setw(25) << inputStr;
				if (symbol == stack.top())
				{
					stackStr = stackStr.substr(0, stackStr.size() - symbol.size());
					inputStr = inputStr.substr(symbol.size(), inputStr.size() - symbol.size());
					stack.pop();
					os << endl;
					break;
				}

				auto row = _grammar._table.find(stack.top())->second;
				auto pos = row.find(symbol);
				if (pos == row.end())
				{
					inputStr = inputStr.substr(symbol.size(), inputStr.size() - symbol.size());
					os << std::setiosflags(std::ios::left) << std::setw(25) << "[ERROR] Skip: " + symbol << endl;
				}
				else if (pos->second.front() == "sync")
				{
					stackStr = stackStr.substr(0, stackStr.size() - stack.top().size());
					os << std::setiosflags(std::ios::left) << std::setw(25) << "[ERROR] Pop: " + stack.top() << endl;
					stack.pop();
					continue;
				}
				else
				{
					auto rule = pos->second;
					os << stack.top() << " -> ";
					for (const auto& str : rule)
						os << str;
					os << endl;
					stackStr = stackStr.substr(0, stackStr.size() - stack.top().size());
					stack.pop();

					if (rule.front() == "epsilon")
						continue;

					for (auto it = rule.rbegin(); it != rule.rend(); it++)
					{
						stack.push(*it);
						stackStr += *it;
					}
					continue;
				}
				break;
			}

		}
			
	}

private:
	Grammar _grammar;
};



int main(int argc, char* argv[])
{
	// 第一个参数为语法生成式文件名
	// 第二个参数为输入文件名
	// 第三个参数为输出结果文件名
	try
	{
		if (argc < 3)
			throw std::runtime_error("Too few arguments");

		std::ifstream grammar(argv[1]);
		std::ifstream input(argv[2]);
		std::ofstream result(argv[3]);

		if (!grammar.is_open())
			throw std::runtime_error(string("Unable to open file: ") + argv[1]);
		if (!input.is_open())
			throw std::runtime_error(string("Unable to open file: ") + argv[2]);
		if (!result.is_open())
			throw std::runtime_error(string("Unable to open file: ") + argv[3]);

		SyntaxParse parse(grammar);
		parse.parse(input, result);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}

