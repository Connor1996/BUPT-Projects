#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include <vector>
#include <set>
#include <stdexcept>

enum State {NORMAL = 1, COMMENT_LINE, COMMENT_BLOCK, DEFINE};

class WordAnalysis
{
public:
    WordAnalysis(std::ifstream &file)
        :  _file(file), _row(1), _charCount(0), _state(NORMAL)
    { }

    bool Run()
    {
        char ch;
        std::string token = "";

		// �ж��ļ��Ƿ�Ϊ��
        if (_GetChar() == EOF)
        {
            _row = 0;
            return true;
        }
        else
            _file.seekg(0, std::ios::beg);

        while ((ch = _GetChar()) != EOF)
		{
			switch (_state)
			{
			case NORMAL:
                try
                {
                    // ���token���Լ�����¼��һ����ʶ��
                    token.clear();
                    _ReadNormal(ch, token);
                    token.clear();
                }
                catch (const std::exception& e)
                {
                    _errors.emplace_back(e.what());
                }

				break;

			case COMMENT_LINE:
                if (ch == '\n')
                {
                    _comments.emplace_back(token);
                    token.clear();
                    _state = NORMAL;
                    break;
                }
                token += ch;
				break;

			case COMMENT_BLOCK:
                if (ch == '*')
                {
                    if (_GetChar() == '/')
                    {
                        _comments.emplace_back(token);
                        token.clear();
                        _state = NORMAL;
                    }
                    else
                        _Rollback();
                }
                token += ch;
                break;
            case DEFINE:
                if (ch == '\n')
                    _state = NORMAL;
                break;
            default:
                return false;
            }
        }
        return true;
    }


    size_t GetRow() const { return _row; }
    size_t GetWordCount() const { return _table.size(); }
    size_t GetCharCount() const { return _charCount; }
    const std::set<std::string>& GetMarkTable() const { return _markTable; }
    const std::vector<std::pair<std::string, std::string>>& GetTable() const { return _table; }
    const std::vector<std::string>& GetComments() const { return _comments; }
    const std::vector<std::string>& GetErrors() const { return _errors; }

private:
    static const std::set<std::string> RESERVED_WORD;
    static const std::set<std::string> OPERATOR;

    std::ifstream& _file;		// �����ļ����
    size_t _row;		// �ļ�����
	size_t _charCount;
    State _state;

	std::set<std::string> _markTable; //���ű��洢ʶ������ı�ʶ��
    std::vector<std::pair<std::string, std::string>> _table;
	std::vector<std::string> _comments;
    std::vector<std::string> _errors;

    char _GetChar()
    {
        char ch = _file.get();
        if (ch == '\n')
            _row++;
        if (ch != ' ' && ch != '\n' && ch != '\t')
            _charCount++;

        return ch;
    }

    void _Rollback()
    {
        _file.seekg(-1, std::ios::cur);
        char ch = _file.peek();
        if (ch != ' ' && ch != '\n' && ch != '\t')
            _charCount--;
        if (ch == '\n')
            _row--;
    }

    void _ReadNormal(char& ch, std::string& token)
	{
        // Ԥ����ָ��
        if (ch == '#')
            _state = DEFINE;
        // ʶ������
        else if (isdigit(ch) || ch == '-' || ch == '+' || ch == '.')
        {
            int state = (ch == '.') ? 1 : 0;
            bool exit = false;
            token += ch;

            // Ԥ���ж��ǼӼ��Ż�������֮ǰ��������
            if (ch == '-' || ch == '+')
            {
                char ch2 = _GetChar();
                if (isalpha(ch2) && ch2 != 'e' && ch2 != 'E' || ch2 == ' ' || ch2 == '\n')
                {
                    _table.emplace_back(std::make_pair(std::string(1, ch), "-"));
                    return;
                }
                else if (ch2 == ch)
                {
                    _table.emplace_back(std::make_pair(std::string(2, ch), "-"));
                    return;
                }
                else if (ch2 == '=')
                {
                    _table.emplace_back(std::make_pair(std::string(1, ch) + "=", "-"));
                    return;
                }
                else
                    _Rollback();
            }

            // ������������״̬�Զ���
            while (!exit)
            {
                ch = _GetChar();

                switch (state) {
                case 0:
                    if (isdigit(ch))
                        break;
                    else if (ch == '.')
                        state = 2;
                    else if (ch == 'e' || ch == 'E')
                        state = 3;
                    else if (isalpha(ch))
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                 ": expected unqualified-id before numeric constant");
                    else
                        exit = true;
                    break;
                case 1:
                    if (isdigit(ch))
                        state = 2;
                    else if (ch == '.')
                        state = 6;
                    else if (isalpha(ch))
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                 ": expected unqualified-id before numeric constant");
                    else
                        exit = true;
                    break;
                case 2:
                    if (isdigit(ch))
                        break;
                    else if (ch == 'e' || ch == 'E')
                        state = 3;
                    else if (isalpha(ch))
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                 ": expected unqualified-id before numeric constant");
                    else
                        exit = true;
                    break;
                case 3: // e E
                    if (ch == '+' || ch == '-')
                        state = 4;
                    else if (isdigit(ch))
                        state = 5;
                    else
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                                 ": Bad Exponential");
                    break;
                case 4:
                    if (isdigit(ch))
                        state = 5;
                    else
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                                 ": Bad Exponential");
                    break;
                case 5:
                    if (isdigit(ch))
                        break;
                    else if (isalpha(ch))
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                                 ": Bad Exponential");
                    else
                        exit = true;
                    break;
                case 6:
                    if (ch == '.')
                    {
                        state = 7;
                    }
                    else
                        throw std::runtime_error("Row " + std::to_string(_row) +
                                                 ": Syntx error " + token + std::string(1, ch));
                    break;
                case 7:
                    exit = true;
                    break;
                }
                if (exit)
                    _Rollback();
                else
                    token += ch;

            }

            if (state == 7)
                _table.emplace_back(std::make_pair(token, "-"));
            else
                _table.emplace_back(std::make_pair("num", token));

        }
		// ʶ���ʶ��
        else if (isalpha(ch) || ch == '_')
		{
			while (isalpha(ch) || isdigit(ch) || ch == '_')
			{
                token += ch;
                ch = _GetChar();
			}
			// ָ�����һ���ַ�
            _Rollback();
			// ��tokenΪ�ؼ���
			if (RESERVED_WORD.find(token) != RESERVED_WORD.end())
                _table.emplace_back(std::make_pair(token, "-"));
			else
			{
				// insert����pair���ͣ�firstΪ��������ָ��,secondΪ�Ƿ����
				// Ϊ����ɹ�ʱ��firstΪ�Ѿ���set����������ָ��
                _markTable.insert(token);
                _table.emplace_back(std::make_pair("id", token));
			}
		}
        // ʶ���ַ���
        else if (ch == '"')
        {
            while ((ch = _GetChar()) != '"')
            {
                if (ch == '\n')
                    throw std::runtime_error("Row " + std::to_string(_row-1) +
                                             ": missing terminating \" character");
                token += ch;
                if (ch == '\\')
                {
                    // ��ֹ��ʶ��ת�������
                    if (_GetChar() == '"')
                    {
                        token += '"';
                    }
                    else
                        _Rollback();
                }
            }
            _table.emplace_back(std::make_pair("string", token));
        }
        // ʶ���ַ�
        else if (ch == '\'')
        {
            ch = _GetChar();
            if (ch == '\'')
                throw std::runtime_error("Row " + std::to_string(_row) +
                                         ": Too few argument for char const");
            else if (ch == '\\')
            {
                char ch2 =_GetChar();
                token = "\\" + ch2;
            }
            else if (ch == '\n')
            {
                throw std::runtime_error("Row " + std::to_string(_row-1) + ": missing terminating ' character");
            }
            else
                token += ch;

            if (_GetChar() == '\'')
            {
                _table.emplace_back(make_pair("char", token));
            }
            else
            {
                _Rollback();
                throw std::runtime_error("Row " + std::to_string(_row) + ": missing terminating ' character");
            }
        }
		// ʶ���ϵ�����
		else if (ch == '<')
        {
            char ch2 = _GetChar();
            if (ch2 == '=')
            {
                _table.emplace_back(std::make_pair("relop", "LE"));
            }
            else if (ch2 == '<')
            {
                _table.emplace_back(std::make_pair("<<", "-"));
            }
			else
			{
                _table.emplace_back(std::make_pair("relop", "LT"));
                _Rollback();
			}
		}
		else if (ch == '=')
		{
            if (_GetChar() == '=')
            {
                 _table.emplace_back(std::make_pair("relop", "EQ"));
            }
			else
			{
                _table.emplace_back(std::make_pair("assign-op", "-"));
                _Rollback();
			}
		}
		else if (ch == '>')
        {
            char ch2 = _GetChar();
            if (ch2 == '=')
            {
                _table.emplace_back(std::make_pair("relop", "GE"));
            }
            else if (ch2 == '>')
            {
                _table.emplace_back(std::make_pair("<<", "-"));
            }
			else
			{
                _table.emplace_back(std::make_pair("relop", "GT"));
                _Rollback();
			}
		}
		else if (ch == '!')
		{
            if (_GetChar() == '=')
            {
                 _table.emplace_back(std::make_pair("relop", "NE"));
            }
			else
			{
                _Rollback();
                _table.emplace_back(std::make_pair("!", "-"));
			}
		}
		// ʶ��ע�Ϳ�ͷ
		else if (ch == '/')
		{
            char ch2 = _GetChar();
            if (ch2 == '/')
            {
				_state = COMMENT_LINE;
            }
            else if (ch2 == '*')
            {
				_state = COMMENT_BLOCK;
            }
			else
            {
                _Rollback();
                _table.emplace_back(std::make_pair("/", "-"));
			}
		}
		// ʶ�����
        else if (OPERATOR.find(std::string(1, ch)) != OPERATOR.end())
        {
            auto findDouble = [&](char pattern) -> bool
            {
                if (ch == pattern)
                {
                    if (_GetChar() == pattern)
                    {
                        _table.emplace_back(std::make_pair(std::string(2, pattern), "-"));
                        return true;
                    }
                    else
                        _Rollback();
                }
                return false;
            };

            if (!findDouble('&') && !findDouble('|') && !findDouble('+') && !findDouble('-'))
                _table.emplace_back(std::make_pair(std::string(1, ch), "-"));


        }
        else if (ch == ' ' || ch == '\n' || ch == '\t')
        { }
		else
            throw std::runtime_error(
                    "Row " + std::to_string(_row) + ": The character " +
                    std::string(1, ch) + "(" + std::to_string(ch) + ")" + " is illegal");
	}
};


const std::set<std::string> WordAnalysis::RESERVED_WORD = { "auto", "break", "case",
        "char", "const", "continue", "default", "do", "double", "else", "main",
        "enum", "extern", "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };

const std::set<std::string> WordAnalysis::OPERATOR = {
    "+", "-", "*", "/", "^", "|", "&", "(", ")", ";", "{", "}", "[", "]", ",",
    ":", "?", ".", "%", "~"
};


int main()
{
    std::string filename = "";
    std::cout << "Please input filename to be analysed: ";
    std::cin >> filename;

    std::ifstream file(filename, std::ios::in);
    if (file.fail())
        std::cout << "The file dose not exist" << std::endl;
    else
    {
        WordAnalysis analysis(file);
        std::ofstream out("result.txt");

        if (!analysis.Run())
        {
            out << "[FATEL ERROR] Something wrong with the program!" << std::endl;
        }

        out << "Total Lines: " << analysis.GetRow() << std::endl;
        out << "Total Words: " << analysis.GetWordCount() << std::endl;
        out << "Total Chars: " << analysis.GetCharCount() << std::endl;
        out << std::endl;


        auto errors = analysis.GetErrors();
        if (errors.size() != 0)
        {
            out << "Error List:" << std::endl;
            for (const auto& str: errors)
            {
                out << "[Error] " << str << std::endl;
            }
            out << std::endl;
        }

        out << "Symbol List:" << std::endl;
        auto markTable = analysis.GetMarkTable();
        for (const auto& str : markTable)
        {
            out << str << std::endl;
        }
        out << std::endl;

        out << "Token List:" << std::endl;
        auto table = analysis.GetTable();
        for (const auto& pair : table)
        {
            out << "< " << pair.first << " , " << pair.second << " >" << std::endl;
        }
        out << std::endl;

        out << "Comment List: ";
        auto comments = analysis.GetComments();
        out << comments.size() << " in total"  << std::endl;
        for (const auto& comment : comments)
        {
            out << "[Comment] " << comment << std::endl;
        }
        out.close();
    }
    file.close();

    return 0;
}
