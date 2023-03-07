#ifndef	MPRINT
#define MPRINT

#include <stdarg.h>
#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include <string>

using std::unordered_map;

constexpr auto START = "\033[";
constexpr auto CONNECT = ";";
constexpr auto END = "m";
constexpr auto _END_ = "\033[0m";

class mprint
{
public:
	enum frontColor
	{
		BLACK = 30,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE,
		CYAN,
		WHITE,
	};

	enum backColor
	{
		B_BLACK = 40,
		B_RED,
		B_GREEN,
		B_YELLOW,
		B_BLUE,
		B_PURPLE,
		B_CYAN,
		B_WHITE,
	};

	enum charCtrl
	{
		RESET,
		LIGHT,
		DIM,
		UNDERLINE = 4,
		FLICKER
	};

private:
	mprint()
	{
		m_color[RESET] = "0";
		m_color[LIGHT] = "1";
		m_color[DIM] = "2";
		m_color[UNDERLINE] = "4";
		m_color[FLICKER] = "5";

		m_color[BLACK] = "30";
		m_color[RED] = "31";
		m_color[GREEN] = "32";
		m_color[YELLOW] = "33";
		m_color[BLUE] = "34";
		m_color[PURPLE] = "35";
		m_color[CYAN] = "36";
		m_color[WHITE] = "37";

		m_color[B_BLACK] = "40";
		m_color[B_RED] = "41";
		m_color[B_GREEN] = "42";
		m_color[B_YELLOW] = "43";
		m_color[B_BLUE] = "44";
		m_color[B_PURPLE] = "45";
		m_color[B_CYAN] = "46";
		m_color[B_WHITE] = "47";
	}

	//确保外部无法直接销毁单例对象
	~mprint()
	{
		m_color.clear();
		delete m_instance;
	}

	mprint(const mprint&) = delete;  // 禁止拷贝构造函数

	mprint& operator=(const mprint&) = delete;  // 禁止赋值运算符

	//单线程时成员
	static mprint* m_instance;

public:
	//声明静态成员函数，提供外接获取m_instance实例对象;
	static mprint* Get();

	void output(std::string out, ...)
	{
		va_list args;
		va_start(args, out);

		std::string put;

		size_t size = out.size();
		bool isEnd = false;

		for (size_t i = 0; i < size; i++)
		{
			if (out[i] == '$')
			{
				if (i == 0 || (i > 0 && out[i - 1] != '$'))
					put += START;

				put += m_color[va_arg(args, int)];

				if (i + 1 < size && out[i + 1] == '$')
					put += CONNECT;
				else
					isEnd = true;

			}
			else
			{
				if (isEnd)
				{
					put += END;
					isEnd = false;
				}

				put += out[i];
			}
		}

		put += _END_;

		std::cout << put;
	}


	bool IsSync(bool sync)
	{
		return std::ios::sync_with_stdio(sync);
	}

private:
	std::unordered_map<int, std::string> m_color;
};

#endif // !PRINT

