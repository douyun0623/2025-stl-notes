#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include "STRING.h"

extern bool 관찰;

int main()
{
	

	/*[문제 1] 파일에 기록된 STRING 객체를 std::vector<STRING> 컨테이너에 저장한 후
		모두 몇 개의 객체가 컨테이너에 저장되었는지 화면에 출력하라.*/

	std::ifstream in{ "시험.txt" };
	if (not in)
		return 20250612;

	std::vector<STRING> v;
	v.reserve(12355);
	STRING temp;

	while (in >> temp) {
		v.emplace_back(std::move(temp));
	}

	std::cout << v.size() << std::endl;
	// 12355


	// [문제 3]
	/*한 STRING 객체의 id 값.
		- 컨테이너에 저장한 방식이 효율적이라고 주장하는 내용*/

	// 48778
	// 이 코드는 std::move(temp)를 통해 임시 객체를 벡터에 이동하여 저장하므로,
	// 복사 생성자의 호출 없이 STRING 객체를 효율적으로 추가할 수 있다.
	// 이동은 복사보다 자원 복제 비용이 적기 때문에, 이 방식은 성능 면에서 효율적이다.


	// [문제 4] 컨테이너에 저장한 STRING 객체 중에서 중복된 객체를 찾아라.

	// 정렬
	std::ranges::sort(v);

	int duplicate_count = 0;
	auto it = v.begin();

	while (it != v.end()) {
		auto [first, last] = std::ranges::equal_range(it, v.end(), *it);
		int count = std::distance(first, last) - 1;
		if (count > 1) duplicate_count += count;
		it = last; // 다음 탐색 시작점
	}

	std::cout << "중복된 STRING 개수: " << duplicate_count << "\n";
	// 중복된 STRING 개수: 10

	// [문제 5] 컨테이너에 저장한 STRING 객체들을 size() 값 기준 오름차순으로 정렬하였을 때
	// 앞에서부터 100번째인 객체를 찾아라.

	std::ranges::sort(v, [](const STRING& a, const STRING& b) {
		return a.size() < b.size();
	});

	std::cout << v[99].size();
	// 16

	관찰 = true;
}
