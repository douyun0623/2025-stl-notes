//---------------------------------------------------------------------------
// 2025 STL 화56목78	 6월 17일 화요일								(15주 1일)
// 6월 19일 목요일 15주 2일 - 기말시험, E320에서...
//---------------------------------------------------------------------------
// concepts - 템플릿 함수의 인자는 자료형(아닌 경우도 있다 - non-type template 
// parameter)인데 이 자료형의 문법적 그리고 의미에서도 작성자가 의도한 것인지를
// compile-tyime에 판단하기 위한 C++언어의 기능
//
// ranges와 concepts을 사용하여 STL의 라이브러리를 재작성한 것이
// constrained algorithm이다.
// 이 알고리즘들은 ranges::algorith에 있다.
//---------------------------------------------------------------------------

#include <iostream>
#include <concepts>
#include <vector>
#include <list>
#include <algorithm>
#include <ranges>
#include "save.h"
#include "STRING.h"
using namespace std;

extern bool 관찰;					// 관찰하려면 true로 설정

//--------
int main()
//--------
{
	vector<int> v{ 1,2,3 };
	list<int> c{ 1,2,3 };

	save("메인.cpp");
} 