#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <vector>
#include <ranges>
#include <algorithm>
#include "STRING.h"

class Test {
public:
	size_t id;
	STRING name; // 공백없는 영문자로만 구성

	friend std::ostream& operator<<(std::ostream& os, const Test& test) {
		os << test.id << " " << test.name << " ";
		return os;
	}

	// 파일 입출력 지원
	friend std::istream& operator>>(std::istream& is, Test& t) {
		is >> t.id >> t.name;
		return is;
	}

public:
	// id 기준으로 정렬
	bool operator<(const Test& other) const {
		return id < other.id;
	}
};

extern bool 관찰;

int main()
{
	/*[문제 1] Test 객체들을 항상 id 값 기준으로 오름차순으로 정렬된 상태로 관리하려고 한다.
	파일에 기록된 Test 객체를 적당한 컨테이너에 저장한 후 모두 몇 개의 객체를 저장하였는지
		화면에 출력하라. (20)
		(주의)관련 코드를 답지에 적을 필요는 없다.
		(주의)파일에 저장된 모든 객체를 저장하여야 한다.

		답지에 적을 내용. (코드를 적지 말 것)
		- 어떤 컨테이너를 어떻게 사용하였는가 간단하게 설명.
		- Test 객체를 저장하는 데 필요한 핵심 코드는 무엇인가 간단하게 설명.
		- 화면에 출력된 Test 객체의 개수.*/

	std::ifstream in{ "시험.txt"};
	if (not in)
		return 20250612;

	std::multiset<Test> tests;
	Test temp;

	while (in >> temp) {
		tests.insert(temp);
	}

	std::cout << "총 " << tests.size() << "개의 Test 객체가 저장되었습니다.\n";
	// 총 23457개의 Test 객체가 저장되었습니다.
	/*std::multiset<Test> 컨테이너를 사용하였다.
		이 컨테이너는 Test 객체를 id 기준으로 자동 정렬하며, 중복된 id도 저장할 수 있다.

		2. Test 객체를 저장하는 데 필요한 핵심 코드
		텍스트 파일 "시험.txt"를 ifstream으로 읽어들인다.

		operator>>를 통해 한 줄씩 Test 객체를 생성한다.

		생성된 객체를 multiset에 insert하여 저장한다.

		Test 클래스는 id 기준 비교를 위해 operator<를 public으로 구현하였다.

		3. 화면에 출력된 Test 객체의 개수
		multiset.size() 함수로 총 저장된 객체 수를 출력하였다.

		(예시)“총 37개의 Test 객체가 저장되었다.”*/

	// [문제2]
	std::cout << *tests.begin() << std::endl;


	// [문제3]
	관찰 = true;
	Test t = *tests.rbegin();
	관찰 = false;
	std::cout << "복사한 Test 객체의 name: " << t.name << std::endl;
	// [   23459] 복사생성자       자원수:3049       메모리:0x1c3293fc68, 자원메모리:0x15feb4bb5a0

	// 1. STRING 객체(Test::name)의 출력 내용
	/*t.name에 저장된 STRING 객체는, 복사 생성자에 의해 원본 문자열 데이터가 복사되어 출력된다.

		출력 결과는 해당 Test 객체의 name 필드 값과 동일하며, operator<<에 의해 문자열 그대로 표시된다.

		2. 컨테이너에 저장한 방식이 효율적이라고 주장하는 근거
		multiset은 내부적으로 균형 이진 탐색 트리(Red - Black Tree) 구조이므로,
		원하는 위치(끝 요소 등)에서의 접근 및 복사 동작이 logarithmic 시간 복잡도를 가진다.

		Test 객체의 복사가 깊은 복사가 아닌 효율적인 복사 생성자를 활용한다면,
		복사 비용이 크지 않고, 이터레이터를 통한 접근도 빠르다.

		또한, multiset은 항상 정렬 상태를 유지하므로, 반복자 rbegin()이 바로 가장 큰 id 객체를 가리켜 효율적이다.

		따라서, Test 객체를 multiset에 저장하는 방식은 데이터 정렬과 접근의 효율성 모두를 만족한다고 볼 수 있다.*/

	// [문제4]
	std::ifstream fin("비교.txt");
	if (!fin) {
		std::cout << "파일 열기 실패\n";
		return 1;
	}

	std::vector<STRING> vec;
	STRING temp1;

	// 관찰 = true;
	while (fin >> temp1) {
		vec.push_back(temp1);
	}
	관찰 = false;

	std::cout << "총 STRING 개수: " << vec.size() << '\n';
	// 30001개
	// [  135400] 복사생성자       자원수:3125       메모리:0x2756a895ca0, 자원메모리:0x275677c9840

	/*1. vector<STRING>에 저장한 STRING의 개수
		텍스트 모드로 열린 "비교.txt" 파일을 ifstream으로 끝까지 읽으며,

		한 줄씩 또는 공백 단위로 STRING 객체를 생성하여 vector<STRING>에 저장하였다.

		파일 끝까지 읽었으므로 저장된 vector의 크기는 파일에 저장된 STRING 객체 수와 같다.

		따라서, vector.size()가 저장된 STRING 객체의 개수가 된다*/

	// [문제5]

	// 문제 5: 공통 STRING 출력
	std::cout << "== 공통된 STRING 목록 ==\n";
	for (const auto& test : tests) {
		auto it = std::ranges::find(vec, test.name);
		if (it != vec.end()) {
			std::cout << test.name;;
		}
	}

	/*1. 동일한 STRING을 찾기 위해 컨테이너를 어떻게 사용하였는가 ?
		std::multiset<Test> 컨테이너에서 각 Test 객체의 name 필드(STRING)를 순회하며,
		std::vector<STRING>에 저장된 문자열들과 비교하였다.
		비교는 STRING 클래스에 정의된 operator==를 기준으로 수행하였다.

		C++20에서 도입된 범위 기반 STL 알고리즘인 std::ranges::find를 사용하였다.
		이 알고리즘은 컨테이너 전체를 하나의 범위로 인식하여 반복자 없이 간결하게 사용할 수 있으며,
		operator==를 기반으로 vector<STRING> 내부에 Test.name과 동일한 문자열이 존재하는지를 선형 탐색으로 확인하였다.
	*/


	/*
	b
	j
	HappySummerVacation
	X
	j
	*/
}
